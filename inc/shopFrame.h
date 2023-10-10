#ifndef _SHOPFRAME_H
#define _SHOPFRAME_H 1

#include "thread.h"

class ShopFrame : public Thread
{
public:
    ShopFrame();
    void run();
};

#endif /* _SHOPFRAME_H */