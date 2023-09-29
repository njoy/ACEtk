# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import EnergyDistributionType
from ACEtk.continuous import DiscretePhotonDistribution

class Test_ACEtk_DiscretePhotonDistribution( unittest.TestCase ) :
    """Unit test for the DiscretePhotonDistribution class."""

    chunk = [ 2.00000000000E+00, 1.00000000000E+05 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.length )
            self.assertEqual( "DiscretePhotonDistribution", chunk.name )

            self.assertEqual( EnergyDistributionType.DiscretePhoton, chunk.LAW )
            self.assertEqual( EnergyDistributionType.DiscretePhoton, chunk.type )

            self.assertAlmostEqual( 1e-5, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertEqual( 2, chunk.LP )
            self.assertEqual( 2, chunk.primary_photon_flag )
            self.assertEqual( True, chunk.is_primary_photon )
            self.assertEqual( True, chunk.is_primary_photon )
            self.assertAlmostEqual( 1e+5, chunk.EG )
            self.assertAlmostEqual( 1e+5, chunk.photon_or_binding_energy )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = DiscretePhotonDistribution(
                    emin = 1e-5,
                    emax = 20.,
                    lp = 2,
                    energy = 1e+5 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
