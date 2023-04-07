# standard imports
import unittest

# third party imports

# local imports
from ACEtk import ParameterData

class Test_ACEtk_ParameterData( unittest.TestCase ) :
    """Unit test for the ParameterData class."""

    chunk = [ 0, 3, 1., 3., 5., 2., 4., 6. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 8, chunk.length )
            self.assertEqual( "DLW::ParameterData", chunk.name )

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
            self.assertEqual( 3, chunk.number_energy_points )

            self.assertEqual( 3, len( chunk.energies ) )
            self.assertEqual( 1., chunk.energies[0] )
            self.assertEqual( 3., chunk.energies[1] )
            self.assertEqual( 5., chunk.energies[2] )

            self.assertEqual( 3, len( chunk.values ) )
            self.assertEqual( 2., chunk.values[0] )
            self.assertEqual( 4., chunk.values[1] )
            self.assertEqual( 6., chunk.values[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = ParameterData( boundaries = [], interpolants = [],
                               energies = [ 1., 3., 5. ],
                               values = [ 2., 4., 6. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
