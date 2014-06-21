Documentation
=============

This is a small list of the different files and the implemented algorithms.

Core module
###########

The *Core* module doesn't implement fancy signal processing algorithm. It is only
meant to manage the pipeline.

* **BaseFilter** is the base filter of the pipeline. It is untyped.
* **TypedBaseFilter** is the class that you will actually use.
* **InPointerFilter** is a class without input ports that will be a source for new data
* **OutPointerFilter** is a class without output ports that will behave as a sink for the data

Mock module
###########

The *Mock* module is meant for testing purposes. It only contains sources and
sinks.

* **FFTCheckerFilter** will check the spectral content for a single port. Its behavior will depend on the backend FFT
* **SinusGeneratorFilter** generates a sinus signal at a specified frequency.
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

* **DecimationFilter** modifies the number of samples in the signal based on the ratio of input/output sampling rates
* **OversamplingFilter** is actually a set of oversampling filters that will multiply the number of samples from the input.
* **MiddleSidefilter** split a stereo signal in middle and side signal, according to the formulas **m=(l+r)/2** and **s=(l-r)/2**.
* **PanFilter** pans a single input signal on a stereo output
* **SumFilter** sums two input signals in one
* **VolumeFilter** multiplies input signal by a certain amount

The general purpose classes are:
* **Exp**, an exponential approcimation with a LUT and a 2-order Taylor expansion
* **FFT**, a class that exposes a FFT
* **SclarNewtonRaphson**, an optimization class for scalar ODEs

EQ module
#########

The *EQ* module contains a lot of different filter types.



Distortion module
#################

