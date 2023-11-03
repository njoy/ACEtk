# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import ReactionQValueBlock

class Test_ACEtk_ReactionQValueBlock( unittest.TestCase ) :
    """Unit test for the ReactionQValueBlock class."""

    chunk = [ 2.22463100000E+00, 0., 0. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 3, chunk.length )
            self.assertEqual( "LQR", chunk.name )

            self.assertEqual( 3, chunk.NTR )
            self.assertEqual( 3, chunk.number_reactions )

            self.assertAlmostEqual( 2.224631, chunk.q_value(1) )
            self.assertAlmostEqual( 0., chunk.q_value(2) )
            self.assertAlmostEqual( 0., chunk.q_value(3) )

            self.assertEqual( 3, len( chunk.q_values ) )
            self.assertAlmostEqual( 2.224631, chunk.q_values[0] )
            self.assertAlmostEqual( 0., chunk.q_values[1] )
            self.assertAlmostEqual( 0., chunk.q_values[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = ReactionQValueBlock( qvalues = [ 2.224631, 0., 0. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
