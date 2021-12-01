# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import KalbachMannDistributionData
from ACEtk import TabulatedKalbachMannDistribution

class Test_ACEtk_KalbachMannDistributionData( unittest.TestCase ) :
    """Unit test for the KalbachMannDistributionData class."""

    chunk = [            0,             2,  1.219437E+01,  2.000000E+01,
                        27,            39,             1,             2,
              0.000000E+00,  1.866919E-02,  5.356419E+01,  0.000000E+00,
              0.000000E+00,  1.000000E+00,  0.000000E+00,  0.000000E+00,
              2.391154E-01,  2.398743E-01,             2,             3,
              0.000000E+00,  1.120151E+00,  7.592137E+00,  7.738696E-02,
              4.209016E-01,  1.226090E-11,  0.000000E+00,  5.382391E-01,
              1.000000E+00,  2.491475E-03,  1.510768E-02,  9.775367E-01,
              2.391154E-01,  2.847920E-01,  5.592013E-01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 35, chunk.length )
            self.assertEqual( "KalbachMannDistributionData", chunk.name )

            self.assertEqual( EnergyDistributionType.KalbachMann, chunk.LAW )
            self.assertEqual( EnergyDistributionType.KalbachMann, chunk.type )

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
            self.assertAlmostEqual( 1.219437E+01, chunk.incident_energies[0] )
            self.assertAlmostEqual( 20., chunk.incident_energies[1] )

            self.assertAlmostEqual( 1.219437E+01, chunk.incident_energy(1) )
            self.assertAlmostEqual( 20., chunk.incident_energy(2) )

            self.assertAlmostEqual( 1.219437E+01, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( 27, chunk.LOCC(1) );
            self.assertEqual( 39, chunk.LOCC(2) );
            self.assertEqual( 27, chunk.distribution_locator(1) );
            self.assertEqual( 39, chunk.distribution_locator(2) );

            self.assertEqual( 7, chunk.relative_distribution_locator(1) );
            self.assertEqual( 19, chunk.relative_distribution_locator(2) );

            self.assertEqual( True, isinstance( chunk.distribution(1), TabulatedKalbachMannDistribution )  )
            self.assertEqual( True, isinstance( chunk.distribution(2), TabulatedKalbachMannDistribution ) )

            data1 = chunk.distribution(1);
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

            data2 = chunk.distribution(2);
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

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = KalbachMannDistributionData(
                    distributions = [

                      TabulatedKalbachMannDistribution(
                        1.219437E+01, 1, [ 0.000000E+00, 1.866919E-02 ],
                        [ 5.356419E+01, 0.000000E+00 ], [ 0., 1. ], [ 0., 0. ],
                        [ 2.391154E-01, 2.398743E-01 ] ),
                      TabulatedKalbachMannDistribution(
                        20., 2, [ 0.000000E+00, 1.120151E+00, 7.592137E+00 ],
                        [ 7.738696E-02, 4.209016E-01, 1.226090E-11 ],
                        [ 0.000000E+00, 5.382391E-01, 1.000000E+00 ],
                        [ 2.491475E-03, 1.510768E-02, 9.775367E-01 ],
                        [ 2.391154E-01, 2.847920E-01, 5.592013E-01 ] ) ],
                   locb = 21 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
