# Windows virtual Camera

虚拟摄像头插件，分为COM组件和调用方DLL，并提供了Node.Js本地模块，可以作为Electron本机模块使用.  

## 项目结构

* `virtual.camera` COM组件，通过注册组件方式来作为虚拟摄像头Server.  
* `virtual.camera.client` 客户端DLL，与Server之间通过共享内存队列通信.  
* `virtual.camera.napi` Node.Js本地插件.  


## 编译

#### virtual.camera

先通过cmake生成vs工程文件:
```bash
mkdir build
cd build
cmake ..
```

打开build目录中的工程文件生成出DLL.

#### virtual.camera.client

直接打开工程文件生成

### virtual.camera.napi

前提条件，需要Node.Js 16.x版本以及Pyhton环境.  

```bash
npm install
npm install -g node-gyp
node-gyp configure
node-gyp build
```