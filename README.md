<!--lint disable no-literal-urls-->
<div align="center">
  <h1>VCam</h1>
</div>
<br/>
<div align="center">
  <strong>Windows Virtual Camera</strong>
</div>
<div align="center">
  <img src="https://img.shields.io/github/actions/workflow/status/mycrl/vcam/release.yml?branch=main"/>
  <img src="https://img.shields.io/github/license/mycrl/vcam"/>
  <img src="https://img.shields.io/github/issues/mycrl/vcam"/>
  <img src="https://img.shields.io/github/stars/mycrl/vcam"/>
</div>
<br/>
<br/>

This is a modified version of the Virtual Camera module from within OBS, providing clients in C/C++ and Node.js.

Using Libobs or separating modules from OBS may not be a difficult task, but this project simplifies the process.

### Building

This is a normal CMake project that follows the standard CMake generation steps.

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

#### Node.js

The npm project automatically triggers the compilation process during the install phase.

```sh
cd napi
npm i
```

### Usage

Firstly you need to register the DLL to the system service, this is a key step to get the virtual camera registered to the system.

```sh
regsvr32.exe /i /s "\to\path\vcam-service.dll"
```

The path to the actual DLL is based on your own situation.

If you don't need the virtual camera, i.e. unregister it, perform a similar operation.

```sh
regsvr32.exe /u /s "\to\path\vcam-service.dll"
```

Then you can use the vcam driver to output the screen to the virtual camera, this is an example of outputting a 1920x1080 empty screen.

```cpp
#include "vcam.h"
#include "windows.h"

int main() {
  auto layout = get_nv12_layout(1920, 1080);
  uint8_t* frame_buf = (uint8_t*)malloc(sizeof(uint8) * layout.size);
  if (frame_buf == NULL) {
    return -1;
  }

  VCam* vcam = vcam_open();
  if (vcam == NULL) {
    return -1;
  }

  if (vcam_start(vcam, 1920, 1080) != 0) {
    return -1;
  }

  for (;;) {
    Sleep(1000 / 30);
    if (vcam_write_frame(vcam, frame_buf) != 0) {
      return -1;
    }
  }
}
```

#### Node.js

This is a Node.js Native Module, similar to the C/C++ example.

```js
const vcam = new VCam();

const layout = vcam.get_nv12_layout(1920, 1080);
const buffer = Buffer.alloc(layout.size);

vcam.start();

for (;;) {
    vcam.write(buffer);
}
```

### License

[GPL](./LICENSE)
Copyright (c) 2024 Mr.Panda.
