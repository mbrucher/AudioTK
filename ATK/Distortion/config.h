/**
 * \file config.h
 */

#ifndef ATK_DISTORTION_CONFIG_H
#define ATK_DISTORTION_CONFIG_H

#ifdef _MSC_VER
# ifdef BUILD_ATK_DISTORTION
#  define ATK_DISTORTION_EXPORT __declspec( dllexport )
# else
#  define ATK_DISTORTION_EXPORT __declspec( dllimport )
# endif
#else
#define ATK_DISTORTION_EXPORT
#endif

#endif
