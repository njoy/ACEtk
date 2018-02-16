Tabulated( Slice energies ):
  energyGrid_( energies )
{   }

template< typename Range >
Tabulated( Range& energies ):
  Tabulated( 
    Slice( energies.begin(), energies.end() )
        )
{   }
  
