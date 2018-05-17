Tabulated( int interpFlag, 
           Slice cosineBins,
           CoupledDensityFunctions&& densityFunctions )
  try:
    interpolationFlag_( interpFlag ),
    cosineBins_( cosineBins ),
    densityFunctions( densityFunctions )
{ 
  try{
    checkHistLinLinFlag( interpolationFlag_ );
  } catch( const std::exception& e ){
    njoy::Log::info(
      "Invalid interpolation flag for tabulated angular distribution." );
    throw e;
  }

  if( cosineBins_.size() != densityFunctions.size() ){
    njoy::Log::info( 
      "The length of the cosine bins ({}) != the length of the PDF/CDF ({})",
      cosineBins_.size(), densityFunctions.size() );
    throw std::exception();
  }
} catch( std::exception& e ){
  njoy::Log::info( 
    "Trouble encountered constructing Tabulated angular distribution" );
  throw e;
}

template< typename Range >
Tabulated( int interpFlag, Range& cosineBins, Range& PDF, Range& CDF ):
  Tabulated( interpFlag, 
             Slice{ cosineBins.begin(), cosineBins.end() },
             CoupledDensityFunctions( PDF, CDF ) )
{ }
