Documentation
=============

This is a small list of the different files and the implemented algorithms.

Core module
###########

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
###########

The *Mock* module is meant for testing purposes. It only contains sources and
sinks.

* **FFTCheckerFilter** will check the spectral content for a single port. Its behavior will depend on the backend FFT
* **SimpleSinusGeneratorFilter** generates a sinus signal at a specified frequency.
* **TriangleCheckerFilter** checks that the signal follows a triangle signal
* **TriangleGeneratorFilter** generates such a traingle signal.

IO module
#########

The *IO* module has facilities to read and write files.

* **InWavFilter** is a simple wav reader filter
* **OutWavFilter** is a simple wav writer filter

If you have access to **libsndfile** you should use these filters instead:

* **InSndFileFilter** is an advanced wav reader filter
* **OutSndFileFilter** is an advanced wav writer filter

Tools module
############

The *Tools* has two kind of classes: filters and general purpose classes.

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

The general purpose classes are:

* **Exp**, an exponential approcimation with a LUT and a 2-order Taylor expansion
* **FFT**, a class that exposes a FFT and iFFT (if compiled with FFTW)
* **SclarNewtonRaphson**, an optimization class for scalar ODEs

EQ module
#########

The *EQ* module contains a lot of different filter types.

* **BesselFilter** is an implementation of Bessel filters
* **ButterworthFilter** is an implementation of Butterworth filters
* **ChamberlinFilter** is an implementation of the Chamberlin state filter
* **Chebyshev1Filter** is an implementation of Chebyshev type 1 filters
* **Chebyshev2Filter** is an implementation of Chebyshev type 2 filters
* **LinkwitzRileyFilter** is an implementation of filters (low pass and high pass second orders) that can be summed together for a flat response
* **RobertBristowJohnsonFilter** is an implementation of RBJ second order filters
* **SecondOrderFilter** is an implementation of second order filters

* **SD1ToneFilter** is an implementation of the Boss SD1 pedal tone section
* **ToneStackFilter** is an implementation of a tone stack section found in several guitar amplifiers

* **CustomIIRFilter** helps designing custom IIR filters
* **CustomFIRFilter** helps designing custom FIR filters

* **IIRFilter** is the base class for IIR filters (Direct Form 1)

* **TimeVaryingSecondOrderFilter** is an implementation of time varying second order filters
* **TimeVaryingIIRFilter** is the base class for time varying IIR filters

Delay module
##############

The *Delay* module contains filters enabling delays construction.

* **FixedDelayLineFilter** is a FIR filter that delays the input by a fixed value
* **StereoUniversalFixedDelayLineFilter** is a stereo filter that implements two concurrent delay lines that can be mixed together
* **UniversalFixedDelayLineFilter** is a filter that delays the input by a fixed value. It can be parametrized  to be a FIR, IIR or all pass, or any combination
* **UniversalVariableDelayLineFilter** is a filter that delays the input by a variable value, on a second port. It can be parametrized  to be a FIR, IIR or all pass, or any combination
* **VariableDelayLineFilter** is a FIR filter that delays the input by a variable value, on a second port.

Dynamic module
##############

The *Dynamic* module contains filters enabling compressor construction.

* **AttackReleaseFilter** is a filter modulating an input with an Attack and a Release envelope specification
* **GainCompressorFilter** is a filter that changes an input signal (a gain) like a compressor does
* **GainExpanderFilter** is a filter that changes an input signal (a gain) like am expander/noise gate does
* **GainLimiterFilter** is a filter that changes an input signal (a gain) like a limiter does
* **PowerFilter** is a filter that outputs an AR(1)-filtered version of the squared input signal
* **RelativePowerFilter** is a filter that outputs the squared input signal divided by an AR(1)-filtered version of the squared input signal

Distortion module
#################

The *Distortion* module contains filters simulation distortion circuits.

* **SimpleOverdriveFilter** is a Newton-Raphson simulation of a diode clipper
* **SD1OverdriveFilter** is a Newton-Raphson simulation of the oversdrive section of the Boss SD1 pedal


Special module
##############

The *Special* module contains specific/special filters.

* **ConvolutionFilter** is a filter based on an FFT implementation with 0 latency
