#ifndef __khrplatform_h_
#define __khrplatform_h_ 1

/*
 * Khronos platform definitions shared by GLES, EGL, and related APIs.
 *
 * Keep this header compatible with the public khrplatform.h contract: it is
 * installed by meta-gl and may therefore be selected by system EGL headers in
 * the same translation unit.
 */

#include <stdint.h>
#include <stddef.h>

#ifndef KHRONOS_APICALL
#if defined(KHRONOS_STATIC)
#define KHRONOS_APICALL
#elif defined(_WIN32)
#define KHRONOS_APICALL __declspec(dllimport)
#elif defined(__ANDROID__)
#define KHRONOS_APICALL __attribute__((visibility("default")))
#else
#define KHRONOS_APICALL
#endif
#endif

#ifndef KHRONOS_APIENTRY
#if defined(_WIN32) && !defined(_WIN32_WCE)
#define KHRONOS_APIENTRY __stdcall
#else
#define KHRONOS_APIENTRY
#endif
#endif

#ifndef KHRONOS_APIPTR
#define KHRONOS_APIPTR KHRONOS_APIENTRY*
#endif

#ifndef KHRONOS_APIATTRIBUTES
#if defined(__ARMCC_2__)
#define KHRONOS_APIATTRIBUTES __softfp
#else
#define KHRONOS_APIATTRIBUTES
#endif
#endif

#define KHRONOS_SUPPORT_INT64 1
#define KHRONOS_SUPPORT_FLOAT 1

typedef int8_t      khronos_int8_t;
typedef uint8_t     khronos_uint8_t;
typedef int16_t     khronos_int16_t;
typedef uint16_t    khronos_uint16_t;
typedef int32_t     khronos_int32_t;
typedef uint32_t    khronos_uint32_t;
typedef int64_t     khronos_int64_t;
typedef uint64_t    khronos_uint64_t;
typedef intptr_t    khronos_intptr_t;
typedef uintptr_t   khronos_uintptr_t;
typedef ptrdiff_t   khronos_ssize_t;
typedef size_t      khronos_usize_t;
typedef float       khronos_float_t;

typedef khronos_uint64_t khronos_utime_nanoseconds_t;
typedef khronos_int64_t  khronos_stime_nanoseconds_t;

#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

typedef enum
{
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

#endif /* __khrplatform_h_ */
