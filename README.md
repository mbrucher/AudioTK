# AudioTK

[![Travis](https://travis-ci.org/mbrucher/AudioTK.svg?branch=master)](https://travis-ci.org/mbrucher/AudioTK)
[![Appveyor](https://ci.appveyor.com/api/projects/status/j6k8jkxk2ebwvvoe/branch/master?svg=true)](https://ci.appveyor.com/project/mbrucher/audiotk)
[![codecov](https://codecov.io/gh/mbrucher/AudioTK/branch/master/graph/badge.svg)](https://codecov.io/gh/mbrucher/AudioTK)
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

Audio ToolKit is a set of audio filters. It helps assembling workflows for specific audio processing workloads.

The audio workflow is split in independent components (without feedback loops) that consist of filters. 
Each filter has a set of synchronized input and output ports that can be connected together. All input 
ports must be connected, but not all output ports need to be.

Sampling rate can be independent between input and output ports, but input sampling rates are identical, 
and output sampling rates are also identical.


## License

Audio Toolkit is published under the BSD license.

## Changelog
### 2.2.3
- Increased test coverage and fix lots of small mistakes in the API

### 2.2.2
* Fix a TDF2 IIR filter bug when the state was not reinitialized, leading to unstabilities
* Fix a bug when delays were changed but not the underlying buffers, leading to buffer underflows
* Adding a new Broadcast filter (filling all SIMD vector lines with the same input value)
* Adding a new Reduce filter (summing all SIMD vector lines to the output value)

### 2.2.1
* Fix alignment issues in SIMD filters
* Fix SIMD EQ dispatcher export issues on Windows (too many possible filters!)
* Implemented relevant Tools SIMD filters

### 2.2.0
* Introduced SIMD filters with libsimdpp
* Refactored EQ filters to work with SIMD filters
* Added module files for JUCE Projucer

### 2.1.1
* Added a Gain Max Compressor filter with wrappers
* Added a dryrun call on BaseFilter to setup maximum sizes on a pipeline
* Added a IIR TDF2 (Transposed Direct Form 2) filter implementation (no Python wrappers for now)
* Fixed max gain reduction in the expanders to use 20 log10 instead of 10 log10 (as it is applied to the amplitude and not power)
* Fix a bug in OutCircularPointerFilter with offset handling
* Fix a bug in RIAA inverse filters

### 2.1.0
* Added a config file for CMake
* Rewrote the Python wrappers to use pybind11 instead of SWIG
* Added MuteSoloSumFilter to allow mute/solo operations on tracks with Python wrappers
* SumFilter can now sum multiple channels together
* Adding fourth order Linkwitz-Riley filters
* Adding a new circular buffer (for FFT plugins for instance)
* Added parameters for tube (inverters) filters definition
* Added Python wrappers in Travis-CI builds
* Added a modified implementation of the Munro-Piazza triode function to remove some artefacts

### 2.0.2
* Fix ARM compilation

### 2.0.1
* Turn set/get into properties when possible (Python wrapper)
* Enhanced Tools API (Audio ToolKit book)
* Added a Feedback Delay Netwrok filter (FDN) with Hadamard mixing matrix with Python wrappers
* Fixed MultipleUniversalFixedDelayLineFilter parameters

### 2.0.0
* Refactored fixed line delays (performance improvement)
* Allow new filters to have unconnected inputs (can only be changed inside a filter)
* Refactored the stereo universal delay line to allow more simultaneous channels (renamed to MultipleUniversalDelayLineFilter)
* ATK now allows complex-valued filters with filters to convert from real from/to complex
* Added a BlockLMSFilter with Python wrappers
* Added a LMSFilter with Python wrappers
* Added a RemezBasedCoefficients with Python wrappers to be used with FIRFilter to generate a FIR filter from a template
* Added a RLSFilter with Python wrappers
* Support for IPP as a FFT backend
* Refactored the API for global unsigned consistency

### 1.5.0
* Adding a follower class solid state preamplifier with Python wrappers
* Adding a Dempwolf model for tube filters with Python wrappers
* Adding a Munro-Piazza model for tube filters with Python wrappers
* Optimized distortion and preamplifier filters by using fmath exp calls

### 1.4.1
* Vectorized x4 the IIR part of the IIR filter
* Vectorized delay filters
* Fixed bug in gain filters

### 1.4.0
* Added a LeachTriodeFunction for simpler tube filters
* Added Intel Compiler support
* Vectorized FIR part of IIRFilter
* Refactored gain filters to enable vectorization
* 256 bits alignment of internal arrays (with or without delay, the first element to process will be 256-bits aligned)

### 1.3.2
* Starting support for ARM platforms (not optimized yet)
* Added a FlushToZero class used in Python interface so that it is activated when process() is called

### 1.3.1
* Added a 1 - input filter with Python wrappers
* Removed the old SD1 filter, replaced it definitely with the SVF version
* Added a TS9 overdrive filter (SD1 without the asymmetry) with Python wrappers
* Added a Tube2Filter with wrappers, adding the plate-grid capacitor in the equations, stabilizing them better (requires Eigen)

### 1.3.0
* Added a family of triode preamplification filters with Python wrappers (requires Eigen)
* Added a class A NPN preamplification filter with Python wrappers (requires Eigen)
* Added a buffer filter with Python wrappers
* Added a new Diode clipper with trapezoidal rule with Python wrappers
* Added a new version of the SD1 distortion with ZDF mode and Python wrappers

### 1.2.0
* Added SecondOrderSVF filters from cytomic with Python wrappers
* Implemented a LowPassReverbFilter with Python wrappers
* Added Python wrappers to AllPassReverbFilter
* Distortion filters optimization
* Bunch of fixes (Linux compil, calls...)

### 1.1.0
* Fix a really nasty bug when changing processing sizes
* Implemented a basic AllPassFilter (algorithmic reverb)

### 1.0.0
* Split ATKTools in Tools and Utility modules
* Allow threaded computation in pipelines
* Added a latency computation

### 0.7.2
* Added an AttackReleaseHysteresis filter with Python wrapper
* Added a GainMaxColoredExpander filter with Python wrapper
* Removed the gain fractional filters
* Added a GainSwellFilter with Python wrapper

### 0.7.1
* Added additional second order filters with Python wrappers (RBJ coefficients)
* Added GainColoredCompressorFilter and GainColoredExpanderFilter with Python wrappers

### 0.7.0
* Fixed the FFT implementation
* Added a fast zero latency convolution filter with tests and comparison with a basic FIR implementation
* Enhanced global framework performance (Core, EQ, Tools)
* Enhanced dynamic gain filters behavior by switching between LUT or direct computation dependening on the LUT state

### 0.6.0
* Added override and final keywords in virtual calls
* Changed the API so that process_impl is now const
* Exposed full_setup to the user (direct reset of the internal state, already called when changing sample rate)
* Added LinkWitz-Riley second order low and high path filters
* Fix resetting the internal state of all delays by using full_setup
* Added a CustomFIRFilter with Python wrapper

### 0.5.1
* Added time-varying IIR filters (variable frequency, coded as transposed direct form II)
* Added second order time varying filter implementations
* Added a RelativePowerFilter with Python wrappers
* Added a DerivativeFilter with Python wrappers
* Added Python wrappers for the InWavFilter
* Fixed some warnings during compilation

### 0.5.0
* Renamed slope attribute to ratio for Gain Compressor and Expander Filters
* Renamed the Chamberlin filter
* Added a StereoUniversalFixedDelayLineFilter that can make mix two channels together with different delay for each channel with Python wrappers
* Added a GainLimiterFilter (maximum ratio) with Python wrappers
* Added a MaxFilter with Python wrappers
* Added a DryWetFilter with Python wrappers

### 0.4.2
* Bug fixes

### 0.4.1
* Added a PipelineGlobalSinkFilter with Python wrapper
* Changed the MiddleSideFilter scale (no more dividing by 2 in the code)
* Additional tools additions (cos generator, offset+volume filter)
* Added a second order all pass filter with Python wrappers

### 0.4.0
* Added a white noise generator filter
* Fixed the delay line filters
* Fixed second order EQ Python wrappers

### 0.3.2
* Added a fixed delay line filter (FIR filter) with Python wrappers
* Added an universal fixed delay line filter (FIR, IIR and all-pass filter + combinations) with Python wrappers
* Added variable delay filters (delay is given on an additional port)

### 0.3.1
* Adding compressor elements and the Python wrappers
* Fixed Python wrappers by adding default number of port/channels
* Added restrict pointer support in all filter that can benefit from this

### 0.3.0
* Enhanced the ScalarNewtonRaphson algorithm to accept different precision. Used a more relaxed one by default
* Fixed a bug in SD1OverdriveFilter
* Optimized array copies between filters
* Added documentation

### 0.2.1
* Fix some issues with deploying ATK
* Tone stacks (Bassman and JCM800) with Python wrappers
* Updated filters C++ interface when then can process several channels at the same time

### 0.2.0
* SD1 tone circuit with Python wrappers
* Changed the main process method behavior, no needed to call reset each time
* Added methods to *PointerFilter to enable use in audio plugins as sinks/sources

### 0.1.1
* Padding/delay support
* FFTW support
* Profiling facilities
* Butterworth high pass, band pass and band stop filters
* Python wrappers for all Butterworth filters
* Bessel filters
* Python wrappers for all Bessel filters
* Chebyshev type 1 and 2 filters
* Python wrappers for all Chebyshev type 1 and 2 filters
* SD1 overdrive filter and Python wrappers

### 0.1.0
* Butterworth low pass filter
* Python wrappers for Distortion filters

### 0.0.3
* Audio files input/output filters based on libsndfile
* Input and output filters based on pointers
* Python wrappers for Core filters
* Python wrappers for EQ filters
* Python wrappers for Tools filters

### 0.0.2
* Middle Side separator filter for stereo channels
* Sinus generator filter for Mock tests
* Frequency tester based on Accelerate FFT for Mock tests
* Second order EQ filters
* Decimation filters
* Oversampling filters
* Basic Wav input/output filters
* Overdrive filter implementation

### 0.0.1
* Base filter with automatic type conversion to help assemble plugins with different processing types
* Mock filters for generating and checking some signals
* Pan filters with different laws
  * 0 dB center, sin/cos taper, constant power
  * -3 dB center, sin/cos taper, constant power
  * 0 dB center, square-root taper, constant power
  * -3 dB center, square-root taper, constant power
  * -6 dB center, linear taper
  * 0 dB center, balance control
* Volume filter, with gain input in dB and no dB
* Sum filter

## Install

### Requirements

* C++11 compiler
* CMake
* Boost 1.60
* FFT library (for some filters like the fast convolution filter)
  * FFTW
  * IPP (default)
* Python with numpy (for Python support)
* Eigen (for some complex modules)
* libsndfile (for sound file I/O)

### Procedure

* Start CMake
* Configure your options
* Run make, Visual Studio or XCode

## Usage

### CMake

By setting ATK_DIR, you can import a package with FIND_PACKAGE(ATK) and components are supported. ATK_INCLUDE_DIRS and ATK_LIBRARIES are the main variables set, but each individual library can also be linked against instead of all of them.

Shared libraries and static libraries are different components (for instance Core and Core_static), by not setting components, all the shared libraries available will be stored in ATK_LIBRARIES. 

## Known Issues

* If a plugin uses the same buffers for input and output and the pipeline has two subgraphs, one from left to right and one to left (for instance), then they are processed in order and the second graph would use the result of the first branch. To fix this, add a BufferFilter just after the input filter so that they are all buffered and copied to an intermediate buffer when the first one is used. It adds a copy, so only use this fix when you have this specific configuration for a pipeline.

## Additional included dependencies

* fmath from herumi (http://homepage1.nifty.com/herumi/)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=EJFNHPJ5TR6F6)

