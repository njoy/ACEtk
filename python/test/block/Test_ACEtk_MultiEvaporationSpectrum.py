# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import MultiEvaporationSpectrum
from ACEtk import DistributionProbability
from ACEtk import EvaporationSpectrum

class Test_ACEtk_MultiEvaporationSpectrum( unittest.TestCase ) :
    """Unit test for the MultiEvaporationSpectrum class."""

    chunk = [           32,                  9,            21,             0,
                         2,               1e-5,  2.000000E+01,  2.500000E-01,
              7.500000E-01,
                         0,
                         4, 1e-5, 2., 5., 20., 5., 6., 7., 8., 1.5e+6,
                         0,                  9,            41,             0,
                         2,               1e-5,  2.000000E+01,  7.500000E-01,
              2.500000E-01,
                         0,
                         4, 1e-5, 1., 10., 20., 1., 2., 3., 4., 2e+6 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 40, chunk.length )
            self.assertEqual( "MultiEvaporationSpectrum", chunk.name )

            self.assertEqual( EnergyDistributionType.MultiEvaporation, chunk.LAW )
            self.assertEqual( EnergyDistributionType.MultiEvaporation, chunk.type )

            self.assertEqual( 2, chunk.number_distributions )
            self.assertEqual( 2, len( chunk.probabilities ) )
            self.assertEqual( 2, len( chunk.distributions ) )

            probability1 = chunk.probability( 1 )
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
            self.assertAlmostEqual( 1e-5, probability1.energies[0] )
            self.assertAlmostEqual( 20., probability1.energies[1] )

            self.assertEqual( 2, len( probability1.probabilities ) )
            self.assertEqual( 0.25, probability1.probabilities[0] )
            self.assertEqual( 0.75, probability1.probabilities[1] )

            probability2 = chunk.probability( 2 )
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

            self.assertEqual( True, isinstance( chunk.distribution( 1 ), EvaporationSpectrum ) )
            self.assertEqual( True, isinstance( chunk.distribution( 2 ), EvaporationSpectrum ) )
            self.assertEqual( True, isinstance( chunk.distributions[0], EvaporationSpectrum ) )
            self.assertEqual( True, isinstance( chunk.distributions[1], EvaporationSpectrum ) )

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

            self.assertEqual( 4, distribution1.NE )
            self.assertEqual( 4, distribution1.number_energy_points )

            self.assertEqual( 4, len( distribution1.energies ) )
            self.assertAlmostEqual( 1e-5, distribution1.energies[0] )
            self.assertAlmostEqual( 2., distribution1.energies[1] )
            self.assertAlmostEqual( 5., distribution1.energies[2] )
            self.assertAlmostEqual( 20., distribution1.energies[3] )

            self.assertEqual( 4, len( distribution1.temperatures ) )
            self.assertAlmostEqual( 5., distribution1.temperatures[0] )
            self.assertAlmostEqual( 6., distribution1.temperatures[1] )
            self.assertAlmostEqual( 7., distribution1.temperatures[2] )
            self.assertAlmostEqual( 8., distribution1.temperatures[3] )

            self.assertAlmostEqual( 1e-5, distribution1.minimum_incident_energy )
            self.assertAlmostEqual( 20., distribution1.maximum_incident_energy )

            self.assertEqual( 1.5e+6, distribution1.U )
            self.assertEqual( 1.5e+6, distribution1.restriction_energy )

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

            self.assertEqual( 2e+6, distribution2.U )
            self.assertEqual( 2e+6, distribution2.restriction_energy )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = MultiEvaporationSpectrum(
                  probabilities  = [
                      DistributionProbability( [ 1e-5, 2.000000E+01 ],
                                               [ 2.500000E-01, 7.500000E-01 ] ),
                      DistributionProbability( [ 1e-5, 2.000000E+01 ],
                                               [ 7.500000E-01, 2.500000E-01 ] ) ],
                  distributions  = [
                      EvaporationSpectrum( [ 1e-5, 2., 5., 20. ], [ 5., 6., 7., 8. ], 1.5e+6 ),
                      EvaporationSpectrum( [ 1e-5, 1., 10., 20. ], [ 1., 2., 3., 4. ], 2e+6 ) ],
                  locb = 12 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
