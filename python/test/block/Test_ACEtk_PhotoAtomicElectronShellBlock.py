# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoAtomicElectronShellBlock

class Test_ACEtk_PhotoAtomicElectronShellBlock( unittest.TestCase ) :
    """Unit test for the PhotoAtomicElectronShellBlock class."""

    chunk = [                                                                                  2,
                                1,  5.480000000000e-05,  1.000000000000e-06,  6.666666666667e-01,
               3.333333333333e-01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 6, chunk.length )
            self.assertEqual( "EPS", chunk.name )

            self.assertEqual( 6, len( chunk.xss_array ) )

            self.assertEqual( 2, chunk.NSH )
            self.assertEqual( 2, chunk.number_electron_shells )

            self.assertEqual( 2, chunk.number_electrons[0] )
            self.assertEqual( 1, chunk.number_electrons[-1] )
            self.assertAlmostEqual( 5.480000000000e-05, chunk.binding_energies[0] )
            self.assertAlmostEqual( 1.000000000000e-06, chunk.binding_energies[-1] )
            self.assertAlmostEqual( 6.666666666667e-01, chunk.interaction_probabilities[0] )
            self.assertAlmostEqual( 3.333333333333e-01, chunk.interaction_probabilities[-1] )

            self.assertEqual( 2, chunk.number_electrons_per_shell( 1 ) )
            self.assertEqual( 1, chunk.number_electrons_per_shell( 2 ) )
            self.assertAlmostEqual( 5.480000000000e-05, chunk.binding_energy( 1 ) )
            self.assertAlmostEqual( 1.000000000000e-06, chunk.binding_energy( 2 ) )
            self.assertAlmostEqual( 6.666666666667e-01, chunk.interaction_probability( 1 ) )
            self.assertAlmostEqual( 3.333333333333e-01, chunk.interaction_probability( 2 ) )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoAtomicElectronShellBlock(
          electrons = [ 2, 1 ],
          energies =  [ 5.480000000000e-05,  1.000000000000e-06 ],
          probabilities = [ 6.666666666667e-01, 3.333333333333e-01 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
