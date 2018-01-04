/**
 * \file config.h
 */

#ifndef ATK_CONFIG_H
#define ATK_CONFIG_H

// Set to activate instrumented profiling (stdout)
#define ATK_PROFILING 0

// Set if you want to use filters using Eigen
#define ATK_EIGEN 0

// Set FFTW or IPP if you want to use FFT capabilities, set both to 0 otherwise
#define ATK_USE_FFTW 0
#ifndef ATK_NO_FFT
#define ATK_USE_IPP 1
#else
#define ATK_USE_IPP 0
#endif

#define ATK_USE_SIMD 0

// Set to 1 if you want to use TBB thread pool in ATK
#define ATK_USE_THREADPOOL 0

// DO NOT TOUCH THESE DEFINITIONS
#if defined __INTEL_COMPILER
# define ATK_RESTRICT restrict
# define ATK_VECTORIZE __pragma(simd)
# define ATK_VECTORIZE_REMAINDER __pragma(simd vecremainder)
#elif defined _MSC_VER
# define ATK_RESTRICT __restrict
# define ATK_VECTORIZE
# define ATK_VECTORIZE_REMAINDER
#elif defined __GNUC__
# define ATK_RESTRICT __restrict__
# define ATK_VECTORIZE
# define ATK_VECTORIZE_REMAINDER
#else
# define ATK_RESTRICT
# define ATK_VECTORIZE
# define ATK_VECTORIZE_REMAINDER
#endif


#endif
