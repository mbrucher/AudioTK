  #include <ATK/IO/libsndfile/InSndFileFilter.h>
  #include <ATK/IO/libsndfile/OutSndFileFilter.h>
  #include <ATK/Tools/MSFilter.h>
  #include <ATK/Tools/VolumeFilter.h>
  
  int main(int argc, char** argv)
  {
    ATK::InSndFileFilter<std::int16_t> generator("stereofile.wav");
    assert(generator.get_nb_output_ports() == 2);
    
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
    volumefilter2.set_volume(.5); // Account for MS gain

    ATK::OutSndFileFilter<std::int16_t> sink("stereofile2.wav", 2);
    sink.set_input_sampling_rate(sampling_rate);
    sink.set_input_port(0, &volumefilter2, 0);
    sink.set_input_port(1, &volumefilter2, 1);
    
    sink.process(generator.get_frames());

    return 0;
  }

