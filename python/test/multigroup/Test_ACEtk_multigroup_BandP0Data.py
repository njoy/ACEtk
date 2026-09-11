# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import BandP0Data

class Test_ACEtk_multigroup_BandP0Data( unittest.TestCase ) :
    """Unit test for the BandP0Data class."""

    chunk = [ 2., 3., 4., 1., 2., 3., 4., 1., 2., 3., 1., 2. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 12, chunk.length )
            self.assertEqual( 12, chunk.block_length )
            self.assertEqual( "BandP0Data", chunk.name )

            self.assertEqual( 12, len( chunk.xss_array ) )

            self.assertEqual( 4, chunk.NGRP )
            self.assertEqual( 4, chunk.number_energy_groups )

            self.assertEqual( 2, chunk.NDS )
            self.assertEqual( 2, chunk.number_down_scatter_groups )
            self.assertEqual( 1, chunk.NUS )
            self.assertEqual( 1, chunk.number_up_scatter_groups )

            self.assertAlmostEqual( 2., chunk.p0_matrix_list[0] )
            self.assertAlmostEqual( 3., chunk.p0_matrix_list[1] )
            self.assertAlmostEqual( 4., chunk.p0_matrix_list[2] )
            self.assertAlmostEqual( 1., chunk.p0_matrix_list[3] )
            self.assertAlmostEqual( 2., chunk.p0_matrix_list[4] )
            self.assertAlmostEqual( 3., chunk.p0_matrix_list[5] )
            self.assertAlmostEqual( 4., chunk.p0_matrix_list[6] )
            self.assertAlmostEqual( 1., chunk.p0_matrix_list[7] )
            self.assertAlmostEqual( 2., chunk.p0_matrix_list[8] )
            self.assertAlmostEqual( 3., chunk.p0_matrix_list[9] )
            self.assertAlmostEqual( 1., chunk.p0_matrix_list[10]) 
            self.assertAlmostEqual( 2., chunk.p0_matrix_list[11])

            self.assertEqual( 2, chunk.group_down_scatter_groups( 1 ) )
            self.assertEqual( 2, chunk.group_down_scatter_groups( 2 ) )
            self.assertEqual( 1, chunk.group_down_scatter_groups( 3 ) )
            self.assertEqual( 0, chunk.group_down_scatter_groups( 4 ) )
            self.assertEqual( 0, chunk.group_up_scatter_groups( 1 ) )
            self.assertEqual( 1, chunk.group_up_scatter_groups( 2 ) )
            self.assertEqual( 1, chunk.group_up_scatter_groups( 3 ) )
            self.assertEqual( 1, chunk.group_up_scatter_groups( 4 ) )

            self.assertAlmostEqual( 2., chunk.p0_value( 1, 1 ) ) 
            self.assertAlmostEqual( 3., chunk.p0_value( 1, 2 ) ) 
            self.assertAlmostEqual( 4., chunk.p0_value( 1, 3 ) ) 
            self.assertAlmostEqual( 0., chunk.p0_value( 1, 4 ) ) 
            self.assertAlmostEqual( 1., chunk.p0_value( 2, 1 ) ) 
            self.assertAlmostEqual( 2., chunk.p0_value( 2, 2 ) ) 
            self.assertAlmostEqual( 3., chunk.p0_value( 2, 3 ) ) 
            self.assertAlmostEqual( 4., chunk.p0_value( 2, 4 ) ) 
            self.assertAlmostEqual( 0., chunk.p0_value( 3, 1 ) ) 
            self.assertAlmostEqual( 1., chunk.p0_value( 3, 2 ) ) 
            self.assertAlmostEqual( 2., chunk.p0_value( 3, 3 ) ) 
            self.assertAlmostEqual( 3., chunk.p0_value( 3, 4 ) ) 
            self.assertAlmostEqual( 0., chunk.p0_value( 4, 1 ) ) 
            self.assertAlmostEqual( 0., chunk.p0_value( 4, 2 ) ) 
            self.assertAlmostEqual( 1., chunk.p0_value( 4, 3 ) ) 
            self.assertAlmostEqual( 2., chunk.p0_value( 4, 4 ) ) 

            self.assertAlmostEqual( 2., chunk.incident_row( 1 )[0] )
            self.assertAlmostEqual( 3., chunk.incident_row( 1 )[1] )
            self.assertAlmostEqual( 4., chunk.incident_row( 1 )[2] )
            self.assertAlmostEqual( 0., chunk.incident_row( 1 )[3] )
            self.assertAlmostEqual( 1., chunk.incident_row( 2 )[0] )
            self.assertAlmostEqual( 2., chunk.incident_row( 2 )[1] )
            self.assertAlmostEqual( 3., chunk.incident_row( 2 )[2] )
            self.assertAlmostEqual( 4., chunk.incident_row( 2 )[3] )
            self.assertAlmostEqual( 0., chunk.incident_row( 3 )[0] )
            self.assertAlmostEqual( 1., chunk.incident_row( 3 )[1] )
            self.assertAlmostEqual( 2., chunk.incident_row( 3 )[2] )
            self.assertAlmostEqual( 3., chunk.incident_row( 3 )[3] )
            self.assertAlmostEqual( 0., chunk.incident_row( 4 )[0] )
            self.assertAlmostEqual( 0., chunk.incident_row( 4 )[1] )
            self.assertAlmostEqual( 1., chunk.incident_row( 4 )[2] )
            self.assertAlmostEqual( 2., chunk.incident_row( 4 )[3] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        block = BandP0Data(
          matrix =  [  
            [ 2., 3., 4., 0. ],
            [ 1., 2., 3., 4. ],
            [ 0., 1., 2., 3. ],
            [ 0., 0., 1., 2. ] ],
          down = 2, 
          up = 1 
          )

        verify_chunk( self, block )

if __name__ == '__main__' :

    unittest.main()
