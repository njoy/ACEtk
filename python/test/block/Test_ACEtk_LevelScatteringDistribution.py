# standard imports
import unittest

# third party imports

# local imports
from ACEtk import LevelScatteringDistribution

class Test_ACEtk_LevelScatteringDistribution( unittest.TestCase ) :
    """Unit test for the LevelScatteringDistribution class."""

    chunk = [ 7.71295800000E-05, 9.91472200000E-01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 2, chunk.length )
            self.assertEqual( "DLW::LevelScatteringDistribution", chunk.name )

            self.assertAlmostEqual( 2.249999e-3, chunk.minimum_incident_energy )
            self.assertAlmostEqual( 20., chunk.maximum_incident_energy )

            self.assertAlmostEqual( 7.712958e-05, chunk.C1 )
            self.assertAlmostEqual( .9914722, chunk.C2 )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = LevelScatteringDistribution(
                    emin = 2.249999e-3,
                    emax = 20.,
                    c1 = 7.712958e-05,
                    c2 = .9914722 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
