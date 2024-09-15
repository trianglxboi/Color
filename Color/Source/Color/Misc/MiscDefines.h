#pragma once

#define CL_STRINGIFY_EVAL(x) #x
#define CL_CONCAT_EVAL(l, r) l##r

#define CL_STRINGIFY(x) CL_STRINGIFY_EVAL(x)
#define CL_CONCAT(l, r) CL_CONCAT_EVAL(l, r)

#define CL_BIT(x) (1 << x)

// For ECS Components
#define CL_COMPONENT_ID(id) static const char* GetCompTypeId() { return id; } const char* GetCompId() const { return GetCompTypeId(); }
