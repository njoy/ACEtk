# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import SecondaryParticleGroupStructureBlock

class Test_ACEtk_multigroup_SecondaryParticleGroupStructureBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleGroupStructureBlock class."""

    chunk = [     
  1.450000000000E+01,  8.500000000000E+00,  7.500000000000E+00,  6.500000000000E+00,  
  5.500000000000E+00,  4.500000000000E+00,  3.500000000000E+00,  2.500000000000E+00,  
  1.500000000000E+00,  7.500000000000E-01,  3.000000000000E-01,  5.500000000000E-02,
                  11,                   1,                   1,                   1, 
                   1,                   1,                   1,                   1,
                   1,  5.000000000000E-01,  4.000000000000E-01,  9.000000000000E-02  
    ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 24, chunk.length )
            self.assertEqual( "ERG2", chunk.name )

            self.assertEqual( 24, len( chunk.xss_array ) )

            self.assertEqual( 12, chunk.NERG )
            self.assertEqual( 12, chunk.number_energy_groups )
            self.assertEqual( 12, len( chunk.group_means ) )
            self.assertEqual( 12, len( chunk.group_widths ) )

            self.assertAlmostEqual( 14.5, chunk.group_means[0] )
            self.assertAlmostEqual( 0.055, chunk.group_means[-1] )
            self.assertAlmostEqual( 11, chunk.group_widths[0] )
            self.assertAlmostEqual( 0.09, chunk.group_widths[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleGroupStructureBlock(
          group_means =  [ 1.450000000000E+01,  8.500000000000E+00,  7.500000000000E+00,  6.500000000000E+00,  
                           5.500000000000E+00,  4.500000000000E+00,  3.500000000000E+00,  2.500000000000E+00,  
                           1.500000000000E+00,  7.500000000000E-01,  3.000000000000E-01,  5.500000000000E-02 ],
          group_widths = [                 11,                   1,                   1,                   1, 
                                            1,                   1,                   1,                   1,
                                            1,  5.000000000000E-01,  4.000000000000E-01,  9.000000000000E-02 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
