#pragma once

#ifndef BUILD_STATIC
# if defined(TRANSFORM_LIB)
#  define TRANSFORM_EXPORT __declspec(dllexport)
# else
#  define TRANSFORM_EXPORT __declspec(dllimport)
# endif
#else
# define TRANSFORM_EXPORT
#endif
