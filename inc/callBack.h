#ifndef _CALLBACK_H
#define _CALLBACK_H 1

#include <iostream>
#include <vector>
#include <semaphore.h>

#include "food.h"
#include "foodFrame.h"
#include "menuFrame.h"
#include "shopFrame.h"

void initData();
void startThread();
void printMain();

void printFrameToScreen(FoodFrame &ra);
void flushShop();
void eachShop();

void MenuFrameTask(MenuFrame &ra);
void FoodFrameTask(FoodFrame &ra);
void ShopFrameTask(ShopFrame &ra);

void addJudgeFrame(char *tag);
void subJudgeFrame(char *tag);

void addToShopA(char *tag);
void addToShopB(char *tag);
void addToShopC(char *tag);

void subToShopA(char *tag);
void subToShopB(char *tag);
void subToShopC(char *tag);

void frameA(int page);
void frameB(int page);
void frameC(int page);

void pay();

typedef struct foodSet
{
    Food *a_1_1 = nullptr;
    Food *a_1_2 = nullptr;
    Food *a_1_3 = nullptr;
    Food *a_1_4 = nullptr;

    Food *a_2_1 = nullptr;
    Food *a_2_2 = nullptr;
    Food *a_2_3 = nullptr;
    Food *a_2_4 = nullptr;

    Food *a_3_1 = nullptr;
    Food *a_3_2 = nullptr;
    Food *a_3_3 = nullptr;
    Food *a_3_4 = nullptr;

    Food *b_1_1 = nullptr;
    Food *b_1_2 = nullptr;
    Food *b_1_3 = nullptr;
    Food *b_1_4 = nullptr;

    Food *b_2_1 = nullptr;
    Food *b_2_2 = nullptr;
    Food *b_2_3 = nullptr;
    Food *b_2_4 = nullptr;

    Food *c_1_1 = nullptr;
    Food *c_1_2 = nullptr;
    Food *c_1_3 = nullptr;
    Food *c_1_4 = nullptr;
} foodSet_t;

#endif /* _CALLBACK_H */