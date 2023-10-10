#include "shopFrame.h"

extern void ShopFrameTask();

ShopFrame::ShopFrame()
{

}

void ShopFrame::run()
{
    ShopFrameTask();
}
