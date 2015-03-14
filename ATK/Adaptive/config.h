/**
 * \file config.h
 */

#ifndef ATK_ADAPTIVE_CONFIG_H
#define ATK_ADAPTIVE_CONFIG_H

#ifdef _MSC_VER
# ifdef ATK_SHARED
#  ifdef BUILD_ATK_ADATIVE
#   define ATK_ADAPTIVE_EXPORT __declspec( dllexport )
#  else
#   define ATK_ADAPTIVE_EXPORT __declspec( dllimport )
#  endif
# else
#  define ATK_ADAPTIVE_EXPORT
# endif
#else
# define ATK_ADAPTIVE_EXPORT
#endif

#endif
