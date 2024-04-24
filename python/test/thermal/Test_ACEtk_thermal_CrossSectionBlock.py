# standard imports
import unittest

# third party imports

# local imports
from ACEtk.thermal import CrossSectionBlock

class Test_ACEtk_thermal_CrossSectionBlock( unittest.TestCase ) :
    """Unit test for the CrossSectionBlock class."""

    chunk = [                 4,  1.00000000000E+01,  2.00000000000E+01,  3.00000000000E+01,
              4.00000000000E+01,  1.00000000000E+00,  2.00000000000E+00,  3.00000000000E+00,
              4.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 9, chunk.length )
            self.assertEqual( "CrossSectionBlock", chunk.name )

            self.assertEqual( 4, chunk.NE )
            self.assertEqual( 4, chunk.number_incident_energies )

            self.assertEqual( 4, len( chunk.energies ) )
            self.assertAlmostEqual( 10., chunk.energies[0] )
            self.assertAlmostEqual( 40., chunk.energies[-1] )

            self.assertEqual( 4, len( chunk.cross_sections ) )
            self.assertAlmostEqual( 1., chunk.cross_sections[0] )
            self.assertAlmostEqual( 4., chunk.cross_sections[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = CrossSectionBlock(
                    energies = [ 10., 20., 30., 40. ],
                    xs = [ 1., 2., 3., 4. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
