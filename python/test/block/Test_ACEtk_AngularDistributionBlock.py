# standard imports
import unittest

# third party imports

# local imports
from ACEtk import AngularDistributionBlock
from ACEtk import DistributionGivenElsewhere
from ACEtk import FullyIsotropicDistribution
from ACEtk import AngularDistributionData
from ACEtk import IsotropicAngularDistribution
from ACEtk import EquiprobableAngularBins
from ACEtk import TabulatedAngularDistribution
from ACEtk import AngularDistributionType

class Test_ACEtk_AngularDistributionBlock( unittest.TestCase ) :
    """Unit test for the AngularDistributionBlock class."""

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

            self.assertEqual( 1, chunk.LAND(0) )
            self.assertEqual( -1, chunk.LAND(1) )
            self.assertEqual( 0, chunk.LAND(2) )
            self.assertEqual( 25, chunk.LAND(3) )
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
            self.assertAlmostEqual( 1e-11, data.incident_energies[0] )
            self.assertAlmostEqual( 20., data.incident_energies[1] )
            self.assertAlmostEqual( 1e-11, data.incident_energy(1) )
            self.assertAlmostEqual( 20., data.incident_energy(2) )
            self.assertEqual( -6, data.LOCC(1) )
            self.assertEqual( -14, data.LOCC(2) )
            self.assertEqual( -6, data.distribution_locator(1) )
            self.assertEqual( -14, data.distribution_locator(2) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(1) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(2) )
            self.assertEqual( 6, data.relative_distribution_locator(1) )
            self.assertEqual( 14, data.relative_distribution_locator(2) )
            self.assertEqual( True, isinstance( data.distribution(1), TabulatedAngularDistribution ) )
            self.assertEqual( True, isinstance( data.distribution(2), TabulatedAngularDistribution ) )

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
            self.assertEqual( -32, data.distribution_locator(1) )
            self.assertEqual( 0, data.distribution_locator(2) )
            self.assertEqual( -43, data.distribution_locator(3) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(1) )
            self.assertEqual( AngularDistributionType.Isotropic, data.distribution_type(2) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(3) )
            self.assertEqual( 8, data.relative_distribution_locator(1) )
            self.assertEqual( 0, data.relative_distribution_locator(2) )
            self.assertEqual( 19, data.relative_distribution_locator(3) )
            self.assertEqual( True, isinstance( data.distribution(1), TabulatedAngularDistribution ) )
            self.assertEqual( True, isinstance( data.distribution(2), IsotropicAngularDistribution ) )
            self.assertEqual( True, isinstance( data.distribution(3), TabulatedAngularDistribution ) )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        def verify_chunk_without_elastic( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 54, chunk.length )
            self.assertEqual( "AND", chunk.name )

            self.assertEqual( 4, chunk.NR )
            self.assertEqual( 4, chunk.number_projectile_production_reactions )

            self.assertEqual( 1, chunk.LAND(1) )
            self.assertEqual( -1, chunk.LAND(2) )
            self.assertEqual( 0, chunk.LAND(3) )
            self.assertEqual( 25, chunk.LAND(4) )
            self.assertEqual( 1, chunk.angular_distribution_locator(1) )
            self.assertEqual( -1, chunk.angular_distribution_locator(2) )
            self.assertEqual( 0, chunk.angular_distribution_locator(3) )
            self.assertEqual( 25, chunk.angular_distribution_locator(4) )

            self.assertEqual( False, chunk.is_fully_isotropic(1) )
            self.assertEqual( False, chunk.is_fully_isotropic(2) )
            self.assertEqual( True, chunk.is_fully_isotropic(3) )
            self.assertEqual( False, chunk.is_fully_isotropic(4) )

            self.assertEqual( True, chunk.is_given(1) )
            self.assertEqual( False, chunk.is_given(2) )
            self.assertEqual( True, chunk.is_given(3) )
            self.assertEqual( True, chunk.is_given(4) )

            self.assertEqual( True, isinstance( chunk.angular_distribution_data(1), AngularDistributionData ) )
            self.assertEqual( True, isinstance( chunk.angular_distribution_data(2), DistributionGivenElsewhere ) )
            self.assertEqual( True, isinstance( chunk.angular_distribution_data(3), FullyIsotropicDistribution ) )
            self.assertEqual( True, isinstance( chunk.angular_distribution_data(4), AngularDistributionData ) )

            data = chunk.angular_distribution_data(1)
            self.assertEqual( 2, data.NE )
            self.assertEqual( 2, data.number_incident_energies )
            self.assertEqual( 2, len( data.incident_energies ) )
            self.assertAlmostEqual( 1e-11, data.incident_energies[0] )
            self.assertAlmostEqual( 20., data.incident_energies[1] )
            self.assertAlmostEqual( 1e-11, data.incident_energy(1) )
            self.assertAlmostEqual( 20., data.incident_energy(2) )
            self.assertEqual( -6, data.LOCC(1) )
            self.assertEqual( -14, data.LOCC(2) )
            self.assertEqual( -6, data.distribution_locator(1) )
            self.assertEqual( -14, data.distribution_locator(2) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(1) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(2) )
            self.assertEqual( 6, data.relative_distribution_locator(1) )
            self.assertEqual( 14, data.relative_distribution_locator(2) )
            self.assertEqual( True, isinstance( data.distribution(1), TabulatedAngularDistribution ) )
            self.assertEqual( True, isinstance( data.distribution(2), TabulatedAngularDistribution ) )

            data = chunk.angular_distribution_data(4)
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
            self.assertEqual( -32, data.distribution_locator(1) )
            self.assertEqual( 0, data.distribution_locator(2) )
            self.assertEqual( -43, data.distribution_locator(3) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(1) )
            self.assertEqual( AngularDistributionType.Isotropic, data.distribution_type(2) )
            self.assertEqual( AngularDistributionType.Tabulated, data.distribution_type(3) )
            self.assertEqual( 8, data.relative_distribution_locator(1) )
            self.assertEqual( 0, data.relative_distribution_locator(2) )
            self.assertEqual( 19, data.relative_distribution_locator(3) )
            self.assertEqual( True, isinstance( data.distribution(1), TabulatedAngularDistribution ) )
            self.assertEqual( True, isinstance( data.distribution(2), IsotropicAngularDistribution ) )
            self.assertEqual( True, isinstance( data.distribution(3), TabulatedAngularDistribution ) )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly using elastic data
        chunk = AngularDistributionBlock(
                  elastic =
                      AngularDistributionData(
                          [ TabulatedAngularDistribution( 1e-11, 2, [ -1.0, 1.0 ],
                                                          [ 0.5, 0.5 ], [ 0.0, 1.0 ] ),
                            TabulatedAngularDistribution( 20., 2, [ -1.0, 0.0, 1.0 ],
                                                          [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ) ] ),
                  distributions = [
                      DistributionGivenElsewhere(),
                      FullyIsotropicDistribution(),
                      AngularDistributionData(
                        [ TabulatedAngularDistribution( 1e-11, 2, [ -1.0, 0.0, 1.0 ],
                                                        [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ),
                          IsotropicAngularDistribution( 1. ),
                          TabulatedAngularDistribution( 20., 2, [ -1.0, 1.0 ],
                                                        [ 0.5, 0.5 ], [ 0.0, 1.0 ] ) ] ) ] )

        verify_chunk( self, chunk )

        # the data is given explicitly without elastic data
        chunk = AngularDistributionBlock(
                  distributions = [
                      AngularDistributionData(
                        [ TabulatedAngularDistribution( 1e-11, 2, [ -1.0, 1.0 ],
                                                        [ 0.5, 0.5 ], [ 0.0, 1.0 ] ),
                          TabulatedAngularDistribution( 20., 2, [ -1.0, 0.0, 1.0 ],
                                                        [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ) ] ),                      DistributionGivenElsewhere(),
                      FullyIsotropicDistribution(),
                      AngularDistributionData(
                        [ TabulatedAngularDistribution( 1e-11, 2, [ -1.0, 0.0, 1.0 ],
                                                        [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ),
                          IsotropicAngularDistribution( 1. ),
                          TabulatedAngularDistribution( 20., 2, [ -1.0, 1.0 ],
                                                        [ 0.5, 0.5 ], [ 0.0, 1.0 ] ) ] ) ] )

        verify_chunk_without_elastic( self, chunk )

if __name__ == '__main__' :

    unittest.main()
