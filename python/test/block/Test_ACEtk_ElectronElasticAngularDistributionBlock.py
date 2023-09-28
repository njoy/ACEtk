# standard imports
import unittest

# third party imports

# local imports
from ACEtk import ElectronElasticAngularDistributionBlock
from ACEtk import ElectronTabulatedAngularDistribution

class Test_ACEtk_ElectronElasticAngularDistributionBlock( unittest.TestCase ) :
    """Unit test for the ElectronElasticAngularDistributionBlock class."""

    chunk = [ 1e-11, 1e-6, 1e-3, 1.,
                 2,    3,    4,  2,
                 0,    4,   10, 18,
              -1.0, 1.0, 0., 1.,
              -1.0, 0.0, 1.0, 0., 0.75, 1.,
              -1.0, 0.5, 0.7, 1.0, 0., 0.25, 0.5, 1.,
              -1.0, 1.0, 0., 1. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 34, chunk.length )
            self.assertEqual( "ELAS", chunk.name )

            self.assertEqual( 4, chunk.NA )
            self.assertEqual( 4, chunk.number_energy_points )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.distributions ) )

            self.assertEqual( 1, chunk.LLOC(1) )
            self.assertEqual( 5, chunk.LLOC(2) )
            self.assertEqual( 11, chunk.LLOC(3) )
            self.assertEqual( 19, chunk.LLOC(4) )
            self.assertEqual( 1, chunk.distribution_locator(1) )
            self.assertEqual( 5, chunk.distribution_locator(2) )
            self.assertEqual( 11, chunk.distribution_locator(3) )
            self.assertEqual( 19, chunk.distribution_locator(4) )

            distribution = chunk.distribution(1)
            self.assertEqual( 1e-11, distribution.energy )
            self.assertEqual( 2, distribution.number_cosines )

            distribution = chunk.distribution(2)
            self.assertEqual( 1e-6, distribution.energy )
            self.assertEqual( 3, distribution.number_cosines )

            distribution = chunk.distribution(3)
            self.assertEqual( 1e-3, distribution.energy )
            self.assertEqual( 4, distribution.number_cosines )

            distribution = chunk.distribution(4)
            self.assertEqual( 1., distribution.energy )
            self.assertEqual( 2, distribution.number_cosines )

            # verify the distributions array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = ElectronElasticAngularDistributionBlock(
                  distributions = [
                      ElectronTabulatedAngularDistribution( 1e-11, [ -1.0, 1.0 ], [ 0., 1. ] ),
                      ElectronTabulatedAngularDistribution(  1e-6, [ -1.0, 0.0, 1.0 ], [ 0., 0.75, 1. ] ),
                      ElectronTabulatedAngularDistribution(  1e-3, [ -1.0, 0.5, 0.7, 1.0 ], [ 0., 0.25, 0.5, 1. ] ),
                      ElectronTabulatedAngularDistribution(    1., [ -1.0, 1.0 ], [ 0., 1. ] ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
