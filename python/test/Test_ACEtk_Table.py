# standard imports
import unittest

# third party imports

# local imports
from ACEtk import Header
from ACEtk import Data
from ACEtk import Table

class Test_ACEtk_Table( unittest.TestCase ) :
    """Unit test for the Table class."""

    chunk = ( ' 92238.80c  236.005800  2.5301E-08   12/13/12\n'
              'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n'
              '      0 15.0000000      1 14.0000000      2 13.0000000      3 12.0000000\n'
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
            self.assertEqual( '1.0.0', chunk.header.VERS )
            self.assertEqual( '1.0.0', chunk.header.version )
            self.assertEqual( '92238.80c', chunk.header.zaid )
            self.assertEqual( 236.005800, chunk.header.AWR )
            self.assertEqual( 236.005800, chunk.header.atomic_weight_ratio )
            self.assertEqual( 2.5301E-08, chunk.header.TEMP )
            self.assertEqual( 2.5301E-08, chunk.header.temperature )
            self.assertEqual( '12/13/12', chunk.header.date )
            self.assertEqual( 'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)',
                              chunk.header.title )
            self.assertEqual( 'mat9237', chunk.header.material )

            self.assertEqual( 16, len( chunk.data.iz_array ) )
            self.assertEqual( 0, chunk.data.iz( 1 ) )
            self.assertEqual( 1, chunk.data.iz( 2 ) )
            self.assertEqual( 2, chunk.data.iz( 3 ) )
            self.assertEqual( 3, chunk.data.iz( 4 ) )
            self.assertEqual( 4, chunk.data.iz( 5 ) )
            self.assertEqual( 5, chunk.data.iz( 6 ) )
            self.assertEqual( 6, chunk.data.iz( 7 ) )
            self.assertEqual( 7, chunk.data.iz( 8 ) )
            self.assertEqual( 8, chunk.data.iz( 9 ) )
            self.assertEqual( 9, chunk.data.iz( 10 ) )
            self.assertEqual( 10, chunk.data.iz( 11 ) )
            self.assertEqual( 11, chunk.data.iz( 12 ) )
            self.assertEqual( 12, chunk.data.iz( 13 ) )
            self.assertEqual( 13, chunk.data.iz( 14 ) )
            self.assertEqual( 14, chunk.data.iz( 15 ) )
            self.assertEqual( 15, chunk.data.iz( 16 ) )

            self.assertEqual( 16, len( chunk.data.aw_array ) )
            self.assertEqual( 15, chunk.data.aw( 1 ) )
            self.assertEqual( 14, chunk.data.aw( 2 ) )
            self.assertEqual( 13, chunk.data.aw( 3 ) )
            self.assertEqual( 12, chunk.data.aw( 4 ) )
            self.assertEqual( 11, chunk.data.aw( 5 ) )
            self.assertEqual( 10, chunk.data.aw( 6 ) )
            self.assertEqual( 9, chunk.data.aw( 7 ) )
            self.assertEqual( 8, chunk.data.aw( 8 ) )
            self.assertEqual( 7, chunk.data.aw( 9 ) )
            self.assertEqual( 6, chunk.data.aw( 10 ) )
            self.assertEqual( 5, chunk.data.aw( 11 ) )
            self.assertEqual( 4, chunk.data.aw( 12 ) )
            self.assertEqual( 3, chunk.data.aw( 13 ) )
            self.assertEqual( 2, chunk.data.aw( 14 ) )
            self.assertEqual( 1, chunk.data.aw( 15 ) )
            self.assertEqual( 0, chunk.data.aw( 16 ) )

            self.assertEqual( 16, len( chunk.data.nxs_array ) )
            self.assertEqual( 6, chunk.data.nxs( 1 ) )
            self.assertEqual( 33074, chunk.data.nxs( 2 ) )
            self.assertEqual( 1595, chunk.data.nxs( 3 ) )
            self.assertEqual( 132, chunk.data.nxs( 4 ) )
            self.assertEqual( 46, chunk.data.nxs( 5 ) )
            self.assertEqual( 814, chunk.data.nxs( 6 ) )
            self.assertEqual( 2, chunk.data.nxs( 7 ) )
            self.assertEqual( 0, chunk.data.nxs( 8 ) )
            self.assertEqual( 0, chunk.data.nxs( 9 ) )
            self.assertEqual( 0, chunk.data.nxs( 10 ) )
            self.assertEqual( 0, chunk.data.nxs( 11 ) )
            self.assertEqual( 0, chunk.data.nxs( 12 ) )
            self.assertEqual( 0, chunk.data.nxs( 13 ) )
            self.assertEqual( 0, chunk.data.nxs( 14 ) )
            self.assertEqual( 0, chunk.data.nxs( 15 ) )
            self.assertEqual( 9, chunk.data.nxs( 16 ) )

            self.assertEqual( 32, len( chunk.data.jxs_array ) )
            self.assertEqual( 1, chunk.data.jxs( 1 ) )
            self.assertEqual( 788721, chunk.data.jxs( 2 ) )
            self.assertEqual( 788768, chunk.data.jxs( 3 ) )
            self.assertEqual( 788815, chunk.data.jxs( 4 ) )
            self.assertEqual( 788862, chunk.data.jxs( 5 ) )
            self.assertEqual( 788909, chunk.data.jxs( 6 ) )
            self.assertEqual( 788956, chunk.data.jxs( 7 ) )
            self.assertEqual( 1270743, chunk.data.jxs( 8 ) )
            self.assertEqual( 1270789, chunk.data.jxs( 9 ) )
            self.assertEqual( 1363882, chunk.data.jxs( 10 ) )
            self.assertEqual( 1363927, chunk.data.jxs( 11 ) )
            self.assertEqual( 1475750, chunk.data.jxs( 12 ) )
            self.assertEqual( 1633494, chunk.data.jxs( 13 ) )
            self.assertEqual( 1633500, chunk.data.jxs( 14 ) )
            self.assertEqual( 1633506, chunk.data.jxs( 15 ) )
            self.assertEqual( 1634036, chunk.data.jxs( 16 ) )
            self.assertEqual( 1634042, chunk.data.jxs( 17 ) )
            self.assertEqual( 1634042, chunk.data.jxs( 18 ) )
            self.assertEqual( 1634048, chunk.data.jxs( 19 ) )
            self.assertEqual( 1637218, chunk.data.jxs( 20 ) )
            self.assertEqual( 789147, chunk.data.jxs( 21 ) )
            self.assertEqual( 1637220, chunk.data.jxs( 22 ) )
            self.assertEqual( 1464171, chunk.data.jxs( 23 ) )
            self.assertEqual( 1465923, chunk.data.jxs( 24 ) )
            self.assertEqual( 1465934, chunk.data.jxs( 25 ) )
            self.assertEqual( 1465976, chunk.data.jxs( 26 ) )
            self.assertEqual( 1465982, chunk.data.jxs( 27 ) )
            self.assertEqual( 0, chunk.data.jxs( 28 ) )
            self.assertEqual( 0, chunk.data.jxs( 29 ) )
            self.assertEqual( 0, chunk.data.jxs( 30 ) )
            self.assertEqual( 0, chunk.data.jxs( 31 ) )
            self.assertEqual( 8, chunk.data.jxs( 32 ) )

            self.assertEqual( 6, len( chunk.data.xss_array ) )
            self.assertAlmostEqual( 1.00000000000E+00, chunk.data.xss( 1 ) )
            self.assertAlmostEqual( 1.03125000000E+00, chunk.data.xss( 2 ) )
            self.assertAlmostEqual( 1.06250000000E+00, chunk.data.xss( 3 ) )
            self.assertAlmostEqual( 1.09375000000E+00, chunk.data.xss( 4 ) )
            self.assertAlmostEqual( 1.12500000000E+00, chunk.data.xss( 5 ) )
            self.assertAlmostEqual( 1.15625000000E+00, chunk.data.xss( 6 ) )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string() )

        # the data is read from a string
        chunk = Table.from_string( self.chunk )

        verify_chunk( self, chunk )

        # the data is made from scratch
        header = Header( zaid = '92238.80c', awr = 236.0058,
                         temperature = 2.5301E-08, date = '12/13/12',
                         title = 'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)',
                         material = 'mat9237' )

        data = Data( iz = [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 ],
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

        chunk = Table( header = header, data = data )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
