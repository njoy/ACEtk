# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import SecondaryParticleTypeBlock

class Test_ACEtk_continuous_SecondaryParticleTypeBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleTypeBlock class."""

    chunk = [ 9, 31, 34 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 3, chunk.length )
            self.assertEqual( "PTYPE", chunk.name )

            self.assertEqual( 3, chunk.NTYPE )
            self.assertEqual( 3, chunk.number_additional_secondary_particle_types )

            self.assertEqual( 9, chunk.IP(1) )
            self.assertEqual( 31, chunk.IP(2) )
            self.assertEqual( 34, chunk.IP(3) )
            self.assertEqual( 9, chunk.particle_type(1) )
            self.assertEqual( 31, chunk.particle_type(2) )
            self.assertEqual( 34, chunk.particle_type(3) )

            self.assertEqual( 3, len( chunk.IPs ) )
            self.assertEqual( 3, len( chunk.particle_types ) )
            self.assertEqual( 9, chunk.IPs[0] )
            self.assertEqual( 31, chunk.IPs[1] )
            self.assertEqual( 34, chunk.IPs[2] )
            self.assertEqual( 9, chunk.particle_types[0] )
            self.assertEqual( 31, chunk.particle_types[1] )
            self.assertEqual( 34, chunk.particle_types[2] )

            self.assertEqual( True, chunk.has_IP(9) )
            self.assertEqual( True, chunk.has_IP(31) )
            self.assertEqual( True, chunk.has_IP(34) )
            self.assertEqual( False, chunk.has_IP(1) )
            self.assertEqual( True, chunk.has_particle_type(9) )
            self.assertEqual( True, chunk.has_particle_type(31) )
            self.assertEqual( True, chunk.has_particle_type(34) )
            self.assertEqual( False, chunk.has_particle_type(1) )

            self.assertEqual( 1, chunk.index(9) )
            self.assertEqual( 2, chunk.index(31) )
            self.assertEqual( 3, chunk.index(34) )

            with self.assertRaises( Exception ) :

                index = chunk.index(1)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleTypeBlock( types = [ 9, 31, 34 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
