template< typename ParentBuilder >
class Builder: public Spectrum< double >::Builder< 
               Builder< ParentBuilder >, ParentBuilder > {

  using SpectrumBuilder = Spectrum< double >::Builder< 
      Builder< ParentBuilder >, ParentBuilder >;

public:
  using SpectrumBuilder::SpectrumBuilder;

  Builder& restrictionEnergy( double energy ){
    return SpectrumBuilder::spectrum( std::move( energy ) );
  }
};
