CrossSection( Slice energies, Slice values ) :
  energyGrid_( energies ),
  xsValues_( values )
{ }

template< typename Range  >
CrossSection( Range& energies, Range& values ):
  CrossSection( Slice{energies.begin(), energies.end() },
                Slice{values.begin(), values.end() } )
{ }
