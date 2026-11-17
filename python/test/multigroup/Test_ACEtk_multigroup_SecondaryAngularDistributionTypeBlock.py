# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import SecondaryAngularDistributionTypeBlock

class Test_ACEtk_multigroup_SecondaryAngularDistributionTypeBlock( unittest.TestCase ) :
    """Unit test for the SecondaryAngularDistributionTypeBlock class."""

    chunk = [ 0, 1, 0 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 3, chunk.length )
            self.assertEqual( "SANG2", chunk.name )

            self.assertEqual( 3, chunk.NSEC )
            self.assertEqual( 3, chunk.number_secondary_particles )

            self.assertEqual( 0, chunk.SANG2(1) )
            self.assertEqual( 1, chunk.SANG2(2) )
            self.assertEqual( 0, chunk.SANG2(3) )
            
            self.assertEqual( 0, chunk.distribution_type(1) )
            self.assertEqual( 1, chunk.distribution_type(2) )
            self.assertEqual( 0, chunk.distribution_type(3) )

            self.assertEqual( 3, len( chunk.SANG2s ) )
            self.assertEqual( 3, len( chunk.distribution_types ) )
            self.assertEqual( 0, chunk.SANG2s[0] )
            self.assertEqual( 1, chunk.SANG2s[1] )
            self.assertEqual( 0, chunk.SANG2s[2] )
            self.assertEqual( 0, chunk.distribution_types[0] )
            self.assertEqual( 1, chunk.distribution_types[1] )
            self.assertEqual( 0, chunk.distribution_types[2] )


            with self.assertRaises( Exception ) :

                index = chunk.index(9)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryAngularDistributionTypeBlock( types = [ 0, 1, 0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
