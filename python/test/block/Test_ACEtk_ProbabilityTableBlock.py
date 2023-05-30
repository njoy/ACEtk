# standard imports
import unittest

# third party imports

# local imports
from ACEtk import ProbabilityTableBlock
from ACEtk import ProbabilityTable

class Test_ACEtk_ProbabilityTableBlock( unittest.TestCase ) :
    """Unit test for the ProbabilityTableBlock class."""

    chunk = [ 2, 2, 2, -1, 0, 1, 1e-3, 1e+3,
              0.5, 1., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10.,
              0.25, 1.0, 11., 12., 13., 14., 15., 16., 17., 18., 19., 20. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 32, chunk.length )
            self.assertEqual( "UNR", chunk.name )

            self.assertEqual( 2, chunk.N )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 2, len( chunk.data ) )

            self.assertEqual( 2, chunk.M )
            self.assertEqual( 2, chunk.number_bins )
            self.assertEqual( -1, chunk.ILF )
            self.assertEqual( -1, chunk.inelastic_competion )
            self.assertEqual( 0, chunk.IOA )
            self.assertEqual( 0, chunk.absorption_competion )
            self.assertEqual( 1, chunk.IFF )
            self.assertEqual( 1, chunk.type )

            self.assertEqual( 2, len( chunk.energies ) )
            self.assertAlmostEqual( 1e-3, chunk.energies[0] )
            self.assertAlmostEqual( 1e+3, chunk.energies[1] )

            table1 = chunk.probability_table(1)
            self.assertAlmostEqual( 1e-3, table1.incident_energy )

            self.assertEqual( 2, table1.number_bins )
            self.assertEqual( 2, len( table1.cumulative_probabilities ) )
            self.assertEqual( 2, len( table1.total ) )
            self.assertEqual( 2, len( table1.elastic ) )
            self.assertEqual( 2, len( table1.fission ) )
            self.assertEqual( 2, len( table1.capture ) )
            self.assertEqual( 2, len( table1.heating ) )

            self.assertAlmostEqual( 0.5, table1.cumulative_probabilities[0] )
            self.assertAlmostEqual( 1.0, table1.cumulative_probabilities[-1] )
            self.assertAlmostEqual( 1., table1.total[0] )
            self.assertAlmostEqual( 2., table1.total[-1] )
            self.assertAlmostEqual( 3., table1.elastic[0] )
            self.assertAlmostEqual( 4., table1.elastic[-1] )
            self.assertAlmostEqual( 5., table1.fission[0] )
            self.assertAlmostEqual( 6., table1.fission[-1] )
            self.assertAlmostEqual( 7., table1.capture[0] )
            self.assertAlmostEqual( 8., table1.capture[-1] )
            self.assertAlmostEqual( 9., table1.heating[0] )
            self.assertAlmostEqual( 10., table1.heating[-1] )

            table2 = chunk.probability_table(2);
            self.assertAlmostEqual( 1e+3, table2.incident_energy )

            self.assertEqual( 2, table2.number_bins )
            self.assertEqual( 2, len( table2.cumulative_probabilities ) )
            self.assertEqual( 2, len( table2.total ) )
            self.assertEqual( 2, len( table2.elastic ) )
            self.assertEqual( 2, len( table2.fission ) )
            self.assertEqual( 2, len( table2.capture ) )
            self.assertEqual( 2, len( table2.heating ) )

            self.assertAlmostEqual( 0.25, table2.cumulative_probabilities[0] )
            self.assertAlmostEqual( 1.0, table2.cumulative_probabilities[-1] )
            self.assertAlmostEqual( 11., table2.total[0] )
            self.assertAlmostEqual( 12., table2.total[-1] )
            self.assertAlmostEqual( 13., table2.elastic[0] )
            self.assertAlmostEqual( 14., table2.elastic[-1] )
            self.assertAlmostEqual( 15., table2.fission[0] )
            self.assertAlmostEqual( 16., table2.fission[-1] )
            self.assertAlmostEqual( 17., table2.capture[0] )
            self.assertAlmostEqual( 18., table2.capture[-1] )
            self.assertAlmostEqual( 19., table2.heating[0] )
            self.assertAlmostEqual( 20., table2.heating[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = ProbabilityTableBlock(
                  interpolation = 2, inelastic = -1, absorption = 0, type = 1,
                  tables = [

                    ProbabilityTable( 1e-3, [ 0.5, 1.0 ], [ 1., 2 ], [ 3., 4. ], [ 5., 6. ],
                                      [ 7., 8. ], [ 9., 10. ] ),
                    ProbabilityTable( 1e+3, [ 0.25, 1.0 ], [ 11., 12 ], [ 13., 14. ],
                                      [ 15., 16. ], [ 17., 18. ], [ 19., 20. ] )
                  ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
