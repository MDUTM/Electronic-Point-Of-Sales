#include "callBack.h"

#include "bmp.h"
#include "fontUtil.h"
#include "touch.h"
#include "menuFrame.h"

/* 全局变量 */
Bmp *pic = nullptr;  // 图片
Font *f30 = nullptr; // 30px字体
Touch *ts = nullptr; // 触摸
Point *p = nullptr;  // 坐标

sem_t *menuFrameSem = nullptr; // 菜单窗口信号量
sem_t *foodFrameSem = nullptr; // 食物窗口信号量
sem_t *shopFrameSem = nullptr; // 购物车窗口信号量

MenuFrame *MFrame = nullptr; // 菜单窗口

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
}

void startThread()
{
    MFrame->start();
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
