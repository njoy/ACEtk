PhotonProduction( Slice energies, Slice cosineBins ):
    energyGrid_( energies ),
    cosineBins_( cosineBins )
{
  try{
    details::verify::isPositive( energyGrid_ );
  } catch( details::verify::exceptions::NotPositive& e ){
    njoy::Log::info( "Energy grid values must be positive" );
    throw;
  }

  auto size = energyGrid_.size();
  if( size*32 != cosineBins_.size() ){
    njoy::Log::error(
        "Cosine bins for photon production angular distributions has the wrong "
        "size ({})", cosineBins_.size() );
    njoy::Log::info( "Size should be: {}", size*32 );
    throw std::range_error( 
        "Photon production cosine bin size has wrong size" );
  }
}

template< typename Range,
utility::Require< true, utility::is_range, Range > = true >
PhotonProduction( Range& energies, Range& cosineBins ):
    PhotonProduction( Table::slice( energies ),
            Table::slice( cosineBins ))
{ }
