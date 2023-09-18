# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoatomicSubshellTransitionDataBlock
from ACEtk import PhotoatomicSubshellTransitionData

class Test_ACEtk_PhotoatomicSubshellTransitionDataBlock( unittest.TestCase ) :
    """Unit test for the PhotoatomicSubshellTransitionDataBlock class."""

    chunk = [ 0, 12, 12, 12,
              1, 0, 3.5, 0.25, 2, 3, 2.5, 0.75, 3, 1, 5.5, 1.00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 16, chunk.length )
            self.assertEqual( "XPROB", chunk.name )

            self.assertEqual( 4, chunk.NSSH )
            self.assertEqual( 4, chunk.number_electron_subshells )
            self.assertEqual( 4, len( chunk.data ) )

            self.assertEqual(  1, chunk.LTRAN(1) )
            self.assertEqual( 13, chunk.LTRAN(2) )
            self.assertEqual( 13, chunk.LTRAN(3) )
            self.assertEqual( 13, chunk.LTRAN(4) )
            self.assertEqual(  1, chunk.transition_data_locator(1) )
            self.assertEqual( 13, chunk.transition_data_locator(2) )
            self.assertEqual( 13, chunk.transition_data_locator(3) )
            self.assertEqual( 13, chunk.transition_data_locator(4) )

            xs = chunk.transition_data(1)

            xs = chunk.transition_data(2)

            xs = chunk.transition_data(3)

            xs = chunk.data[0]

            xs = chunk.data[1]

            xs = chunk.data[2]

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoatomicSubshellTransitionDataBlock(
                    transitions = [

                          PhotoatomicSubshellTransitionData( [ 1, 2, 3 ], [ 0, 3, 1 ],
                                                             [ 3.5, 2.5, 5.5 ], [ 0.25, 0.75, 1. ] ),
                          PhotoatomicSubshellTransitionData(),
                          PhotoatomicSubshellTransitionData(),
                          PhotoatomicSubshellTransitionData() ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
