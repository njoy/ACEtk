class Builder {
private:

  using ParentBuilder = ContinuousEnergyNeutron::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< std::vector< double > > coefficients_;
  std::string nuType;

protected:
  Polynomial construct(){ 
    return Polynomial{ std::move( this->coefficients_.value() ) }; }

public:
  Builder( ParentBuilder& parent, std::string nuType ): 
    parent( parent ),
    nuType( nuType )
  { }

  ParentBuilder& add() { 
    return parent.get().addFissionMultiplicity( this->nuType,  
                                                this->construct() );
  }
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder/src/coefficients.hpp"
};
