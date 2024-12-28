#include "lib.h"

Napi::FunctionReference VCamWrapper::constructor;

Napi::Object VCamWrapper::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function vcam_wrapper = DefineClass(env, "VCam", {
        InstanceMethod("start", &VCamWrapper::Start),
        InstanceMethod("write", &VCamWrapper::Write),
        InstanceMethod("stop", &VCamWrapper::Stop),
        InstanceMethod("getNV12Layout", &VCamWrapper::GetNV12Layout),
        InstanceMethod("i420ToNV12", &VCamWrapper::I420ToNV12),
        InstanceMethod("freeNv12", &VCamWrapper::FreeNv12),
                                              });

    constructor = Napi::Persistent(vcam_wrapper);
    constructor.SuppressDestruct();

    exports.Set("VCam", vcam_wrapper);
    return exports;
}

VCamWrapper::VCamWrapper(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<VCamWrapper>(info)
{
    Napi::Env env = info.Env();
    this->_vcam = vcam_open();
    if (this->_vcam == NULL)
    {
        Napi::TypeError::New(env, "vcam create failed!")
            .ThrowAsJavaScriptException();
    }
}

Napi::Value VCamWrapper::Start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    uint32_t height = info[1].As<Napi::Number>().Uint32Value();

    int ret = vcam_start(this->_vcam, width, height);
    if (ret == -2)
    {
        Napi::TypeError::New(env, "vcam already opened!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }
    else
        if (ret == -1)
        {
            Napi::TypeError::New(env, "vcam open failed!")
                .ThrowAsJavaScriptException();
            return env.Null();
        }

    return env.Null();
}

Napi::Value VCamWrapper::Write(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsBuffer())
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    uint8_t* data = info[0].As<Napi::Buffer<uint8_t>>().Data();
    if (vcam_write_frame(this->_vcam, data) == -2)
    {
        Napi::TypeError::New(env, "vcam already opened!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    return env.Null();
}

Napi::Value VCamWrapper::Stop(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    vcam_stop(this->_vcam);
    return env.Null();
}

Napi::Value VCamWrapper::I420ToNV12(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 3)
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsBuffer())
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    uint32_t height = info[1].As<Napi::Number>().Uint32Value();
    uint8_t* data = info[2].As<Napi::Buffer<uint8_t>>().Data();

    NV12Layout layout = get_nv12_layout((size_t)width, (size_t)height);
    uint8_t* nv12 = i420_to_nv12((size_t)width, (size_t)height, data);
    if (nv12 == NULL)
    {
        return env.Null();
    }

    return Napi::Buffer<uint8_t>::New(env, nv12, layout.size);
}

Napi::Value VCamWrapper::FreeNv12(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsBuffer())
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    free(info[0].As<Napi::Buffer<uint8_t>>().Data());
    return env.Null();
}

Napi::Value VCamWrapper::GetNV12Layout(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "invalid arguments!")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    uint32_t height = info[1].As<Napi::Number>().Uint32Value();

    Napi::Object layout_obj = Napi::Object::New(env);
    NV12Layout layout = get_nv12_layout((size_t)width, (size_t)height);

    layout_obj.Set("size", layout.size);
    layout_obj.Set("y", layout.y_size);
    layout_obj.Set("uv", layout.uv_size);
    return layout_obj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    return VCamWrapper::Init(env, exports);
}

NODE_API_MODULE(vcam, Init)
