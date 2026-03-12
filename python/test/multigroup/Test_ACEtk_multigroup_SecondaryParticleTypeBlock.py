# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import SecondaryParticleTypeBlock

class Test_ACEtk_multigroup_SecondaryParticleTypeBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleTypeBlock class."""

    chunk = [ 1, 2 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.length )
            self.assertEqual( "IPT", chunk.name )

            self.assertEqual( 2, chunk.NTYPE )
            self.assertEqual( 2, chunk.number_secondary_particle_types )

            self.assertEqual( 1, chunk.IPT(1) )
            self.assertEqual( 2, chunk.IPT(2) )
            self.assertEqual( 1, chunk.particle_type(1) )
            self.assertEqual( 2, chunk.particle_type(2) )

            self.assertEqual( 2, len( chunk.IPTs ) )
            self.assertEqual( 2, len( chunk.particle_types ) )
            self.assertEqual( 1, chunk.IPTs[0] )
            self.assertEqual( 2, chunk.IPTs[1] )
            self.assertEqual( 1, chunk.particle_types[0] )
            self.assertEqual( 2, chunk.particle_types[1] )

            self.assertEqual( True, chunk.has_IPT(1) )
            self.assertEqual( True, chunk.has_IPT(2) )
            self.assertEqual( False, chunk.has_IPT(34) )
            self.assertEqual( False, chunk.has_IPT(9) )
            self.assertEqual( True, chunk.has_particle_type(1) )
            self.assertEqual( True, chunk.has_particle_type(2) )
            self.assertEqual( False, chunk.has_particle_type(9) )

            self.assertEqual( 1, chunk.index(1) )
            self.assertEqual( 2, chunk.index(2) )

            with self.assertRaises( Exception ) :

                index = chunk.index(9)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleTypeBlock( types = [ 1, 2 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
