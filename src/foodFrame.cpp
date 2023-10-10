#include "foodFrame.h"

extern void FoodFrameTask();

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

void FoodFrame::run()
{
    FoodFrameTask();
}
