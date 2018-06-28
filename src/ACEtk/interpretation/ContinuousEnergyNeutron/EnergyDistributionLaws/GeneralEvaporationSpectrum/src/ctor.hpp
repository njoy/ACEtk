template< typename Range >
GeneralEvaporationSpectrum( Range& NBT, Range& INT, Range& energies,
                            Table::Slice theta, Table::Slice X ):
  BaseLaw( NBT, INT, energies ),
  theta_( theta ),
  tabulatedProbabilisticFunction_( X )
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
GeneralEvaporationSpectrum( Range& NBT, Range& INT, Range& energies,
                            Range& theta, Range& X )
try:
  GeneralEvaporationSpectrum( NBT, INT, energies,
    Table::Slice{ theta.begin(), theta.end() },
    Table::Slice{ X.begin(), X.end() }
  )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing GeneralEvaporationSpectrum" );
  throw e;
}
