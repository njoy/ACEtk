CrossSection( Slice energies, Slice values ) :
  energyGrid_( energies ),
  values_( values )
{ 
  assert( energyGrid_.size() == values_.size() );
}

template< typename Range  >
CrossSection( Range& energies, Range& values ):
  CrossSection( Slice{energies.begin(), energies.end() },
                Slice{values.begin(), values.end() } )
{ }
