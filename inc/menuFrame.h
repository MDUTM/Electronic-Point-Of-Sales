#ifndef _MENUFRAME_H
#define _MENUFRAME_H 1

#include "thread.h"

class MenuFrame : public Thread
{
    void run();
};

#endif /* _MENUFRAME_H */