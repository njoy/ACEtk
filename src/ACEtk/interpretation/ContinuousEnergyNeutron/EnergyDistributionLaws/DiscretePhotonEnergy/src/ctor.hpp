DiscretePhotonEnergy( int LP, double EG ):
  primaryFlag_( LP ),
  photonEnergy_( EG )
{ 
  if( ( primaryFlag_ < 0 ) or ( primaryFlag_ > 2 ) ){
    njoy::Log::error( "Invalid LP flag ({}) for LAW2", primaryFlag_ );
    njoy::Log::info( "LP flag must be 0, 1, or 2" );
    throw std::exception();
  }
}
