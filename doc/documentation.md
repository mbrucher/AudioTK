Documentation
=============

This is a small list of the different files and the implemented algorithms.

Utility module
------------

This module contains a set of basic general purpose classes:

* **Exp**, an exponential approcimation with a LUT and a 2-order Taylor expansion
* **FFT**, a class that exposes a FFT and iFFT (if compiled with FFTW or IPP)
* **FlushToZero**, a RAII class to activate flush denormals to zero behavior on some platforms
* **ScalarNewtonRaphson**, an optimization class for scalar ODEs
* **VectorizedNewtonRaphson**, an optimization class for vector ODEs

Core module
-----------

The *Core* module doesn't implement fancy signal processing algorithm. It is only
meant to manage the pipeline.

* **BaseFilter** is the base filter of the pipeline. It is untyped
* **TypedBaseFilter** is the class that you will actually use.. The following methods can be implemented:

  * **process_impl** is the main (const) processing function
  * **setup** is called for parameter changes
  * **full_setup** is called for internal state reset

* **InPointerFilter** is a class without input ports that will be a source for new data
* **OutPointerFilter** is a class without output ports that will behave as a sink for the data
* **PipelineGlobalSinkFilter** is a special class without inputs or outputs, but that can process several sinks simultaneously (not possible without this special class)

Mock module
-----------

The *Mock* module is meant for testing purposes. It only contains sources and
sinks.

* **FFTCheckerFilter** will check the spectral content for a single port. Its behavior will depend on the backend FFT
* **SimpleSinusGeneratorFilter** generates a sinus signal at a specified frequency.
* **TriangleCheckerFilter** checks that the signal follows a triangle signal
* **TriangleGeneratorFilter** generates such a traingle signal.

IO module
---------

The *IO* module has facilities to read and write files.

* **InWavFilter** is a simple wav reader filter
* **OutWavFilter** is a simple wav writer filter

If you have access to **libsndfile** you should use these filters instead:

* **InSndFileFilter** is an advanced wav reader filter
* **OutSndFileFilter** is an advanced wav writer filter

Tools module
------------

The *Tools* contains simple but useful filters.

* **ApplyGainFilter** is a filter that multiplies two input signals together
* **CachedCosinusGeneratorFilter** is a filter that outputs a cached cosinus
* **CachedSinusGeneratorFilter** is a filter that outputs a cached sinus
* **DecimationFilter** modifies the number of samples in the signal based on the ratio of input/output sampling rates
* **DerivativeFilter** is a filter computing the derivative of an input signal
* **MaxFilter** is a filter computing the maximum of two input arrays
* **MiddleSidefilter** split a stereo signal in middle and side signal, according to the formulas **m=(l+r)/2** and **s=(l-r)/2**
* **OffsetVolumeFilter** multiplies input signal by a certain amount and adds a constant offset
* **OversamplingFilter** is actually a set of oversampling filters that will multiply the number of samples from the input
* **PanFilter** pans a single input signal on a stereo output
* **SinusGeneratorFilter** generates sinus and cosinus signals at a specified frequency
* **SumFilter** sums two input signals in one
* **VolumeFilter** multiplies input signal by a certain amount
* **WhitenoiseGeneratorFilter** is a filter that outputs a white noise

EQ module
---------

The *EQ* module contains a lot of different filter types.

* **ChamberlinFilter** is an implementation of the Chamberlin state filter

* **BesselCoefficients** is an implementation of Bessel coefficients
* **ButterworthCoefficients** is an implementation of Butterworth coefficients
* **Chebyshev1Coefficients** is an implementation of Chebyshev type 1 coefficients
* **Chebyshev2Coefficients** is an implementation of Chebyshev type 2 coefficients
* **LinkwitzRileyCoefficients** is an implementation of coefficients (low pass and high pass second orders) that can be summed together for a flat response
* **RobertBristowJohnsonCoefficients** is an implementation of RBJ second order coefficients
* **SecondOrderCoefficients** is an implementation of second order coefficients
* **SD1ToneCoefficients** is an implementation of the Boss SD1 pedal tone section
* **ToneStackCoefficients** is an implementation of a tone stack section found in several guitar amplifiers
* **CustomIIRFilter** helps designing custom IIR coefficients
* **IIRFilter** is an implementation of DF1 IIR filters for the previous coefficients

* **SecondOrderSVFCoefficients** is an implementation of second order SVF coefficients from cytomic
* **SecondOrderSVFFilter** is an implementation of second order SVF filters for the previous coefficients

* **RemezeBasedFilter** helps designing custom FIR filters from a template
* **CustomFIRFilter** helps designing custom FIR filters
* **FIRFilter** is an implementation of DF1 FIR filters for the previous coefficients

* **TimeVaryingSecondOrderCoefficients** is an implementation of time varying second order filters
* **TimeVaryingIIRFilter** is the base class for time varying IIR filters

* **TimeVaryingSecondOrderSVFCoefficients** is an implementation of second order SVF coefficients from cytomic for time-varying parameters
* **TimeVaryingSecondOrderSVFFilter** is an implementation of second order SVF filters for the previous coefficients

Delay module
------------

The *Delay* module contains filters enabling delays construction.

* **FixedDelayLineFilter** is a FIR filter that delays the input by a fixed value
* **HadamardFeedbackDelayNetworkFilter** is a Feedback Delay Network (FDN) with a Hadamard mixing matrix
* **MultipleUniversalDelayLineFilter** is a multiple channels filter that implements several concurrent delay lines that can be mixed together
* **UniversalFixedDelayLineFilter** is a filter that delays the input by a fixed value. It can be parametrized  to be a FIR, IIR or all pass, or any combination
* **UniversalVariableDelayLineFilter** is a filter that delays the input by a variable value, on a second port. It can be parametrized  to be a FIR, IIR or all pass, or any combination
* **VariableDelayLineFilter** is a FIR filter that delays the input by a variable value, on a second port.

Dynamic module
--------------

The *Dynamic* module contains filters enabling compressor construction.

* **AttackReleaseFilter** is a filter modulating an input with an Attack and a Release envelope specification
* **AttackReleaseHysteresisFilter** is a filter modulating an input with an Attack and a Release envelope specification and a hysteresis mode
* **GainCompressorFilter** is a filter that changes an input signal (a gain) like a compressor does
* **GainExpanderFilter** is a filter that changes an input signal (a gain) like an expander/noise gate does
* **GainLimiterFilter** is a filter that changes an input signal (a gain) like a limiter does
* **GainSwellFilter** is a filter that changes an input signal (a gain) like aan auto swell does
* **PowerFilter** is a filter that outputs an AR(1)-filtered version of the squared input signal
* **RelativePowerFilter** is a filter that outputs the squared input signal divided by an AR(1)-filtered version of the squared input signal
* **GainColoredCompressorFilter** is a filter that changes an input signal (a gain) like a compressor does with an additional color component
* **GainColoredExpanderFilter** is a filter that changes an input signal (a gain) like am expander/noise gate does with an additional color component
* **GainMaxExpanderFilter** is a filter that changes an input signal (a gain) like am expander/noise gate does with a maximum gain reduction

Distortion module
-----------------

The *Distortion* module contains filters simulation distortion circuits.

* **DiodeClipperFilter** is a Newton-Raphson simulation of a diode clipper
* **SimpleOverdriveFilter** is a Newton-Raphson simulation of another diode clipper
* **SD1OverdriveFilter** is a Newton-Raphson simulation of the oversdrive section of the Boss SD1 pedal
* **TS9OverdriveFilter** is a Newton-Raphson simulation of the oversdrive section of the Ibanez Tube Screamer/TS9/TS808 pedal

Reverberation module
--------------------

The *Reverberation* module contains reverberation specific filters

* **AllPassReverbFilter** is the simplest reverb filter
* **LowPassReverbFilter** adds a low pass filter to *AllPassFilter*

Special module
--------------

The *Special* module contains specific/special filters.

* **ConvolutionFilter** is a filter based on an FFT implementation with 0 latency

Preamplification module
-----------------------

The *Preamplification* module contains filters that simulate preamplifiers.

* **EnhancedKorenFunction** is a model of the triode transfer functions based on a model by Ivan Cohen
* **KorenFunction** is a model of the triode transfer functions based on a Koren model
* **LeachFunction** is a model of the triode transfer functions based on a Leach model
* **MunroPiazzaFunction** is a model of the triode transfer functions based on a Munro-Piazza model
* **DempwolfFunction** is a model of the triode transfer functions based on a Dempwolf model
* **TransistorClassAFilter** is a solid state class A filter, inversing the input signal
* **FollowerTransistorClassAFilter** is a solid state class A filter, not inversing the input signal
* **TriodeFilter** is a triode based filter
* **Triode2Filter** is a triode based filter with a grid-plate capacitor

Adaptive module
---------------

The *Adaptive* module contains filters that evolve based on their input.

* **LMSFilter** is a filter based on the Least Mean Square algorithm (Haykin)
* **BlockLMSFilter** is a filter based on the block variant of the Least Mean Square algorithm (Haykin)
* **RLSFilter** is a filter based on the Recursive Least Square algorithm (Haykin)
