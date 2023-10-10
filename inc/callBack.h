#ifndef _CALLBACK_H
#define _CALLBACK_H 1

#include <semaphore.h>

void initData();
void startThread();
void printMain();

void MenuFrameTask();
void FoodFrameTask();
void ShopFrameTask();

#endif /* _CALLBACK_H */