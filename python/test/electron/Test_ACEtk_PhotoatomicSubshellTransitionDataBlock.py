# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import SubshellTransitionDataBlock
from ACEtk.electron import SubshellTransitionData

class Test_ACEtk_electron_SubshellTransitionDataBlock( unittest.TestCase ) :
    """Unit test for the SubshellTransitionDataBlock class."""

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

            self.assertEqual( 3, xs.NT )
            self.assertEqual( 3, xs.number_transitions )

            self.assertEqual( 4, len( xs.transition(1) ) )
            self.assertEqual( 4, len( xs.transition(2) ) )
            self.assertEqual( 4, len( xs.transition(3) ) )

            self.assertAlmostEqual(    1, xs.transition(1)[0] )
            self.assertAlmostEqual(    0, xs.transition(1)[1] )
            self.assertAlmostEqual(  3.5, xs.transition(1)[2] )
            self.assertAlmostEqual( 0.25, xs.transition(1)[3] )
            self.assertAlmostEqual(    2, xs.transition(2)[0] )
            self.assertAlmostEqual(    3, xs.transition(2)[1] )
            self.assertAlmostEqual(  2.5, xs.transition(2)[2] )
            self.assertAlmostEqual( 0.75, xs.transition(2)[3] )
            self.assertAlmostEqual(    3, xs.transition(3)[0] )
            self.assertAlmostEqual(    1, xs.transition(3)[1] )
            self.assertAlmostEqual(  5.5, xs.transition(3)[2] )
            self.assertAlmostEqual( 1.00, xs.transition(3)[3] )

            self.assertEqual( 1, xs.primary_designator(1) )
            self.assertEqual( 0, xs.secondary_designator(1) )
            self.assertAlmostEqual( 3.5, xs.energy(1) )
            self.assertAlmostEqual( 0.25, xs.probability(1) )
            self.assertEqual( 2, xs.primary_designator(2) )
            self.assertEqual( 3, xs.secondary_designator(2) )
            self.assertAlmostEqual( 2.5, xs.energy(2) )
            self.assertAlmostEqual( 0.75, xs.probability(2) )
            self.assertEqual( 3, xs.primary_designator(3) )
            self.assertEqual( 1, xs.secondary_designator(3) )
            self.assertAlmostEqual( 5.5, xs.energy(3) )
            self.assertAlmostEqual( 1.00, xs.probability(3) )

            self.assertEqual( True, xs.is_radiative_transition(1) )
            self.assertEqual( False, xs.is_radiative_transition(2) )
            self.assertEqual( False, xs.is_radiative_transition(3) )

            xs = chunk.transition_data(2)

            self.assertEqual( 0, xs.NT )
            self.assertEqual( 0, xs.number_transitions )

            xs = chunk.transition_data(3)

            self.assertEqual( 0, xs.NT )
            self.assertEqual( 0, xs.number_transitions )

            xs = chunk.data[0]

            self.assertEqual( 3, xs.NT )
            self.assertEqual( 3, xs.number_transitions )

            self.assertEqual( 4, len( xs.transition(1) ) )
            self.assertEqual( 4, len( xs.transition(2) ) )
            self.assertEqual( 4, len( xs.transition(3) ) )

            self.assertAlmostEqual(    1, xs.transition(1)[0] )
            self.assertAlmostEqual(    0, xs.transition(1)[1] )
            self.assertAlmostEqual(  3.5, xs.transition(1)[2] )
            self.assertAlmostEqual( 0.25, xs.transition(1)[3] )
            self.assertAlmostEqual(    2, xs.transition(2)[0] )
            self.assertAlmostEqual(    3, xs.transition(2)[1] )
            self.assertAlmostEqual(  2.5, xs.transition(2)[2] )
            self.assertAlmostEqual( 0.75, xs.transition(2)[3] )
            self.assertAlmostEqual(    3, xs.transition(3)[0] )
            self.assertAlmostEqual(    1, xs.transition(3)[1] )
            self.assertAlmostEqual(  5.5, xs.transition(3)[2] )
            self.assertAlmostEqual( 1.00, xs.transition(3)[3] )

            self.assertEqual( 1, xs.primary_designator(1) )
            self.assertEqual( 0, xs.secondary_designator(1) )
            self.assertAlmostEqual( 3.5, xs.energy(1) )
            self.assertAlmostEqual( 0.25, xs.probability(1) )
            self.assertEqual( 2, xs.primary_designator(2) )
            self.assertEqual( 3, xs.secondary_designator(2) )
            self.assertAlmostEqual( 2.5, xs.energy(2) )
            self.assertAlmostEqual( 0.75, xs.probability(2) )
            self.assertEqual( 3, xs.primary_designator(3) )
            self.assertEqual( 1, xs.secondary_designator(3) )
            self.assertAlmostEqual( 5.5, xs.energy(3) )
            self.assertAlmostEqual( 1.00, xs.probability(3) )

            self.assertEqual( True, xs.is_radiative_transition(1) )
            self.assertEqual( False, xs.is_radiative_transition(2) )
            self.assertEqual( False, xs.is_radiative_transition(3) )

            xs = chunk.data[1]

            self.assertEqual( 0, xs.NT )
            self.assertEqual( 0, xs.number_transitions )

            xs = chunk.data[2]

            self.assertEqual( 0, xs.NT )
            self.assertEqual( 0, xs.number_transitions )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SubshellTransitionDataBlock(
                    transitions = [

                          SubshellTransitionData( [ 1, 2, 3 ], [ 0, 3, 1 ],
                                                             [ 3.5, 2.5, 5.5 ], [ 0.25, 0.75, 1. ] ),
                          SubshellTransitionData(),
                          SubshellTransitionData(),
                          SubshellTransitionData() ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
