# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import AngularDistributionData
from ACEtk.continuous import IsotropicAngularDistribution
from ACEtk.continuous import EquiprobableAngularBins
from ACEtk.continuous import TabulatedAngularDistribution
from ACEtk import AngularDistributionType

class Test_ACEtk_AngularDistributionData( unittest.TestCase ) :
    """Unit test for the AngularDistributionData class."""

    chunk = [                  3,  1.00000000000E-11,  1.00000000000E+00,  2.00000000000E+01,
                               0,                 13,               -46,  -1.00000000000E+00,
              -0.90000000000E+00, -0.80000000000E+00, -0.70000000000E+00, -0.60000000000E+00,
              -0.50000000000E+00, -0.30000000000E+00, -0.20000000000E+00, -0.10000000000E+00,
               0.00000000000E+00,  0.05000000000E+00,  0.10000000000E+00,  0.15000000000E+00,
               0.20000000000E+00,  0.25000000000E+00,  0.30000000000E+00,  0.35000000000E+00,
               0.40000000000E+00,  0.45000000000E+00,  0.50000000000E+00,  0.55000000000E+00,
               0.60000000000E+00,  0.65000000000E+00,  0.70000000000E+00,  0.75000000000E+00,
               0.80000000000E+00,  0.85000000000E+00,  0.90000000000E+00,  0.92500000000E+00,
               0.95000000000E+00,  0.96250000000E+00,  0.97500000000E+00,  1.00000000000E+00,
                               2,                  3, -1.00000000000E+00,  0.00000000000E+00,
               1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,  5.00000000000E-01,
               0.00000000000E+00,  5.00000000000E-01,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 51, chunk.length )
            self.assertEqual( "AngularDistributionData", chunk.name )

            self.assertEqual( 3, chunk.NE )
            self.assertEqual( 3, chunk.number_incident_energies )
            self.assertEqual( 3, len( chunk.distributions ) )

            self.assertEqual( 3, len( chunk.incident_energies ) )
            self.assertEqual( 1e-11, chunk.incident_energies[0] )
            self.assertEqual( 1., chunk.incident_energies[1] )
            self.assertEqual( 20., chunk.incident_energies[2] )

            self.assertEqual( 1e-11, chunk.incident_energy(1) )
            self.assertEqual( 1., chunk.incident_energy(2) )
            self.assertEqual( 20., chunk.incident_energy(3) )

            self.assertEqual( 0, chunk.LOCC(1) )
            self.assertEqual( 13, chunk.LOCC(2) )
            self.assertEqual( -46, chunk.LOCC(3) )
            self.assertEqual( 0, chunk.distribution_locator(1) )
            self.assertEqual( 13, chunk.distribution_locator(2) )
            self.assertEqual( -46, chunk.distribution_locator(3) )

            self.assertEqual( AngularDistributionType.Isotropic, chunk.distribution_type(1) )
            self.assertEqual( AngularDistributionType.Equiprobable, chunk.distribution_type(2) )
            self.assertEqual( AngularDistributionType.Tabulated, chunk.distribution_type(3) )
            self.assertEqual( 0, chunk.relative_distribution_locator(1) )
            self.assertEqual( 8, chunk.relative_distribution_locator(2) )
            self.assertEqual( 41, chunk.relative_distribution_locator(3) )

            self.assertEqual( True, isinstance( chunk.distribution(1), IsotropicAngularDistribution )  )
            self.assertEqual( True, isinstance( chunk.distribution(2), EquiprobableAngularBins ) )
            self.assertEqual( True, isinstance( chunk.distribution(3), TabulatedAngularDistribution ) )

            self.assertEqual( True, isinstance( chunk.distributions[0], IsotropicAngularDistribution )  )
            self.assertEqual( True, isinstance( chunk.distributions[1], EquiprobableAngularBins ) )
            self.assertEqual( True, isinstance( chunk.distributions[2], TabulatedAngularDistribution ) )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = AngularDistributionData(
                    distributions = [

                      IsotropicAngularDistribution( 1e-11 ),
                      EquiprobableAngularBins(
                        1.,
                        [ -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.3, -0.2, -0.1, 0.0,
                          0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5,
                          0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.925, 0.95,
                          0.9625, 0.975, 1.0 ] ),
                      TabulatedAngularDistribution(
                        20., 2, [ -1.0, 0.0, 1.0 ], [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ) ],
                   locb = 6 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
