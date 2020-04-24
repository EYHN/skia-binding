#include <napi.h>
#include <include/core/SkPath.h>
#include "utils.h"

class NapiSkPath : public SkObjectWrap<NapiSkPath, SkPath> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    static Napi::FunctionReference constructor;
    NapiSkPath(const Napi::CallbackInfo &info);
};

inline SkPath Napi_val_as_SkPath(Napi::Value val) {
	NapiSkPath* matrix = NapiSkPath::Unwrap(val.As<Napi::Object>());
	return matrix->self;
}