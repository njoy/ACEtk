# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import IsotropicAngularDistribution

class Test_ACEtk_continuous_IsotropicAngularDistribution( unittest.TestCase ) :
    """Unit test for the IsotropicAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2.1, chunk.energy )

        # the data is given explicitly
        chunk = IsotropicAngularDistribution( energy = 2.1 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
