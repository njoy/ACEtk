#ifndef NJOY_ACETK_ANGULARDISTRIBUTIONTYPE
#define NJOY_ACETK_ANGULARDISTRIBUTIONTYPE

// system includes

// other includes

namespace njoy {
namespace ACEtk {

  enum class AngularDistributionType : short {

    Isotropic,       // isotropic angular distribution
    Equiprobable,    // 32 equiprobable cosine bins
    Tabulated        // tabulated angular distribution
  };

} // ACEtk namespace
} // njoy namespace

#endif
