# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import TotalCrossSectionBlock

class Test_ACEtk_multigroup_TotalCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the TotalCrossSectionBlock class."""

    chunk = [6.200214709000E-01,  6.907907662000E-01,  7.470023222000E-01,  8.664838066000E-01,
             1.065043497900E+00,  1.302895248200E+00,  1.764466230400E+00,  2.198615796500E+00,
             2.559534971900E+00,  2.953224310900E+00,  3.399364333600E+00,  4.156264517600E+00,
             5.377266221000E+00,  6.951312025200E+00,  8.974946776000E+00,  1.228060128300E+01,
             1.619300617700E+01,  1.860559492500E+01,  1.972700825100E+01,  2.018539517000E+01,
             2.036104716000E+01,  2.042841748000E+01,  2.045502148000E+01,  2.046529307000E+01,
             2.048379130000E+01,  2.052821300000E+01,  2.063794770000E+01,  2.092175030000E+01,
             2.166585600000E+01,  2.972354900000E+01 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 30, chunk.length )
            self.assertEqual( "TOT", chunk.name )

            self.assertEqual( 30, len( chunk.xss_array ) )

            self.assertEqual( 30, len( chunk.total_cross_section ) )

            self.assertAlmostEqual( 6.200214709000E-01, chunk.total_cross_section[0] )
            self.assertAlmostEqual( 2.972354900000E+01, chunk.total_cross_section[-1] )
            self.assertAlmostEqual( 6.200214709000E-01, chunk.SIGTOT[0] )
            self.assertAlmostEqual( 2.972354900000E+01, chunk.SIGTOT[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = TotalCrossSectionBlock(
          total_cross_section =  [ 6.200214709000E-01,  6.907907662000E-01,  7.470023222000E-01,  8.664838066000E-01,
             1.065043497900E+00,  1.302895248200E+00,  1.764466230400E+00,  2.198615796500E+00,
             2.559534971900E+00,  2.953224310900E+00,  3.399364333600E+00,  4.156264517600E+00,
             5.377266221000E+00,  6.951312025200E+00,  8.974946776000E+00,  1.228060128300E+01,
             1.619300617700E+01,  1.860559492500E+01,  1.972700825100E+01,  2.018539517000E+01,
             2.036104716000E+01,  2.042841748000E+01,  2.045502148000E+01,  2.046529307000E+01,
             2.048379130000E+01,  2.052821300000E+01,  2.063794770000E+01,  2.092175030000E+01,
             2.166585600000E+01,  2.972354900000E+01] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
