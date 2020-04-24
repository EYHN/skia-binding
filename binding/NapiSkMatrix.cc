#include "NapiSkMatrix.h"

Napi::Object NapiSkMatrix::makeConstructor(Napi::Env env) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SkMatrix", {
        
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return func;
}

NapiSkMatrix::NapiSkMatrix(const Napi::CallbackInfo &info) : SkObjectWrap<NapiSkMatrix, SkMatrix>(info) {
}

Napi::FunctionReference NapiSkMatrix::constructor;
