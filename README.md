# Windows virtual Camera

Virtual camera plugin, divided into COM components and caller dll and provides Node.Js native modules.


## Build

first generate the visual studio project file through cmake:
```bash
cd virtual.camera
mkdir build
cd build
cmake ..
```

open the project file in the build directory to generate the dll.


### Node.js Napi Module

prerequisites, Node.Js 16.x version and Pyhton environment are required.  

```bash
npm install
npm install -g node-gyp
node-gyp configure build
```


## Usage

register com component:

```bash
cd virtual.camera
./install.bat
```

output empty frame:

```c
#include "client.h"
#include "windows.h"

int main() 
{
    NV12Layout layout = get_nv12_layout(1920, 1080);
    uint8_t* frame_buf = (uint8_t*)malloc(sizeof(uint8) * layout.size);
    if (frame_buf == NULL)
    {
        return -1;
    }
    
    VCam* vcam = vcam_open();
    if (vcam == NULL)
    {
        return -1;
    }
    
    if (vcam_start(vcam, 1920, 1080) != 0)
    {
        return -1;
    }
    
    for (;;)
    {
        Sleep(1000 / 30);
        if (vcam_write_frame(vcam, frame_buf) != 0)
        {
            return -1;
        }
    }
}
```


## License

[GPL](./LICENSE)
Copyright (c) 2020 Mr.Panda.