# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import RectangularXPNData

class Test_ACEtk_multigroup_RectangularXPNData( unittest.TestCase ) :
    """Unit test for the RectangularXPNData class."""

    chunk = [ 1,  5,  9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, -1, -1, -1, -1, -1, -1, -1  ]

    def test_component( self ) :

        def verify_chunk( self, chunk, ans ) :


            # verify content
            self.assertFalse( chunk.empty )
            self.assertEqual( 30, chunk.length )
            self.assertEqual( 30, chunk.block_length )
            self.assertEqual( "RectangularXPNData", chunk.name )

            self.assertEqual( 30, len( chunk.xss_array ) )

            self.assertEqual( 6, chunk.NGRP )
            self.assertEqual( 6, chunk.number_incident_energy_groups )

            self.assertEqual( 5, chunk.NERG )
            self.assertEqual( 5, chunk.number_outgoing_energy_groups )

            for i in range(6):

              self.assertEqual(5, len(chunk.incident_row( i+1 )))
              for j in range(5):

                self.assertEqual( ans[i][j], chunk.xpn_matrix_list[ 5*i + j ] )
                self.assertEqual( ans[i][j], chunk.LPND( i+1, j+1 ) ) 
                self.assertEqual( ans[i][j], chunk.locator( i+1, j+1 ) ) 
                self.assertEqual( ans[i][j], chunk.incident_row( i+1 )[j] )
                self.assertEqual( ans[i][j], chunk.outgoing_column( j+1 )[i] )
                self.assertEqual(6, len(chunk.outgoing_column( j+1 )))
 

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        ans = [  
            [  1,  5,  9, 13, 17 ],
            [ 21, 25, 29, 33, 37 ],
            [ 41, 45, 49, 53, 57 ], 
            [ 61, 65, 69, 73, 77 ], 
            [ 81, 85, 89, -1, -1 ],
            [ -1, -1, -1, -1, -1 ]
        ]

        # the data is given explicitly
        block = RectangularXPNData( matrix =  ans )


        verify_chunk( self, block, ans )

if __name__ == '__main__' :

    unittest.main()
