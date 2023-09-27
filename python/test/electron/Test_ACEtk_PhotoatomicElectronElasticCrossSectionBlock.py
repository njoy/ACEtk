# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoatomicElectronElasticCrossSectionBlock

class Test_ACEtk_PhotoatomicElectronElasticCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the PhotoatomicElectronElasticCrossSectionBlock class."""

    chunk = [   1.,   2.,   3.,
                4.,   5.,   6. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 6, chunk.length )
            self.assertEqual( "SELAS", chunk.name )

            self.assertEqual( 6, len( chunk.xss_array ) )

            self.assertEqual( 3, chunk.NE )
            self.assertEqual( 3, chunk.number_energy_points )

            self.assertEqual( 3, len( chunk.transport ) )
            self.assertEqual( 3, len( chunk.total ) )

            self.assertAlmostEqual(   1., chunk.transport[0] )
            self.assertAlmostEqual(   2., chunk.transport[1] )
            self.assertAlmostEqual(   3., chunk.transport[2] )
            self.assertAlmostEqual(   4., chunk.total[0] )
            self.assertAlmostEqual(   5., chunk.total[1] )
            self.assertAlmostEqual(   6., chunk.total[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoatomicElectronElasticCrossSectionBlock(
                  transport = [ 1., 2., 3. ],
                  total = [ 4., 5., 6. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
