#include "foodFrame.h"

extern void FoodFrameTask(FoodFrame &ra);

FoodFrame::FoodFrame(char tag, int pageMax)
{
    _tag = tag;
    _page = 1;
    _pageMax = pageMax;
    _threadStatus = false;
}

void FoodFrame::setThreadStatus(bool status)
{
    _threadStatus = status;
}

bool FoodFrame::ThreadStatus()
{
    return _threadStatus;
}

int FoodFrame::Page()
{
    return _page;
}

char FoodFrame::Tag()
{
    return _tag;
}

void FoodFrame::subPage()
{
    _page = --_page < 1 ? _pageMax : _page;
}

void FoodFrame::addPage()
{
    _page = ++_page > _pageMax ? 1 : _page;
}

void FoodFrame::run()
{
    FoodFrameTask(*this);
}
