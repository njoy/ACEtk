# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import EnergyAngleDistributionData
from ACEtk import TabulatedEnergyAngleDistribution
from ACEtk import TabulatedAngularDistribution

class Test_ACEtk_EnergyAngleDistributionData( unittest.TestCase ) :
    """Unit test for the KalbachMannDistributionData class."""

    chunk = [              0,             2,  1.000000E-05,  2.000000E+01,
                          27,            52,
                           0,             2,  2.100000E+00,  2.000000E+01,
                          33,            44,             2,             3,
               -1.000000E+00,  0.000000E+00,  1.000000E+00,  0.500000E+00,
                0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
                1.000000E+00,             1,             2, -1.000000E+00,
                1.000000E+00,  0.500000E+00,  0.500000E+00,  0.000000E+00,
                1.000000E+00,
                           0,             2,  1.100000E+00,  1.500000E+01,
                          58,            66,             1,             2,
               -1.000000E+00,  1.000000E+00,  0.500000E+00,  0.500000E+00,
                0.000000E+00,  1.000000E+00,             2,             3,
               -1.000000E+00,  0.000000E+00,  1.000000E+00,  0.500000E+00,
                0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
                1.000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 56, chunk.length )
            self.assertEqual( "EnergyAngleDistributionData", chunk.name )

            self.assertEqual( EnergyDistributionType.TabulatedEnergyAngle, chunk.LAW )
            self.assertEqual( EnergyDistributionType.TabulatedEnergyAngle, chunk.type )

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
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 20., chunk.incident_energies[-1] )

            self.assertAlmostEqual( 1e-5, chunk.incident_energy(1) )
            self.assertAlmostEqual( 20., chunk.incident_energy(2) )

            self.assertAlmostEqual( 1e-5, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( 27, chunk.LOCC(1) );
            self.assertEqual( 52, chunk.LOCC(2) );
            self.assertEqual( 27, chunk.distribution_locator(1) );
            self.assertEqual( 52, chunk.distribution_locator(2) );

            self.assertEqual( 7, chunk.relative_distribution_locator(1) );
            self.assertEqual( 32, chunk.relative_distribution_locator(2) );

            self.assertEqual( True, isinstance( chunk.distribution(1), TabulatedEnergyAngleDistribution )  )
            self.assertEqual( True, isinstance( chunk.distribution(2), TabulatedEnergyAngleDistribution ) )

            data1 = chunk.distribution(1)
            self.assertAlmostEqual( 1e-5, data1.incident_energy )

            self.assertEqual( 0, data1.interpolation_data.NB )
            self.assertEqual( 0, data1.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( data1.interpolation_data.INT ) )
            self.assertEqual( 0, len( data1.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( data1.interpolation_data.NBT ) )
            self.assertEqual( 0, len( data1.interpolation_data.boundaries ) )

            self.assertEqual( 0, data1.NB )
            self.assertEqual( 0, data1.number_interpolation_regions )
            self.assertEqual( 0, len( data1.INT ) )
            self.assertEqual( 0, len( data1.interpolants ) )
            self.assertEqual( 0, len( data1.NBT ) )
            self.assertEqual( 0, len( data1.boundaries ) )

            self.assertEqual( 2, data1.NE )
            self.assertEqual( 2, data1.number_outgoing_energies )

            self.assertEqual( 2, len( data1.outgoing_energies ) )
            self.assertAlmostEqual( 2.1, data1.outgoing_energies[0] )
            self.assertAlmostEqual( 20., data1.outgoing_energies[-1] )

            self.assertAlmostEqual( 2.1, data1.outgoing_energy(1) )
            self.assertAlmostEqual( 20., data1.outgoing_energy(2) )

            self.assertEqual( 33, data1.LOCC(1) );
            self.assertEqual( 44, data1.LOCC(2) );
            self.assertEqual( 33, data1.distribution_locator(1) );
            self.assertEqual( 44, data1.distribution_locator(2) );

            self.assertEqual( 7, data1.relative_distribution_locator(1) );
            self.assertEqual( 18, data1.relative_distribution_locator(2) );

            data11 = data1.distribution(1)
            self.assertAlmostEqual( 2.1, data11.energy )
            self.assertEqual( 2, data11.interpolation )
            self.assertEqual( 3, data11.number_cosines )

            self.assertEqual( 3, len( data11.cosines ) )
            self.assertEqual( -1., data11.cosines[0] )
            self.assertEqual( +1., data11.cosines[-1] )

            self.assertEqual( 3, len( data11.pdf ) )
            self.assertEqual( .5, data11.pdf[0] )
            self.assertEqual( .5, data11.pdf[-1] )

            self.assertEqual( 3, len( data11.cdf ) )
            self.assertEqual( 0., data11.cdf[0] )
            self.assertEqual( 1., data11.cdf[-1] )

            data12 = data1.distribution(2)
            self.assertEqual( 20, data12.energy )
            self.assertEqual( 1, data12.interpolation )
            self.assertEqual( 2, data12.number_cosines )

            self.assertEqual( 2, len( data12.cosines ) )
            self.assertEqual( -1., data12.cosines[0] )
            self.assertEqual( +1., data12.cosines[-1] )

            self.assertEqual( 2, len( data12.pdf ) )
            self.assertEqual( .5, data12.pdf[0] )
            self.assertEqual( .5, data12.pdf[-1] )

            self.assertEqual( 2, len( data12.cdf ) )
            self.assertEqual( 0., data12.cdf[0] )
            self.assertEqual( 1., data12.cdf[-1] )

            data2 = chunk.distribution(2)
            self.assertAlmostEqual( 20., data2.incident_energy )

            self.assertEqual( 0, data2.interpolation_data.NB )
            self.assertEqual( 0, data2.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( data2.interpolation_data.INT ) )
            self.assertEqual( 0, len( data2.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( data2.interpolation_data.NBT ) )
            self.assertEqual( 0, len( data2.interpolation_data.boundaries ) )

            self.assertEqual( 0, data2.NB )
            self.assertEqual( 0, data2.number_interpolation_regions )
            self.assertEqual( 0, len( data2.INT ) )
            self.assertEqual( 0, len( data2.interpolants ) )
            self.assertEqual( 0, len( data2.NBT ) )
            self.assertEqual( 0, len( data2.boundaries ) )

            self.assertEqual( 2, data2.NE )
            self.assertEqual( 2, data2.number_outgoing_energies )

            self.assertEqual( 2, len( data2.outgoing_energies ) )
            self.assertAlmostEqual( 1.1, data2.outgoing_energies[0] )
            self.assertAlmostEqual( 15., data2.outgoing_energies[-1] )

            self.assertAlmostEqual( 1.1, data2.outgoing_energy(1) )
            self.assertAlmostEqual( 15., data2.outgoing_energy(2) )

            self.assertEqual( 58, data2.LOCC(1) );
            self.assertEqual( 66, data2.LOCC(2) );
            self.assertEqual( 58, data2.distribution_locator(1) );
            self.assertEqual( 66, data2.distribution_locator(2) );

            self.assertEqual( 7, data2.relative_distribution_locator(1) );
            self.assertEqual( 15, data2.relative_distribution_locator(2) );

            data21 = data2.distribution(1)
            self.assertAlmostEqual( 1.1, data21.energy )
            self.assertEqual( 1, data21.interpolation )
            self.assertEqual( 2, data21.number_cosines )

            self.assertEqual( 2, len( data21.cosines ) )
            self.assertEqual( -1., data21.cosines[0] )
            self.assertEqual( +1., data21.cosines[-1] )

            self.assertEqual( 2, len( data21.pdf ) )
            self.assertEqual( .5, data21.pdf[0] )
            self.assertEqual( .5, data21.pdf[-1] )

            self.assertEqual( 2, len( data21.cdf ) )
            self.assertEqual( 0., data21.cdf[0] )
            self.assertEqual( 1., data21.cdf[-1] )

            data22 = data2.distribution(2)
            self.assertEqual( 15, data22.energy )
            self.assertEqual( 2, data22.interpolation )
            self.assertEqual( 3, data22.number_cosines )

            self.assertEqual( 3, len( data22.cosines ) )
            self.assertEqual( -1., data22.cosines[0] )
            self.assertEqual( +1., data22.cosines[-1] )

            self.assertEqual( 3, len( data22.pdf ) )
            self.assertEqual( .5, data22.pdf[0] )
            self.assertEqual( .5, data22.pdf[-1] )

            self.assertEqual( 3, len( data22.cdf ) )
            self.assertEqual( 0., data22.cdf[0] )
            self.assertEqual( 1., data22.cdf[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = EnergyAngleDistributionData(
                    distributions = [

                      TabulatedEnergyAngleDistribution(
                        1e-5,
                        [ TabulatedAngularDistribution(
                            2.1, 2, [ -1.0, 0.0, 1.0 ], [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ),
                          TabulatedAngularDistribution(
                            20., 1, [ -1.0, 1.0 ], [ 0.5, 0.5 ], [ 0.0, 1.0 ] ) ] ),
                      TabulatedEnergyAngleDistribution(
                        20.,
                        [ TabulatedAngularDistribution(
                            1.1, 1, [ -1.0, 1.0 ], [ 0.5, 0.5 ], [ 0.0, 1.0 ] ),
                          TabulatedAngularDistribution(
                            15., 2, [ -1.0, 0.0, 1.0 ], [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ) ] ) ],
                   locb = 21 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
