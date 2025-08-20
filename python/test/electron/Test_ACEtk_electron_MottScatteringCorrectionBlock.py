# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import MottScatteringCorrectionBlock

class Test_ACEtk_electron_MottScatteringCorrectionBlock( unittest.TestCase ) :
    """Unit test for the MottScatteringCorrectionBlock class."""
    
    chunk = [ 10.0, 1.0, 0.1,
              1.0, 1.0, 1.0,
              1.03823, 1.04539, 1.06645,
              0.68123, 0.73096, 0.97863,
              0.21291, 0.31213, 0.83060,
              2.55e-3, 0.12341, 0.76169 ]
    
    def test_component( self ) :
        
        def verify_block( self, block ) :
            
            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 18, block.length )
            self.assertEqual( "MOT", block.name )
            
            self.assertEqual( 3, block.NMOT )
            self.assertEqual( 3, block.number_energy_points )
            
            self.assertEqual( 3, len( block.energies ) )
            self.assertEqual( 3, len( block.mott_scattering_correction( 1 ) ) )
            self.assertEqual( 3, len( block.mott_scattering_correction( 2 ) ) )
            self.assertEqual( 3, len( block.mott_scattering_correction( 3 ) ) )
            self.assertEqual( 3, len( block.mott_scattering_correction( 4 ) ) )
            self.assertEqual( 3, len( block.mott_scattering_correction( 5 ) ) )
            
            self.assertAlmostEqual( self.chunk[0], block.energies[0] )
            self.assertAlmostEqual( self.chunk[1], block.energies[1] )
            self.assertAlmostEqual( self.chunk[2], block.energies[2] )
            self.assertAlmostEqual( self.chunk[3], 
                                    block.mott_scattering_correction( 1 )[0] )
            self.assertAlmostEqual( self.chunk[4], 
                                    block.mott_scattering_correction( 1 )[1] )
            self.assertAlmostEqual( self.chunk[5], 
                                    block.mott_scattering_correction( 1 )[2] )
            self.assertAlmostEqual( self.chunk[6], 
                                    block.mott_scattering_correction( 2 )[0] )
            self.assertAlmostEqual( self.chunk[7], 
                                    block.mott_scattering_correction( 2 )[1] )
            self.assertAlmostEqual( self.chunk[8], 
                                    block.mott_scattering_correction( 2 )[2] )
            self.assertAlmostEqual( self.chunk[9], 
                                    block.mott_scattering_correction( 3 )[0] )
            self.assertAlmostEqual( self.chunk[10], 
                                    block.mott_scattering_correction( 3 )[1] )
            self.assertAlmostEqual( self.chunk[11], 
                                    block.mott_scattering_correction( 3 )[2] )
            self.assertAlmostEqual( self.chunk[12], 
                                    block.mott_scattering_correction( 4 )[0] )
            self.assertAlmostEqual( self.chunk[13], 
                                    block.mott_scattering_correction( 4 )[1] )
            self.assertAlmostEqual( self.chunk[14], 
                                    block.mott_scattering_correction( 4 )[2] )
            self.assertAlmostEqual( self.chunk[15], 
                                    block.mott_scattering_correction( 5 )[0] )
            self.assertAlmostEqual( self.chunk[16], 
                                    block.mott_scattering_correction( 5 )[1] )
            self.assertAlmostEqual( self.chunk[17], 
                                    block.mott_scattering_correction( 5 )[2] )
            
            # verify the xss array
            self.assertEqual( 18, len( block.xss_array ) )
            for index in range( block.length ) :

                self.assertAlmostEqual( self.chunk[index],
                                        block.xss_array[index] )
        
        block = MottScatteringCorrectionBlock( self.chunk[0:3],
                                               self.chunk[3:6],
                                               self.chunk[6:9],
                                               self.chunk[9:12],
                                               self.chunk[12:15],
                                               self.chunk[15:18] )
        
        verify_block( self, block )

if __name__ == '__main__' :

    unittest.main()
