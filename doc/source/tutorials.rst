Tutorials
=========

Audio Toolkit is about creating pipelines. Each filter offers a number of input
ports and another number of output ports. All inputs have to be connected to
another filter, and then the pipeline is used by calling **process**.

Creating a basic pipeline
#########################

Let's create a simple pipeline. We will start by opening a file (stereo file),
split the stereo channels between middle and side tracks, divide the volume
of the side one by 2, combine them again to stereo channels, and finally the
result is saved to another stereo file.

.. code-block:: cpp
  :linenos:
  
  #include <ATK/IO/libsndfile/InSndFileFilter.h>
  #include <ATK/IO/libsndfile/OutSndFileFilter.h>
  #include <ATK/Tools/MSFilter.h>
  #include <ATK/Tools/VolumeFilter.h>
  
  int main(int argc, char** argv)
  {
    ATK::InSndFileFilter<std::int16_t> generator("stereofile.wav");
    assert(generator->get_nb_output_ports() == 2);
    
    int sampling_rate = generator.get_output_sampling_rate();
    
    ATK::MiddleSideFilter<float> msfilter;
    msfilter.set_input_sampling_rate(sampling_rate);
    msfilter.set_input_port(0, &generator, 0);
    msfilter.set_input_port(1, &generator, 1);

    ATK::VolumeFilter<float> volumefilter;
    volumefilter.set_input_sampling_rate(sampling_rate);
    volumefilter.set_input_port(0, &msfilter, 1);
    volumefilter.set_volume(.5);

    ATK::MiddleSideFilter<float> msmergefilter;
    msmergefilter.set_input_sampling_rate(sampling_rate);
    msmergefilter.set_input_port(0, &msfilter, 0);
    msmergefilter.set_input_port(1, &volumefilter, 0);
  
    ATK::VolumeFilter<float> volumefilter2(2);
    volumefilter2.set_input_sampling_rate(sampling_rate);
    volumefilter2.set_input_port(0, &msmergefilter, 0);
    volumefilter2.set_input_port(1, &msmergefilter, 1);
    volumefilter2.set_volume(2);

    ATK::OutSndFileFilter<std::int16_t> sink("stereofile2.wav", 2);
    sink.set_input_sampling_rate(sampling_rate);
    sink.set_input_port(0, &volumefilter2, 0);
    sink.set_input_port(1, &volumefilter2, 1);
    
    sink.process(generator.get_frames());

    return 0;
  }

Creating a Python pipeline
##########################

Now let's do something similar with Python. The only exception is that the IO
will be handled by **numpy**.

.. code-block:: python
  :linenos:

  import numpy as np
  from scipy.io import wavfile
    
  from ATK.Core import Int16InPointerFilter, Int16OutPointerFilter
  from ATK.Tools import FloatMiddleSideFilter, FloatVolumeFilter
    
  sampling_rate, data = wavfile.read("stereofile.wav")
    
  infilter = Int16InPointerFilter(data, True)
  infilter.set_output_sampling_rate(sampling_rate)
    
  print infilter.get_nb_output_ports()
  assert infilter.get_nb_output_ports() == 2
    
  msfilter = FloatMiddleSideFilter()
  msfilter.set_input_sampling_rate(sampling_rate)
  msfilter.set_input_port(0, infilter, 0)
  msfilter.set_input_port(1, infilter, 1)
    
  volumefilter = FloatVolumeFilter(1)
  volumefilter.set_input_sampling_rate(sampling_rate)
  volumefilter.set_input_port(0, msfilter, 1)
  volumefilter.set_volume(.5)
    
  msmergefilter = FloatMiddleSideFilter()
  msmergefilter.set_input_sampling_rate(sampling_rate)
  msmergefilter.set_input_port(0, msfilter, 0)
  msmergefilter.set_input_port(1, volumefilter, 0)
    
  volumefilter2 = FloatVolumeFilter(2)
  volumefilter2.set_input_sampling_rate(sampling_rate)
  volumefilter2.set_input_port(0, msmergefilter, 0)
  volumefilter2.set_input_port(1, msmergefilter, 1)
  volumefilter2.set_volume(2)
    
  outdata = np.zeros(data.shape, dtype=np.int16)
  outfilter = Int16OutPointerFilter(outdata, True)
  outfilter.set_input_sampling_rate(sampling_rate)
  outfilter.set_input_port(0, volumefilter2, 0)
  outfilter.set_input_port(1, volumefilter2, 1)
    
  outfilter.process(len(data))
  wavfile.write("stereofile3.wav", sampling_rate, outdata)
