AudioTK
=======

Audio ToolKit is a set of audio filters. It is supposed to help assemble workflows for specific audio processing.

License
-------

Audio Toolkit is published under the BSD license.

Changelog
---------

0.3.0
* Enhanced the ScalarNewtonRaphson algorithm to accept different precision. Used a more relaxed one by default
* Fixed a bug in SD1OverdriveFilter
* Optimized array copies between filters

0.2.1
* Fix some issues with deploying ATK
* Tone stacks (Bassman and JCM800) with Python wrappers
* Updated filters C++ interface when then can process several channels at the same time

0.2.0
* SD1 tone circuit with Python wrappers
* Changed the main process method behavior, no needed to call reset each time
* Added methods to *PointerFilter to enable use in audio plugins as sinks/sources

0.1.1
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

0.1.0
* Butterworth low pass filter
* Python wrappers for Distortion filters

0.0.3
* Audio files input/output filters based on libsndfile
* Input and output filters based on pointers
* Python wrappers for Core filters
* Python wrappers for EQ filters
* Python wrappers for Tools filters

0.0.2
* Middle Side separator filter for stereo channels
* Sinus generator filter for Mock tests
* Frequency tester based on Accelerate FFT for Mock tests
* Second order EQ filters
* Decimation filters
* Oversampling filters
* Basic Wav input/output filters
* Overdrive filter implementation

0.0.1
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

