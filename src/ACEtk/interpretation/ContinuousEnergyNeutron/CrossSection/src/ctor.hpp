CrossSection( Slice energies, Slice values ) :
  energyGrid_( energies ),
  values_( values )
{ 
  if( energyGrid_.size() != values_.size() ){
    Log::error( "Energy grid size must equal size of cross section values." );
    throw std::exception();
  }
}

template< typename Range  >
CrossSection( Range& energies, Range& values ):
  CrossSection( Slice{energies.begin(), energies.end() },
                Slice{values.begin(), values.end() } )
{ }
