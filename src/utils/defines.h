#pragma once

#define private static
#define override // empty (used for readability)
#define abstract // empty (used for readability)

#define typedef(type_name) typedef struct __##type_name* type_name
#define type(type_name, ...) \
    typedef(type_name); \
    type_name construct(type_name, __VA_ARGS__); \
    struct __##type_name
#define sizeoftype(type_name) sizeof(struct __##type_name)

#define fcall(obj, function_name, ...) obj->function_name(__VA_ARGS__)
#define mcall(obj, method_name, ...) fcall(obj, method_name, obj, __VA_ARGS__)
#define mcall0(obj, method_name) fcall(obj, method_name, obj)

#define function(function_name, ...) (*function_name)(__VA_ARGS__)
#define method(type_name, method_name, ...) function(method_name, type_name obj, __VA_ARGS__)
#define method0(type_name, method_name) function(method_name, type_name obj)

#define get_impl(type_name, function_name) impl_##type_name##_##function_name
#define set_impl(type_name, obj, function_name) obj->function_name = get_impl(type_name, function_name)
#define impl_function(type_name, function_name, ...) get_impl(type_name, function_name)(__VA_ARGS__)
#define impl_method(type_name, method_name, ...) impl_function(type_name, method_name, type_name obj, __VA_ARGS__)
#define impl_method0(type_name, method_name) impl_function(type_name, method_name, type_name obj)

#define construct(type_name, ...) new_##type_name(__VA_ARGS__)
#define constructor(type_name, ...) type_name construct(type_name, __VA_ARGS__)
#define new(type_name, ...) new_##type_name(__VA_ARGS__)

#define destruct(type_name) void method0(type_name, __destruct)
#define destructor(type_name) private void impl_method0(type_name, __destruct)
#define delete(obj) \
    mcall0(obj, __destruct); \
    free(obj)
