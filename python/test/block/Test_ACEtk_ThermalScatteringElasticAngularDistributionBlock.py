# standard imports
import unittest

# third party imports

# local imports
from ACEtk import ThermalScatteringElasticAngularDistributionBlock

class Test_ACEtk_ThermalScatteringElasticAngularDistributionBlock( unittest.TestCase ) :
    """Unit test for the ThermalScatteringElasticAngularDistributionBlock class."""

    chunk = [  -1.00000000000E+00, -0.90000000000E+00,  1.00000000000E+00,
               -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
               -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
               -1.00000000000E+00,  0.90000000000E+00,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 12, chunk.length )
            self.assertEqual( "ThermalScatteringElasticAngularDistributionBlock", chunk.name )

            self.assertEqual( 4, chunk.NE )
            self.assertEqual( 4, chunk.number_incident_energies )
            self.assertEqual( 3, chunk.NC )
            self.assertEqual( 3, chunk.number_discrete_cosines )

            cosines = chunk.cosines( 1 )
            self.assertEqual( 3, len( cosines ) )
            self.assertAlmostEqual( -1., cosines[0] )
            self.assertAlmostEqual( -.9, cosines[1] )
            self.assertAlmostEqual( +1., cosines[2] )

            cosines = chunk.cosines( 2 )
            self.assertEqual( 3, len( cosines ) )
            self.assertAlmostEqual( -1., cosines[0] )
            self.assertAlmostEqual(  0., cosines[1] )
            self.assertAlmostEqual( +1., cosines[2] )

            cosines = chunk.cosines( 3 )
            self.assertEqual( 3, len( cosines ) )
            self.assertAlmostEqual( -1., cosines[0] )
            self.assertAlmostEqual(  .5, cosines[1] )
            self.assertAlmostEqual( +1., cosines[2] )

            cosines = chunk.cosines( 4 )
            self.assertEqual( 3, len( cosines ) )
            self.assertAlmostEqual( -1., cosines[0] )
            self.assertAlmostEqual(  .9, cosines[1] )
            self.assertAlmostEqual( +1., cosines[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = ThermalScatteringElasticAngularDistributionBlock(
                    cosines = [ [ -1.0, -0.9, 1.0 ], [ -1.0, 0.0, 1.0 ],
                                [ -1.0, 0.5, 1.0 ], [ -1.0, 0.9, 1.0 ] ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
