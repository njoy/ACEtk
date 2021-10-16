# standard imports
import unittest

# third party imports

# local imports
from ACEtk import AngularDistributionData
from ACEtk import IsotropicAngularDistribution
from ACEtk import EquiprobableAngularBins
from ACEtk import TabulatedAngularDistribution
from ACEtk import AngularDistributionType

class Test_ACEtk_TabulatedAngularDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedAngularDistribution class."""

    chunk = [                  1,                 -1,                  0,                 25,
                               2,  1.00000000000E-11,  2.00000000000E+01,                 -6,
                             -14,                  2,                  2, -1.00000000000E+00,
               1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,  0.00000000000E+00,
               1.00000000000E+00,                  2,                  3, -1.00000000000E+00,
               0.00000000000E+00,  1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,
               5.00000000000E-01,  0.00000000000E+00,  5.00000000000E-01,  1.00000000000E+00,
                               3,  1.00000000000E-11,  1.00000000000E+00,  2.00000000000E+01,
                             -32,                  0,                -43,                  2,
                               3, -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
               5.00000000000E-01,  5.00000000000E-01,  5.00000000000E-01,  0.00000000000E+00,
               5.00000000000E-01,  1.00000000000E+00,                  2,                  2,
              -1.00000000000E+00,  1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,
               0.00000000000E+00,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 54, chunk.length )
            self.assertEqual( "AND", chunk.name )

            self.assertEqual( 3, chunk.NR )
            self.assertEqual( 3, chunk.number_projectile_production_reactions )

            self.assertEqual( 1, chunk.LOCC(0) )
            self.assertEqual( -1, chunk.LOCC(1) )
            self.assertEqual( 0, chunk.LOCC(2) )
            self.assertEqual( 25, chunk.LOCC(3) )
            self.assertEqual( 1, chunk.angular_distribution_locator(0) )
            self.assertEqual( -1, chunk.angular_distribution_locator(1) )
            self.assertEqual( 0, chunk.angular_distribution_locator(2) )
            self.assertEqual( 25, chunk.angular_distribution_locator(3) )

            self.assertEqual( False, chunk.is_fully_isotropic(0) )
            self.assertEqual( False, chunk.is_fully_isotropic(1) )
            self.assertEqual( True, chunk.is_fully_isotropic(2) )
            self.assertEqual( False, chunk.is_fully_isotropic(3) )

            self.assertEqual( True, chunk.is_given(0) )
            self.assertEqual( False, chunk.is_given(1) )
            self.assertEqual( True, chunk.is_given(2) )
            self.assertEqual( True, chunk.is_given(3) )

            self.assertEqual( True, isinstance( chunk.angular_distribution_data(0), AngularDistributionData ) )
            self.assertEqual( True, isinstance( chunk.angular_distribution_data(1), DistributionGivenElsewhere ) )
            self.assertEqual( True, isinstance( chunk.angular_distribution_data(2), FullyIsotropicDistribution ) )
            self.assertEqual( True, isinstance( chunk.angular_distribution_data(3), AngularDistributionData ) )

            data = chunk.angular_distribution_data(0) # elastic
            self.assertEqual( 2, data.NE )
            self.assertEqual( 2, data.number_incident_energies )
            self.assertEqual( 2, len( data.incident_energies ) )
            self.assertAlmosEqual( 1e-11, data.incident_energies[0] )
            self.assertAlmosEqual( 20., data.incident_energies[1] )
            self.assertAlmosEqual( 1e-11, data.incident_energy(1) )
            self.assertAlmosEqual( 20., data.incident_energy(2) )
            self.assertEqual( -6, data.LOCC(1) )
            self.assertEqual( -14, data.LOCC(2) )
            self.assertEqual( -6, data.angular_distribution_locator(1) )
            self.assertEqual( -14, data.angular_distribution_locator(2) )
            self.assertEqual( AngularDistributionType.Tabulated, data.angular_distribution_type(1) )
            self.assertEqual( AngularDistributionType.Tabulated, data.angular_distribution_type(2) )
            self.assertEqual( 6, data.relative_angular_distribution_locator(1) )
            self.assertEqual( 14, data.relative_angular_distribution_locator(2) )
            self.assertEqual( true, isinstance( data.angularDistributionData(1), TabulatedAngularDistribution ) )
            self.assertEqual( true, isinstance( data.angularDistributionData(2), TabulatedAngularDistribution ) )

            data = chunk.angular_distribution_data(3)
            self.assertEqual( 3, data.NE )
            self.assertEqual( 3, data.number_incident_energies )
            self.assertEqual( 3, len( data.incident_energies ) )
            self.assertAlmostEqual( 1e-11, data.incident_energies[0] )
            self.assertAlmostEqual( 1., data.incident_energies[1] )
            self.assertAlmostEqual( 20., data.incident_energies[2] )
            self.assertAlmostEqual( 1e-11, data.incident_energy(1) )
            self.assertAlmostEqual( 1., data.incident_energy(2) )
            self.assertAlmostEqual( 20., data.incident_energy(3) )
            self.assertEqual( -32, data.LOCC(1) )
            self.assertEqual( 0, data.LOCC(2) )
            self.assertEqual( -43, data.LOCC(3) )
            self.assertEqual( -32, data.angular_distribution_locator(1) )
            self.assertEqual( 0, data.angular_distribution_locator(2) )
            self.assertEqual( -43, data.angular_distribution_locator(3) )
            self.assertEqual( AngularDistributionType.Tabulated, data.angular_distribution_type(1) )
            self.assertEqual( AngularDistributionType.Isotropic, data.angular_distribution_type(2) )
            self.assertEqual( AngularDistributionType.Tabulated, data.angular_distribution_type(3) )
            self.assertEqual( 8, data.relative_angular_distribution_locator(1) )
            self.assertEqual( 0, data.relative_angular_distribution_locator(2) )
            self.assertEqual( 19, data.relative_angular_distribution_locator(3) )
            self.assertEqual( true, isinstance( data.angularDistributionData(1), TabulatedAngularDistribution ) )
            self.assertEqual( true, isinstance( data.angularDistributionData(1), IsotropicAngularDistribution ) )
            self.assertEqual( true, isinstance( data.angularDistributionData(2), TabulatedAngularDistribution ) )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        # chunk = AngularDistributionData(
        #             distributions = [

        #               IsotropicAngularDistribution( 1e-11 ),
        #               EquiprobableAngularBins(
        #                 1.,
        #                 [ -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.3, -0.2, -0.1, 0.0,
        #                   0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5,
        #                   0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.925, 0.95,
        #                   0.9625, 0.975, 1.0 ] ),
        #               TabulatedAngularDistribution(
        #                 20., 2, [ -1.0, 0.0, 1.0 ], [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ) ],
        #            locb = 6 )

        # verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
