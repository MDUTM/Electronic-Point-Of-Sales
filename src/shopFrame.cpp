#include "shopFrame.h"

extern void ShopFrameTask(ShopFrame &ra);

ShopFrame::ShopFrame()
{

}

void ShopFrame::run()
{
    ShopFrameTask(*this);
}
