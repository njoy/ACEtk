# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoelectricCrossSectionBlock

class Test_ACEtk_PhotoelectricCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the PhotoelectricCrossSectionBlock class."""

    chunk = [  1.,  2.,  3.,  4.,  5.,
               6.,  7.,  8.,  9., 10.,
              11., 12., 13., 14., 15. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 15, chunk.length )
            self.assertEqual( "SPHEL", chunk.name )

            self.assertEqual( 15, len( chunk.xss_array ) )

            self.assertEqual( 5, chunk.NES )
            self.assertEqual( 5, chunk.number_energy_points )
            self.assertEqual( 5, chunk.NSSH )
            self.assertEqual( 5, chunk.number_electron_subshells )

            self.assertEqual( 5, len( chunk.photoelectric( 1 ) ) )
            self.assertEqual( 5, len( chunk.photoelectric( 2 ) ) )
            self.assertEqual( 5, len( chunk.photoelectric( 2 ) ) )

            self.assertAlmostEqual(  1., chunk.electroionisation(1)[0] )
            self.assertAlmostEqual(  2., chunk.electroionisation(1)[1] )
            self.assertAlmostEqual(  3., chunk.electroionisation(1)[2] )
            self.assertAlmostEqual(  4., chunk.electroionisation(1)[3] )
            self.assertAlmostEqual(  5., chunk.electroionisation(1)[4] )
            self.assertAlmostEqual(  6., chunk.electroionisation(2)[0] )
            self.assertAlmostEqual(  7., chunk.electroionisation(2)[1] )
            self.assertAlmostEqual(  8., chunk.electroionisation(2)[2] )
            self.assertAlmostEqual(  9., chunk.electroionisation(2)[3] )
            self.assertAlmostEqual( 10., chunk.electroionisation(2)[4] )
            self.assertAlmostEqual( 11., chunk.electroionisation(3)[0] )
            self.assertAlmostEqual( 12., chunk.electroionisation(3)[1] )
            self.assertAlmostEqual( 13., chunk.electroionisation(3)[2] )
            self.assertAlmostEqual( 14., chunk.electroionisation(3)[3] )
            self.assertAlmostEqual( 15., chunk.electroionisation(3)[4] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoelectricCrossSectionBlock(
                  electroionisation = [ [  1.,  2.,  3.,  4.,  5. ],
                                        [  6.,  7.,  8.,  9., 10. ],
                                        [ 11., 12., 13., 14., 15. ] ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()