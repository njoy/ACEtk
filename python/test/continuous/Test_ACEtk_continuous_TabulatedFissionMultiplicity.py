# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import TabulatedFissionMultiplicity

class Test_ACEtk_TabulatedFissionMultiplicity( unittest.TestCase ) :
    """Unit test for the TabulatedFissionMultiplicity class."""

    chunk = [                  2,                   0,                   3,
               1.00000000000E-11,   1.00000000000E+00,   2.00000000000E+01,   2.35000000000E+00,
               2.55000000000E+00,   7.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 9, chunk.length )
            self.assertEqual( "TabulatedFissionMultiplicity", chunk.name )

            self.assertEqual( 2, chunk.LNU )
            self.assertEqual( 2, chunk.type )

            self.assertEqual( 0, chunk.interpolation_data.NB )
            self.assertEqual( 0, chunk.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.interpolation_data.INT ) )
            self.assertEqual( 0, len( chunk.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( chunk.interpolation_data.NBT ) )
            self.assertEqual( 0, len( chunk.interpolation_data.boundaries ) )

            self.assertEqual( 0, chunk.NB )
            self.assertEqual( 0, chunk.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.INT ) )
            self.assertEqual( 0, len( chunk.interpolants ) )
            self.assertEqual( 0, len( chunk.NBT ) )
            self.assertEqual( 0, len( chunk.boundaries ) )

            self.assertEqual( 3, chunk.NE )
            self.assertEqual( 3, chunk.number_values )

            self.assertEqual( 3, len( chunk.energies ) )
            self.assertAlmostEqual( 1e-11, chunk.energies[0] )
            self.assertAlmostEqual( 1., chunk.energies[1] )
            self.assertAlmostEqual( 20., chunk.energies[2] )

            self.assertEqual( 3, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 2.35, chunk.multiplicities[0] )
            self.assertAlmostEqual( 2.55, chunk.multiplicities[1] )
            self.assertAlmostEqual( 7., chunk.multiplicities[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = TabulatedFissionMultiplicity(
                  energies = [ 1e-11, 1., 20. ],
                  multiplicities = [ 2.35, 2.55, 7. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
