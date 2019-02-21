template< typename ParentBuilder >
class Builder: public Spectrum< double >::Builder< ParentBuilder > {

  using SpectrumBuilder = Spectrum< double >::Builder< ParentBuilder >;

public:
  using SpectrumBuilder::SpectrumBuilder;

  SpectrumBuilder& restrictionEnergy( double energy ){
    return SpectrumBuilder::spectrum( std::move( energy ) );
  }
};
