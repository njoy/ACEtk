# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import NumberSecondaryAngularVariablesBlock

class Test_ACEtk_multigroup_NumberSecondaryAngularVariablesBlock( unittest.TestCase ) :
    """Unit test for the NumberSecondaryAngularVariablesBlock class."""

    chunk = [ 4 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 1, chunk.length )
            self.assertEqual( "NLEG2", chunk.name )

            self.assertEqual( 1, chunk.NSEC )
            self.assertEqual( 1, chunk.number_secondary_particles )

            self.assertEqual( 4, chunk.NLEG2(1) )
            
            self.assertEqual( 4, chunk.number_angular_distribution_variables(1) )

            self.assertEqual( 1, len( chunk.NLEG2s ) )
            self.assertEqual( 1, len( chunk.number_angular_distribution_variables_list ) )
            self.assertEqual( 4, chunk.NLEG2s[0] )
            self.assertEqual( 4, chunk.number_angular_distribution_variables_list[0] )


            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = NumberSecondaryAngularVariablesBlock( numbers = [ 4 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
