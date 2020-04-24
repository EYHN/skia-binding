#ifndef SK_JS_UTILS_
#define SK_JS_UTILS_

#include <napi.h>

#include <include/core/SkScalar.h>
#include <include/core/SkRect.h>
#include <include/core/SkPathTypes.h>
#include <include/core/SkPoint.h>

inline SkScalar Napi_val_as_SkScalar(Napi::Value val) {
  return static_cast<SkScalar>((val).As<Napi::Number>().FloatValue());
}

inline SkRect Napi_val_as_SkRect(Napi::Value val) {
  auto obj = val.As<Napi::Object>();
  return SkRect::MakeLTRB(
    Napi_val_as_SkScalar(obj.Get("left")),
    Napi_val_as_SkScalar(obj.Get("top")),
    Napi_val_as_SkScalar(obj.Get("right")),
    Napi_val_as_SkScalar(obj.Get("bottom"))
  );
}

template <typename T>
inline T Napi_val_as_enum(Napi::Value val) {
  auto i = val.As<Napi::Number>().Int32Value();
  return static_cast<T>(i);
}

template <typename T>
inline T Napi_val_as_enum(Napi::Value val, T def) {
  if (val.IsUndefined()) {
    return def;
  }
  auto i = val.As<Napi::Number>().Int32Value();
  return static_cast<T>(i);
}

template <typename T>
inline T* Napi_val_as_array(Napi::Value val, T (*converter)(Napi::Value val)) {
  auto array = val.As<Napi::Array>();
  T *target = new T[array.Length()];

  for (uint32_t i = 0; i < array.Length(); i++) {
    target[i] = converter(array[i]);
  }
  return target;
}

inline SkPoint Napi_val_as_SkPoint(Napi::Value val) {
  auto obj = val.As<Napi::Object>();
  return SkPoint::Make(
    Napi_val_as_SkScalar(obj.Get("x")),
    Napi_val_as_SkScalar(obj.Get("y"))
  );
}

inline bool Napi_val_as_bool(Napi::Value val) {
  return val.As<Napi::Boolean>();
}

inline int Napi_val_as_int(Napi::Value val) {
  return val.As<Napi::Number>();
}

inline Napi::Value bool_as_Napi_val(bool b, const Napi::Env &env) {
  return Napi::Boolean::New(env, b);;
}

inline Napi::Value int_as_Napi_val(int i, const Napi::Env &env) {
  return Napi::Number::New(env, i);;
}

template <typename T>
inline Napi::Value enum_as_Napi_val(T i, const Napi::Env &env) {
  return Napi::Number::New(env, static_cast<int>(i));;
}

inline Napi::Value SkRect_as_Napi_val(SkRect i, const Napi::Env &env) {
  auto obj = Napi::Object::New(env);
  obj.Set("left", i.left());
  obj.Set("top", i.top());
  obj.Set("right", i.right());
  obj.Set("bottom", i.bottom());
  return obj;
}

inline Napi::Value SkPoint_as_Napi_val(SkPoint point, const Napi::Env &env) {
  auto obj = Napi::Object::New(env);
  obj.Set("x", point.x());
  obj.Set("y", point.y());
  return obj;
}

template <typename T, typename SkObjectType>
class SkObjectWrap : public Napi::ObjectWrap<T> {
  public:
    typedef void (*VoidSkObjectWrapMethodCallback)(SkObjectType &self, const Napi::CallbackInfo &info);
    typedef Napi::Value (*SkObjectWrapMethodCallback)(SkObjectType &self, const Napi::CallbackInfo &info);

    static Napi::ClassPropertyDescriptor<T> SkObjectWrapInstanceMethod(const char *utf8name, VoidSkObjectWrapMethodCallback callback);
    static Napi::ClassPropertyDescriptor<T> SkObjectWrapInstanceMethod(const char *utf8name, SkObjectWrapMethodCallback callback);
    SkObjectWrap(const Napi::CallbackInfo &info);
    virtual ~SkObjectWrap();

    SkObjectType self;

  protected:
    typedef std::function<Napi::Value(SkObjectType &self, const Napi::CallbackInfo &info)> _function_type;
    static std::vector<std::shared_ptr<_function_type>> _functions;
    Napi::Value _useCallback(const Napi::CallbackInfo &info);
};

template <typename T, typename SkObjectType>
inline SkObjectWrap<T, SkObjectType>::~SkObjectWrap() {}

template <typename T, typename SkObjectType>
Napi::Value SkObjectWrap<T, SkObjectType>::_useCallback(const Napi::CallbackInfo &info) {
  _function_type cb = *((_function_type*)info.Data()); 
  return cb(self, info);
}

template <typename T, typename SkObjectType>
inline Napi::ClassPropertyDescriptor<T> SkObjectWrap<T, SkObjectType>::SkObjectWrapInstanceMethod(const char *utf8name, SkObjectWrapMethodCallback callback) {
  std::shared_ptr<_function_type> ptr = std::make_shared<_function_type>(callback);
  T::_functions.push_back(ptr);

  return Napi::ObjectWrap<T>::InstanceMethod(utf8name, &T::_useCallback, napi_default, ptr.get());
}

template <typename T, typename SkObjectType>
inline Napi::ClassPropertyDescriptor<T> SkObjectWrap<T, SkObjectType>::SkObjectWrapInstanceMethod(const char *utf8name, VoidSkObjectWrapMethodCallback callback) {
  std::shared_ptr<_function_type> ptr = std::make_shared<_function_type>([callback](SkObjectType &self, const Napi::Env &env) {
    callback();
    return env.Undefined();
  });
  T::_functions.push_back(ptr);

  return Napi::ObjectWrap<T>::InstanceMethod(utf8name, &T::_useCallback, napi_default, ptr.get());
}

template <typename T, typename SkObjectType>
SkObjectWrap<T, SkObjectType>::SkObjectWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<T>(info) {

}

template <typename T, typename SkObjectType>
std::vector<std::shared_ptr<std::function<Napi::Value(SkObjectType &self, const Napi::CallbackInfo &info)>>> SkObjectWrap<T, SkObjectType>::_functions;

#endif