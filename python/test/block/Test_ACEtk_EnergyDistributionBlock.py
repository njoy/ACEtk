# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionBlock
from ACEtk import TabulatedKalbachMannDistribution
from ACEtk import LevelScatteringDistribution
from ACEtk import KalbachMannDistributionData
from ACEtk import EnergyDistributionType
from ACEtk import ReferenceFrame
from ACEtk import TabulatedMultiplicity

class Test_ACEtk_EnergyDistributionBlock( unittest.TestCase ) :
    """Unit test for the EnergyDistributionBlock class."""

    chunk = [ # LDLW
                              7,                 18,
              # DLW - reaction 1 - energy dependent multiplicity
                              0,                  2,  1.00000000000E-11,  2.00000000000E+01,
              1.00000000000E+00,  1.00000000000E+00,
              # DLW - reaction 1 - LNW = 0, LAW = 3, IDAT = 16
                              0,                  3,                 16,                  0,
                              2,        2.249999e-3,  2.00000000000E+01,  1.00000000000E+00,
              1.00000000000E+00,  7.71295800000E-05,           .9914722,
              # DLW - reaction 1 - LNW = 0, LAW = 44, IDAT = 27
                              0,                 44,                 27,                  0,
                              2,       1.219437E+01,  2.00000000000E+01,  1.00000000000E+00,
              1.00000000000E+00,                  0,                  2,       1.219437E+01,
                   2.000000E+01,                 33,                 45,                  1,
                              2,       0.000000E+00,       1.866919E-02,       5.356419E+01,
                   0.000000E+00,       0.000000E+00,       1.000000E+00,       0.000000E+00,
                   0.000000E+00,       2.391154E-01,       2.398743E-01,                  2,
                              3,       0.000000E+00,       1.120151E+00,       7.592137E+00,
                   7.738696E-02,       4.209016E-01,       1.226090E-11,       0.000000E+00,
                   5.382391E-01,       1.000000E+00,       2.491475E-03,       1.510768E-02,
                   9.775367E-01,       2.391154E-01,       2.847920E-01,       5.592013E-01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 63, chunk.length )
            self.assertEqual( "DLW", chunk.name )

            self.assertEqual( 2, chunk.NR )
            self.assertEqual( 2, chunk.number_reactions )
            self.assertEqual( 2, len( chunk.data ) )

            self.assertEqual( 7, chunk.LDLW(1) )
            self.assertEqual( 18, chunk.LDLW(2) )
            self.assertEqual( 7, chunk.energy_distribution_locator(1) )
            self.assertEqual( 18, chunk.energy_distribution_locator(2) )

            self.assertEqual( True, isinstance( chunk.energy_distribution_data(1), LevelScatteringDistribution ) )
            self.assertEqual( True, isinstance( chunk.energy_distribution_data(2), KalbachMannDistributionData ) )

            self.assertEqual( True, isinstance( chunk.data[0], LevelScatteringDistribution ) )
            self.assertEqual( True, isinstance( chunk.data[1], KalbachMannDistributionData ) )

            data1 = chunk.energy_distribution_data(1)
            self.assertEqual( EnergyDistributionType.LevelScattering, data1.LAW )
            self.assertEqual( EnergyDistributionType.LevelScattering, data1.type )
            self.assertAlmostEqual( 2.249999e-3, data1.minimum_incident_energy )
            self.assertAlmostEqual( 20., data1.maximum_incident_energy )
            self.assertAlmostEqual( 7.71295800000E-05, data1.C1 )
            self.assertAlmostEqual( .9914722, data1.C2 )

            data2 = chunk.energy_distribution_data(2)
            self.assertEqual( EnergyDistributionType.KalbachMann, data2.LAW )
            self.assertEqual( EnergyDistributionType.KalbachMann, data2.type )
            self.assertEqual( 2, data2.NE )
            self.assertEqual( 2, data2.number_incident_energies )
            self.assertEqual( 2, len( data2.incident_energies ) )
            self.assertAlmostEqual( 1.219437E+01, data2.incident_energies[0] )
            self.assertAlmostEqual( 20., data2.incident_energies[1] )
            self.assertAlmostEqual( 1.219437E+01, data2.incident_energy(1) )
            self.assertAlmostEqual( 20., data2.incident_energy(2) )
            self.assertAlmostEqual( 1.219437E+01, data2.minimum_incident_energy )
            self.assertAlmostEqual( 20., data2.maximum_incident_energy )
            self.assertEqual( 33, data2.LOCC(1) )
            self.assertEqual( 45, data2.LOCC(2) )
            self.assertEqual( 33, data2.distribution_locator(1) )
            self.assertEqual( 45, data2.distribution_locator(2) )
            self.assertEqual( 7, data2.relative_distribution_locator(1) )
            self.assertEqual( 19, data2.relative_distribution_locator(2) )
            data21 = data2.distribution(1)
            self.assertAlmostEqual( 1.219437E+01, data21.incident_energy )
            self.assertEqual( 1, data21.interpolation )
            self.assertEqual( 0, data21.number_discrete_photon_lines )
            self.assertEqual( 2, data21.number_outgoing_energies )
            self.assertEqual( 2, len( data21.outgoing_energies ) )
            self.assertAlmostEqual( 0.0, data21.outgoing_energies[0] )
            self.assertAlmostEqual( 1.866919E-02, data21.outgoing_energies[-1] )
            self.assertEqual( 2, len( data21.pdf  ) )
            self.assertAlmostEqual( 5.356419E+01, data21.pdf[0] )
            self.assertAlmostEqual( 0., data21.pdf[-1] )
            self.assertEqual( 2, len( data21.cdf ) )
            self.assertAlmostEqual( 0., data21.cdf[0] )
            self.assertAlmostEqual( 1., data21.cdf[-1] )
            self.assertEqual( 2, len( data21.precompound_fraction_values ) )
            self.assertEqual( 0., data21.precompound_fraction_values[0] )
            self.assertEqual( 0., data21.precompound_fraction_values[-1] )
            self.assertEqual( 2, len( data21.angular_distribution_slope_values ) )
            self.assertEqual( 2.391154E-01, data21.angular_distribution_slope_values[0] )
            self.assertEqual( 2.398743E-01, data21.angular_distribution_slope_values[-1] )
            data22 = data2.distribution(2)
            self.assertAlmostEqual( 20., data22.incident_energy )
            self.assertEqual( 2, data22.interpolation )
            self.assertEqual( 0, data22.number_discrete_photon_lines )
            self.assertEqual( 3, data22.number_outgoing_energies )
            self.assertEqual( 3, len( data22.outgoing_energies ) )
            self.assertAlmostEqual( 0.0, data22.outgoing_energies[0] )
            self.assertAlmostEqual( 7.592137E+00, data22.outgoing_energies[-1] )
            self.assertEqual( 3, len( data22.pdf ) )
            self.assertAlmostEqual( 7.738696E-02, data22.pdf[0] )
            self.assertAlmostEqual( 1.226090E-11, data22.pdf[-1] )
            self.assertEqual( 3, len( data22.cdf ) )
            self.assertAlmostEqual( 0., data22.cdf[0] )
            self.assertAlmostEqual( 1., data22.cdf[-1] )
            self.assertEqual( 3, len( data22.precompound_fraction_values ) )
            self.assertAlmostEqual( 2.491475E-03, data22.precompound_fraction_values[0] )
            self.assertAlmostEqual( 9.775367E-01, data22.precompound_fraction_values[-1] )
            self.assertEqual( 3, len( data22.angular_distribution_slope_values ) )
            self.assertAlmostEqual( 2.391154E-01, data22.angular_distribution_slope_values[0] )
            self.assertAlmostEqual( 5.592013E-01, data22.angular_distribution_slope_values[-1] )

            self.assertEqual( ReferenceFrame.Laboratory, chunk.reference_frame(1) )
            self.assertEqual( ReferenceFrame.CentreOfMass, chunk.reference_frame(2) )

            self.assertEqual( True, isinstance( chunk.multiplicity_data(1), TabulatedMultiplicity ) )
            self.assertEqual( True, isinstance( chunk.multiplicity_data(2), int ) )

            multiplicity1 = chunk.multiplicity_data(1)
            self.assertEqual( 0, multiplicity1.interpolation_data.NB )
            self.assertEqual( 0, multiplicity1.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( multiplicity1.interpolation_data.INT ) )
            self.assertEqual( 0, len( multiplicity1.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( multiplicity1.interpolation_data.NBT ) )
            self.assertEqual( 0, len( multiplicity1.interpolation_data.boundaries ) )

            self.assertEqual( 0, multiplicity1.NB )
            self.assertEqual( 0, multiplicity1.number_interpolation_regions )
            self.assertEqual( 0, len( multiplicity1.INT ) )
            self.assertEqual( 0, len( multiplicity1.interpolants ) )
            self.assertEqual( 0, len( multiplicity1.NBT ) )
            self.assertEqual( 0, len( multiplicity1.boundaries ) )

            self.assertEqual( 2, multiplicity1.NE )
            self.assertEqual( 2, multiplicity1.number_energy_points )

            self.assertEqual( 2, len( multiplicity1.energies ) )
            self.assertAlmostEqual( 1e-11, multiplicity1.energies[0] )
            self.assertAlmostEqual( 20., multiplicity1.energies[1] )

            self.assertEqual( 2, len( multiplicity1.multiplicities ) )
            self.assertEqual( 1., multiplicity1.multiplicities[0] )
            self.assertEqual( 1., multiplicity1.multiplicities[1] )

            multiplicity2 = chunk.multiplicity_data(2)
            self.assertEqual( 1, multiplicity2 )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = EnergyDistributionBlock(
                  distributions = [
                      LevelScatteringDistribution( 2.249999e-3, 20.,
                                                   7.71295800000E-05, .9914722 ),
                      KalbachMannDistributionData(
                        [ TabulatedKalbachMannDistribution(
                            1.219437E+01, 1, [ 0.000000E+00, 1.866919E-02 ],
                            [ 5.356419E+01, 0.000000E+00 ], [ 0., 1. ], [ 0., 0. ],
                            [ 2.391154E-01, 2.398743E-01 ] ),
                          TabulatedKalbachMannDistribution(
                            20., 2, [ 0.000000E+00, 1.120151E+00, 7.592137E+00 ],
                            [ 7.738696E-02, 4.209016E-01, 1.226090E-11 ],
                            [ 0.000000E+00, 5.382391E-01, 1.000000E+00 ],
                            [ 2.491475E-03, 1.510768E-02, 9.775367E-01 ],
                            [ 2.391154E-01, 2.847920E-01, 5.592013E-01 ] ) ] ) ],
                  frames = [ ReferenceFrame.Laboratory,
                             ReferenceFrame.CentreOfMass ],
                  multiplicities = [
                      TabulatedMultiplicity( [ 1e-11, 20. ], [ 1., 1. ] ),
                      1 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
