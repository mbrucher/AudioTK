/**
 * \file config.h
 */

#ifndef ATK_REVERBERATION_CONFIG_H
#define ATK_REVERBERATION_CONFIG_H

#ifdef _MSC_VER
#pragma warning( disable : 4275 4251 )
# ifdef ATK_SHARED
#  ifdef BUILD_ATK_REVERBERATION
#   define ATK_REVERBERATION_EXPORT __declspec( dllexport )
#  else
#   define ATK_REVERBERATION_EXPORT __declspec( dllimport )
#  endif
# else
#  define ATK_REVERBERATION_EXPORT
# endif
#else
# define ATK_REVERBERATION_EXPORT
#endif

#endif
