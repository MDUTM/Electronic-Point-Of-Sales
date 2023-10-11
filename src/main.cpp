#include <iostream>

#include "callBack.h"
#include "touch.h"

using namespace std;

std::string *tableNo = nullptr;

extern Touch *ts; // 触摸
extern Point *p;  // 坐标

extern sem_t *menuFrameSem; // 菜单窗口信号量
extern sem_t *foodFrameSem; // 食物窗口信号量
extern sem_t *shopFrameSem; // 购物车窗口信号量

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "请指定桌号!" << std::endl;
        exit(EXIT_FAILURE);
    }

    tableNo = new std::string(argv[1]);

    // 初始化
    initData();

    // 主界面
    printMain();

    // 启动线程
    startThread();

    // 触摸
    while (1)
    {
        *p = ts->wait();
        sem_post(menuFrameSem);
        sem_post(foodFrameSem);
        sem_post(shopFrameSem);

        // 退出
        if (4 <= p->X() && p->X() <= 104 && 4 <= p->Y() && p->Y() <= 44)
        {
            cout << "已退出!" << endl;
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
