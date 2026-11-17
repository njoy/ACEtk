# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import SecondaryParticleGroupStructureLocatorBlock

class Test_ACEtk_multigroup_SecondaryParticleGroupStructureLocatorBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleGroupStructureLocatorBlock class."""

    chunk = [ 369, 2880 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.length )
            self.assertEqual( "ERG2L", chunk.name )

            self.assertEqual( 2, chunk.NSEC )
            self.assertEqual( 2, chunk.number_secondary_particle_types )

            self.assertEqual( 369, chunk.ERG2(1) )
            self.assertEqual( 2880, chunk.ERG2(2) )
            
            self.assertEqual( 369, chunk.locator(1) )
            self.assertEqual( 2880, chunk.locator(2) )


            with self.assertRaises( Exception ) :

                index = chunk.index(1)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleGroupStructureLocatorBlock(
                  locators = [ 369, 2880 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
