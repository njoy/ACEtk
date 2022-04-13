# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import EquiprobableOutgoingEnergyBinData
from ACEtk import EquiprobableOutgoingEnergyBins

class Test_ACEtk_EquiprobableOutgoingEnergyBinData( unittest.TestCase ) :
    """Unit test for the EquiprobableOutgoingEnergyBinData class."""

    chunk = [                 0,
                              2,
                         1.0e-5,  2.00000000000E+01,
                              4,
              1.00000000000E-04,  1.00000000000E+00,  1.00000000000E+01,  2.00000000000E+01,
              1.00000000000E-05,  3.00000000000E+00,  1.20000000000E+01,  2.00000000000E+01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 13, chunk.length )
            self.assertEqual( "EquiprobableOutgoingEnergyBinData", chunk.name )

            self.assertEqual( EnergyDistributionType.Equiprobable, chunk.LAW )
            self.assertEqual( EnergyDistributionType.Equiprobable, chunk.type )

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

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )

            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 20., chunk.incident_energies[1] )

            self.assertAlmostEqual( 1e-5, chunk.incident_energy(1) )
            self.assertAlmostEqual( 20., chunk.incident_energy(2) )

            self.assertAlmostEqual( 1e-5, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( True, isinstance( chunk.distribution(1), EquiprobableOutgoingEnergyBins )  )
            self.assertEqual( True, isinstance( chunk.distribution(2), EquiprobableOutgoingEnergyBins ) )

            self.assertEqual( 2, len( chunk.distributions ) )

            data1 = chunk.distributions[0]
            self.assertAlmostEqual( 1e-5, data1.incident_energy )
            self.assertEqual( 3, data1.number_bins )
            self.assertEqual( 4, len( data1.energies ) )
            self.assertAlmostEqual( 1e-4, data1.energies[0] )
            self.assertAlmostEqual( 1., data1.energies[1] )
            self.assertAlmostEqual( 10., data1.energies[2] )
            self.assertAlmostEqual( 20., data1.energies[3] )

            data2 = chunk.distributions[1]
            self.assertAlmostEqual( 20., data2.incident_energy )
            self.assertEqual( 3, data2.number_bins )
            self.assertEqual( 4, len( data2.energies ) )
            self.assertAlmostEqual( 1e-5, data2.energies[0] )
            self.assertAlmostEqual( 3., data2.energies[1] )
            self.assertAlmostEqual( 12., data2.energies[2] )
            self.assertAlmostEqual( 20., data2.energies[3] )

            data1 = chunk.distribution(1)
            self.assertAlmostEqual( 1e-5, data1.incident_energy )
            self.assertEqual( 3, data1.number_bins )
            self.assertEqual( 4, len( data1.energies ) )
            self.assertAlmostEqual( 1e-4, data1.energies[0] )
            self.assertAlmostEqual( 1., data1.energies[1] )
            self.assertAlmostEqual( 10., data1.energies[2] )
            self.assertAlmostEqual( 20., data1.energies[3] )

            data2 = chunk.distribution(2)
            self.assertAlmostEqual( 20., data2.incident_energy )
            self.assertEqual( 3, data2.number_bins )
            self.assertEqual( 4, len( data2.energies ) )
            self.assertAlmostEqual( 1e-5, data2.energies[0] )
            self.assertAlmostEqual( 3., data2.energies[1] )
            self.assertAlmostEqual( 12., data2.energies[2] )
            self.assertAlmostEqual( 20., data2.energies[3] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = EquiprobableOutgoingEnergyBinData(
                    distributions = [

                      EquiprobableOutgoingEnergyBins( 1e-5, [ 1e-4, 1., 10., 20. ] ),
                      EquiprobableOutgoingEnergyBins( 20., [ 1e-5, 3., 12., 20. ] ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
