# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import AbsorptionCrossSectionBlock

class Test_ACEtk_multigroup_AbsorptionCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the AbsorptionCrossSectionBlock class."""

    chunk = [2.847090000000E-05,  2.976620000000E-05,
             3.032220000000E-05,  3.180660000000E-05,  3.349790000000E-05,  3.524820000000E-05,
             3.623040000000E-05,  3.579650000000E-05,  3.497190000000E-05,  3.431090000000E-05,
             3.433360000000E-05,  3.451760000000E-05,  3.622100000000E-05,  4.202520000000E-05,
             5.677600000000E-05,  1.012830000000E-04,  2.061770000000E-04,  3.949250000000E-04,
             7.082510000000E-04,  1.195170000000E-03,  1.947160000000E-03,  3.217480000000E-03,
             5.321480000000E-03,  8.793070000000E-03,  1.449130000000E-02,  2.391300000000E-02,
             3.934770000000E-02,  6.495030000000E-02,  1.071560000000E-01,  3.011490000000E-01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 30, chunk.length )
            self.assertEqual( "ABS", chunk.name )

            self.assertEqual( 30, len( chunk.xss_array ) )

            self.assertEqual( 30, len( chunk.absorption_cross_section ) )

            self.assertAlmostEqual( 2.847090000000E-05, chunk.absorption_cross_section[0] )
            self.assertAlmostEqual( 3.011490000000E-01, chunk.absorption_cross_section[-1] )
            self.assertAlmostEqual( 2.847090000000E-05, chunk.SIGABS[0] )
            self.assertAlmostEqual( 3.011490000000E-01, chunk.SIGABS[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = AbsorptionCrossSectionBlock(
          absorption_cross_section =  [ 2.847090000000E-05,  2.976620000000E-05,
             3.032220000000E-05,  3.180660000000E-05,  3.349790000000E-05,  3.524820000000E-05,
             3.623040000000E-05,  3.579650000000E-05,  3.497190000000E-05,  3.431090000000E-05,
             3.433360000000E-05,  3.451760000000E-05,  3.622100000000E-05,  4.202520000000E-05,
             5.677600000000E-05,  1.012830000000E-04,  2.061770000000E-04,  3.949250000000E-04,
             7.082510000000E-04,  1.195170000000E-03,  1.947160000000E-03,  3.217480000000E-03,
             5.321480000000E-03,  8.793070000000E-03,  1.449130000000E-02,  2.391300000000E-02,
             3.934770000000E-02,  6.495030000000E-02,  1.071560000000E-01,  3.011490000000E-01] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
