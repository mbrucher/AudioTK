/**
 * \file config.h
 */

#ifndef ATK_IO_CONFIG_H
#define ATK_IO_CONFIG_H

#ifdef _MSC_VER
# ifdef BUILD_ATK_IO
#  define ATK_IO_EXPORT __declspec( dllexport )
# else
#  define ATK_IO_EXPORT __declspec( dllimport )
# endif
#else
#define ATK_IO_EXPORT
#endif

#endif
