Tutorials
=========

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
    ATK::InSndFileFilter<float> generator("stereofile.wav");
    assert(generator->get_nb_output_ports() == 2);
    
    int sampling_rate = generator.get_output_sampling_rate();
    
    ATK::MSFilter<float> msfilter;
    msfilter.set_input_sampling_rate(sampling_rate);
    msfilter.set_input_port(0, &generator, 0);
    msfilter.set_input_port(1, &generator, 1);

    ATK::VolumeFilter<float> volumefilter;
    volumefilter.set_input_sampling_rate(sampling_rate);
    volumefilter.set_input_port(0, &msfilter, 1);
    volumefilter.set_volume(.5);

    ATK::MSFilter<float> msmergefilter;
    msmergefilter.set_input_sampling_rate(sampling_rate);
    msmergefilter.set_input_port(0, &msfilter, 0);
    msmergefilter.set_input_port(1, &volumefilter, 0);
  
    return 0;
  }

Creating a Python pipeline
##########################

Now let's do the same with Python. The only exception is that the IO will be
handled by **scipy**.

.. code-block:: python
  :linenos:

  import numpy as np
  
  import ATK.Core
  import ATK.Tools
  
  