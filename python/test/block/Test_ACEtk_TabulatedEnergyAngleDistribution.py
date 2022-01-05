# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import TabulatedEnergyAngleDistribution
from ACEtk import TabulatedAngularDistribution

class Test_ACEtk_TabulatedEnergyAngleDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedEnergyAngleDistribution class."""

    chunk = [             0,             2,  2.100000E+00,  2.000000E+01,
                         27,            38,             2,             3,
              -1.000000E+00,  0.000000E+00,  1.000000E+00,  0.500000E+00,
               0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
               1.000000E+00,             1,             2, -1.000000E+00,
               1.000000E+00,  0.500000E+00,  0.500000E+00,  0.000000E+00,
               1.000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 25, chunk.length )
            self.assertEqual( "TabulatedEnergyAngleDistribution", chunk.name )

            self.assertEqual( 1.1, chunk.incident_energy )

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
            self.assertEqual( 2, chunk.number_outgoing_energies )
            self.assertEqual( 2, len( chunk.distributions ) )

            self.assertEqual( 2, len( chunk.outgoing_energies ) )
            self.assertAlmostEqual( 2.1, chunk.outgoing_energies[0] )
            self.assertAlmostEqual( 20., chunk.outgoing_energies[1] )

            self.assertAlmostEqual( 2.1, chunk.outgoing_energy(1) )
            self.assertAlmostEqual( 20., chunk.outgoing_energy(2) )

            self.assertEqual( 27, chunk.LOCC(1) );
            self.assertEqual( 38, chunk.LOCC(2) );
            self.assertEqual( 27, chunk.distribution_locator(1) );
            self.assertEqual( 38, chunk.distribution_locator(2) );

            self.assertEqual( 7, chunk.relative_distribution_locator(1) );
            self.assertEqual( 18, chunk.relative_distribution_locator(2) );

            self.assertEqual( True, isinstance( chunk.distribution(1), TabulatedAngularDistribution )  )
            self.assertEqual( True, isinstance( chunk.distribution(2), TabulatedAngularDistribution ) )

            data1 = chunk.distribution(1)
            self.assertAlmostEqual( 2.1, data1.energy )
            self.assertEqual( 2, data1.interpolation )
            self.assertEqual( 3, data1.number_cosines )

            self.assertEqual( 3, len( data1.cosines ) )
            self.assertAlmostEqual( -1., data1.cosines[0] )
            self.assertAlmostEqual( +1., data1.cosines[-1] )

            self.assertEqual( 3, len( data1.pdf ) )
            self.assertAlmostEqual( .5, data1.pdf[0] )
            self.assertAlmostEqual( .5, data1.pdf[-1] )

            self.assertEqual( 3, len( data1.cdf ) )
            self.assertAlmostEqual( 0., data1.cdf[0] )
            self.assertAlmostEqual( 1., data1.cdf[-1] )

            data2 = chunk.distribution(2);
            self.assertAlmostEqual( 20., data2.energy )
            self.assertEqual( 1, data2.interpolation )
            self.assertEqual( 2, data2.number_cosines )

            self.assertEqual( 2, len( data2.cosines ) )
            self.assertAlmostEqual( -1., data2.cosines[0] )
            self.assertAlmostEqual( +1., data2.cosines[-1] )

            self.assertEqual( 2, len( data2.pdf ) )
            self.assertAlmostEqual( .5, data2.pdf[0] )
            self.assertAlmostEqual( .5, data2.pdf[-1] )

            self.assertEqual( 2, len( data2.cdf ) )
            self.assertAlmostEqual( 0., data2.cdf[0] )
            self.assertAlmostEqual( 1., data2.cdf[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = TabulatedEnergyAngleDistribution(
                    incident = 1.1,
                    distributions = [

                      TabulatedAngularDistribution(
                        2.1, 2, [ -1.0, 0.0, 1.0 ],
                        [ 0.5, 0.5, 0.5 ], [ 0.0, 0.5, 1.0 ] ),
                      TabulatedAngularDistribution(
                        20., 1, [ -1.0, 1.0 ], [ 0.5, 0.5 ], [ 0.0, 1.0 ] ) ],
                    locb = 21 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
