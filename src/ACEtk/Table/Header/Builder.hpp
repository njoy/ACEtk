template< typename ParentBuilder >
class Builder {
  std::optional< year_month_day >                  processDate_;
  std::optional< Quantity< Mega<ElectronVolts> > > processTemperature_;
  std::optional< double >                          atomicWeightRatio_;
  std::optional< SZAID >                           szaid_;
  std::vector< Comment >                           comments_;
  std::optional< MAT >                             mat_;
  std::optional< Source >                          source_;

protected:
  std::reference_wrapper< ParentBuilder > parent;
  #include "ACEtk/Table/Header/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addHeader( this->construct() );
  }

  #include "ACEtk/Table/Header/Builder/src/processDate.hpp"
  #include "ACEtk/Table/Header/Builder/src/temperature.hpp"
  #include "ACEtk/Table/Header/Builder/src/atomicWeightRatio.hpp"
  #include "ACEtk/Table/Header/Builder/src/szaid.hpp"
  #include "ACEtk/Table/Header/Builder/src/materialNumber.hpp"
  #include "ACEtk/Table/Header/Builder/src/source.hpp"
  #include "ACEtk/Table/Header/Builder/src/comment.hpp"
};
