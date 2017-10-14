# How to add AudioTK as JUCE modules

* Get an official relase version of ATK from github
* Copy modules/JUCE/ATK/config.h in the folder ATK and modify to select a FFT implementation
* In Projucer

  * Add to the extra compiler flag -I/path/to/ATK/folder -I/path/to/Boost/headers
  * Add also the path to Eigen if you selected it
  * Depending on the choice of FFT backend, add the compiler and linker extra flags
  * Add the modules you want to your project
