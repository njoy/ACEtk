# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import SecondaryParticleInformationBlock

class Test_ACEtk_SecondaryParticleInformationBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleInformationBlock class."""

    chunk = [ 3, 2, 4 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 3, chunk.length )
            self.assertEqual( "NTRO", chunk.name )

            self.assertEqual( 3, chunk.NTYPE )
            self.assertEqual( 3, chunk.number_additional_secondary_particle_types )

            self.assertEqual( 3, chunk.NP(1) )
            self.assertEqual( 2, chunk.NP(2) )
            self.assertEqual( 4, chunk.NP(3) )
            self.assertEqual( 3, chunk.number_secondary_particle_production_reactions(1) )
            self.assertEqual( 2, chunk.number_secondary_particle_production_reactions(2) )
            self.assertEqual( 4, chunk.number_secondary_particle_production_reactions(3) )

            self.assertEqual( 3, len( chunk.NPs ) )
            self.assertEqual( 3, len( chunk.number_reactions ) )
            self.assertEqual( 3, chunk.NPs[0] )
            self.assertEqual( 2, chunk.NPs[1] )
            self.assertEqual( 4, chunk.NPs[2] )
            self.assertEqual( 3, chunk.number_reactions[0] )
            self.assertEqual( 2, chunk.number_reactions[1] )
            self.assertEqual( 4, chunk.number_reactions[2] )

            with self.assertRaises( Exception ) :

                index = chunk.index(1)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleInformationBlock( numbers = [ 3, 2, 4 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
