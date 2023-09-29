# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import TabulatedAngularDistributionWithProbability

class Test_ACEtk_TabulatedAngularDistributionWithProbability( unittest.TestCase ) :
    """Unit test for the TabulatedAngularDistributionWithProbability class."""

    chunk = [                 2,                  3, -1.00000000000E+00,  0.00000000000E+00,
              1.00000000000E+00,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
              0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 11, chunk.length )
            self.assertEqual( "TabulatedAngularDistribution", chunk.name )

            self.assertEqual( 2.1, chunk.energy )
            self.assertEqual( 0.5, chunk.probability )
            self.assertEqual( 0.75, chunk.cumulative_probability )
            self.assertEqual( 2, chunk.interpolation )
            self.assertEqual( 3, chunk.number_cosines )

            self.assertEqual( 3, len( chunk.cosines ) )
            self.assertAlmostEqual( -1, chunk.cosines[0] )
            self.assertAlmostEqual( +1, chunk.cosines[-1] )

            self.assertEqual( 3, len( chunk.pdf ) )
            self.assertAlmostEqual( .5, chunk.pdf[0] )
            self.assertAlmostEqual( .5, chunk.pdf[-1] )

            self.assertEqual( 3, len( chunk.cdf ) )
            self.assertAlmostEqual( 0., chunk.cdf[0] )
            self.assertAlmostEqual( 1., chunk.cdf[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = TabulatedAngularDistributionWithProbability(
                    energy = 2.1,
                    probability = 0.5,
                    cumulative = 0.75,
                    interpolation = 2,
                    cosines = [ -1.0, 0.0, 1.0 ],
                    pdf = [ 0.5, 0.5, 0.5 ],
                    cdf = [ 0.0, 0.5, 1.0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
