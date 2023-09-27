# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoatomicElectronCrossSectionBlock

class Test_ACEtk_PhotoatomicElectronCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the PhotoatomicElectronCrossSectionBlock class."""

    chunk = [  10.,  20., 200.,
               35.,  40.,  45.,
                1.,   2.,   3.,
                4.,   5.,   6.,
                7.,   8.,   9.,
               23.,  25.,  27.,
               10.,  11.,  12.,
               13.,  14.,  15. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 24, chunk.length )
            self.assertEqual( "ESZE", chunk.name )

            self.assertEqual( 24, len( chunk.xss_array ) )

            self.assertEqual( 3, chunk.NE )
            self.assertEqual( 3, chunk.number_energy_points )
            self.assertEqual( 2, chunk.NSSH )
            self.assertEqual( 2, chunk.number_electron_subshells )

            self.assertEqual( 3, len( chunk.energies ) )
            self.assertEqual( 3, len( chunk.total ) )
            self.assertEqual( 3, len( chunk.elastic ) )
            self.assertEqual( 3, len( chunk.bremsstrahlung ) )
            self.assertEqual( 3, len( chunk.excitation ) )
            self.assertEqual( 3, len( chunk.total_electroionisation ) )
            self.assertEqual( 3, len( chunk.electroionisation( 1 ) ) )
            self.assertEqual( 3, len( chunk.electroionisation( 2 ) ) )

            self.assertAlmostEqual(  10., chunk.energies[0] )
            self.assertAlmostEqual(  20., chunk.energies[1] )
            self.assertAlmostEqual( 200., chunk.energies[2] )
            self.assertAlmostEqual(  35., chunk.total[0] )
            self.assertAlmostEqual(  40., chunk.total[1] )
            self.assertAlmostEqual(  45., chunk.total[2] )
            self.assertAlmostEqual(   1., chunk.elastic[0] )
            self.assertAlmostEqual(   2., chunk.elastic[1] )
            self.assertAlmostEqual(   3., chunk.elastic[2] )
            self.assertAlmostEqual(   4., chunk.bremsstrahlung[0] )
            self.assertAlmostEqual(   5., chunk.bremsstrahlung[1] )
            self.assertAlmostEqual(   6., chunk.bremsstrahlung[2] )
            self.assertAlmostEqual(   7., chunk.excitation[0] )
            self.assertAlmostEqual(   8., chunk.excitation[1] )
            self.assertAlmostEqual(   9., chunk.excitation[2] )
            self.assertAlmostEqual(  23., chunk.total_electroionisation[0] )
            self.assertAlmostEqual(  25., chunk.total_electroionisation[1] )
            self.assertAlmostEqual(  27., chunk.total_electroionisation[2] )
            self.assertAlmostEqual(  10., chunk.electroionisation(1)[0] )
            self.assertAlmostEqual(  11., chunk.electroionisation(1)[1] )
            self.assertAlmostEqual(  12., chunk.electroionisation(1)[2] )
            self.assertAlmostEqual(  13., chunk.electroionisation(2)[0] )
            self.assertAlmostEqual(  14., chunk.electroionisation(2)[1] )
            self.assertAlmostEqual(  15., chunk.electroionisation(2)[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoatomicElectronCrossSectionBlock(
                  energies = [ 10., 20., 200. ],
                  elastic = [ 1., 2., 3. ],
                  bremsstrahlung = [ 4., 5., 6. ],
                  excitation = [ 7., 8., 9. ],
                  electroionisation = [ [ 10., 11., 12. ],
                                        [ 13., 14., 15. ] ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
