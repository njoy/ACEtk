Equiprobable( Slice energies, 
             std::vector< std::optional< std::vector< double > > > bins ):
  energyGrid_( energies ),
  boundaries_( bins )
{   
  if( energyGrid_.size() != boundaries_.size() ){
    Log::error( "There must be one and only one set of cosine bins\n"
                "for each element of the energy grid." );
    Log::info( "Energy grid size: {}", energyGrid_.size() );
    Log::info( "Cosine bins size: {}", boundaries_.size() );
    throw std::exception();
  }

  for( size_t i=0; i<boundaries_.size(); i++ ){
    if( boundaries_[i] ){
      if( boundaries_[i]->size() != 33 ){
        Log::error( "There must be 33 cosine bin boundaires. Found: {}.", 
                   boundaries_[i]->size() );
        throw std::exception();
      }
    }
  }
}

// Need to change this so it's no to specific to std::vector
template< typename Range >
Equiprobable( Range& energies,
              std::vector< std::optional< std::vector< double > > > bins ):
  Equiprobable( 
      Slice( energies.begin(), energies.end() ),
      bins )
{   }
