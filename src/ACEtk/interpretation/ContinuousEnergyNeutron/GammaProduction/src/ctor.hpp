GammaProduction( Slice crossSection, 
                 Slice grid ):
  crossSection_( crossSection ),
  outgoingEnergyGrid_( grid )
{
  auto size = outgoingEnergyGrid_.size();
  if( size != 600 ){
    njoy::Log::error( 
      "Gamma production outgoing energy grid size ({})!= 600", size );
    throw std::range_error( "Gamma production grid size != 600." );
  }

  try{
    details::verify::isPositive( crossSection_ );
  } catch( details::verify::exceptions::NotPositive& e ){
    njoy::Log::info( "Cross section values must be positive" );
    throw;
  }

  try{
    details::verify::isPositive( outgoingEnergyGrid_ );
  } catch( details::verify::exceptions::NotPositive& e ){
    njoy::Log::info( "Outgoing energy grid values must be positive" );
    throw;
  }
}

template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
GammaProduction( Range& crossSection, Range& grid ):
  GammaProduction( Table::slice( crossSection ),
                   Table::slice( grid ) )
{ }
