#ifndef _SHOPFRAME_H
#define _SHOPFRAME_H 1

#include "thread.h"

class ShopFrame : public Thread
{
    int _page;
    int _pageMax;
public:
    ShopFrame();
    void run();

    void addPage();
    void subPage();
    int Page();
    int PageMax();
    void setPageMax(int pageMax);
};

#endif /* _SHOPFRAME_H */