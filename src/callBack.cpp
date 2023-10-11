#include "callBack.h"

#include "bmp.h"
#include "fontUtil.h"
#include "touch.h"

/* 全局变量 */
double sumPrice = 0;
Bmp *pic = nullptr;  // 图片
Font *f30 = nullptr; // 30px字体
Touch *ts = nullptr; // 触摸
Point *p = nullptr;  // 坐标

sem_t *menuFrameSem = nullptr; // 菜单窗口信号量
sem_t *foodFrameSem = nullptr; // 食物窗口信号量
sem_t *shopFrameSem = nullptr; // 购物车窗口信号量

MenuFrame *MFrame = nullptr;  // 菜单窗口
FoodFrame *FFrameA = nullptr; // 食物窗口A
FoodFrame *FFrameB = nullptr; // 食物窗口B
FoodFrame *FFrameC = nullptr; // 食物窗口C
ShopFrame *SFrame = nullptr;  // 购物车窗口

foodSet_t *FSet = nullptr;               // 食物集合
std::vector<Food *> *shopCart = nullptr; // 记录已下单的食物

extern std::string *tableNo; // 桌号

bool isActivity = true;

void initData()
{
    pic = new Bmp;
    f30 = new Font(30);
    ts = new Touch;
    p = new Point;

    menuFrameSem = new sem_t();
    foodFrameSem = new sem_t();
    shopFrameSem = new sem_t();

    sem_init(menuFrameSem, 0, 0);
    sem_init(foodFrameSem, 0, 0);
    sem_init(shopFrameSem, 0, 0);

    MFrame = new MenuFrame();
    FFrameA = new FoodFrame('a', 3);
    FFrameB = new FoodFrame('b', 2);
    FFrameC = new FoodFrame('c', 1);
    SFrame = new ShopFrame();

    FSet = new foodSet_t();

    // A类
    FSet->a_1_1 = new Food("北京烤鸭", 99.9);
    FSet->a_1_2 = new Food("八宝鸭", 89.9);
    FSet->a_1_3 = new Food("清蒸排骨", 69.9);
    FSet->a_1_4 = new Food("清蒸鲥鱼", 79.9);

    FSet->a_2_1 = new Food("麻婆豆腐", 45.9);
    FSet->a_2_2 = new Food("腊味合蒸", 79.9);
    FSet->a_2_3 = new Food("宫保鸡丁", 58.8);
    FSet->a_2_4 = new Food("九转大肠", 69.0);

    FSet->a_3_1 = new Food("火锅", 128.0);
    FSet->a_3_2 = new Food("佛跳墙", 188.8);
    FSet->a_3_3 = new Food("葱油凤尾虾", 128.0);
    FSet->a_3_4 = new Food("燕窝", 188.8);

    // B类
    FSet->b_1_1 = new Food("糯米鸡", 13.9);
    FSet->b_1_2 = new Food("干蒸", 12.0);
    FSet->b_1_3 = new Food("虾饺皇", 20.0);
    FSet->b_1_4 = new Food("叉烧包", 23.9);

    FSet->b_2_1 = new Food("蛋挞", 9.9);
    FSet->b_2_2 = new Food("萝卜糕", 16.0);
    FSet->b_2_3 = new Food("流沙包", 15.0);
    FSet->b_2_4 = new Food("凤爪", 29.9);

    // C类
    FSet->c_1_1 = new Food("微醺", 6.9);
    FSet->c_1_2 = new Food("可乐", 5.9);
    FSet->c_1_3 = new Food("天地壹号", 4.9);
    FSet->c_1_4 = new Food("美年达", 4.9);

    shopCart = new std::vector<Food *>();
}

void startThread()
{
    MFrame->start();
    FFrameA->setThreadStatus(true);
    FFrameA->start();
    SFrame->start();
}

void stopThread()
{
    if (FFrameA->ThreadStatus())
    {
        FFrameA->setThreadStatus(false);
        FFrameA->stop();
    }
    if (FFrameB->ThreadStatus())
    {
        FFrameB->setThreadStatus(false);
        FFrameB->stop();
    }
    if (FFrameC->ThreadStatus())
    {
        FFrameC->setThreadStatus(false);
        FFrameC->stop();
    }

    MFrame->stop();
}

void printMain()
{
    pic->setBmp("res/ui/main.bmp");
    pic->display();

    char *info = new char[24 + tableNo->length()]();
    sprintf(info, "桌号:%s 请开始点餐", tableNo->data());

    f30->show(std::string(info), 428, 30, 104, 9);
    delete[] info;
}

void printFrameToScreen(FoodFrame &ra)
{
    switch (ra.Tag())
    {
    case 'a':
        frameA(ra.Page());
        break;

    case 'b':
        frameB(ra.Page());
        break;

    case 'c':
        frameC(ra.Page());
        break;

    default:
        break;
    }
}

void flushShop()
{
    if (shopCart->size() == 0)
        return;

    int now = (SFrame->Page() - 1) * 4;
    int no = shopCart->size() - now;

    pic->setBmp("res/ui/fontBg.bmp");
    char *buf = new char[14]();

    // 1
    pic->display(547, 62);
    sprintf(buf, "合计: %d", shopCart->at(now + 0)->Count());
    f30->show(shopCart->at(now + 0)->Name(), 240, 30, 547, 70);
    f30->show(std::string(buf), 240, 30, 547, 104);

    // 2
    if (no >= 2)
    {
        pic->display(547, 154);
        memset(buf, 0, 14);
        sprintf(buf, "合计: %d", shopCart->at(now + 1)->Count());
        f30->show(shopCart->at(now + 1)->Name(), 240, 30, 547, 162);
        f30->show(std::string(buf), 240, 30, 547, 196);
    }

    // 3
    if (no >= 3)
    {
        pic->display(547, 246);
        memset(buf, 0, 14);
        sprintf(buf, "合计: %d", shopCart->at(now + 2)->Count());
        f30->show(shopCart->at(now + 2)->Name(), 240, 30, 547, 254);
        f30->show(std::string(buf), 240, 30, 547, 288);
    }

    // 4
    if (no >= 4)
    {
        pic->display(547, 337);
        memset(buf, 0, 14);
        sprintf(buf, "合计: %d", shopCart->at(now + 3)->Count());
        f30->show(shopCart->at(now + 3)->Name(), 240, 30, 547, 346);
        f30->show(std::string(buf), 240, 30, 547, 380);
    }

    // 合计
    sumPrice = 0;
    for (auto &refVal : *shopCart)
        sumPrice += (refVal->Count() * refVal->Price());

    memset(buf, 0, 14);
    sprintf(buf, "合计:%.1lf", sumPrice);
    f30->show(std::string(buf), 170, 30, 540, 440);

    delete[] buf;
}

void eachShop()
{
    bool isFlush = false;

    for (auto it = shopCart->begin(); it != shopCart->end(); it++)
        if ((*it)->Count() == 0)
        {
            shopCart->erase(it);
            isFlush = true;
            break;
        }

    if (isFlush)
    {
        // 清空购物车页面
        pic->setBmp("res/ui/bgClear.bmp");
        pic->display(543, 52);
    }

    SFrame->setPageMax(shopCart->size() / 4 + (shopCart->size() % 4 == 0 ? 0 : 1));
    SFrame->flushPage();
}

void MenuFrameTask(MenuFrame &ra)
{
    while (1)
    {
        // 等待触摸
        sem_wait(menuFrameSem);

        if (436 <= p->Y() && p->Y() <= 476)
        {
            // A类
            if (4 <= p->X() && p->X() <= 154)
            {
                // std::cout << "A" << std::endl;
                if (!FFrameA->ThreadStatus())
                {
                    FFrameA->setThreadStatus(true);
                    FFrameA->start();
                }
                if (FFrameB->ThreadStatus())
                {
                    FFrameB->setThreadStatus(false);
                    FFrameB->stop();
                }
                if (FFrameC->ThreadStatus())
                {
                    FFrameC->setThreadStatus(false);
                    FFrameC->stop();
                }
                continue;
            }

            // B类
            if (195 <= p->X() && p->X() <= 345)
            {
                // std::cout << "B" << std::endl;
                if (FFrameA->ThreadStatus())
                {
                    FFrameA->setThreadStatus(false);
                    FFrameA->stop();
                }
                if (!FFrameB->ThreadStatus())
                {
                    FFrameB->setThreadStatus(true);
                    FFrameB->start();
                }
                if (FFrameC->ThreadStatus())
                {
                    FFrameC->setThreadStatus(false);
                    FFrameC->stop();
                }
                continue;
            }

            // C类
            if (386 <= p->X() && p->X() <= 536)
            {
                // std::cout << "C" << std::endl;
                if (FFrameA->ThreadStatus())
                {
                    FFrameA->setThreadStatus(false);
                    FFrameA->stop();
                }
                if (FFrameB->ThreadStatus())
                {
                    FFrameB->setThreadStatus(false);
                    FFrameB->stop();
                }
                if (!FFrameC->ThreadStatus())
                {
                    FFrameC->setThreadStatus(true);
                    FFrameC->start();
                }
                continue;
            }
        }
    }
}

void FoodFrameTask(FoodFrame &ra)
{
    printFrameToScreen(ra);

    while (1)
    {
        // 等待触摸
        sem_wait(foodFrameSem);

        // 点击事件
        if (8 <= p->X() && p->X() <= 48) // 左
        {
            // 1 +
            if (52 <= p->Y() && p->Y() <= 121)
            {
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_1", ra.Tag(), ra.Page());

                addJudgeFrame(bufTag);
                // std::cout << "1+" << std::endl;
                delete[] bufTag;
                continue;
            }

            // 1 -
            if (128 <= p->Y() && p->Y() <= 197)
            {

                // std::cout << "1-" << std::endl;
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_1", ra.Tag(), ra.Page());
                subJudgeFrame(bufTag);
                delete[] bufTag;
                continue;
            }

            // 上一页
            if (205 <= p->Y() && p->Y() <= 274)
            {
                ra.subPage();
                printFrameToScreen(ra);
                continue;
            }

            // 2 +
            if (281 <= p->Y() && p->Y() <= 350)
            {
                // std::cout << "2+" << std::endl;
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_2", ra.Tag(), ra.Page());
                addJudgeFrame(bufTag);
                delete[] bufTag;
                continue;
            }

            // 2 -
            if (357 <= p->Y() && p->Y() <= 426)
            {
                // std::cout << "2-" << std::endl;
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_2", ra.Tag(), ra.Page());
                subJudgeFrame(bufTag);
                delete[] bufTag;
                continue;
            }
        }

        if (482 <= p->X() && p->X() <= 531) // 右
        {
            // 3 +
            if (52 <= p->Y() && p->Y() <= 121)
            {
                // std::cout << "3+" << std::endl;
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_3", ra.Tag(), ra.Page());
                addJudgeFrame(bufTag);
                delete[] bufTag;
                continue;
            }

            // 3 -
            if (128 <= p->Y() && p->Y() <= 197)
            {
                // std::cout << "3-" << std::endl;
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_3", ra.Tag(), ra.Page());
                subJudgeFrame(bufTag);
                delete[] bufTag;
                continue;
            }

            // 下一页
            if (205 <= p->Y() && p->Y() <= 274)
            {
                ra.addPage();
                printFrameToScreen(ra);
                continue;
            }

            // 4 +
            if (281 <= p->Y() && p->Y() <= 350)
            {
                // std::cout << "4+" << std::endl;
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_4", ra.Tag(), ra.Page());
                addJudgeFrame(bufTag);
                delete[] bufTag;
                continue;
            }

            // 4 -
            if (357 <= p->Y() && p->Y() <= 426)
            {
                // std::cout << "4-" << std::endl;
                char *bufTag = new char[7]();
                sprintf(bufTag, "%c_%d_4", ra.Tag(), ra.Page());
                subJudgeFrame(bufTag);
                delete[] bufTag;
                continue;
            }
        }
    }
}

void ShopFrameTask(ShopFrame &ra)
{
    while (1)
    {
        // 等待触摸
        sem_wait(shopFrameSem);

        if (4 <= p->Y() && p->Y() <= 44)
        {
            // 上一页
            if (540 <= p->X() && p->X() <= 620)
            {
                // std::cout << "上一页" << std::endl;
                ra.setPageMax(shopCart->size() / 4 + (shopCart->size() % 4 == 0 ? 0 : 1));
                if (ra.PageMax() <= 1)
                    continue;

                ra.subPage();

                // 清空购物车页面
                pic->setBmp("res/ui/bgClear.bmp");
                pic->display(543, 52);

                flushShop();
                continue;
            }

            // 下一页
            if (716 <= p->X() && p->X() <= 796)
            {
                // std::cout << "下一页" << std::endl;
                ra.setPageMax(shopCart->size() / 4 + (shopCart->size() % 4 == 0 ? 0 : 1));
                if (ra.PageMax() <= 1)
                    continue;

                ra.addPage();

                // 清空购物车页面
                pic->setBmp("res/ui/bgClear.bmp");
                pic->display(543, 52);

                flushShop();
                continue;
            }
        }

        if (isActivity)
            if (716 <= p->X() && p->X() <= 796 && 436 <= p->Y() && p->Y() <= 476) // 结算
            {
                std::cout << "结算" << std::endl;
                pay();
            }
    }
}

void addJudgeFrame(char *tag)
{
    int cmd = -1;
    if (strstr(tag, "a"))
        cmd = 1;
    if (strstr(tag, "b"))
        cmd = 2;
    if (strstr(tag, "c"))
        cmd = 3;

    switch (cmd)
    {
    case 1:
        addToShopA(tag);
        break;

    case 2:
        addToShopB(tag);
        break;

    case 3:
        addToShopC(tag);
        break;

    default:
        break;
    }
}

void subJudgeFrame(char *tag)
{
    int cmd = -1;
    if (strstr(tag, "a"))
        cmd = 1;
    if (strstr(tag, "b"))
        cmd = 2;
    if (strstr(tag, "c"))
        cmd = 3;

    switch (cmd)
    {
    case 1:
        subToShopA(tag);
        break;

    case 2:
        subToShopB(tag);
        break;

    case 3:
        subToShopC(tag);
        break;

    default:
        break;
    }
}

void addToShopA(char *tag)
{
    // a-1
    if (strstr(tag, "a_1_1"))
    {
        FSet->a_1_1->addCount();
        if (FSet->a_1_1->Count() == 1)
            shopCart->push_back(FSet->a_1_1);
        goto flushTag;
    }

    if (strstr(tag, "a_1_2"))
    {
        FSet->a_1_2->addCount();
        if (FSet->a_1_2->Count() == 1)
            shopCart->push_back(FSet->a_1_2);
        goto flushTag;
    }

    if (strstr(tag, "a_1_3"))
    {
        FSet->a_1_3->addCount();
        if (FSet->a_1_3->Count() == 1)
            shopCart->push_back(FSet->a_1_3);
        goto flushTag;
    }

    if (strstr(tag, "a_1_4"))
    {
        FSet->a_1_4->addCount();
        if (FSet->a_1_4->Count() == 1)
            shopCart->push_back(FSet->a_1_4);
        goto flushTag;
    }

    // a-2
    if (strstr(tag, "a_2_1"))
    {
        FSet->a_2_1->addCount();
        if (FSet->a_2_1->Count() == 1)
            shopCart->push_back(FSet->a_2_1);
        goto flushTag;
    }

    if (strstr(tag, "a_2_2"))
    {
        FSet->a_2_2->addCount();
        if (FSet->a_2_2->Count() == 1)
            shopCart->push_back(FSet->a_2_2);
        goto flushTag;
    }

    if (strstr(tag, "a_2_3"))
    {
        FSet->a_2_3->addCount();
        if (FSet->a_2_3->Count() == 1)
            shopCart->push_back(FSet->a_2_3);
        goto flushTag;
    }

    if (strstr(tag, "a_2_4"))
    {
        FSet->a_2_4->addCount();
        if (FSet->a_2_4->Count() == 1)
            shopCart->push_back(FSet->a_2_4);
        goto flushTag;
    }

    // a-3
    if (strstr(tag, "a_3_1"))
    {
        FSet->a_3_1->addCount();
        if (FSet->a_3_1->Count() == 1)
            shopCart->push_back(FSet->a_3_1);
        goto flushTag;
    }

    if (strstr(tag, "a_3_2"))
    {
        FSet->a_3_2->addCount();
        if (FSet->a_3_2->Count() == 1)
            shopCart->push_back(FSet->a_3_2);
        goto flushTag;
    }

    if (strstr(tag, "a_3_3"))
    {
        FSet->a_3_3->addCount();
        if (FSet->a_3_3->Count() == 1)
            shopCart->push_back(FSet->a_3_3);
        goto flushTag;
    }

    if (strstr(tag, "a_3_4"))
    {
        FSet->a_3_4->addCount();
        if (FSet->a_3_4->Count() == 1)
            shopCart->push_back(FSet->a_3_4);
        goto flushTag;
    }

flushTag:
    SFrame->setPageMax(shopCart->size() / 4 + (shopCart->size() % 4 == 0 ? 0 : 1));
    SFrame->flushPage();
    // 清空购物车页面
    pic->setBmp("res/ui/bgClear.bmp");
    pic->display(543, 52);
    flushShop();
}

void addToShopB(char *tag)
{
    // b-1
    if (strstr(tag, "b_1_1"))
    {
        FSet->b_1_1->addCount();
        if (FSet->b_1_1->Count() == 1)
            shopCart->push_back(FSet->b_1_1);
        goto flushTag;
    }

    if (strstr(tag, "b_1_2"))
    {
        FSet->b_1_2->addCount();
        if (FSet->b_1_2->Count() == 1)
            shopCart->push_back(FSet->b_1_2);
        goto flushTag;
    }

    if (strstr(tag, "b_1_3"))
    {
        FSet->b_1_3->addCount();
        if (FSet->b_1_3->Count() == 1)
            shopCart->push_back(FSet->b_1_3);
        goto flushTag;
    }

    if (strstr(tag, "b_1_4"))
    {
        FSet->b_1_4->addCount();
        if (FSet->b_1_4->Count() == 1)
            shopCart->push_back(FSet->b_1_4);
        goto flushTag;
    }

    // b-2
    if (strstr(tag, "b_2_1"))
    {
        FSet->b_2_1->addCount();
        if (FSet->b_2_1->Count() == 1)
            shopCart->push_back(FSet->b_2_1);
        goto flushTag;
    }

    if (strstr(tag, "b_2_2"))
    {
        FSet->b_2_2->addCount();
        if (FSet->b_2_2->Count() == 1)
            shopCart->push_back(FSet->b_2_2);
        goto flushTag;
    }

    if (strstr(tag, "b_2_3"))
    {
        FSet->b_2_3->addCount();
        if (FSet->b_2_3->Count() == 1)
            shopCart->push_back(FSet->b_2_3);
        goto flushTag;
    }

    if (strstr(tag, "b_2_4"))
    {
        FSet->b_2_4->addCount();
        if (FSet->b_2_4->Count() == 1)
            shopCart->push_back(FSet->b_2_4);
        goto flushTag;
    }

flushTag:
    SFrame->setPageMax(shopCart->size() / 4 + (shopCart->size() % 4 == 0 ? 0 : 1));
    SFrame->flushPage();

    // 清空购物车页面
    pic->setBmp("res/ui/bgClear.bmp");
    pic->display(543, 52);
    flushShop();
}

void addToShopC(char *tag)
{
    // c-1
    if (strstr(tag, "c_1_1"))
    {
        FSet->c_1_1->addCount();
        if (FSet->c_1_1->Count() == 1)
            shopCart->push_back(FSet->c_1_1);
        goto flushTag;
    }

    if (strstr(tag, "c_1_2"))
    {
        FSet->c_1_2->addCount();
        if (FSet->c_1_2->Count() == 1)
            shopCart->push_back(FSet->c_1_2);
        goto flushTag;
    }

    if (strstr(tag, "c_1_2"))
    {
        FSet->c_1_2->addCount();
        if (FSet->c_1_2->Count() == 1)
            shopCart->push_back(FSet->c_1_2);
        goto flushTag;
    }

    if (strstr(tag, "c_1_3"))
    {
        FSet->c_1_3->addCount();
        if (FSet->c_1_3->Count() == 1)
            shopCart->push_back(FSet->c_1_3);
        goto flushTag;
    }

    if (strstr(tag, "c_1_4"))
    {
        FSet->c_1_4->addCount();
        if (FSet->c_1_4->Count() == 1)
            shopCart->push_back(FSet->c_1_4);
        goto flushTag;
    }

flushTag:
    SFrame->setPageMax(shopCart->size() / 4 + (shopCart->size() % 4 == 0 ? 0 : 1));
    SFrame->flushPage();

    // 清空购物车页面
    pic->setBmp("res/ui/bgClear.bmp");
    pic->display(543, 52);
    flushShop();
}

void subToShopA(char *tag)
{
    // a-1
    if (strstr(tag, "a_1_1"))
    {
        FSet->a_1_1->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_1_2"))
    {
        FSet->a_1_2->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_1_3"))
    {
        FSet->a_1_3->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_1_4"))
    {
        FSet->a_1_4->subCount();
        goto flushTag;
    }

    // a-2
    if (strstr(tag, "a_2_1"))
    {
        FSet->a_2_1->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_2_2"))
    {
        FSet->a_2_2->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_2_3"))
    {
        FSet->a_2_3->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_2_4"))
    {
        FSet->a_2_4->subCount();
        goto flushTag;
    }

    // a-3
    if (strstr(tag, "a_3_1"))
    {
        FSet->a_3_1->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_3_2"))
    {
        FSet->a_3_2->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_3_3"))
    {
        FSet->a_3_3->subCount();
        goto flushTag;
    }

    if (strstr(tag, "a_3_4"))
    {
        FSet->a_3_4->subCount();
        goto flushTag;
    }

flushTag:
    eachShop();
    flushShop();
}

void subToShopB(char *tag)
{
    // b-1
    if (strstr(tag, "b_1_1"))
    {
        FSet->b_1_1->subCount();
        goto flushTag;
    }

    if (strstr(tag, "b_1_2"))
    {
        FSet->b_1_2->subCount();
        goto flushTag;
    }

    if (strstr(tag, "b_1_3"))
    {
        FSet->b_1_3->subCount();
        goto flushTag;
    }

    if (strstr(tag, "b_1_4"))
    {
        FSet->b_1_4->subCount();
        goto flushTag;
    }

    // b-2
    if (strstr(tag, "b_2_1"))
    {
        FSet->b_2_1->subCount();
        goto flushTag;
    }

    if (strstr(tag, "b_2_2"))
    {
        FSet->b_2_2->subCount();
        goto flushTag;
    }

    if (strstr(tag, "b_2_3"))
    {
        FSet->b_2_3->subCount();
        goto flushTag;
    }

    if (strstr(tag, "b_2_4"))
    {
        FSet->b_2_4->subCount();
        goto flushTag;
    }

flushTag:
    eachShop();
    flushShop();
}

void subToShopC(char *tag)
{
    if (strstr(tag, "c_1_1"))
    {
        FSet->c_1_1->subCount();
        goto flushTag;
    }

    if (strstr(tag, "c_1_2"))
    {
        FSet->c_1_2->subCount();
        goto flushTag;
    }

    if (strstr(tag, "c_1_3"))
    {
        FSet->c_1_3->subCount();
        goto flushTag;
    }

    if (strstr(tag, "c_1_4"))
    {
        FSet->c_1_4->subCount();
        goto flushTag;
    }
flushTag:
    eachShop();
    flushShop();
}

void frameA(int page)
{
    switch (page)
    {
    case 1:
        pic->setBmp("res/pic/a_1.bmp");
        pic->display(52, 62);
        break;

    case 2:
        pic->setBmp("res/pic/a_2.bmp");
        pic->display(52, 62);
        break;

    case 3:
        pic->setBmp("res/pic/a_3.bmp");
        pic->display(52, 62);
        break;

    default:
        break;
    }
}

void frameB(int page)
{
    switch (page)
    {
    case 1:
        pic->setBmp("res/pic/b_1.bmp");
        pic->display(52, 62);
        break;

    case 2:
        pic->setBmp("res/pic/b_2.bmp");
        pic->display(52, 62);
        break;

    default:
        break;
    }
}

void frameC(int page)
{
    switch (page)
    {
    case 1:
        pic->setBmp("res/pic/c_1.bmp");
        pic->display(52, 62);
        break;

    default:
        break;
    }
}

void pay()
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "桌号", tableNo->data());
    for (auto &ra : *shopCart)
        cJSON_AddNumberToObject(root, ra->Name().data(), ra->Count());
    cJSON_AddNumberToObject(root, "总价", sumPrice);

    std::cout << cJSON_Print(root) << std::endl;

    // 向服务器发送数据
    Udp *client = new Udp(std::string("192.168.2.253"));
    client->sendMsg(std::string(cJSON_Print(root)), "192.168.2.35");

    cJSON_Delete(root);
    delete[] client;

    stopThread();
    isActivity = false;

    // "桌号: 已成功下单 祝您用餐愉快" //43
    char *info = new char[43 + tableNo->length()]();
    sprintf(info, "桌号:%s成功下单 祝您用餐愉快", tableNo->data());
    f30->show(std::string(info), 432, 30, 104, 9);
    delete[] info;
}
