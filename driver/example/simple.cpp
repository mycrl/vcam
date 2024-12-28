#include "vcam.h"
#include "windows.h"

int main()
{
    auto layout = get_nv12_layout(1920, 1080);
    uint8_t* frame_buf = (uint8_t*)malloc(sizeof(uint8_t) * layout.size);
    if (frame_buf == nullptr)
    {
        return -1;
    }

    VCam* vcam = vcam_open();
    if (vcam == nullptr)
    {
        return -2;
    }

    if (vcam_start(vcam, 1920, 1080) != 0)
    {
        return -3;
    }

    for (;;)
    {
        Sleep(1000 / 30);
        if (vcam_write_frame(vcam, frame_buf) != 0)
        {
            return -4;
        }
    }

    return 0;
}
