NbodyPhaseSpace( int NPSX, double Ap ):
  numberBodies_( NPSX ),
  totalMassRatio_( Ap )
{ 
  if( totalMassRatio_ < 0.0 ){
    njoy::Log::error( "Total mass ratio must be positive" );
    njoy::Log::info( "Total mass ratio: {}", totalMassRatio_ );
    throw std::exception();
  }
}
