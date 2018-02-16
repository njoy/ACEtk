Equiprobable( Slice energies, Slice bins ):
  energyGrid_( energies ),
  boundaries_( bins )
{   
  if( boundaries_.size() != 33 ){
    Log::error( "There must be 33 cosine bin boundaires. Found: {}.", 
               boundaries_.size() );
    throw std::exception();
  }
}

template< typename Range >
Equiprobable( Range& energies, Range& bins ):
  Equiprobable( 
      Slice( energies.begin(), energies.end() ),
      Slice( bins.begin(), bins.end() ) )
{   }
