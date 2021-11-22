# standard imports
import unittest

# third party imports

# local imports
from ACEtk import EnergyDistributionType
from ACEtk import NBodyPhaseSpaceDistribution

class Test_ACEtk_NBodyPhaseSpaceDistribution( unittest.TestCase ) :
    """Unit test for the NBodyPhaseSpaceDistribution class."""

    chunk = [ 4.00000000000E+00, 9.91472200000E-01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.length )
            self.assertEqual( "DLW::NBodyPhaseSpaceDistribution", chunk.name )

            self.assertEqual( EnergyDistributionType.NBodyPhaseSpace, chunk.LAW )
            self.assertEqual( EnergyDistributionType.NBodyPhaseSpace, chunk.type )

            self.assertAlmostEqual( 2.249999e-3, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertAlmostEqual( 4, chunk.NPSX )
            self.assertAlmostEqual( 4, chunk.number_particles )
            self.assertAlmostEqual( .9914722, chunk.AP )
            self.assertAlmostEqual( .9914722, chunk.total_mass_ratio )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = NBodyPhaseSpaceDistribution(
                    emin = 2.249999e-3,
                    emax = 20.,
                    npsx = 4,
                    ap = .9914722 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
