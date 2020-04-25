#include "NapiSkPath.h"
#include "NapiSkMatrix.h"

Napi::Object NapiSkPath::makeConstructor(Napi::Env env) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SkPath", {
      SkObjectWrapInstanceMethod("isInterpolatable", [](SkPath& self, const Napi::CallbackInfo& info) -> Napi::Value {
        return bool_as_Napi_val(
          self.isInterpolatable(NapiSkPath::from(info[0]).getSelf()),
          info.Env()
        );
      }),
      SkObjectWrapInstanceMethod("interpolate", [](SkPath& self, const Napi::CallbackInfo& info) -> Napi::Value {
        auto newSkPath = SkPath();
        self.interpolate(
          NapiSkPath::from(info[0]).getSelf(),
          Napi_val_as_SkScalar(info[1]),
          &newSkPath
        );
        return NapiSkPath::New(newSkPath, info.Env()).Value();
      }),
      SkObjectWrapInstanceMethod("getFillType", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return enum_as_Napi_val(self.getFillType(), info.Env());
      }),
      SkObjectWrapInstanceMethod("setFillType", [](SkPath &self, const Napi::CallbackInfo &info) {
        self.setFillType(
          Napi_val_as_enum<SkPathFillType>(info[0])
        );
      }),
      SkObjectWrapInstanceMethod("isInverseFillType", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return bool_as_Napi_val(self.isInverseFillType(), info.Env());
      }),
      SkObjectWrapInstanceMethod("toggleInverseFillType", [](SkPath &self, const Napi::CallbackInfo &info) {
        self.toggleInverseFillType();
      }),
      SkObjectWrapInstanceMethod("getConvexityType", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return enum_as_Napi_val(self.getConvexityType(), info.Env());
      }),
      SkObjectWrapInstanceMethod("getConvexityTypeOrUnknown", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return enum_as_Napi_val(self.getConvexityTypeOrUnknown(), info.Env());
      }),
      SkObjectWrapInstanceMethod("setConvexityType", [](SkPath &self, const Napi::CallbackInfo &info) {
        self.setConvexityType(
          Napi_val_as_enum<SkPathConvexityType>(info[0])
        );
      }),
      SkObjectWrapInstanceMethod("isConvex", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return bool_as_Napi_val(self.isConvex(), info.Env());
      }),
      // todo: bool isOval(SkRect* bounds) const;
      // todo: bool isRRect(SkRRect* rrect) const;
      SkObjectWrapInstanceMethod("reset", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.reset();
        return info.This();
      }),
      SkObjectWrapInstanceMethod("rewind", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.rewind();
        return info.This();
      }),
      SkObjectWrapInstanceMethod("moveTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.moveTo(Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]));
        return info.This();
      }),
      SkObjectWrapInstanceMethod("rMoveTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.rMoveTo(Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]));
        return info.This();
      }),
      SkObjectWrapInstanceMethod("lineTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.lineTo(Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]));
        return info.This();
      }),
      SkObjectWrapInstanceMethod("rLineTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.rLineTo(Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]));
        return info.This();
      }),
      SkObjectWrapInstanceMethod("quadTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        if (info.Length() == 2) {
          self.quadTo(
            Napi_val_as_SkPoint(info[0]),
            Napi_val_as_SkPoint(info[1])
          );
        } else {
          self.quadTo(
            Napi_val_as_SkScalar(info[0]),
            Napi_val_as_SkScalar(info[1]),
            Napi_val_as_SkScalar(info[2]),
            Napi_val_as_SkScalar(info[3])
          );
        }
        return info.This();
      }),
      SkObjectWrapInstanceMethod("rQuadTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.rQuadTo(
          Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]),
          Napi_val_as_SkScalar(info[2]),
          Napi_val_as_SkScalar(info[3])
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("close", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.close();
        return info.This();
      }),
      SkObjectWrapInstanceMethod("addArc", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.addArc(
          Napi_val_as_SkRect(info[0]),
          Napi_val_as_SkScalar(info[1]),
          Napi_val_as_SkScalar(info[2])
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("addOval", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.addOval(
          Napi_val_as_SkRect(info[0]),
          Napi_val_as_enum<SkPathDirection>(info[1], SkPathDirection::kCW)
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("addPath", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        auto source = Unwrap(info[0].As<Napi::Object>());
        self.addPath(
          source->getSelf(),
          Napi_val_as_enum<SkPath::AddPathMode>(info[1], SkPath::kAppend_AddPathMode)
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("addPoly", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        SkPoint* points = Napi_val_as_array(info[0], &Napi_val_as_SkPoint);
        self.addPoly(
          points,
          info[0].As<Napi::Array>().Length(),
          Napi_val_as_bool(info[1])
        );
        delete points;
        return info.This();
      }),
      SkObjectWrapInstanceMethod("addRect", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.addRect(
          Napi_val_as_SkRect(info[0]),
          Napi_val_as_enum<SkPathDirection>(info[1], SkPathDirection::kCW)
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("addRoundRect", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.addRoundRect(
          Napi_val_as_SkRect(info[0]),
          Napi_val_as_array(info[1], &Napi_val_as_SkScalar),
          Napi_val_as_enum<SkPathDirection>(info[2], SkPathDirection::kCW)
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("arcTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        if (info.Length() == 3) {
          self.arcTo(
            Napi_val_as_SkPoint(info[0]),
            Napi_val_as_SkPoint(info[1]),
            Napi_val_as_SkScalar(info[2])
          );
        } else if (info.Length() == 4) {
          self.arcTo(
            Napi_val_as_SkRect(info[0]),
            Napi_val_as_SkScalar(info[1]),
            Napi_val_as_SkScalar(info[2]),
            Napi_val_as_bool(info[3])
          );
        } else {
          self.arcTo(
            Napi_val_as_SkScalar(info[0]),
            Napi_val_as_SkScalar(info[1]),
            Napi_val_as_SkScalar(info[2]),
            Napi_val_as_enum<SkPath::ArcSize>(info[3]),
            Napi_val_as_enum<SkPathDirection>(info[4]),
            Napi_val_as_SkScalar(info[5]),
            Napi_val_as_SkScalar(info[6])
          );
        }
        return info.This();
      }),
      SkObjectWrapInstanceMethod("rArcTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.rArcTo(
          Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]),
          Napi_val_as_SkScalar(info[2]),
          Napi_val_as_enum<SkPath::ArcSize>(info[3]),
          Napi_val_as_enum<SkPathDirection>(info[4]),
          Napi_val_as_SkScalar(info[5]),
          Napi_val_as_SkScalar(info[6])
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("conicTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        if (info.Length() == 3) {
          self.conicTo(
            Napi_val_as_SkPoint(info[0]),
            Napi_val_as_SkPoint(info[1]),
            Napi_val_as_SkScalar(info[2])
          );
        } else {
          self.conicTo(
            Napi_val_as_SkScalar(info[0]),
            Napi_val_as_SkScalar(info[1]),
            Napi_val_as_SkScalar(info[2]),
            Napi_val_as_SkScalar(info[3]),
            Napi_val_as_SkScalar(info[4])
          );
        }
        return info.This();
      }),
      SkObjectWrapInstanceMethod("rConicTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.rConicTo(
          Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]),
          Napi_val_as_SkScalar(info[2]),
          Napi_val_as_SkScalar(info[3]),
          Napi_val_as_SkScalar(info[4])
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("countPoints", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return Napi::Number::New(info.Env(), self.countPoints());
      }),
      SkObjectWrapInstanceMethod("contains", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        auto r = self.contains(Napi_val_as_SkScalar(info[0]),Napi_val_as_SkScalar(info[1]));
        return Napi::Boolean::New(info.Env(), r);
      }),
      SkObjectWrapInstanceMethod("cubicTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        if (info.Length() == 3) {
          self.cubicTo(
            Napi_val_as_SkPoint(info[0]),
            Napi_val_as_SkPoint(info[1]),
            Napi_val_as_SkPoint(info[2])
          );
        } else {
          self.cubicTo(
            Napi_val_as_SkScalar(info[0]),
            Napi_val_as_SkScalar(info[1]),
            Napi_val_as_SkScalar(info[2]),
            Napi_val_as_SkScalar(info[3]),
            Napi_val_as_SkScalar(info[4]),
            Napi_val_as_SkScalar(info[5])
          );
        }
        return info.This();
      }),
      SkObjectWrapInstanceMethod("rCubicTo", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.rCubicTo(
          Napi_val_as_SkScalar(info[0]),
          Napi_val_as_SkScalar(info[1]),
          Napi_val_as_SkScalar(info[2]),
          Napi_val_as_SkScalar(info[3]),
          Napi_val_as_SkScalar(info[4]),
          Napi_val_as_SkScalar(info[5])
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("getPoint", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        auto r = self.getPoint(Napi_val_as_int(info[0]));
        return SkPoint_as_Napi_val(r, info.Env());
      }),
      SkObjectWrapInstanceMethod("isEmpty", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        auto r = self.isEmpty();
        return bool_as_Napi_val(r, info.Env());
      }),
      SkObjectWrapInstanceMethod("isVolatile", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        auto r = self.isVolatile();
        return bool_as_Napi_val(r, info.Env());
      }),
      SkObjectWrapInstanceMethod("setIsVolatile", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.setIsVolatile(Napi_val_as_bool(info[0]));
        return info.This();
      }),
      SkObjectWrapInstanceMethod("transform", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        self.transform(
          Napi_val_as_SkMatrix(info[0]),
          Napi_val_as_enum<SkApplyPerspectiveClip>(info[1], SkApplyPerspectiveClip::kYes)
        );
        return info.This();
      }),
      SkObjectWrapInstanceMethod("getBounds", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return SkRect_as_Napi_val(self.getBounds(), info.Env());
      }),
      SkObjectWrapInstanceMethod("getBounds", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        return SkRect_as_Napi_val(self.computeTightBounds(), info.Env());
      }),
      SkObjectWrapInstanceMethod("copy", [](SkPath &self, const Napi::CallbackInfo &info) -> Napi::Value {
        auto copy = SkPath(self);
        return NapiSkPath::New(copy, info.Env()).Value();
      })
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return func;
}

NapiSkPath::NapiSkPath(const Napi::CallbackInfo &info) : SkObjectWrap<NapiSkPath, SkPath>(info) {
	self = std::make_shared<SkPath>(SkPath());
}
