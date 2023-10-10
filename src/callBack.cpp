#include "callBack.h"

#include "bmp.h"
#include "fontUtil.h"
#include "touch.h"
#include "menuFrame.h"
#include "foodFrame.h"

/* 全局变量 */
Bmp *pic = nullptr;  // 图片
Font *f30 = nullptr; // 30px字体
Touch *ts = nullptr; // 触摸
Point *p = nullptr;  // 坐标

sem_t *menuFrameSem = nullptr; // 菜单窗口信号量
sem_t *foodFrameSem = nullptr; // 食物窗口信号量
sem_t *shopFrameSem = nullptr; // 购物车窗口信号量

MenuFrame *MFrame = nullptr; // 菜单窗口
FoodFrame *FFrameA = nullptr; // 食物窗口A
FoodFrame *FFrameB = nullptr; // 食物窗口B
FoodFrame *FFrameC = nullptr; // 食物窗口C

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
}

void startThread()
{
    MFrame->start();
    FFrameA->setThreadStatus(true);
    FFrameA->start();
}

void printMain()
{
    pic->setBmp("res/ui/main.bmp");
    pic->display();
}

void MenuFrameTask()
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
                std::cout << "A" << std::endl;
                // if (!FMA->ThreadStatus())
                // {
                //     FMA->setThreadStatus(true);
                //     FMA->start();
                // }
                // if (FMB->ThreadStatus())
                // {
                //     FMB->setThreadStatus(false);
                //     FMB->stop();
                // }
                // if (FMC->ThreadStatus())
                // {
                //     FMC->setThreadStatus(false);
                //     FMC->stop();
                // }
                continue;
            }

            // B类
            if (195 <= p->X() && p->X() <= 345)
            {
                std::cout << "B" << std::endl;
                // if (FMA->ThreadStatus())
                // {
                //     FMA->setThreadStatus(false);
                //     FMA->stop();
                // }
                // if (!FMB->ThreadStatus())
                // {
                //     FMB->setThreadStatus(true);
                //     FMB->start();
                // }
                // if (FMC->ThreadStatus())
                // {
                //     FMC->setThreadStatus(false);
                //     FMC->stop();
                // }
                continue;
            }

            // C类
            if (386 <= p->X() && p->X() <= 536)
            {
                std::cout << "C" << std::endl;
                // if (FMA->ThreadStatus())
                // {
                //     FMA->setThreadStatus(false);
                //     FMA->stop();
                // }
                // if (FMB->ThreadStatus())
                // {
                //     FMB->setThreadStatus(false);
                //     FMB->stop();
                // }
                // if (!FMC->ThreadStatus())
                // {
                //     FMC->setThreadStatus(true);
                //     FMC->start();
                // }
                continue;
            }
        }
    }
}

void FoodFrameTask()
{
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
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_1", _tag, _page);
                // operate(buf, addToShopping);
                // delete[] buf;
                std::cout << "1+" << std::endl;
                continue;
            }

            // 1 -
            if (128 <= p->Y() && p->Y() <= 197)
            {
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_1", _tag, _page);
                // operate(buf, subToShopping);
                // delete[] buf;
                std::cout << "1-" << std::endl;
                continue;
            }

            // 上一页
            if (205 <= p->Y() && p->Y() <= 274)
            {
                // _page = --_page < 1 ? _pageMax : _page;
                // std::cout << "page: " << _page << std::endl;
                // operate(*this, displayCallBack);
                std::cout << "up" << std::endl;
                continue;
            }

            // 2 +
            if (281 <= p->Y() && p->Y() <= 350)
            {
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_2", _tag, _page);
                // operate(buf, addToShopping);
                // delete[] buf;
                std::cout << "2+" << std::endl;
                continue;
            }

            // 2 -
            if (357 <= p->Y() && p->Y() <= 426)
            {
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_2", _tag, _page);
                // operate(buf, subToShopping);
                // delete[] buf;
                std::cout << "2-" << std::endl;
                continue;
            }
        }

        if (482 <= p->X() && p->X() <= 531) // 右
        {
            // 3 +
            if (52 <= p->Y() && p->Y() <= 121)
            {
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_3", _tag, _page);
                // operate(buf, addToShopping);
                // delete[] buf;
                std::cout << "3+" << std::endl;
                continue;
            }

            // 3 -
            if (128 <= p->Y() && p->Y() <= 197)
            {
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_3", _tag, _page);
                // operate(buf, subToShopping);
                // delete[] buf;
                std::cout << "3-" << std::endl;
                continue;
            }

            // 下一页
            if (205 <= p->Y() && p->Y() <= 274)
            {
                // _page = ++_page > _pageMax ? 1 : _page;
                // std::cout << "page: " << _page << std::endl;
                // operate(*this, displayCallBack);
                std::cout << "down" << std::endl;
                continue;
            }

            // 4 +
            if (281 <= p->Y() && p->Y() <= 350)
            {
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_4", _tag, _page);
                // operate(buf, addToShopping);
                // delete[] buf;
                std::cout << "4+" << std::endl;
                continue;
            }

            // 4 -
            if (357 <= p->Y() && p->Y() <= 426)
            {
                // char *buf = new char[7]();
                // sprintf(buf, "%c_%d_4", _tag, _page);
                // operate(buf, subToShopping);
                // delete[] buf;
                std::cout << "4-" << std::endl;
                continue;
            }
        }
    }
}
