# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoAtomicComptonProfile

class Test_ACEtk_PhotoAtomicComptonProfile( unittest.TestCase ) :
    """Unit test for the PhotoAtomicComptonProfile class."""

    chunk = [                 2,                  3,  1.00000000000E-11,  1.00000000000E+00,
              2.00000000000E+01,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
              0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 11, chunk.length )
            self.assertEqual( "PhotoAtomicComptonProfile", chunk.name )

            self.assertEqual( 2, chunk.interpolation )
            self.assertEqual( 3, chunk.number_values )

            self.assertEqual( 3, len( chunk.momentum ) )
            self.assertAlmostEqual( 1e-11, chunk.momentum[0] )
            self.assertAlmostEqual( 20., chunk.momentum[-1] )

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
        chunk = PhotoAtomicComptonProfile(
                    interpolation = 2,
                    momentum = [ 1e-11, 1., 20. ],
                    pdf = [ 0.5, 0.5, 0.5 ],
                    cdf = [ 0.0, 0.5, 1.0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
