/**
 * \file config.h
 */

#ifndef ATK_MOCK_CONFIG_H
#define ATK_MOCK_CONFIG_H

#ifdef _MSC_VER
# ifdef BUILD_ATK_MOCK
#  define ATK_MOCK_EXPORT __declspec( dllexport )
# else
#  define ATK_MOCK_EXPORT __declspec( dllimport )
# endif
#else
#define ATK_MOCK_EXPORT
#endif

#endif
