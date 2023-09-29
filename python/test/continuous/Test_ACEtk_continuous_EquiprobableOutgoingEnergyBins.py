# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import EquiprobableOutgoingEnergyBins

class Test_ACEtk_EquiprobableOutgoingEnergyBins( unittest.TestCase ) :
    """Unit test for the EquiprobableOutgoingEnergyBins class."""

    chunk = [  1.00000000000E-05,  2.00000000000E-02,  1.00000000000E+00,  2.00000000000E+01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 4, chunk.length )
            self.assertEqual( "EquiprobableOutgoingEnergyBins", chunk.name )

            self.assertEqual( 2.1, chunk.incident_energy )
            self.assertEqual( 3, chunk.number_bins )

            self.assertEqual( 4, len( chunk.energies ) )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 2e-2, chunk.energies[1] )
            self.assertAlmostEqual( 1., chunk.energies[2] )
            self.assertAlmostEqual( 20., chunk.energies[3] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = EquiprobableOutgoingEnergyBins(
                    incident = 2.1,
                    energies = [ 1e-5, 2e-2, 1., 20. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
