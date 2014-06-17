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
  
  