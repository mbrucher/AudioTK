/**
 * \file config.h
 */

#ifndef ATK_UTILITY_CONFIG_H
#define ATK_UTILITY_CONFIG_H

#ifdef _MSC_VER
# ifdef ATK_SHARED
#  ifdef BUILD_ATK_UTILITY
#   define ATK_UTILITY_EXPORT __declspec( dllexport )
#  else
#   define ATK_UTILITY_EXPORT __declspec( dllimport )
# endif
# else
#  define ATK_UTILITY_EXPORT
# endif
#else
# define ATK_UTILITY_EXPORT
#endif

#endif
