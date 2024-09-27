#pragma once

#define CL_STRINGIFY_EVAL(x) #x
#define CL_CONCAT_EVAL(l, r) l##r

#define CL_STRINGIFY(x) CL_STRINGIFY_EVAL(x)
#define CL_CONCAT(l, r) CL_CONCAT_EVAL(l, r)

#define CL_BIT(x) (1 << x)

// For ECS Components
#define CL_COMPONENT_ID(id) static const char* GetCompTypeId() { return id; } const char* GetCompId() const { return GetCompTypeId(); }

#define CL_BIND_METHOD_ON_OBJECT_ON_CLASS(pObject, classToUse, method) [this](auto&&... args) -> decltype(auto) { return pObject->classToUse::method(std::forward<decltype(args)>(args)...); }
#define CL_BIND_METHOD_ON_OBJECT(pObject, method) [this](auto&&... args) -> decltype(auto) { return pObject->method(std::forward<decltype(args)>(args)...); }

#define CL_BIND_METHOD_OF_CLASS(classToUse, method) CL_BIND_METHOD_ON_OBJECT_ON_CLASS(this, classToUse, method)
#define CL_BIND_METHOD(method)                      CL_BIND_METHOD_ON_OBJECT(this, method)
