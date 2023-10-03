# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import PolynomialFissionMultiplicity

class Test_ACEtk_continuous_PolynomialFissionMultiplicity( unittest.TestCase ) :
    """Unit test for the PolynomialFissionMultiplicity class."""

    chunk = [ 1, 2, 2.5, 1e-8 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 4, chunk.length )
            self.assertEqual( "PolynomialFissionMultiplicity", chunk.name )

            self.assertEqual( 1, chunk.LNU )
            self.assertEqual( 1, chunk.type )

            self.assertEqual( 2, chunk.NC )
            self.assertEqual( 2, chunk.number_coefficients )
            self.assertEqual( 2, len( chunk.C ) )
            self.assertEqual( 2, len( chunk.coefficients ) )

            self.assertAlmostEqual( 2.5, chunk.C[0] )
            self.assertAlmostEqual( 1e-8, chunk.C[-1] )
            self.assertAlmostEqual( 2.5, chunk.coefficients[0] )
            self.assertAlmostEqual( 1e-8, chunk.coefficients[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PolynomialFissionMultiplicity( coefficients = [ 2.5, 1e-8 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
