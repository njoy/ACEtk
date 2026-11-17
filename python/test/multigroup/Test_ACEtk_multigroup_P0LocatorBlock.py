# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import P0LocatorBlock

class Test_ACEtk_multigroup_P0LocatorBlock( unittest.TestCase ) :
    """Unit test for the P0LocatorBlock class."""

    chunk = [ 369, 2880 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.length )
            self.assertEqual( "P0L", chunk.name )

            self.assertEqual( 1, chunk.NSEC )
            self.assertEqual( 1, chunk.number_secondary_particle_types )

            self.assertEqual( 369, chunk.P01() )
            self.assertEqual( 2880, chunk.P02(1) )
            
            self.assertEqual( 369, chunk.incident_locator() )
            self.assertEqual( 2880, chunk.secondary_locator(1) )


            with self.assertRaises( Exception ) :

                index = chunk.index(1)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = P0LocatorBlock(
                  locators = [ 369, 2880 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
