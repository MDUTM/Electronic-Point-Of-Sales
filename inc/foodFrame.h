#ifndef _FOODFRAME_H
#define _FOODFRAME_H 1

#include "thread.h"

class FoodFrame : public Thread
{
    bool _threadStatus;
    int _page;
    int _pageMax;
    char _tag;

public:
    FoodFrame(char tag, int pageMax);

    void setThreadStatus(bool status);
    bool ThreadStatus();
    int Page();
    char Tag();

    void subPage();
    void addPage();

    void run();
};

#endif /* _FOODFRAME_H */