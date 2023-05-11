template < typename Iterator >
static EvaporationSpectrum
readDistributionData( const EnergyDistributionType& law,
                      Iterator begin, Iterator end,
                      double, double ) {

  if ( EnergyDistributionType::Evaporation != law ) {

    Log::error( "Illegal law for MultiEvaporationSpectrum block" );
    Log::info( "Expected law value {} but found {}",
               static_cast< short >( EnergyDistributionType::Evaporation ),
               static_cast< short >( law ) );
    throw std::exception();
  }

  return EvaporationSpectrum( begin, end );
}
