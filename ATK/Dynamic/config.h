/**
 * \file config.h
 */

#ifndef ATK_DYNAMIC_CONFIG_H
#define ATK_DYNAMIC_CONFIG_H

#ifdef _MSC_VER
# ifdef ATK_SHARED
#  ifdef BUILD_ATK_DYNAMIC
#   define ATK_DYNAMIC_EXPORT __declspec( dllexport )
#  else
#   define ATK_DYNAMIC_EXPORT __declspec( dllimport )
#  endif
# else
#  define ATK_DYNAMIC_EXPORT
# endif
#else
# define ATK_DYNAMIC_EXPORT
#endif

#endif
