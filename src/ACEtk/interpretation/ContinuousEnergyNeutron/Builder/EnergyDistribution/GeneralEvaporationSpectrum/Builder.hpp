template< typename ParentBuilder >
class Builder: 
    public Spectrum< std::vector< double > >::Builder< ParentBuilder > {

  using SpectrumBuilder = 
      Spectrum< std::vector< double > >::Builder< ParentBuilder >;

public:
  using SpectrumBuilder::SpectrumBuilder;

  template< typename Range,
            utility::Require< true, utility::is_range, Range > = true >
  SpectrumBuilder& equiprobableBins( Range&& spectrum ){
    return SpectrumBuilder::spectrum( std::move( spectrum ) );
  }
};
