/**
 * \file config.h
 */

#ifndef ATK_EQ_CONFIG_H
#define ATK_EQ_CONFIG_H

#ifdef _MSC_VER
# ifdef ATK_SHARED
#  ifdef BUILD_ATK_EQ
#   define ATK_EQ_EXPORT __declspec( dllexport )
#  else
#   define ATK_EQ_EXPORT __declspec( dllimport )
#  endif
# else
#  define ATK_EQ_EXPORT
# endif
#else
#define ATK_EQ_EXPORT
#endif

#endif
