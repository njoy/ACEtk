template < typename Iterator >
static FissionMultiplicityData generateData( Iterator begin, Iterator end ) {

  unsigned int LNU = static_cast< unsigned int >( round( *begin ) );
  switch (LNU) {

    case 1: return PolynomialFissionMultiplicity( begin, end );
    case 2: return TabulatedFissionMultiplicity( begin, end );
    default: {

      Log::error( "Illegal fission multiplicity representation LNU = {}", LNU );
      Log::info( "Only LNU = 1 (polynomial) or LNU = 2 (tabulated) are allowed" );
      throw std::exception();
    }
  }
}

void generateBlocks() {

  if ( this->length() > 0 ) {

    Iterator begin = this->begin();
    Iterator end = this->end();

    bool both = this->XSS( 1 ) < 0;
    if ( both ) {

      auto knu = static_cast<unsigned int>( std::abs( round( *begin ) ) ) + 1;
      end = std::next( begin, knu );
      begin = std::next( begin );
    }

    this->prompt_ = generateData( begin, end );
    this->total_ = both ? std::make_optional( generateData( end, this->end() ) )
                        : std::nullopt;
  }
}
