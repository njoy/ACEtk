# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import PNLocatorBlock

class Test_ACEtk_multigroup_PNLocatorBlock( unittest.TestCase ) :
    """Unit test for the PNLocatorBlock class."""

    chunk = [ 1299, 0 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertFalse( chunk.empty )
            self.assertEqual( 2, chunk.length )
            self.assertEqual( "PNL", chunk.name )

            self.assertEqual( 1, chunk.NSEC )
            self.assertEqual( 1, chunk.number_secondary_particle_types )

            self.assertEqual( 1299, chunk.LPN1 )
            self.assertEqual( 0, chunk.LPN(1) )
            
            self.assertEqual( 1299, chunk.incident_locator )
            self.assertEqual( 0, chunk.secondary_locator(1) )

            self.assertFalse( chunk.incident_isotropic )
            self.assertTrue( chunk.is_isotropic( 1 ) )


            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PNLocatorBlock(
                  locators = [ 1299, 0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
