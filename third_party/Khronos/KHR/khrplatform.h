#ifndef __khrplatform_h_
#define __khrplatform_h_ 1

/* Minimal Khronos platform definitions required by the bundled GLES headers. */

#include <stdint.h>
#include <stddef.h>

#ifndef KHRONOS_APICALL
#define KHRONOS_APICALL
#endif

#ifndef KHRONOS_APIENTRY
#define KHRONOS_APIENTRY
#endif

#ifndef KHRONOS_APIPTR
#define KHRONOS_APIPTR KHRONOS_APIENTRY*
#endif

typedef int8_t      khronos_int8_t;
typedef uint8_t     khronos_uint8_t;
typedef int16_t     khronos_int16_t;
typedef uint16_t    khronos_uint16_t;
typedef int32_t     khronos_int32_t;
typedef uint32_t    khronos_uint32_t;
typedef int64_t     khronos_int64_t;
typedef uint64_t    khronos_uint64_t;
typedef intptr_t    khronos_intptr_t;
typedef ptrdiff_t   khronos_ssize_t;
typedef float       khronos_float_t;

#endif /* __khrplatform_h_ */
