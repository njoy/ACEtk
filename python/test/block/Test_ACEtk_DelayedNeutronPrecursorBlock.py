# standard imports
import unittest

# third party imports

# local imports
from ACEtk import DelayedNeutronPrecursorBlock
from ACEtk import DelayedNeutronPrecursorData

class Test_ACEtk_DelayedNeutronPrecursorBlock( unittest.TestCase ) :
    """Unit test for the DelayedNeutronPrecursorBlock class."""

    chunk = [  2.30000000000E-04,                   0,                   3,
               1.00000000000E-11,   1.00000000000E+00,   2.00000000000E+01,   1.20000000000E-03,
               2.50000000000E-02,   1.00000000000E+00,
               3.20000000000E-04,                   0,                   2,
               1.00000000000E-11,   2.00000000000E+01,   2.40000000000E-03,   2.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 16, chunk.length )
            self.assertEqual( "BDD", chunk.name )

            self.assertEqual( 2, chunk.NPCR )
            self.assertEqual( 2, chunk.number_delayed_precursors )
            self.assertEqual( 2, len( chunk.data ) )

            group = chunk.precursor_group_data( 1 );
            self.assertEqual( 1, group.number )

            self.assertAlmostEqual( 2.3e-4, group.DEC )
            self.assertAlmostEqual( 2.3e-4, group.decay_constant )

            self.assertEqual( 0, group.interpolation_data.NB )
            self.assertEqual( 0, group.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( group.interpolation_data.INT ) )
            self.assertEqual( 0, len( group.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( group.interpolation_data.NBT ) )
            self.assertEqual( 0, len( group.interpolation_data.boundaries ) )

            self.assertEqual( 0, group.NB )
            self.assertEqual( 0, group.number_interpolation_regions )
            self.assertEqual( 0, len( group.INT ) )
            self.assertEqual( 0, len( group.interpolants ) )
            self.assertEqual( 0, len( group.NBT ) )
            self.assertEqual( 0, len( group.boundaries ) )

            self.assertEqual( 3, group.NE )
            self.assertEqual( 3, group.number_values )

            self.assertEqual( 3, len( group.energies ) )
            self.assertAlmostEqual( 1e-11, group.energies[0] )
            self.assertAlmostEqual( 1., group.energies[1] )
            self.assertAlmostEqual( 20., group.energies[2] )

            self.assertEqual( 3, len( group.probabilities ) )
            self.assertAlmostEqual( 1.2e-3, group.probabilities[0] )
            self.assertAlmostEqual( 2.5e-2, group.probabilities[1] )
            self.assertAlmostEqual( 1., group.probabilities[2] )

            group = chunk.precursor_group_data( 2 );
            self.assertEqual( 2, group.number )

            self.assertAlmostEqual( 3.2e-4, group.DEC )
            self.assertAlmostEqual( 3.2e-4, group.decay_constant )

            self.assertEqual( 0, group.interpolation_data.NB )
            self.assertEqual( 0, group.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( group.interpolation_data.INT ) )
            self.assertEqual( 0, len( group.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( group.interpolation_data.NBT ) )
            self.assertEqual( 0, len( group.interpolation_data.boundaries ) )

            self.assertEqual( 0, group.NB )
            self.assertEqual( 0, group.number_interpolation_regions )
            self.assertEqual( 0, len( group.INT ) )
            self.assertEqual( 0, len( group.interpolants ) )
            self.assertEqual( 0, len( group.NBT ) )
            self.assertEqual( 0, len( group.boundaries ) )

            self.assertEqual( 2, group.NE )
            self.assertEqual( 2, group.number_values )

            self.assertEqual( 2, len( group.energies ) )
            self.assertAlmostEqual( 1e-11, group.energies[0] )
            self.assertAlmostEqual( 20., group.energies[1] )

            self.assertEqual( 2, len( group.probabilities ) )
            self.assertAlmostEqual( 2.4e-3, group.probabilities[0] )
            self.assertAlmostEqual( 2., group.probabilities[1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = DelayedNeutronPrecursorBlock(
                  groups = [
                      DelayedNeutronPrecursorData( number = 2,
                                                   constant = 3.2e-4,
                                                   energies = [ 1e-11, 20. ],
                                                   probabilities = [ 2.4e-3, 2. ] ),
                      DelayedNeutronPrecursorData( number = 1,
                                                   constant = 2.3e-4,
                                                   energies = [ 1e-11, 1., 20. ],
                                                   probabilities = [ 1.2e-3, 2.5e-2, 1. ] ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
