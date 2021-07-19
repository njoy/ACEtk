# standard imports
import unittest

# third party imports

# local imports
from ACEtk import Data

class Test_ACEtk_Data( unittest.TestCase ) :
    """Unit test for the Data class."""

    chunk = ( '      0 15.0000000      1 14.0000000      2 13.0000000      3 12.0000000\n'
              '      4 11.0000000      5 10.0000000      6  9.0000000      7  8.0000000\n'
              '      8  7.0000000      9  6.0000000     10  5.0000000     11  4.0000000\n'
              '     12  3.0000000     13  2.0000000     14  1.0000000     15  0.0000000\n'
              '        6    33074     1595      132       46      814        2        0\n'
              '        0        0        0        0        0        0        0        9\n'
              '        1   788721   788768   788815   788862   788909   788956  1270743\n'
              '  1270789  1363882  1363927  1475750  1633494  1633500  1633506  1634036\n'
              '  1634042  1634042  1634048  1637218   789147  1637220  1464171  1465923\n'
              '  1465934  1465976  1465982        0        0        0        0        8\n'
              '  1.000000000000E+00  1.031250000000E+00  1.062500000000E+00  1.093750000000E+00\n'
              '  1.125000000000E+00  1.156250000000E+00\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 16, len( chunk.iz_array ) )
            self.assertEqual( 0, chunk.iz( 1 ) )
            self.assertEqual( 1, chunk.iz( 2 ) )
            self.assertEqual( 2, chunk.iz( 3 ) )
            self.assertEqual( 3, chunk.iz( 4 ) )
            self.assertEqual( 4, chunk.iz( 5 ) )
            self.assertEqual( 5, chunk.iz( 6 ) )
            self.assertEqual( 6, chunk.iz( 7 ) )
            self.assertEqual( 7, chunk.iz( 8 ) )
            self.assertEqual( 8, chunk.iz( 9 ) )
            self.assertEqual( 9, chunk.iz( 10 ) )
            self.assertEqual( 10, chunk.iz( 11 ) )
            self.assertEqual( 11, chunk.iz( 12 ) )
            self.assertEqual( 12, chunk.iz( 13 ) )
            self.assertEqual( 13, chunk.iz( 14 ) )
            self.assertEqual( 14, chunk.iz( 15 ) )
            self.assertEqual( 15, chunk.iz( 16 ) )

            self.assertEqual( 16, len( chunk.aw_array ) )
            self.assertEqual( 15, chunk.aw( 1 ) )
            self.assertEqual( 14, chunk.aw( 2 ) )
            self.assertEqual( 13, chunk.aw( 3 ) )
            self.assertEqual( 12, chunk.aw( 4 ) )
            self.assertEqual( 11, chunk.aw( 5 ) )
            self.assertEqual( 10, chunk.aw( 6 ) )
            self.assertEqual( 9, chunk.aw( 7 ) )
            self.assertEqual( 8, chunk.aw( 8 ) )
            self.assertEqual( 7, chunk.aw( 9 ) )
            self.assertEqual( 6, chunk.aw( 10 ) )
            self.assertEqual( 5, chunk.aw( 11 ) )
            self.assertEqual( 4, chunk.aw( 12 ) )
            self.assertEqual( 3, chunk.aw( 13 ) )
            self.assertEqual( 2, chunk.aw( 14 ) )
            self.assertEqual( 1, chunk.aw( 15 ) )
            self.assertEqual( 0, chunk.aw( 16 ) )

            self.assertEqual( 16, len( chunk.nxs_array ) )
            self.assertEqual( 6, chunk.nxs( 1 ) )
            self.assertEqual( 33074, chunk.nxs( 2 ) )
            self.assertEqual( 1595, chunk.nxs( 3 ) )
            self.assertEqual( 132, chunk.nxs( 4 ) )
            self.assertEqual( 46, chunk.nxs( 5 ) )
            self.assertEqual( 814, chunk.nxs( 6 ) )
            self.assertEqual( 2, chunk.nxs( 7 ) )
            self.assertEqual( 0, chunk.nxs( 8 ) )
            self.assertEqual( 0, chunk.nxs( 9 ) )
            self.assertEqual( 0, chunk.nxs( 10 ) )
            self.assertEqual( 0, chunk.nxs( 11 ) )
            self.assertEqual( 0, chunk.nxs( 12 ) )
            self.assertEqual( 0, chunk.nxs( 13 ) )
            self.assertEqual( 0, chunk.nxs( 14 ) )
            self.assertEqual( 0, chunk.nxs( 15 ) )
            self.assertEqual( 9, chunk.nxs( 16 ) )

            self.assertEqual( 32, len( chunk.jxs_array ) )
            self.assertEqual( 1, chunk.jxs( 1 ) )
            self.assertEqual( 788721, chunk.jxs( 2 ) )
            self.assertEqual( 788768, chunk.jxs( 3 ) )
            self.assertEqual( 788815, chunk.jxs( 4 ) )
            self.assertEqual( 788862, chunk.jxs( 5 ) )
            self.assertEqual( 788909, chunk.jxs( 6 ) )
            self.assertEqual( 788956, chunk.jxs( 7 ) )
            self.assertEqual( 1270743, chunk.jxs( 8 ) )
            self.assertEqual( 1270789, chunk.jxs( 9 ) )
            self.assertEqual( 1363882, chunk.jxs( 10 ) )
            self.assertEqual( 1363927, chunk.jxs( 11 ) )
            self.assertEqual( 1475750, chunk.jxs( 12 ) )
            self.assertEqual( 1633494, chunk.jxs( 13 ) )
            self.assertEqual( 1633500, chunk.jxs( 14 ) )
            self.assertEqual( 1633506, chunk.jxs( 15 ) )
            self.assertEqual( 1634036, chunk.jxs( 16 ) )
            self.assertEqual( 1634042, chunk.jxs( 17 ) )
            self.assertEqual( 1634042, chunk.jxs( 18 ) )
            self.assertEqual( 1634048, chunk.jxs( 19 ) )
            self.assertEqual( 1637218, chunk.jxs( 20 ) )
            self.assertEqual( 789147, chunk.jxs( 21 ) )
            self.assertEqual( 1637220, chunk.jxs( 22 ) )
            self.assertEqual( 1464171, chunk.jxs( 23 ) )
            self.assertEqual( 1465923, chunk.jxs( 24 ) )
            self.assertEqual( 1465934, chunk.jxs( 25 ) )
            self.assertEqual( 1465976, chunk.jxs( 26 ) )
            self.assertEqual( 1465982, chunk.jxs( 27 ) )
            self.assertEqual( 0, chunk.jxs( 28 ) )
            self.assertEqual( 0, chunk.jxs( 29 ) )
            self.assertEqual( 0, chunk.jxs( 30 ) )
            self.assertEqual( 0, chunk.jxs( 31 ) )
            self.assertEqual( 8, chunk.jxs( 32 ) )

            self.assertEqual( 6, len( chunk.xss_array ) )
            self.assertAlmostEqual( 1.00000000000E+00, chunk.xss( 1 ) )
            self.assertAlmostEqual( 1.03125000000E+00, chunk.xss( 2 ) )
            self.assertAlmostEqual( 1.06250000000E+00, chunk.xss( 3 ) )
            self.assertAlmostEqual( 1.09375000000E+00, chunk.xss( 4 ) )
            self.assertAlmostEqual( 1.12500000000E+00, chunk.xss( 5 ) )
            self.assertAlmostEqual( 1.15625000000E+00, chunk.xss( 6 ) )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string() )

        # the data is given explicitly (5 arrays)
        chunk = Data( iz = [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 ],
                      aw = [ 15., 14., 13., 12., 11., 10., 9., 8.,
                              7., 6., 5., 4., 3., 2., 1., 0. ],
                      nxs = [  6, 33074, 1595, 132, 46, 814, 2, 0,
                               0,     0,    0,   0,  0,   0, 0, 9 ],
                      jxs = [       1,  788721,  788768,  788815,
                                788862,  788909,  788956, 1270743,
                               1270789, 1363882, 1363927, 1475750,
                               1633494, 1633500, 1633506, 1634036,
                               1634042, 1634042, 1634048, 1637218,
                                789147, 1637220, 1464171, 1465923,
                               1465934, 1465976, 1465982,       0,
                                     0,       0,       0,       8 ],
                      xss = [ 1.00000000000E+00, 1.03125000000E+00,
                              1.06250000000E+00, 1.09375000000E+00,
                              1.12500000000E+00, 1.15625000000E+00 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Data.from_string( self.chunk )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
