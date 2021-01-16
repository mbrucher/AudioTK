/**
 * \file FFT.h
 */

#ifndef ATK_UTILITY_FFT_H
#define ATK_UTILITY_FFT_H

#include <ATK/Utility/config.h>

#include <gsl/gsl>

#include <complex>
#include <cstdint>
#include <memory>
#include <vector>

namespace ATK
{
  /// An FFT class
  template<class DataType_>
  class ATK_UTILITY_EXPORT FFT
  {
  public:
    /// Builds the wrapper class
    FFT();
    /// Destructor
    ~FFT();
    
    FFT(const FFT&) = delete;
    FFT& operator=(const FFT&) = delete;

    /*!
     * @brief Sets a new size for the FFT and creates an associated plan for it
     * @ size is the new size of the plan
     */
    void set_size(gsl::index size);
    gsl::index get_size() const;
    /*!
     * @brief Processes a FFT from a real input array and stores it internally
     * @param input is the real input array of data to process
     * @param input_size is the size of the input array
     */
    void process(const DataType_* input, gsl::index input_size) const;
    /*!
    * @brief Processes a FFT from a real input to a complex output
    * @param input is the real input array of data to process
    * @param output is the complex output array
    * @param input_size is the size of both input and output arrays
    */
    void process_forward(const DataType_* input, std::complex<DataType_>* output, gsl::index input_size) const;
    /*!
    * @brief Processes an inverse FFT from a complex input to a real output
    * @param input is the complex input array of data to process
    * @param output is the real output array
    * @param input_size is the size of both input and output arrays
    */
    void process_backward(const std::complex<DataType_>* input, DataType_* output, gsl::index input_size) const;
    /*!
    * @brief Processes a FFT from a complex input array and stores it internally
    * @param input is the real input array of data to process
    * @param input_size is the size of the input array
    */
    void process(const std::complex<DataType_>* input, gsl::index input_size) const;
    /*!
    * @brief Processes a FFT from a complex input to a complex output
    * @param input is the real input array of data to process
    * @param output is the complex output array
    * @param input_size is the size of both input and output arrays
    */
    void process_forward(const std::complex<DataType_>* input, std::complex<DataType_>* output, gsl::index input_size) const;
    /*!
    * @brief Processes an inverse FFT from a complex input to a complex output
    * @param input is the complex input array of data to process
    * @param output is the real output array
    * @param input_size is the size of both input and output arrays
    */
    void process_backward(const std::complex<DataType_>* input, std::complex<DataType_>* output, gsl::index input_size) const;
    /*!
    * @brief Computes the amplitude of the resulting spectrum
    * @param amp is the output angle container
    */
    void get_amp(std::vector<DataType_>& amp) const;
    /*!
    * @brief Computes the angle of the resulting spectrum
    * @param angle is the output angle container
    */
    void get_angle(std::vector<DataType_>& angle) const;

  protected:
	  gsl::index size;

    class FFTImpl;
    std::unique_ptr<FFTImpl> impl;
  };
}

#endif
