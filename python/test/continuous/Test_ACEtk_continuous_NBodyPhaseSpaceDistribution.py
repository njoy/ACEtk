# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk.continuous import NBodyPhaseSpaceDistribution

class Test_ACEtk_continuous_NBodyPhaseSpaceDistribution( unittest.TestCase ) :
    """Unit test for the NBodyPhaseSpaceDistribution class."""

    chunk = [ 4.00000000000E+00, 9.91472200000E-01,
              2.00000000000E+00, 4.00000000000E+00,
              0.00000000000E+00, 2.50000000000E-01, 7.50000000000E-01, 1.00000000000E+00,
              1.00000000000E+00, 1.00000000000E+00, 1.00000000000E+00, 1.00000000000E+00,
              0.00000000000E+00, 3.30000000000E-01, 6.60000000000E-01, 1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 16, chunk.length )
            self.assertEqual( "NBodyPhaseSpaceDistribution", chunk.name )

            self.assertEqual( EnergyDistributionType.NBodyPhaseSpace, chunk.LAW )
            self.assertEqual( EnergyDistributionType.NBodyPhaseSpace, chunk.type )

            self.assertAlmostEqual( 2.249999e-3, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( 4, chunk.NPSX )
            self.assertEqual( 4, chunk.number_particles )
            self.assertAlmostEqual( .9914722, chunk.AP )
            self.assertAlmostEqual( .9914722, chunk.total_mass_ratio )

            self.assertEqual( 2, chunk.interpolation )
            self.assertEqual( 4, chunk.number_values )

            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 0., chunk.values[0] )
            self.assertAlmostEqual( 0.25, chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )

            self.assertEqual( 4, len( chunk.pdf ) )
            self.assertAlmostEqual( 1., chunk.pdf[0] )
            self.assertAlmostEqual( 1., chunk.pdf[1] )
            self.assertAlmostEqual( 1., chunk.pdf[2] )
            self.assertAlmostEqual( 1., chunk.pdf[3] )

            self.assertEqual( 4, len( chunk.cdf ) )
            self.assertAlmostEqual( 0., chunk.cdf[0] )
            self.assertAlmostEqual( .33, chunk.cdf[1] )
            self.assertAlmostEqual( .66, chunk.cdf[2] )
            self.assertAlmostEqual( 1., chunk.cdf[3] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = NBodyPhaseSpaceDistribution(
                    emin = 2.249999e-3,
                    emax = 20.,
                    npsx = 4,
                    ap = .9914722,
                    interpolation = 2,
                    values = [ 0., 0.25, 0.75, 1. ],
                    pdf = [ 1., 1., 1., 1. ],
                    cdf = [ 0., 0.33, 0.66, 1.0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
