# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import MultiDistributionData
from ACEtk import DistributionProbability
from ACEtk import KalbachMannDistributionData
from ACEtk import TabulatedKalbachMannDistribution
from ACEtk import GeneralEvaporationSpectrum

class Test_ACEtk_MultiDistributionData( unittest.TestCase ) :
    """Unit test for the MultiDistributionData class."""

    chunk = [           56,                 44,            21,             0,
                         2,       1.219437E+01,  2.000000E+01,  2.500000E-01,
              7.500000E-01,
                         0,             2,  1.219437E+01,  2.000000E+01,
                        27,            39,             1,             2,
              0.000000E+00,  1.866919E-02,  5.356419E+01,  0.000000E+00,
              0.000000E+00,  1.000000E+00,  0.000000E+00,  0.000000E+00,
              2.391154E-01,  2.398743E-01,             2,             3,
              0.000000E+00,  1.120151E+00,  7.592137E+00,  7.738696E-02,
              4.209016E-01,  1.226090E-11,  0.000000E+00,  5.382391E-01,
              1.000000E+00,  2.491475E-03,  1.510768E-02,  9.775367E-01,
              2.391154E-01,  2.847920E-01,  5.592013E-01,
                        0,                  5,            65,             0,
                        2,               1e-5,  2.000000E+01,  7.500000E-01,
              2.500000E-01,
              0,
              4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
              3, 5., 6., 7. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 67, chunk.length )
            self.assertEqual( "DLW::MultiDistributionData", chunk.name )

            self.assertEqual( EnergyDistributionType.MultiDistribution, chunk.LAW )
            self.assertEqual( EnergyDistributionType.MultiDistribution, chunk.type )

            self.assertEqual( 2, chunk.number_distributions )
            self.assertEqual( 2, len( chunk.probabilities ) )
            self.assertEqual( 2, len( chunk.distributions ) )

            probability1 = chunk.probability( 1 );
            self.assertEqual( 0, probability1.interpolation_data.NB )
            self.assertEqual( 0, probability1.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( probability1.interpolation_data.INT ) )
            self.assertEqual( 0, len( probability1.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( probability1.interpolation_data.NBT ) )
            self.assertEqual( 0, len( probability1.interpolation_data.boundaries ) )

            self.assertEqual( 0, probability1.NB )
            self.assertEqual( 0, probability1.number_interpolation_regions )
            self.assertEqual( 0, len( probability1.INT ) )
            self.assertEqual( 0, len( probability1.interpolants ) )
            self.assertEqual( 0, len( probability1.NBT ) )
            self.assertEqual( 0, len( probability1.boundaries ) )

            self.assertEqual( 2, probability1.NE )
            self.assertEqual( 2, probability1.number_energy_points )

            self.assertEqual( 2, len( probability1.energies ) )
            self.assertAlmostEqual( 1.219437E+01, probability1.energies[0] )
            self.assertAlmostEqual( 20., probability1.energies[1] )

            self.assertEqual( 2, len( probability1.probabilities ) )
            self.assertEqual( 0.25, probability1.probabilities[0] )
            self.assertEqual( 0.75, probability1.probabilities[1] )

            probability2 = chunk.probability( 2 );
            self.assertEqual( 0, probability2.interpolation_data.NB )
            self.assertEqual( 0, probability2.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( probability2.interpolation_data.INT ) )
            self.assertEqual( 0, len( probability2.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( probability2.interpolation_data.NBT ) )
            self.assertEqual( 0, len( probability2.interpolation_data.boundaries ) )

            self.assertEqual( 0, probability2.NB )
            self.assertEqual( 0, probability2.number_interpolation_regions )
            self.assertEqual( 0, len( probability2.INT ) )
            self.assertEqual( 0, len( probability2.interpolants ) )
            self.assertEqual( 0, len( probability2.NBT ) )
            self.assertEqual( 0, len( probability2.boundaries ) )

            self.assertEqual( 2, probability2.NE )
            self.assertEqual( 2, probability2.number_energy_points )

            self.assertEqual( 2, len( probability2.energies ) )
            self.assertEqual( 1e-5, probability2.energies[0] )
            self.assertEqual( 20., probability2.energies[1] )

            self.assertEqual( 2, len( probability2.probabilities ) )
            self.assertEqual( 0.75, probability2.probabilities[0] )
            self.assertEqual( 0.25, probability2.probabilities[1] )

            self.assertEqual( True, isinstance( chunk.distribution( 1 ), KalbachMannDistributionData ) )
            self.assertEqual( True, isinstance( chunk.distribution( 2 ), GeneralEvaporationSpectrum ) )
            self.assertEqual( True, isinstance( chunk.distributions[0], KalbachMannDistributionData ) )
            self.assertEqual( True, isinstance( chunk.distributions[1], GeneralEvaporationSpectrum ) )

            distribution1 = chunk.distribution( 1 )
            self.assertEqual( 0, distribution1.interpolation_data.NB )
            self.assertEqual( 0, distribution1.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( distribution1.interpolation_data.INT ) )
            self.assertEqual( 0, len( distribution1.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( distribution1.interpolation_data.NBT ) )
            self.assertEqual( 0, len( distribution1.interpolation_data.boundaries ) )

            self.assertEqual( 0, distribution1.NB )
            self.assertEqual( 0, distribution1.number_interpolation_regions )
            self.assertEqual( 0, len( distribution1.INT ) )
            self.assertEqual( 0, len( distribution1.interpolants ) )
            self.assertEqual( 0, len( distribution1.NBT ) )
            self.assertEqual( 0, len( distribution1.boundaries ) )

            self.assertEqual( 2, distribution1.NE )
            self.assertEqual( 2, distribution1.number_incident_energies )

            self.assertEqual( 2, len( distribution1.incident_energies ) )
            self.assertAlmostEqual( 1.219437E+01, distribution1.incident_energies[0] )
            self.assertAlmostEqual( 20., distribution1.incident_energies[1] )

            self.assertAlmostEqual( 1.219437E+01, distribution1.incident_energy(1) )
            self.assertAlmostEqual( 20., distribution1.incident_energy(2) )

            self.assertAlmostEqual( 1.219437E+01, distribution1.minimum_incident_energy )
            self.assertAlmostEqual( 20., distribution1.maximum_incident_energy )

            self.assertEqual( 27, distribution1.LOCC(1) );
            self.assertEqual( 39, distribution1.LOCC(2) );
            self.assertEqual( 27, distribution1.distribution_locator(1) );
            self.assertEqual( 39, distribution1.distribution_locator(2) );

            self.assertEqual( 7, distribution1.relative_distribution_locator(1) );
            self.assertEqual( 19, distribution1.relative_distribution_locator(2) );

            self.assertEqual( True, isinstance( distribution1.distribution(1), TabulatedKalbachMannDistribution )  )
            self.assertEqual( True, isinstance( distribution1.distribution(2), TabulatedKalbachMannDistribution ) )

            data1 = distribution1.distribution(1);
            self.assertAlmostEqual( 1.219437E+01, data1.incident_energy )
            self.assertEqual( 1, data1.interpolation )
            self.assertEqual( 0, data1.number_discrete_photon_lines )
            self.assertEqual( 2, data1.number_outgoing_energies )

            self.assertEqual( 2, len( data1.outgoing_energies ) )
            self.assertAlmostEqual( 0., data1.outgoing_energies[0] )
            self.assertAlmostEqual( 1.866919E-02, data1.outgoing_energies[-1] )

            self.assertEqual( 2, len( data1.pdf ) )
            self.assertAlmostEqual( 5.356419E+01, data1.pdf[0] )
            self.assertAlmostEqual( 0., data1.pdf[-1] )

            self.assertEqual( 2, len( data1.cdf ) )
            self.assertAlmostEqual( 0., data1.cdf[0] )
            self.assertAlmostEqual( 1., data1.cdf[-1] )

            self.assertEqual( 2, len( data1.precompound_fraction_values ) )
            self.assertAlmostEqual( 0., data1.precompound_fraction_values[0] )
            self.assertAlmostEqual( 0., data1.precompound_fraction_values[-1] )

            self.assertEqual( 2, len( data1.angular_distribution_slope_values ) )
            self.assertAlmostEqual( 2.391154E-01, data1.angular_distribution_slope_values[0] )
            self.assertAlmostEqual( 2.398743E-01, data1.angular_distribution_slope_values[-1] )

            data2 = distribution1.distribution(2);
            self.assertAlmostEqual( 20., data2.incident_energy )
            self.assertEqual( 2, data2.interpolation )
            self.assertEqual( 0, data2.number_discrete_photon_lines )
            self.assertEqual( 3, data2.number_outgoing_energies )

            self.assertEqual( 3, len( data2.outgoing_energies ) )
            self.assertAlmostEqual( 0., data2.outgoing_energies[0] )
            self.assertAlmostEqual( 7.592137E+00, data2.outgoing_energies[-1] )

            self.assertEqual( 3, len( data2.pdf ) )
            self.assertAlmostEqual( 7.738696E-02, data2.pdf[0] )
            self.assertAlmostEqual( 1.226090E-11, data2.pdf[-1] )

            self.assertEqual( 3, len( data2.cdf ) )
            self.assertAlmostEqual( 0., data2.cdf[0] )
            self.assertAlmostEqual( 1., data2.cdf[-1] )

            self.assertEqual( 3, len( data2.precompound_fraction_values ) )
            self.assertAlmostEqual( 2.491475E-03, data2.precompound_fraction_values[0] )
            self.assertAlmostEqual( 9.775367E-01, data2.precompound_fraction_values[-1] )

            self.assertEqual( 3, len( data2.angular_distribution_slope_values ) )
            self.assertAlmostEqual( 2.391154E-01, data2.angular_distribution_slope_values[0] )
            self.assertAlmostEqual( 5.592013E-01, data2.angular_distribution_slope_values[-1] )

            distribution2 = chunk.distribution( 2 )
            self.assertEqual( 0, distribution2.interpolation_data.NB )
            self.assertEqual( 0, distribution2.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( distribution2.interpolation_data.INT ) )
            self.assertEqual( 0, len( distribution2.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( distribution2.interpolation_data.NBT ) )
            self.assertEqual( 0, len( distribution2.interpolation_data.boundaries ) )

            self.assertEqual( 0, distribution2.NB )
            self.assertEqual( 0, distribution2.number_interpolation_regions )
            self.assertEqual( 0, len( distribution2.INT ) )
            self.assertEqual( 0, len( distribution2.interpolants ) )
            self.assertEqual( 0, len( distribution2.NBT ) )
            self.assertEqual( 0, len( distribution2.boundaries ) )

            self.assertEqual( 4, distribution2.NE )
            self.assertEqual( 4, distribution2.number_energy_points )

            self.assertEqual( 4, len( distribution2.energies ) )
            self.assertAlmostEqual( 1e-5, distribution2.energies[0] )
            self.assertAlmostEqual( 1., distribution2.energies[1] )
            self.assertAlmostEqual( 10., distribution2.energies[2] )
            self.assertAlmostEqual( 20., distribution2.energies[3] )

            self.assertEqual( 4, len( distribution2.temperatures ) )
            self.assertAlmostEqual( 1., distribution2.temperatures[0] )
            self.assertAlmostEqual( 2., distribution2.temperatures[1] )
            self.assertAlmostEqual( 3., distribution2.temperatures[2] )
            self.assertAlmostEqual( 4., distribution2.temperatures[3] )

            self.assertAlmostEqual( 1e-5, distribution2.minimum_incident_energy )
            self.assertAlmostEqual( 20., distribution2.maximum_incident_energy )

            self.assertEqual( 3, distribution2.NET )
            self.assertEqual( 2, distribution2.number_bins )

            self.assertEqual( 3, len( distribution2.bins ) )
            self.assertAlmostEqual( 5., distribution2.bins[0] )
            self.assertAlmostEqual( 6., distribution2.bins[1] )
            self.assertAlmostEqual( 7., distribution2.bins[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = MultiDistributionData(
                  probabilities  = [
                      DistributionProbability( [ 1.219437E+01, 2.000000E+01 ],
                                               [ 2.500000E-01, 7.500000E-01 ] ),
                      DistributionProbability( [ 1e-5, 2.000000E+01 ],
                                               [ 7.500000E-01, 2.500000E-01 ] ) ],
                  distributions  = [
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
                              [ 2.391154E-01, 2.847920E-01, 5.592013E-01 ] ) ] ),
                          GeneralEvaporationSpectrum(
                              [ 1e-5, 1., 10., 20. ], [ 1., 2., 3., 4. ], [ 5., 6., 7. ] ) ],
                  locb = 12 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
