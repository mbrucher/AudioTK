/**
 * \file BesselFilter.hxx
 */

#include "BesselFilter.h"
#include <ATK/EQ/helpers.h>

#include <boost/math/constants/constants.hpp>

namespace BesselUtilities
{
  template<typename DataType>
  void create_bessel_analog_coefficients(int order, EQUtilities::ZPK<DataType>& zpk)
  {
    zpk.k = 1;
    auto& z = zpk.z;
    auto& p = zpk.p;
    z.clear(); // no zeros for this filter type
    p.clear();
    switch (order)
    {
      case 0:
        break;
      case 1:
        p.push_back(1);
        break;
      case 2:
        p.push_back(std::complex<DataType>(-.8660254037844386467637229, .4999999999999999999999996));
        p.push_back(std::complex<DataType>(-.8660254037844386467637229, -.4999999999999999999999996));
        break;
      case 3:
        p.push_back(std::complex<DataType>(-.9416000265332067855971980, 0));
        p.push_back(std::complex<DataType>(-.7456403858480766441810907, .7113666249728352680992154));
        p.push_back(std::complex<DataType>(-.7456403858480766441810907, -.7113666249728352680992154));
        break;
      case 4:
        p.push_back(std::complex<DataType>(-.6572111716718829545787781, .8301614350048733772399715));
        p.push_back(std::complex<DataType>(-.6572111716718829545787781, -.8301614350048733772399715));
        p.push_back(std::complex<DataType>(-.9047587967882449459642637, .2709187330038746636700923));
        p.push_back(std::complex<DataType>(-.9047587967882449459642637, -.2709187330038746636700923));
        break;
      case 5:
        p.push_back(std::complex<DataType>(-.9264420773877602247196260, 0));
        p.push_back(std::complex<DataType>(-.8515536193688395541722677, .4427174639443327209850002));
        p.push_back(std::complex<DataType>(-.8515536193688395541722677, -.4427174639443327209850002));
        p.push_back(std::complex<DataType>(-.5905759446119191779319432, .9072067564574549539291747));
        p.push_back(std::complex<DataType>(-.5905759446119191779319432, -.9072067564574549539291747));
        break;
      case 6:
        p.push_back(std::complex<DataType>(-.9093906830472271808050953, .1856964396793046769246397));
        p.push_back(std::complex<DataType>(-.9093906830472271808050953, -.1856964396793046769246397));
        p.push_back(std::complex<DataType>(-.7996541858328288520243325, .5621717346937317988594118));
        p.push_back(std::complex<DataType>(-.7996541858328288520243325, -.5621717346937317988594118));
        p.push_back(std::complex<DataType>(-.5385526816693109683073792, .9616876881954277199245657));
        p.push_back(std::complex<DataType>(-.5385526816693109683073792, -.9616876881954277199245657));
        break;
      case 7:
        p.push_back(std::complex<DataType>(-.9194871556490290014311619, 0));
        p.push_back(std::complex<DataType>(-.8800029341523374639772340, .3216652762307739398381830));
        p.push_back(std::complex<DataType>(-.8800029341523374639772340, -.3216652762307739398381830));
        p.push_back(std::complex<DataType>(-.7527355434093214462291616, .6504696305522550699212995));
        p.push_back(std::complex<DataType>(-.7527355434093214462291616, -.6504696305522550699212995));
        p.push_back(std::complex<DataType>(-.4966917256672316755024763, 1.002508508454420401230220));
        p.push_back(std::complex<DataType>(-.4966917256672316755024763, -1.002508508454420401230220));
        break;
      case 8:
        p.push_back(std::complex<DataType>(-.9096831546652910216327629, .1412437976671422927888150));
        p.push_back(std::complex<DataType>(-.9096831546652910216327629, -.1412437976671422927888150));
        p.push_back(std::complex<DataType>(-.8473250802359334320103023, .4259017538272934994996429));
        p.push_back(std::complex<DataType>(-.8473250802359334320103023, -.4259017538272934994996429));
        p.push_back(std::complex<DataType>(-.7111381808485399250796172, .7186517314108401705762571));
        p.push_back(std::complex<DataType>(-.7111381808485399250796172, -.7186517314108401705762571));
        p.push_back(std::complex<DataType>(-.4621740412532122027072175, 1.034388681126901058116589));
        p.push_back(std::complex<DataType>(-.4621740412532122027072175, -1.034388681126901058116589));
        break;
      case 9:
        p.push_back(std::complex<DataType>(-.9154957797499037686769223, 0));
        p.push_back(std::complex<DataType>(-.8911217017079759323183848, .2526580934582164192308115));
        p.push_back(std::complex<DataType>(-.8911217017079759323183848, -.2526580934582164192308115));
        p.push_back(std::complex<DataType>(-.8148021112269012975514135, .5085815689631499483745341));
        p.push_back(std::complex<DataType>(-.8148021112269012975514135, -.5085815689631499483745341));
        p.push_back(std::complex<DataType>(-.6743622686854761980403401, .7730546212691183706919682));
        p.push_back(std::complex<DataType>(-.6743622686854761980403401, -.7730546212691183706919682));
        p.push_back(std::complex<DataType>(-.4331415561553618854685942, 1.060073670135929666774323));
        p.push_back(std::complex<DataType>(-.4331415561553618854685942, -1.060073670135929666774323));
        break;
      case 10:
        p.push_back(std::complex<DataType>(-.9091347320900502436826431, .1139583137335511169927714));
        p.push_back(std::complex<DataType>(-.9091347320900502436826431, -.1139583137335511169927714));
        p.push_back(std::complex<DataType>(-.8688459641284764527921864, .3430008233766309973110589));
        p.push_back(std::complex<DataType>(-.8688459641284764527921864, -.3430008233766309973110589));
        p.push_back(std::complex<DataType>(-.7837694413101441082655890, .5759147538499947070009852));
        p.push_back(std::complex<DataType>(-.7837694413101441082655890, -.5759147538499947070009852));
        p.push_back(std::complex<DataType>(-.6417513866988316136190854, .8175836167191017226233947));
        p.push_back(std::complex<DataType>(-.6417513866988316136190854, -.8175836167191017226233947));
        p.push_back(std::complex<DataType>(-.4083220732868861566219785, 1.081274842819124562037210));
        p.push_back(std::complex<DataType>(-.4083220732868861566219785, -1.081274842819124562037210));
        break;
      case 11:
        p.push_back(std::complex<DataType>(-.9129067244518981934637318, 0));
        p.push_back(std::complex<DataType>(-.8963656705721166099815744, .2080480375071031919692341));
        p.push_back(std::complex<DataType>(-.8963656705721166099815744, -.2080480375071031919692341));
        p.push_back(std::complex<DataType>(-.8453044014712962954184557, .4178696917801248292797448));
        p.push_back(std::complex<DataType>(-.8453044014712962954184557, -.4178696917801248292797448));
        p.push_back(std::complex<DataType>(-.7546938934722303128102142, .6319150050721846494520941));
        p.push_back(std::complex<DataType>(-.7546938934722303128102142, -.6319150050721846494520941));
        p.push_back(std::complex<DataType>(-.6126871554915194054182909, .8547813893314764631518509));
        p.push_back(std::complex<DataType>(-.6126871554915194054182909, -.8547813893314764631518509));
        p.push_back(std::complex<DataType>(-.3868149510055090879155425, 1.099117466763120928733632));
        p.push_back(std::complex<DataType>(-.3868149510055090879155425, -1.099117466763120928733632));
        break;
      case 12:
        p.push_back(std::complex<DataType>(-.9084478234140682638817772, 95506365213450398415258360.0e-27));
        p.push_back(std::complex<DataType>(-.9084478234140682638817772, -95506365213450398415258360.0e-27));
        p.push_back(std::complex<DataType>(-.8802534342016826507901575, .2871779503524226723615457));
        p.push_back(std::complex<DataType>(-.8802534342016826507901575, -.2871779503524226723615457));
        p.push_back(std::complex<DataType>(-.8217296939939077285792834, .4810212115100676440620548));
        p.push_back(std::complex<DataType>(-.8217296939939077285792834, -.4810212115100676440620548));
        p.push_back(std::complex<DataType>(-.7276681615395159454547013, .6792961178764694160048987));
        p.push_back(std::complex<DataType>(-.7276681615395159454547013, -.6792961178764694160048987));
        p.push_back(std::complex<DataType>(-.5866369321861477207528215, .8863772751320727026622149));
        p.push_back(std::complex<DataType>(-.5866369321861477207528215, -.8863772751320727026622149));
        p.push_back(std::complex<DataType>(-.3679640085526312839425808, 1.114373575641546257595657));
        p.push_back(std::complex<DataType>(-.3679640085526312839425808, -1.114373575641546257595657));
        break;
      case 13:
        p.push_back(std::complex<DataType>(-.9110914665984182781070663, 0));
        p.push_back(std::complex<DataType>(-.8991314665475196220910718, .1768342956161043620980863));
        p.push_back(std::complex<DataType>(-.8991314665475196220910718, -.1768342956161043620980863));
        p.push_back(std::complex<DataType>(-.8625094198260548711573628, .3547413731172988997754038));
        p.push_back(std::complex<DataType>(-.8625094198260548711573628, -.3547413731172988997754038));
        p.push_back(std::complex<DataType>(-.7987460692470972510394686, .5350752120696801938272504));
        p.push_back(std::complex<DataType>(-.7987460692470972510394686, -.5350752120696801938272504));
        p.push_back(std::complex<DataType>(-.7026234675721275653944062, .7199611890171304131266374));
        p.push_back(std::complex<DataType>(-.7026234675721275653944062, -.7199611890171304131266374));
        p.push_back(std::complex<DataType>(-.5631559842430199266325818, .9135900338325109684927731));
        p.push_back(std::complex<DataType>(-.5631559842430199266325818, -.9135900338325109684927731));
        p.push_back(std::complex<DataType>(-.3512792323389821669401925, 1.127591548317705678613239));
        p.push_back(std::complex<DataType>(-.3512792323389821669401925, -1.127591548317705678613239));
        break;
      default:
        throw std::out_of_range("Can't create a Bessel filter with this order");
    }
  }
  
  template<typename DataType, typename Container>
  void create_default_bessel_coeffs(size_t order, DataType Wn, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;
    
    int fs = 2;
    create_bessel_analog_coefficients(static_cast<int>(order), zpk);
    EQUtilities::populate_lp_coeffs(Wn, fs, order, zpk, coefficients_in, coefficients_out);
  }
  
  template<typename DataType, typename Container>
  void create_bp_bessel_coeffs(size_t order, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_bessel_analog_coefficients(static_cast<int>(order/2), zpk);
    EQUtilities::populate_bp_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
  
  template<typename DataType, typename Container>
  void create_bs_bessel_coeffs(size_t order, DataType wc1, DataType wc2, Container& coefficients_in, Container& coefficients_out)
  {
    EQUtilities::ZPK<DataType> zpk;

    int fs = 2;
    create_bessel_analog_coefficients(static_cast<int>(order/2), zpk);
    EQUtilities::populate_bs_coeffs(wc1, wc2, fs, order, zpk, coefficients_in, coefficients_out);
  }
}

namespace ATK
{
  template <typename DataType>
  BesselLowPassCoefficients<DataType>::BesselLowPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void BesselLowPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename BesselLowPassCoefficients<DataType_>::CoeffDataType BesselLowPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void BesselLowPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }

  template <typename DataType>
  unsigned int BesselLowPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void BesselLowPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    BesselUtilities::create_default_bessel_coeffs(in_order, 2 * cut_frequency / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  BesselHighPassCoefficients<DataType>::BesselHighPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void BesselHighPassCoefficients<DataType_>::set_cut_frequency(CoeffDataType cut_frequency)
  {
    if(cut_frequency <= 0)
    {
      throw std::out_of_range("Frequency can't be negative");
    }
    this->cut_frequency = cut_frequency;
    setup();
  }
  
  template <typename DataType_>
  typename BesselHighPassCoefficients<DataType_>::CoeffDataType BesselHighPassCoefficients<DataType_>::get_cut_frequency() const
  {
    return cut_frequency;
  }
  
  template <typename DataType>
  void BesselHighPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = order;
    setup();
  }
  
  template <typename DataType>
  unsigned int BesselHighPassCoefficients<DataType>::get_order() const
  {
    return in_order;
  }

  template <typename DataType>
  void BesselHighPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    BesselUtilities::create_default_bessel_coeffs(in_order, (input_sampling_rate - 2 * cut_frequency) / input_sampling_rate, coefficients_in, coefficients_out);
    for(gsl::index i = in_order - 1; i >= 0; i -= 2)
    {
      coefficients_in[i] = - coefficients_in[i];
      coefficients_out[i] = - coefficients_out[i];
    }
  }
  
  template <typename DataType>
  BesselBandPassCoefficients<DataType>::BesselBandPassCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void BesselBandPassCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void BesselBandPassCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }
  
  template <typename DataType_>
  std::pair<typename BesselBandPassCoefficients<DataType_>::CoeffDataType, typename BesselBandPassCoefficients<DataType_>::CoeffDataType> BesselBandPassCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType>
  void BesselBandPassCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  unsigned int BesselBandPassCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }
  
  template <typename DataType>
  void BesselBandPassCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    BesselUtilities::create_bp_bessel_coeffs(in_order, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
  
  template <typename DataType>
  BesselBandStopCoefficients<DataType>::BesselBandStopCoefficients(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
  }
  
  template <typename DataType_>
  void BesselBandStopCoefficients<DataType_>::set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies)
  {
    if(cut_frequencies.first <= 0 || cut_frequencies.second <= 0)
    {
      throw std::out_of_range("Frequencies can't be negative");
    }
    this->cut_frequencies = cut_frequencies;
    setup();
  }
  
  template <typename DataType_>
  void BesselBandStopCoefficients<DataType_>::set_cut_frequencies(CoeffDataType f0, CoeffDataType f1)
  {
    set_cut_frequencies(std::make_pair(f0, f1));
  }
  
  template <typename DataType_>
  std::pair<typename BesselBandStopCoefficients<DataType_>::CoeffDataType, typename BesselBandStopCoefficients<DataType_>::CoeffDataType> BesselBandStopCoefficients<DataType_>::get_cut_frequencies() const
  {
    return cut_frequencies;
  }
  
  template <typename DataType>
  void BesselBandStopCoefficients<DataType>::set_order(unsigned int order)
  {
    if(order == 0)
    {
      throw std::out_of_range("Order can't be null");
    }
    in_order = out_order = 2 * order;
    setup();
  }
  
  template <typename DataType>
  unsigned int BesselBandStopCoefficients<DataType>::get_order() const
  {
    return in_order / 2;
  }

  template <typename DataType>
  void BesselBandStopCoefficients<DataType>::setup()
  {
    Parent::setup();
    coefficients_in.assign(in_order+1, 0);
    coefficients_out.assign(out_order, 0);
    
    BesselUtilities::create_bs_bessel_coeffs(in_order, 2 * cut_frequencies.first / input_sampling_rate, 2 * cut_frequencies.second / input_sampling_rate, coefficients_in, coefficients_out);
  }
}
