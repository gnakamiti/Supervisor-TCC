#ifndef _WIN_DEFS_H_
#define _WIN_DEFS_H_


#include <cmath>
#include <float.h>
#define isnan(x) ((x) != (x))
#define isinf(x) (!_finite(x))
#define fpu_error(x) (isinf(x) || isnan(x))


#ifndef NAN
        static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
        #define NAN (*(const float *) __nan)
#endif

#ifdef _MSC_VER
#ifndef INFINITY
union MSVC_FL
{
   unsigned __int8 Bytes[4];
   float Value;
};
static union MSVC_FL INFINITY_HACK = {{0x00, 0x00, 0x80, 0x7F}};
#define INFINITY (INFINITY_HACK.Value)
#endif
#endif

#endif
