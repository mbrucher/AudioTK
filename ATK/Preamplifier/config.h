/**
 * \file config.h
 */

#ifndef ATK_PREAMPLIFIER_CONFIG_H
#define ATK_PREAMPLIFIER_CONFIG_H

#ifdef _MSC_VER
#pragma warning( disable : 4275 4251 )
# ifdef ATK_SHARED
#  ifdef BUILD_ATK_PREAMPLIFIER
#   define ATK_PREAMPLIFIER_EXPORT __declspec( dllexport )
#  else
#   define ATK_PREAMPLIFIER_EXPORT __declspec( dllimport )
#  endif
# else
#  define ATK_PREAMPLIFIER_EXPORT
# endif
#else
# define ATK_PREAMPLIFIER_EXPORT
#endif

#endif
