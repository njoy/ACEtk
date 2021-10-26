# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import OutgoingEnergyDistributionData
from ACEtk import TabulatedOutgoingEnergyDistribution

class Test_ACEtk_OutgoingEnergyDistributionData( unittest.TestCase ) :
    """Unit test for the OutgoingEnergyDistributionData class."""

    chunk = [            0,             2,  1.000000E-11,  2.000000E+01,
                        27,            38,             2,             3,
              0.000000E+00,  3.100000E-01,  1.840000E+00,  2.364290E-01,
              1.050191E+00,  0.000000E+00,  0.000000E+00,  4.932501E-01,
              1.000000E+00,             2,             2,  0.000000E+00,
              1.840000E+00,  5.000000E-01,  5.000000E-01,  0.000000E+00,
              1.000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 25, chunk.length )
            self.assertEqual( "DLW::OutgoingEnergyDistributionData", chunk.name )

            self.assertEqual( EnergyDistributionType.TabulatedEnergy, chunk.LAW )
            self.assertEqual( EnergyDistributionType.TabulatedEnergy, chunk.type )

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )

            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 1e-11, chunk.incident_energies[0] )
            self.assertAlmostEqual( 20., chunk.incident_energies[1] )

            self.assertAlmostEqual( 1e-11, chunk.incident_energy(1) )
            self.assertAlmostEqual( 20., chunk.incident_energy(2) )

            self.assertEqual( 27, chunk.LOCC(1) );
            self.assertEqual( 38, chunk.LOCC(2) );
            self.assertEqual( 27, chunk.distribution_locator(1) );
            self.assertEqual( 38, chunk.distribution_locator(2) );

            self.assertEqual( 7, chunk.relative_distribution_locator(1) );
            self.assertEqual( 18, chunk.relative_distribution_locator(2) );

            self.assertEqual( True, isinstance( chunk.distribution(1), TabulatedOutgoingEnergyDistribution )  )
            self.assertEqual( True, isinstance( chunk.distribution(2), TabulatedOutgoingEnergyDistribution ) )

            data1 = chunk.distribution(1);
            self.assertAlmostEqual( 1e-11, data1.incident_energy )
            self.assertEqual( 2, data1.interpolation )
            self.assertEqual( 0, data1.number_discrete_photon_lines )
            self.assertEqual( 3, data1.number_outgoing_energies )

            self.assertEqual( 3, len( data1.outgoing_energies ) )
            self.assertAlmostEqual( 0., data1.outgoing_energies[0] )
            self.assertAlmostEqual( 1.84, data1.outgoing_energies[-1] )

            self.assertEqual( 3, len( data1.pdf ) )
            self.assertAlmostEqual( 2.364290E-01, data1.pdf[0] )
            self.assertAlmostEqual( 0., data1.pdf[-1] )

            self.assertEqual( 3, len( data1.cdf ) )
            self.assertAlmostEqual( 0., data1.cdf[0] )
            self.assertAlmostEqual( 1., data1.cdf[-1] )

            data2 = chunk.distribution(2);
            self.assertAlmostEqual( 20., data2.incident_energy )
            self.assertEqual( 2, data2.interpolation )
            self.assertEqual( 0, data2.number_discrete_photon_lines )
            self.assertEqual( 2, data2.number_outgoing_energies )

            self.assertEqual( 2, len( data2.outgoing_energies ) )
            self.assertAlmostEqual( 0., data2.outgoing_energies[0] )
            self.assertAlmostEqual( 1.84, data2.outgoing_energies[-1] )

            self.assertEqual( 2, len( data2.pdf ) )
            self.assertAlmostEqual( 0.5, data2.pdf[0] )
            self.assertAlmostEqual( 0.5, data2.pdf[-1] )

            self.assertEqual( 2, len( data2.cdf ) )
            self.assertAlmostEqual( 0., data2.cdf[0] )
            self.assertAlmostEqual( 1., data2.cdf[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = OutgoingEnergyDistributionData(
                    distributions = [

                      TabulatedOutgoingEnergyDistribution(
                          1e-11, 2, [ 0.0, .31, 1.84 ],
                          [ 2.364290E-01, 1.050191E+00, 0. ], [ 0., 4.932501E-01, 1. ] ),
                      TabulatedOutgoingEnergyDistribution(
                          20., 2, [ 0.0, 1.84 ], [ .5, .5 ], [ 0., 1. ] ) ],
                   locb = 21 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
