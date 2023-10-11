#include "menuFrame.h"

extern void MenuFrameTask(MenuFrame &ra);

void MenuFrame::run()
{
    MenuFrameTask(*this);
}