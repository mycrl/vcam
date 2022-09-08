#include <napi.h>
#include <client.h>

class VCamWrapper: public Napi::ObjectWrap<VCamWrapper> 
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    VCamWrapper(const Napi::CallbackInfo& info);
private:
    Napi::Value Start(const Napi::CallbackInfo& info);
    Napi::Value Write(const Napi::CallbackInfo& info);
    Napi::Value Stop(const Napi::CallbackInfo& info);
    Napi::Value GetNV12Layout(const Napi::CallbackInfo& info);
    Napi::Value I420ToNV12(const Napi::CallbackInfo& info);
    Napi::Value FreeNv12(const Napi::CallbackInfo& info);

    static Napi::FunctionReference constructor;
    VCam* _vcam;
};
