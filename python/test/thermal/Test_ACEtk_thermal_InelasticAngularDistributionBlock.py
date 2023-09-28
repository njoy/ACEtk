# standard imports
import unittest

# third party imports

# local imports
from ACEtk.thermal import InelasticAngularDistributionBlock
from ACEtk.thermal import DiscreteCosines
from ACEtk.thermal import DiscreteCosinesWithProbability

class Test_ACEtk_thermal_InelasticAngularDistributionBlock( unittest.TestCase ) :
    """Unit test for the InelasticAngularDistributionBlock class."""

    chunk = [  1.00000000000E+00, -1.00000000000E+00, -0.90000000000E+00,  1.00000000000E+00,
               2.00000000000E+00, -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
               3.00000000000E+00, -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
               4.00000000000E+00, -1.00000000000E+00,  0.90000000000E+00,  1.00000000000E+00,
               5.00000000000E+00, -1.00000000000E+00,  0.40000000000E+00,  1.00000000000E+00,
               6.00000000000E+00, -1.00000000000E+00,  0.80000000000E+00,  1.00000000000E+00,
               7.00000000000E+00, -1.00000000000E+00,  0.30000000000E+00,  1.00000000000E+00,
               8.00000000000E+00, -1.00000000000E+00,  0.70000000000E+00,  1.00000000000E+00 ]

    chunk_with_ifeng_2 = [                  16,                 28,                 52,                 70,
                                             2,                  4,                  3,                  3,
                             1.00000000000E+00,  5.00000000000E-01,  0.00000000000E+00, -1.00000000000E+00, -0.90000000000E+00,  1.00000000000E+00,
                             2.00000000000E+00,  5.00000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
                             3.00000000000E+00,  2.50000000000E-01,  0.00000000000E+00, -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
                             4.00000000000E+00,  2.50000000000E-01,  3.30000000000E-01, -1.00000000000E+00,  0.90000000000E+00,  1.00000000000E+00,
                             5.00000000000E+00,  2.50000000000E-01,  6.60000000000E-01, -1.00000000000E+00,  0.40000000000E+00,  1.00000000000E+00,
                             6.00000000000E+00,  2.50000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.80000000000E+00,  1.00000000000E+00,
                             7.00000000000E+00,  3.30000000000E-01,  0.00000000000E+00, -1.00000000000E+00,  0.30000000000E+00,  1.00000000000E+00,
                             8.00000000000E+00,  3.30000000000E-01,  5.00000000000E-01, -1.00000000000E+00,  0.70000000000E+00,  1.00000000000E+00,
                             9.00000000000E+00,  3.30000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.60000000000E+00,  1.00000000000E+00,
                            10.00000000000E+00,  3.30000000000E-01,  0.00000000000E+00, -1.00000000000E+00,  0.20000000000E+00,  1.00000000000E+00,
                            11.00000000000E+00,  3.30000000000E-01,  5.00000000000E-01, -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
                            12.00000000000E+00,  3.30000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.40000000000E+00,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 32, chunk.length )
            self.assertEqual( "InelasticAngularDistributionBlock", chunk.name )

            self.assertEqual( 1, chunk.IFENG )
            self.assertEqual( 1, chunk.secondary_energy_mode )
            self.assertEqual( 4, chunk.NE )
            self.assertEqual( 4, chunk.number_incident_energies )
            self.assertEqual( 3, chunk.NC )
            self.assertEqual( 3, chunk.number_discrete_cosines )
            self.assertEqual( 2, chunk.NIL )
            self.assertEqual( 2, chunk.inelastic_dimensioning_parameter )

            self.assertEqual( 2, chunk.NIEB( 1 ) )
            self.assertEqual( 2, chunk.NIEB( 2 ) )
            self.assertEqual( 2, chunk.NIEB( 3 ) )
            self.assertEqual( 2, chunk.NIEB( 4 ) )
            self.assertEqual( 2, chunk.number_outgoing_energies( 1 ) )
            self.assertEqual( 2, chunk.number_outgoing_energies( 2 ) )
            self.assertEqual( 2, chunk.number_outgoing_energies( 3 ) )
            self.assertEqual( 2, chunk.number_outgoing_energies( 4 ) )

            data = chunk.discrete_cosine_data( 1, 1 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 1., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( -.9, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            data = chunk.discrete_cosine_data( 1, 2 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 2., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( 0., data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            data = chunk.discrete_cosine_data( 2, 1 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 3., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( .5, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            data = chunk.discrete_cosine_data( 2, 2 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 4., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( .9, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            data = chunk.discrete_cosine_data( 3, 1 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 5., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( .4, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            data = chunk.discrete_cosine_data( 3, 2 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 6., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( .8, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            data = chunk.discrete_cosine_data( 4, 1 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 7., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( .3, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            data = chunk.discrete_cosine_data( 4, 2 )
            self.assertEqual( True, isinstance( data, DiscreteCosines ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 8., data.energy )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( .7, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        def verify_chunk_with_ifeng_2( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 80, chunk.length )
            self.assertEqual( "InelasticAngularDistributionBlock", chunk.name )

            self.assertEqual( 2, chunk.IFENG )
            self.assertEqual( 2, chunk.secondary_energy_mode )
            self.assertEqual( 4, chunk.NE )
            self.assertEqual( 4, chunk.number_incident_energies )
            self.assertEqual( 3, chunk.NC )
            self.assertEqual( 3, chunk.number_discrete_cosines )
            self.assertEqual( 4, chunk.NIL )
            self.assertEqual( 4, chunk.inelastic_dimensioning_parameter )

            self.assertEqual( 2, chunk.NIEB( 1 ) )
            self.assertEqual( 4, chunk.NIEB( 2 ) )
            self.assertEqual( 3, chunk.NIEB( 3 ) )
            self.assertEqual( 3, chunk.NIEB( 4 ) )
            self.assertEqual( 2, chunk.number_outgoing_energies( 1 ) )
            self.assertEqual( 4, chunk.number_outgoing_energies( 2 ) )
            self.assertEqual( 3, chunk.number_outgoing_energies( 3 ) )
            self.assertEqual( 3, chunk.number_outgoing_energies( 4 ) )

            data = chunk.discrete_cosine_data( 1, 1 )
            self.assertEqual( True, isinstance( data, DiscreteCosinesWithProbability ) )
            self.assertEqual( 3, data.NC )
            self.assertEqual( 3, data.number_discrete_cosines )
            self.assertAlmostEqual( 1., data.energy )
            self.assertAlmostEqual( .5, data.pdf )
            self.assertAlmostEqual( 0., data.cdf )
            self.assertAlmostEqual( -1., data.cosines[0] )
            self.assertAlmostEqual( -.9, data.cosines[1] )
            self.assertAlmostEqual( +1., data.cosines[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk_with_ifeng_2[index], xss[index] )

        # the data is given explicitly for ifeng = 1
        chunk = InelasticAngularDistributionBlock(
                    cosines = [ [ DiscreteCosines( 1., [ -1.0, -0.9, 1.0 ] ),
                                  DiscreteCosines( 2., [ -1.0, 0.0, 1.0 ] ) ],
                                [ DiscreteCosines( 3., [ -1.0, 0.5, 1.0 ] ),
                                  DiscreteCosines( 4., [ -1.0, 0.9, 1.0 ] ) ],
                                [ DiscreteCosines( 5., [ -1.0, 0.4, 1.0 ] ),
                                  DiscreteCosines( 6., [ -1.0, 0.8, 1.0 ] ) ],
                                [ DiscreteCosines( 7., [ -1.0, 0.3, 1.0 ] ),
                                  DiscreteCosines( 8., [ -1.0, 0.7, 1.0 ] ) ] ],
                    skewed = True )

        verify_chunk( self, chunk )

        # the data is given explicitly for ifeng = 2
        chunk = InelasticAngularDistributionBlock(
                    cosines = [ [ DiscreteCosinesWithProbability(  1., 0.5, 0., [ -1.0, -0.9, 1.0 ] ),
                                  DiscreteCosinesWithProbability(  2., 0.5, 1., [ -1.0, 0.0, 1.0 ] ) ],
                                [ DiscreteCosinesWithProbability(  3., 0.25, 0.00, [ -1.0, 0.5, 1.0 ] ),
                                  DiscreteCosinesWithProbability(  4., 0.25, 0.33, [ -1.0, 0.9, 1.0 ] ),
                                  DiscreteCosinesWithProbability(  5., 0.25, 0.66, [ -1.0, 0.4, 1.0 ] ),
                                  DiscreteCosinesWithProbability(  6., 0.25, 1.00, [ -1.0, 0.8, 1.0 ] ) ],
                                [ DiscreteCosinesWithProbability(  7., 0.33, 0.0, [ -1.0, 0.3, 1.0 ] ),
                                  DiscreteCosinesWithProbability(  8., 0.33, 0.5, [ -1.0, 0.7, 1.0 ] ),
                                  DiscreteCosinesWithProbability(  9., 0.33, 1.0, [ -1.0, 0.6, 1.0 ] ) ],
                                [ DiscreteCosinesWithProbability( 10., 0.33, 0.0, [ -1.0, 0.2, 1.0 ] ),
                                  DiscreteCosinesWithProbability( 11., 0.33, 0.5, [ -1.0, 0.5, 1.0 ] ),
                                  DiscreteCosinesWithProbability( 12., 0.33, 1.0, [ -1.0, 0.4, 1.0 ] ) ] ],
                    locb = 9 )

        verify_chunk_with_ifeng_2( self, chunk )

if __name__ == '__main__' :

    unittest.main()
