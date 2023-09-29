# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import EnergyDependentWattSpectrum
from ACEtk.continuous import ParameterData
from ACEtk.continuous import EnergyDistributionType

class Test_ACEtk_EnergyDependentWattSpectrum( unittest.TestCase ) :
    """Unit test for the EnergyDependentWattSpectrum class."""

    chunk = [ 0, 4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
              0, 3, 1e-5, 2., 20., 5., 6., 7.,
              1.5e+6 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 19, chunk.length )
            self.assertEqual( "EnergyDependentWattSpectrum", chunk.name )

            self.assertEqual( EnergyDistributionType.Watt, chunk.LAW )
            self.assertEqual( EnergyDistributionType.Watt, chunk.type )

            self.assertEqual( 0, chunk.a.interpolation_data.NB )
            self.assertEqual( 0, chunk.a.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.a.interpolation_data.INT ) )
            self.assertEqual( 0, len( chunk.a.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( chunk.a.interpolation_data.NBT ) )
            self.assertEqual( 0, len( chunk.a.interpolation_data.boundaries ) )

            self.assertEqual( 0, chunk.a.NB )
            self.assertEqual( 0, chunk.a.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.a.INT ) )
            self.assertEqual( 0, len( chunk.a.interpolants ) )
            self.assertEqual( 0, len( chunk.a.NBT ) )
            self.assertEqual( 0, len( chunk.a.boundaries ) )

            self.assertEqual( 4, chunk.a.NE )
            self.assertEqual( 4, chunk.a.number_energy_points )

            self.assertEqual( 4, len( chunk.a.energies ) )
            self.assertEqual( 1e-5, chunk.a.energies[0] )
            self.assertEqual( 1., chunk.a.energies[1] )
            self.assertEqual( 10., chunk.a.energies[2] )
            self.assertEqual( 20., chunk.a.energies[3] )

            self.assertEqual( 4, len( chunk.a.values ) )
            self.assertEqual( 1., chunk.a.values[0] )
            self.assertEqual( 2., chunk.a.values[1] )
            self.assertEqual( 3., chunk.a.values[2] )
            self.assertEqual( 4., chunk.a.values[3] )

            self.assertEqual( 0, chunk.b.interpolation_data.NB )
            self.assertEqual( 0, chunk.b.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.b.interpolation_data.INT ) )
            self.assertEqual( 0, len( chunk.b.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( chunk.b.interpolation_data.NBT ) )
            self.assertEqual( 0, len( chunk.b.interpolation_data.boundaries ) )

            self.assertEqual( 0, chunk.b.NB )
            self.assertEqual( 0, chunk.b.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.b.INT ) )
            self.assertEqual( 0, len( chunk.b.interpolants ) )
            self.assertEqual( 0, len( chunk.b.NBT ) )
            self.assertEqual( 0, len( chunk.b.boundaries ) )

            self.assertEqual( 3, chunk.b.NE )
            self.assertEqual( 3, chunk.b.number_energy_points )

            self.assertEqual( 3, len( chunk.b.energies ) )
            self.assertEqual( 1e-5, chunk.b.energies[0] )
            self.assertEqual( 2., chunk.b.energies[1] )
            self.assertEqual( 20., chunk.b.energies[2] )

            self.assertEqual( 3, len( chunk.b.values ) )
            self.assertEqual( 5., chunk.b.values[0] )
            self.assertEqual( 6., chunk.b.values[1] )
            self.assertEqual( 7., chunk.b.values[2] )

            self.assertAlmostEqual( 1e-5, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( 1.5e+6, chunk.U )
            self.assertEqual( 1.5e+6, chunk.restriction_energy )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = EnergyDependentWattSpectrum(
                   a = ParameterData( [ 1e-5, 1., 10., 20. ],
                                      [ 1., 2., 3., 4. ] ),
                   b = ParameterData( [ 1e-5, 2., 20. ],
                                      [ 5., 6., 7. ] ),
                   energy = 1.5e+6 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
