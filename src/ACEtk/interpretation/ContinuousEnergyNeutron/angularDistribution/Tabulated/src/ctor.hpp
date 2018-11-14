Tabulated( int interpFlag, 
           Slice cosineBins,
           CoupledDensityFunctions&& densityFunctions )
  try:
    interpolationFlag_( interpFlag ),
    cosineBins_( cosineBins ),
    densityFunctions( densityFunctions )
{ 
  try{
    details::verify::checkHistLinLinFlag( interpolationFlag_ );
  } catch( const std::exception& e ){
    njoy::Log::info(
      "Invalid interpolation flag for tabulated angular distribution." );
    throw;
  }

  try{
    details::verify::equalSize( cosineBins, densityFunctions.PDF() );
  } catch( std::range_error& e ){
    njoy::Log::info( 
      "The length of the cosine bins ({}) != the length of the PDF/CDF ({})",
      ranges::distance( cosineBins_ ), 
      ranges::distance( densityFunctions.PDF() ) );
    throw;
  }
} catch( std::exception& e ){
  njoy::Log::info( 
    "Trouble encountered constructing Tabulated angular distribution" );
  throw;
}

template< typename Range >
Tabulated( int interpFlag, Range& cosineBins, Range& PDF, Range& CDF ):
  Tabulated( interpFlag, 
             Slice{ cosineBins.begin(), cosineBins.end() },
             CoupledDensityFunctions( PDF, CDF ) )
{ }
