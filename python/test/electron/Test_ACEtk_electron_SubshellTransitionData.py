# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import SubshellTransitionData

class Test_ACEtk_electron_SubshellTransitionData( unittest.TestCase ) :
    """Unit test for the SubshellTransitionData class."""

    chunk = [  1,   0,   3.5, 0.25,
               2,   3,   2.5, 0.75,
               3,   1,   5.5, 1.00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 12, chunk.length )
            self.assertEqual( "TRAN", chunk.name )

            self.assertEqual( 12, len( chunk.xss_array ) )

            self.assertEqual( 3, chunk.NT )
            self.assertEqual( 3, chunk.number_transitions )

            self.assertEqual( 4, len( chunk.transition(1) ) )
            self.assertEqual( 4, len( chunk.transition(2) ) )
            self.assertEqual( 4, len( chunk.transition(3) ) )

            self.assertAlmostEqual(    1, chunk.transition(1)[0] )
            self.assertAlmostEqual(    0, chunk.transition(1)[1] )
            self.assertAlmostEqual(  3.5, chunk.transition(1)[2] )
            self.assertAlmostEqual( 0.25, chunk.transition(1)[3] )
            self.assertAlmostEqual(    2, chunk.transition(2)[0] )
            self.assertAlmostEqual(    3, chunk.transition(2)[1] )
            self.assertAlmostEqual(  2.5, chunk.transition(2)[2] )
            self.assertAlmostEqual( 0.75, chunk.transition(2)[3] )
            self.assertAlmostEqual(    3, chunk.transition(3)[0] )
            self.assertAlmostEqual(    1, chunk.transition(3)[1] )
            self.assertAlmostEqual(  5.5, chunk.transition(3)[2] )
            self.assertAlmostEqual( 1.00, chunk.transition(3)[3] )

            self.assertEqual( 1, chunk.primary_designator(1) )
            self.assertEqual( 0, chunk.secondary_designator(1) )
            self.assertAlmostEqual( 3.5, chunk.energy(1) )
            self.assertAlmostEqual( 0.25, chunk.probability(1) )
            self.assertEqual( 2, chunk.primary_designator(2) )
            self.assertEqual( 3, chunk.secondary_designator(2) )
            self.assertAlmostEqual( 2.5, chunk.energy(2) )
            self.assertAlmostEqual( 0.75, chunk.probability(2) )
            self.assertEqual( 3, chunk.primary_designator(3) )
            self.assertEqual( 1, chunk.secondary_designator(3) )
            self.assertAlmostEqual( 5.5, chunk.energy(3) )
            self.assertAlmostEqual( 1.00, chunk.probability(3) )

            self.assertEqual( True, chunk.is_radiative_transition(1) )
            self.assertEqual( False, chunk.is_radiative_transition(2) )
            self.assertEqual( False, chunk.is_radiative_transition(3) )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SubshellTransitionData(
                  primary = [ 1, 2, 3 ],
                  secondary = [ 0, 3, 1 ],
                  energies = [ 3.5, 2.5, 5.5 ],
                  probabilities = [ 0.25, 0.75, 1. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
