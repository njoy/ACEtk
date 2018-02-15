Polynomial( Slice coeffs ):
  coefficients_( coeffs )
{   }

template< typename Range >
Polynomial( Range& coeffs ):
  Polynomial( Slice( coeffs.begin(), coeffs.end() ) )
{   }
