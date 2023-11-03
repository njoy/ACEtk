# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import MultiplicityReactionNumberBlock

class Test_ACEtk_continuous_MultiplicityReactionNumberBlock( unittest.TestCase ) :
    """Unit test for the MultiplicityReactionNumberBlock class."""

    chunk = [ 3, 102, 204, 444 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 4, chunk.length )
            self.assertEqual( "YP", chunk.name )

            self.assertEqual( 3, chunk.NYP )
            self.assertEqual( 3, chunk.number_reactions )

            self.assertEqual( 102, chunk.MT(1) )
            self.assertEqual( 204, chunk.MT(2) )
            self.assertEqual( 444, chunk.MT(3) )

            self.assertEqual( 3, len( chunk.MTs ) )
            self.assertEqual( 102, chunk.MTs[0] )
            self.assertEqual( 204, chunk.MTs[1] )
            self.assertEqual( 444, chunk.MTs[2] )

            self.assertEqual( True, chunk.has_MT(102) )
            self.assertEqual( True, chunk.has_MT(204) )
            self.assertEqual( True, chunk.has_MT(444) )
            self.assertEqual( False, chunk.has_MT(1) )

            self.assertEqual( 1, chunk.index(102) )
            self.assertEqual( 2, chunk.index(204) )
            self.assertEqual( 3, chunk.index(444) )

            with self.assertRaises( Exception ) :

                index = chunk.index(1)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = MultiplicityReactionNumberBlock( reactions = [ 102, 204, 444 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
