/**
 * \file config.h
 */

#ifndef ATK_TOOLS_CONFIG_H
#define ATK_TOOLS_CONFIG_H

#ifdef _MSC_VER
# ifdef ATK_SHARED
#  ifdef BUILD_ATK_TOOLS
#   define ATK_TOOLS_EXPORT __declspec( dllexport )
#  else
#   define ATK_TOOLS_EXPORT __declspec( dllimport )
# endif
# else
#  define ATK_TOOLS_EXPORT
# endif
#else
# define ATK_TOOLS_EXPORT
#endif

#endif
