# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk.continuous import AngleEnergyDistributionData
from ACEtk.continuous import TabulatedAngleEnergyDistribution
from ACEtk.continuous import TabulatedEnergyDistribution

class Test_ACEtk_AngleEnergyDistributionData( unittest.TestCase ) :
    """Unit test for the KalbachMannDistributionData class."""

    chunk = [              0,             2,  1.000000E-05,  2.000000E+01,
                          27,            52,
                           2,             2, -1.000000E+00,  1.000000E+00,
                          33,            44,             2,             3,
                1.000000E-05,  1.000000E+00,  2.000000E+01,  0.500000E+00,
                0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
                1.000000E+00,             1,             2,  1.000000E-03,
                1.500000E+01,  0.500000E+00,  0.500000E+00,  0.000000E+00,
                1.000000E+00,
                           2,             2, -9.000000E-01,  9.000000E-01,
                          58,            66,             1,             2,
                1.000000E-04,  1.200000E+01,  0.500000E+00,  0.500000E+00,
                0.000000E+00,  1.000000E+00,             2,             3,
                1.000000E-02,  2.000000E+00,  1.800000E+01,  0.500000E+00,
                0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
                1.000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 56, chunk.length )
            self.assertEqual( "AngleEnergyDistributionData", chunk.name )

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
            self.assertEqual( 2, len( chunk.distributions ) )

            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 20., chunk.incident_energies[-1] )

            self.assertAlmostEqual( 1e-5, chunk.incident_energy(1) )
            self.assertAlmostEqual( 20., chunk.incident_energy(2) )

            self.assertAlmostEqual( 1e-5, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( 27, chunk.LOCC(1) )
            self.assertEqual( 52, chunk.LOCC(2) )
            self.assertEqual( 27, chunk.distribution_locator(1) )
            self.assertEqual( 52, chunk.distribution_locator(2) )

            self.assertEqual( 7, chunk.relative_distribution_locator(1) )
            self.assertEqual( 32, chunk.relative_distribution_locator(2) )

            self.assertEqual( True, isinstance( chunk.distribution(1), TabulatedAngleEnergyDistribution )  )
            self.assertEqual( True, isinstance( chunk.distribution(2), TabulatedAngleEnergyDistribution ) )

            data1 = chunk.distribution(1)
            self.assertAlmostEqual( 1e-5, data1.incident_energy )

            self.assertEqual( 2, data1.interpolation )

            self.assertEqual( 2, data1.NC )
            self.assertEqual( 2, data1.number_cosines )

            self.assertEqual( 2, len( data1.cosines ) )
            self.assertAlmostEqual( -1., data1.cosines[0] )
            self.assertAlmostEqual( 1., data1.cosines[-1] )

            self.assertAlmostEqual( -1., data1.cosine(1) )
            self.assertAlmostEqual( 1., data1.cosine(2) )

            self.assertEqual( 33, data1.LOCC(1) )
            self.assertEqual( 44, data1.LOCC(2) )
            self.assertEqual( 33, data1.distribution_locator(1) )
            self.assertEqual( 44, data1.distribution_locator(2) )

            self.assertEqual( 7, data1.relative_distribution_locator(1) )
            self.assertEqual( 18, data1.relative_distribution_locator(2) )

            data11 = data1.distribution(1)
            self.assertAlmostEqual( -1., data11.energy_or_cosine )
            self.assertEqual( 2, data11.interpolation )
            self.assertEqual( 3, data11.number_outgoing_energies )

            self.assertEqual( 3, len( data11.outgoing_energies ) )
            self.assertEqual( 1e-5, data11.outgoing_energies[0] )
            self.assertEqual( 20., data11.outgoing_energies[-1] )

            self.assertEqual( 3, len( data11.pdf ) )
            self.assertEqual( .5, data11.pdf[0] )
            self.assertEqual( .5, data11.pdf[-1] )

            self.assertEqual( 3, len( data11.cdf ) )
            self.assertEqual( 0., data11.cdf[0] )
            self.assertEqual( 1., data11.cdf[-1] )

            data12 = data1.distribution(2)
            self.assertEqual( 1., data12.energy_or_cosine )
            self.assertEqual( 1, data12.interpolation )
            self.assertEqual( 2, data12.number_outgoing_energies )

            self.assertEqual( 2, len( data12.outgoing_energies ) )
            self.assertEqual( 1e-3, data12.outgoing_energies[0] )
            self.assertEqual( 15., data12.outgoing_energies[-1] )

            self.assertEqual( 2, len( data12.pdf ) )
            self.assertEqual( .5, data12.pdf[0] )
            self.assertEqual( .5, data12.pdf[-1] )

            self.assertEqual( 2, len( data12.cdf ) )
            self.assertEqual( 0., data12.cdf[0] )
            self.assertEqual( 1., data12.cdf[-1] )

            data2 = chunk.distribution(2)
            self.assertAlmostEqual( 20., data2.incident_energy )

            self.assertEqual( 2, data2.interpolation )

            self.assertEqual( 2, data2.NC )
            self.assertEqual( 2, data2.number_cosines )

            self.assertEqual( 2, len( data2.cosines ) )
            self.assertAlmostEqual( -0.9, data2.cosines[0] )
            self.assertAlmostEqual( 0.9, data2.cosines[-1] )

            self.assertAlmostEqual( -0.9, data2.cosine(1) )
            self.assertAlmostEqual( 0.9, data2.cosine(2) )

            self.assertEqual( 58, data2.LOCC(1) )
            self.assertEqual( 66, data2.LOCC(2) )
            self.assertEqual( 58, data2.distribution_locator(1) )
            self.assertEqual( 66, data2.distribution_locator(2) )

            self.assertEqual( 7, data2.relative_distribution_locator(1) )
            self.assertEqual( 15, data2.relative_distribution_locator(2) )

            data21 = data2.distribution(1)
            self.assertAlmostEqual( -0.9, data21.energy_or_cosine )
            self.assertEqual( 1, data21.interpolation )
            self.assertEqual( 2, data21.number_outgoing_energies )

            self.assertEqual( 2, len( data21.outgoing_energies ) )
            self.assertEqual( 1e-4, data21.outgoing_energies[0] )
            self.assertEqual( 12., data21.outgoing_energies[-1] )

            self.assertEqual( 2, len( data21.pdf ) )
            self.assertEqual( .5, data21.pdf[0] )
            self.assertEqual( .5, data21.pdf[-1] )

            self.assertEqual( 2, len( data21.cdf ) )
            self.assertEqual( 0., data21.cdf[0] )
            self.assertEqual( 1., data21.cdf[-1] )

            data22 = data2.distribution(2)
            self.assertEqual( 0.9, data22.energy_or_cosine )
            self.assertEqual( 2, data22.interpolation )
            self.assertEqual( 3, data22.number_outgoing_energies )

            self.assertEqual( 3, len( data22.outgoing_energies ) )
            self.assertEqual( 1e-2, data22.outgoing_energies[0] )
            self.assertEqual( 18., data22.outgoing_energies[-1] )

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
        chunk = AngleEnergyDistributionData(
                    distributions = [

                      TabulatedAngleEnergyDistribution(
                        1e-5, 2,
                        [ TabulatedEnergyDistribution(
                            -1., 2, [ 1e-5, 1.0, 20.0 ], [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ),
                          TabulatedEnergyDistribution(
                            1., 1, [ 1e-3, 15.0 ], [ 0.5, 0.5 ], [ 0.0, 1.0 ] ) ] ),
                      TabulatedAngleEnergyDistribution(
                        20., 2,
                        [ TabulatedEnergyDistribution(
                            -0.9, 1, [ 1e-4, 12.0 ], [ 0.5, 0.5 ], [ 0.0, 1.0 ] ),
                          TabulatedEnergyDistribution(
                            0.9, 2, [ 1e-2, 2.0, 18.0 ], [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ) ] ) ],
                   locb = 21 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
