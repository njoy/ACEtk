# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import BremsstrahlungProductionBlock

class Test_ACEtk_electron_BremsstrahlungProductionBlock( unittest.TestCase ) :
    """Unit test for the BremsstrahlungProductionBlock class."""

    chunk = [ 0.1, 1.0, 10.0,
              0.1, 0.3, 1.0,
              0.01, 0.1, 1.0,
              0.03, 0.3, 3.0,
              0.1, 1.0, 10.0 ]

    def test_component( self ) :

        def verify_block( self, block ) :

            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 15, block.length )
            self.assertEqual( "XSB", block.name )

            self.assertEqual( 3, block.NEB )
            self.assertEqual( 3, block.number_electron_energies )
            self.assertEqual( 3, block.NPB )
            self.assertEqual( 3, block.number_photon_ratios )
            self.assertEqual( 9, block.number_cross_sections )
            
            self.assertEqual( 3, len( block.electron_energies ) )
            self.assertEqual( 3, len( block.photon_ratios ) )
            self.assertEqual( 3, len( block.cross_sections( 1 ) ) )
            self.assertEqual( 3, len( block.cross_sections( 2 ) ) )
            self.assertEqual( 3, len( block.cross_sections( 3 ) ) )
            self.assertEqual( 9, len( block.cross_section_data ) )
            
            self.assertEqual( self.chunk[0], block.electron_energy( 1 ) )
            self.assertEqual( self.chunk[0], block.electron_energies[0] )
            self.assertEqual( self.chunk[1], block.electron_energy( 2 ) )
            self.assertEqual( self.chunk[1], block.electron_energies[1] )
            self.assertEqual( self.chunk[2], block.electron_energy( 3 ) )
            self.assertEqual( self.chunk[2], block.electron_energies[2] )
            
            self.assertEqual( self.chunk[3], block.photon_ratio( 1 ) )
            self.assertEqual( self.chunk[3], block.photon_ratios[0] )
            self.assertEqual( self.chunk[4], block.photon_ratio( 2 ) )
            self.assertEqual( self.chunk[4], block.photon_ratios[1] )
            self.assertEqual( self.chunk[5], block.photon_ratio( 3 ) )
            self.assertEqual( self.chunk[5], block.photon_ratios[2] )
            
            self.assertEqual( self.chunk[6], block.cross_section( 1, 1 ) )
            self.assertEqual( self.chunk[6], block.cross_sections( 1 )[0] )
            self.assertEqual( self.chunk[6], block.cross_section_data[0] )
            self.assertEqual( self.chunk[7], block.cross_section( 2, 1 ) )
            self.assertEqual( self.chunk[7], block.cross_sections( 2 )[0] )
            self.assertEqual( self.chunk[7], block.cross_section_data[1] )
            self.assertEqual( self.chunk[8], block.cross_section( 3, 1 ) )
            self.assertEqual( self.chunk[8], block.cross_sections( 3 )[0] )
            self.assertEqual( self.chunk[8], block.cross_section_data[2] )
            self.assertEqual( self.chunk[9], block.cross_section( 1, 2 ) )
            self.assertEqual( self.chunk[9], block.cross_sections( 1 )[1] )
            self.assertEqual( self.chunk[9], block.cross_section_data[3] )
            self.assertEqual( self.chunk[10], block.cross_section( 2, 2 ) )
            self.assertEqual( self.chunk[10], block.cross_sections( 2 )[1] )
            self.assertEqual( self.chunk[10], block.cross_section_data[4] )
            self.assertEqual( self.chunk[11], block.cross_section( 3, 2 ) )
            self.assertEqual( self.chunk[11], block.cross_sections( 3 )[1] )
            self.assertEqual( self.chunk[11], block.cross_section_data[5] )
            self.assertEqual( self.chunk[12], block.cross_section( 1, 3 ) )
            self.assertEqual( self.chunk[12], block.cross_sections( 1 )[2] )
            self.assertEqual( self.chunk[12], block.cross_section_data[6] )
            self.assertEqual( self.chunk[13], block.cross_section( 2, 3 ) )
            self.assertEqual( self.chunk[13], block.cross_sections( 2 )[2] )
            self.assertEqual( self.chunk[13], block.cross_section_data[7] )
            self.assertEqual( self.chunk[14], block.cross_section( 3, 3 ) )
            self.assertEqual( self.chunk[14], block.cross_sections( 3 )[2] )
            self.assertEqual( self.chunk[14], block.cross_section_data[8] )

            # verify the xss array
            self.assertEqual( 15, len( block.xss_array ) )
            for index in range( block.length ) :

                self.assertAlmostEqual( self.chunk[index],
                                        block.xss_array[index] )

        # the data is given explicitly
        block = BremsstrahlungProductionBlock(
            self.chunk[0:3], self.chunk[3:6], [
                self.chunk[6:9], self.chunk[9:12], self.chunk[12:15] ] )

        verify_block( self, block )

if __name__ == '__main__' :

    unittest.main()
