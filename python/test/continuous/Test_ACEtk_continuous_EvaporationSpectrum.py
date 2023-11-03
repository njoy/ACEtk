# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk.continuous import EvaporationSpectrum

class Test_ACEtk_continuous_EvaporationSpectrum( unittest.TestCase ) :
    """Unit test for the EvaporationSpectrum class."""

    chunk = [ 0,
              4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
              1.5e+6 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 11, chunk.length )
            self.assertEqual( "EvaporationSpectrum", chunk.name )

            self.assertEqual( EnergyDistributionType.Evaporation, chunk.LAW )
            self.assertEqual( EnergyDistributionType.Evaporation, chunk.type )

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

            self.assertEqual( 4, chunk.NE )
            self.assertEqual( 4, chunk.number_energy_points )

            self.assertEqual( 4, len( chunk.energies ) )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 1., chunk.energies[1] )
            self.assertAlmostEqual( 10., chunk.energies[2] )
            self.assertAlmostEqual( 20., chunk.energies[3] )

            self.assertEqual( 4, len( chunk.temperatures ) )
            self.assertAlmostEqual( 1., chunk.temperatures[0] )
            self.assertAlmostEqual( 2., chunk.temperatures[1] )
            self.assertAlmostEqual( 3., chunk.temperatures[2] )
            self.assertAlmostEqual( 4., chunk.temperatures[3] )

            self.assertAlmostEqual( 1e-5, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( 1.5e+6, chunk.U )
            self.assertEqual( 1.5e+6, chunk.restriction_energy )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = EvaporationSpectrum(
                    boundaries = [], interpolants = [],
                    energies = [ 1e-5, 1., 10., 20. ],
                    temperatures = [ 1., 2., 3., 4. ],
                    energy = 1.5e+6 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
