# standard imports
import unittest

# third party imports

# local imports
from ACEtk import TabulatedAngularDistribution

class Test_ACEtk_TabulatedAngularDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedAngularDistribution class."""

    chunk = [ -1.00000000000E+00, -0.90000000000E+00, -0.80000000000E+00, -0.70000000000E+00,
              -0.60000000000E+00, -0.50000000000E+00, -0.30000000000E+00, -0.20000000000E+00,
              -0.10000000000E+00,  0.00000000000E+00,  0.05000000000E+00,  0.10000000000E+00,
               0.15000000000E+00,  0.20000000000E+00,  0.25000000000E+00,  0.30000000000E+00,
               0.35000000000E+00,  0.40000000000E+00,  0.45000000000E+00,  0.50000000000E+00,
               0.55000000000E+00,  0.60000000000E+00,  0.65000000000E+00,  0.70000000000E+00,
               0.75000000000E+00,  0.80000000000E+00,  0.85000000000E+00,  0.90000000000E+00,
               0.92500000000E+00,  0.95000000000E+00,  0.96250000000E+00,  0.97500000000E+00,
               1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 33, chunk.length )
            self.assertEqual( "AND::TabulatedAngularDistribution", chunk.name )

            self.assertEqual( 2.1, chunk.incident_energy )
            self.assertEqual( 32, chunk.number_bins )

            self.assertEqual( 33, len( chunk.cosines ) )
            self.assertAlmostEqual( -1, chunk.cosines[0] )
            self.assertAlmostEqual( +1, chunk.cosines[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = TabulatedAngularDistribution(
                    incident = 2.1,
                    cosines = [ -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.3, -0.2, -0.1, 0.0,
                                0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5,
                                0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.925, 0.95,
                                0.9625, 0.975, 1.0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
