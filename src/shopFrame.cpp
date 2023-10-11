#include "shopFrame.h"

extern void ShopFrameTask(ShopFrame &ra);

ShopFrame::ShopFrame()
{
    _page = 1;
    _pageMax = 0;
}

void ShopFrame::run()
{
    ShopFrameTask(*this);
}

void ShopFrame::addPage()
{
    _page = ++_page > _pageMax ? 1 : _page;
}

void ShopFrame::subPage()
{
    _page = --_page < 1 ? _pageMax : _page;

    _page = _page == 0 ? 1 : _page;
}

int ShopFrame::Page()
{
    return _page;
}

int ShopFrame::PageMax()
{
    return _pageMax;
}

void ShopFrame::setPageMax(int pageMax)
{
    _pageMax = pageMax;
}

void ShopFrame::flushPage()
{
    if (!_pageMax)
        _page = 1;
    else
        _page = _pageMax;
}
