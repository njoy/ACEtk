# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoatomicElectronSubshellBlock

class Test_ACEtk_PhotoatomicElectronSubshellBlock( unittest.TestCase ) :
    """Unit test for the PhotoatomicElectronSubshellBlock class."""

    chunk = [                                                             1.000000000000E+00,
              2.000000000000E+00, 3.000000000000E+00, 4.000000000000E+00, 5.000000000000E+00,
              2.000000000000E+00, 2.000000000000E+00, 2.000000000000E+00, 4.000000000000E+00,
              2.000000000000E+00, 1.294500000000E-03, 8.946000000000E-05, 5.655000000000E-05,
              5.624000000000E-05, 6.890000000000E-06, 1.666666666667E-01, 3.333333333333E-01,
              5.000000000000E-01, 8.333333333333E-01, 1.000000000000E+00, 1.200000000000E+01,
              5.000000000000E+00, 3.000000000000E+00, 2.000000000000E+00, 0.000000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 25, chunk.length )
            self.assertEqual( "SUBSH", chunk.name )

            self.assertEqual( 25, len( chunk.xss_array ) )

            self.assertEqual( 5, chunk.NSSH )
            self.assertEqual( 5, chunk.number_electron_subshells )

            self.assertEqual( 1, chunk.ENDF[0] )
            self.assertEqual( 2, chunk.ENDF[1] )
            self.assertEqual( 3, chunk.ENDF[2] )
            self.assertEqual( 4, chunk.ENDF[3] )
            self.assertEqual( 5, chunk.ENDF[4] )
            self.assertEqual( 1, chunk.designators[0] )
            self.assertEqual( 2, chunk.designators[1] )
            self.assertEqual( 3, chunk.designators[2] )
            self.assertEqual( 4, chunk.designators[3] )
            self.assertEqual( 5, chunk.designators[4] )

            self.assertEqual( 2, chunk.EP[0] )
            self.assertEqual( 2, chunk.EP[1] )
            self.assertEqual( 2, chunk.EP[2] )
            self.assertEqual( 4, chunk.EP[3] )
            self.assertEqual( 2, chunk.EP[4] )
            self.assertEqual( 2, chunk.populations[0] )
            self.assertEqual( 2, chunk.populations[1] )
            self.assertEqual( 2, chunk.populations[2] )
            self.assertEqual( 4, chunk.populations[3] )
            self.assertEqual( 2, chunk.populations[4] )

            self.assertEqual( 1.2945e-3, chunk.BE[0] )
            self.assertEqual( 8.9460e-5, chunk.BE[1] )
            self.assertEqual( 5.6550e-5, chunk.BE[2] )
            self.assertEqual( 5.6240e-5, chunk.BE[3] )
            self.assertEqual( 6.8900e-6, chunk.BE[4] )
            self.assertEqual( 1.2945e-3, chunk.binding_energies[0] )
            self.assertEqual( 8.9460e-5, chunk.binding_energies[1] )
            self.assertEqual( 5.6550e-5, chunk.binding_energies[2] )
            self.assertEqual( 5.6240e-5, chunk.binding_energies[3] )
            self.assertEqual( 6.8900e-6, chunk.binding_energies[4] )

            self.assertEqual( 1.666666666667e-1, chunk.CV[0] )
            self.assertEqual( 3.333333333333e-1, chunk.CV[1] )
            self.assertEqual( 5.000000000000e-1, chunk.CV[2] )
            self.assertEqual( 8.333333333333e-1, chunk.CV[3] )
            self.assertEqual( 1.000000000000e+0, chunk.CV[4] )
            self.assertEqual( 1.666666666667e-1, chunk.vacancy_probabilities[0] )
            self.assertEqual( 3.333333333333e-1, chunk.vacancy_probabilities[1] )
            self.assertEqual( 5.000000000000e-1, chunk.vacancy_probabilities[2] )
            self.assertEqual( 8.333333333333e-1, chunk.vacancy_probabilities[3] )
            self.assertEqual( 1.000000000000e+0, chunk.vacancy_probabilities[4] )

            self.assertEqual( 12, chunk.NT[0] )
            self.assertEqual(  5, chunk.NT[1] )
            self.assertEqual(  3, chunk.NT[2] )
            self.assertEqual(  2, chunk.NT[3] )
            self.assertEqual(  0, chunk.NT[4] )
            self.assertEqual( 12, chunk.number_transitions[0] )
            self.assertEqual(  5, chunk.number_transitions[1] )
            self.assertEqual(  3, chunk.number_transitions[2] )
            self.assertEqual(  2, chunk.number_transitions[3] )
            self.assertEqual(  0, chunk.number_transitions[4] )

            self.assertEqual( 1, chunk.designator( 1 ) )
            self.assertEqual( 2, chunk.designator( 2 ) )
            self.assertEqual( 3, chunk.designator( 3 ) )
            self.assertEqual( 4, chunk.designator( 4 ) )
            self.assertEqual( 5, chunk.designator( 5 ) )

            self.assertEqual( 2, chunk.population( 1 ) )
            self.assertEqual( 2, chunk.population( 2 ) )
            self.assertEqual( 2, chunk.population( 3 ) )
            self.assertEqual( 4, chunk.population( 4 ) )
            self.assertEqual( 2, chunk.population( 5 ) )

            self.assertEqual( 1.2945e-3, chunk.binding_energy( 1 ) )
            self.assertEqual( 8.9460e-5, chunk.binding_energy( 2 ) )
            self.assertEqual( 5.6550e-5, chunk.binding_energy( 3 ) )
            self.assertEqual( 5.6240e-5, chunk.binding_energy( 4 ) )
            self.assertEqual( 6.8900e-6, chunk.binding_energy( 5 ) )

            self.assertEqual( 1.666666666667e-1, chunk.vacancy_probability( 1 ) )
            self.assertEqual( 3.333333333333e-1, chunk.vacancy_probability( 2 ) )
            self.assertEqual( 5.000000000000e-1, chunk.vacancy_probability( 3 ) )
            self.assertEqual( 8.333333333333e-1, chunk.vacancy_probability( 4 ) )
            self.assertEqual( 1.000000000000e+0, chunk.vacancy_probability( 5 ) )

            self.assertEqual( 12, chunk.transitions( 1 ) )
            self.assertEqual(  5, chunk.transitions( 2 ) )
            self.assertEqual(  3, chunk.transitions( 3 ) )
            self.assertEqual(  2, chunk.transitions( 4 ) )
            self.assertEqual(  0, chunk.transitions( 5 ) )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoatomicElectronSubshellBlock(
                  designators = [ 1, 2, 3, 4, 5 ],
                  electrons = [ 2, 2, 2, 4, 2 ],
                  energies = [ 1.2945e-3, 8.946e-5, 5.655e-5,
                                                   5.6240e-5, 6.890e-6 ],
                  probabilities = [ 1.666666666667E-1, 3.333333333333E-1,
                                                        5.000000000000E-1, 8.333333333333E-1,
                                                        1.000000000000E+0 ],
                  transitions = [ 12, 5, 3, 2, 0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
