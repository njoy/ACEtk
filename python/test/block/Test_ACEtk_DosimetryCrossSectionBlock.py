# standard imports
import unittest

# third party imports

# local imports
from ACEtk import DosimetryCrossSectionBlock
from ACEtk import DosimetryCrossSectionData

class Test_ACEtk_DosimetryCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the DosimetryCrossSectionBlock class."""

    chunk = [                   1,                  11,
                                0,                   4,  1.896100000000E+00,  2.000000000000E+00,
               2.050000000000E+00,  2.000000000000E+01,  0.000000000000E+00,  9.090000000000E-15,
               3.638500000000E-02,  3.220000000000E-02,                   0,                   3,
               3.248700000000E+00,  3.600000000000E+00,  2.000000000000E+01,  0.000000000000E+00,
               5.653700000000E-02,  4.980000000000E-02 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 20, chunk.length )
            self.assertEqual( "SIGD", chunk.name )

            self.assertEqual( 2, chunk.NTR )
            self.assertEqual( 2, chunk.number_reactions )
            self.assertEqual( 2, len( chunk.data ) )

            self.assertEqual( 1, chunk.LSIG(1) )
            self.assertEqual( 11, chunk.LSIG(2) )
            self.assertEqual( 1, chunk.cross_section_locator(1) )
            self.assertEqual( 11, chunk.cross_section_locator(2) )

            xs = chunk.cross_section_data(1)
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 4, xs.number_energy_points )
            self.assertEqual( 4, len( xs.energies ) )
            self.assertEqual( 4, len( xs.cross_sections ) )
            self.assertAlmostEqual( 1.8961, xs.energies[0] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertAlmostEqual( 0., xs.cross_sections[0] )
            self.assertAlmostEqual( 0.0322, xs.cross_sections[-1] )

            xs = chunk.cross_section_data(2)
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 3, xs.number_energy_points )
            self.assertEqual( 3, len( xs.energies ) )
            self.assertEqual( 3, len( xs.cross_sections ) )
            self.assertAlmostEqual( 3.2487, xs.energies[0] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertAlmostEqual( 0., xs.cross_sections[0] )
            self.assertAlmostEqual( 0.0498, xs.cross_sections[-1] )

            xs = chunk.data[0]
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 4, xs.number_energy_points )
            self.assertEqual( 4, len( xs.energies ) )
            self.assertEqual( 4, len( xs.cross_sections ) )
            self.assertAlmostEqual( 1.8961, xs.energies[0] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertAlmostEqual( 0., xs.cross_sections[0] )
            self.assertAlmostEqual( 0.0322, xs.cross_sections[-1] )

            xs = chunk.data[1]
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 3, xs.number_energy_points )
            self.assertEqual( 3, len( xs.energies ) )
            self.assertEqual( 3, len( xs.cross_sections ) )
            self.assertAlmostEqual( 3.2487, xs.energies[0] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertAlmostEqual( 0., xs.cross_sections[0] )
            self.assertAlmostEqual( 0.0498, xs.cross_sections[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = DosimetryCrossSectionBlock(
                  xs = [ DosimetryCrossSectionData(
                           [ 1.896100000000E+00,  2.000000000000E+00,
                             2.050000000000E+00,  2.000000000000E+01 ],
                           [ 0.000000000000E+00,  9.090000000000E-15,
                             3.638500000000E-02,  3.220000000000E-02 ] ),
                         DosimetryCrossSectionData(
                           [ 3.248700000000E+00,  3.600000000000E+00,
                             2.000000000000E+01 ],
                           [ 0.000000000000E+00,  5.653700000000E-02,
                             4.980000000000E-02 ] ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
