class Builder: protected BaseBuilder  {

  std::optional< std::vector< double > > boundaries_;
  std::optional< std::vector< double > > schemes_;
  std::optional< std::vector< double > > energies_;
  std::optional< std::vector< double > > multiplicities_;

protected:
  //#include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Tabulated/Builder/src/construct.hpp"

public:
  using BaseBuilder::BaseBuilder;

  // ContinuousEnergyNeutron::Builder& add() { 
  //   return parent.get().addFissionNeutrons( this->construct() );
  // }

  using BaseBuilder::boundaries;
  using BaseBuilder::schemes;
#define RENAME(basename, derivedname)\
  Builder& derivedname( std::vector< double>&& derivedname ){\
    return static_cast< Builder& >(  \
      BaseBuilder::basename( std::move( derivedname ) ) );\
  }

  RENAME( y, multiplicities );
  RENAME( y, nubar );
#undef RENAME
};

