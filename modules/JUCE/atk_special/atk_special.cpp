/*
 ==============================================================================
 
 This file is part of the ATK library.
 Copyright (c) 2017 - Matthieu Brucher
 
 ATK is an open source library subject to the BSD licnse.
 
 ==============================================================================
 */

#include "atk_special.h"

#if (ATK_USE_FFTW == 1) or (ATK_USE_IPP == 1)
# include <ATK/Special/ConvolutionFilter.cpp>
#endif
