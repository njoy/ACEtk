# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import EditReactionNumberBlock

class Test_ACEtk_multigroup_EditReactionNumberBlock( unittest.TestCase ) :
    """Unit test for the EditReactionNumberBlock class."""

    chunk = [ 2, 102, 101, 204, 401, 1, 301, 302 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 8, chunk.length )
            self.assertEqual( "MTED", chunk.name )

            self.assertEqual( 8, chunk.NEDIT )
            self.assertEqual( 8, chunk.number_edit_reactions )

            self.assertEqual( 2, chunk.MT(1) )
            self.assertEqual( 102, chunk.MT(2) )
            self.assertEqual( 101, chunk.MT(3) )

            self.assertEqual( 8, len( chunk.MTs ) )
            self.assertEqual( 2, chunk.MTs[0] )
            self.assertEqual( 102, chunk.MTs[1] )
            self.assertEqual( 101, chunk.MTs[2] )

            self.assertEqual( True, chunk.has_MT(2) )
            self.assertEqual( True, chunk.has_MT(102) )
            self.assertEqual( True, chunk.has_MT(101) )
            self.assertEqual( True, chunk.has_MT(1) )
            self.assertEqual( False, chunk.has_MT(16) )

            self.assertEqual( 1, chunk.index(2) )
            self.assertEqual( 2, chunk.index(102) )
            self.assertEqual( 3, chunk.index(101) )

            with self.assertRaises( Exception ) :

                index = chunk.index(16)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = EditReactionNumberBlock( edit_reaction_numbers = [ 2, 102, 101, 204, 401, 1, 301, 302 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
