template< typename Range >
SimpleMaxwellFissionSpectrum( Range& NBT, Range& INT, Range& energies,
                              Table::Slice theta, double U ):
  BaseLaw( NBT, INT, energies ),
  restrictionEnergy_( U ),
  theta_( theta )
{ 
  if( theta_.size() != incidentEnergies().size() ){
    njoy::Log::error(
      "The number of tabulated incident energies (theta) must be the same\n"
      "as the number incident energies" );
    njoy::Log::info( 
        "# tabulated incident energies (theta) {}", theta_.size() );
    njoy::Log::info( 
        "# incident energies {}", incidentEnergies().size() );
    throw std::exception();
  }
}

template< typename Range >
SimpleMaxwellFissionSpectrum( Range& NBT, Range& INT, Range& energies,
                              Range& theta, double U )
try:
  SimpleMaxwellFissionSpectrum( NBT, INT, energies,
    Table::Slice{ theta.begin(), theta.end() }, U
  )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing SimpleMaxwellFissionSpectrum" );
  throw e;
}

