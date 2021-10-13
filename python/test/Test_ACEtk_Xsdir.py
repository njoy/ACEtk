# standard imports
import unittest

# third party imports

# local imports
from ACEtk import Xsdir
from ACEtk import XsdirEntry

class Test_ACEtk_XsdirEntry( unittest.TestCase ) :
    """Unit test for the XsdirEntry class."""

    chunk = ( 'datapath=/some/path/to/Data\n'
              'atomic weight ratios\n'
              '       1   1.00000000\n'
              '    1000   0.99931697    1001   0.99916733    1002   1.99679968    1003   2.99013997\n'
              '                         1004   3.99320563\n'
              '   92000 235.98412800   92235 233.02478975 1092235 233.02478975\n'
              '\n'
              'directory\n'
              ' 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n'
              ' 92235.00c   235.000000 file2 0 1 3 2000 0 0 2.530000e-08 ptable\n'
              ' 92000.00p   233.000000 file3 0 1 4 3000\n' )

    chunk_with_upper_case = ( '   DaTaPatH=/some/path/to/Data   \n'
                              ' atomic WEIGHT ratios                      \n'
                              '       1   1.00000000\n'
                              '    1000   0.99931697    1001   0.99916733    1002   1.99679968    1003   2.99013997\n'
                              '                         1004   3.99320563\n'
                              '   92000 235.98412800   92235 233.02478975 1092235 233.02478975\n'
                              '\n'
                              '  DIRECTory               \n'
                              ' 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n'
                              ' 92235.00c   235.000000 file2 0 1 3 2000 0 0 2.530000e-08 ptable\n'
                              ' 92000.00p   233.000000 file3 0 1 4 3000\n' )

    chunk_without_datapath = ( '\n'
                               'atomic weight ratios\n'
                               '       1   1.00000000\n'
                               '    1000   0.99931697    1001   0.99916733    1002   1.99679968    1003   2.99013997\n'
                               '                         1004   3.99320563\n'
                               '   92000 235.98412800   92235 233.02478975 1092235 233.02478975\n'
                               '\n'
                               'directory\n'
                               ' 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n'
                               ' 92235.00c   235.000000 file2 0 1 3 2000 0 0 2.530000e-08 ptable\n'
                               ' 92000.00p   233.000000 file3 0 1 4 3000\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( '/some/path/to/Data', chunk.data_path )

            self.assertEqual( 9, len( chunk.atomic_weight_ratios ) )
            self.assertAlmostEqual(   1.00000000, chunk.atomic_weight_ratios[ 1 ] )
            self.assertAlmostEqual(   0.99931697, chunk.atomic_weight_ratios[ 1000 ] )
            self.assertAlmostEqual(   0.99916733, chunk.atomic_weight_ratios[ 1001 ] )
            self.assertAlmostEqual(   1.99679968, chunk.atomic_weight_ratios[ 1002 ] )
            self.assertAlmostEqual(   2.99013997, chunk.atomic_weight_ratios[ 1003 ] )
            self.assertAlmostEqual(   3.99320563, chunk.atomic_weight_ratios[ 1004 ] )
            self.assertAlmostEqual( 235.98412800, chunk.atomic_weight_ratios[ 92000 ] )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratios[ 92235 ] )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratios[ 1092235 ] )

            self.assertAlmostEqual(   1.00000000, chunk.atomic_weight_ratio( 1 ) )
            self.assertAlmostEqual(   0.99931697, chunk.atomic_weight_ratio( 1000 ) )
            self.assertAlmostEqual(   0.99916733, chunk.atomic_weight_ratio( 1001 ) )
            self.assertAlmostEqual(   1.99679968, chunk.atomic_weight_ratio( 1002 ) )
            self.assertAlmostEqual(   2.99013997, chunk.atomic_weight_ratio( 1003 ) )
            self.assertAlmostEqual(   3.99320563, chunk.atomic_weight_ratio( 1004 ) )
            self.assertAlmostEqual( 235.98412800, chunk.atomic_weight_ratio( 92000 ) )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratio( 92235 ) )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratio( 1092235 ) )

            self.assertEqual( 3, len( chunk.entries ) )
            self.assertEqual( '92234.00c', chunk.entries[0].zaid )
            self.assertEqual( '92235.00c', chunk.entries[1].zaid )
            self.assertEqual( '92000.00p', chunk.entries[2].zaid )

            entry = chunk.entry( '92234.00c' );
            self.assertEqual( '92234.00c', entry.zaid )

            entry = chunk.entry( '92235.00c' );
            self.assertEqual( '92235.00c', entry.zaid )

            entry = chunk.entry( '92000.00p' );
            self.assertEqual( '92000.00p', entry.zaid )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string() )

        def verify_chunk_without_datapath( self, chunk ) :

            # verify content
            self.assertEqual( None, chunk.data_path )

            self.assertEqual( 9, len( chunk.atomic_weight_ratios ) )
            self.assertAlmostEqual(   1.00000000, chunk.atomic_weight_ratios[ 1 ] )
            self.assertAlmostEqual(   0.99931697, chunk.atomic_weight_ratios[ 1000 ] )
            self.assertAlmostEqual(   0.99916733, chunk.atomic_weight_ratios[ 1001 ] )
            self.assertAlmostEqual(   1.99679968, chunk.atomic_weight_ratios[ 1002 ] )
            self.assertAlmostEqual(   2.99013997, chunk.atomic_weight_ratios[ 1003 ] )
            self.assertAlmostEqual(   3.99320563, chunk.atomic_weight_ratios[ 1004 ] )
            self.assertAlmostEqual( 235.98412800, chunk.atomic_weight_ratios[ 92000 ] )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratios[ 92235 ] )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratios[ 1092235 ] )

            self.assertAlmostEqual(   1.00000000, chunk.atomic_weight_ratio( 1 ) )
            self.assertAlmostEqual(   0.99931697, chunk.atomic_weight_ratio( 1000 ) )
            self.assertAlmostEqual(   0.99916733, chunk.atomic_weight_ratio( 1001 ) )
            self.assertAlmostEqual(   1.99679968, chunk.atomic_weight_ratio( 1002 ) )
            self.assertAlmostEqual(   2.99013997, chunk.atomic_weight_ratio( 1003 ) )
            self.assertAlmostEqual(   3.99320563, chunk.atomic_weight_ratio( 1004 ) )
            self.assertAlmostEqual( 235.98412800, chunk.atomic_weight_ratio( 92000 ) )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratio( 92235 ) )
            self.assertAlmostEqual( 233.02478975, chunk.atomic_weight_ratio( 1092235 ) )

            self.assertEqual( 3, len( chunk.entries ) )
            self.assertEqual( '92234.00c', chunk.entries[0].zaid )
            self.assertEqual( '92235.00c', chunk.entries[1].zaid )
            self.assertEqual( '92000.00p', chunk.entries[2].zaid )

            entry = chunk.entry( '92234.00c' );
            self.assertEqual( '92234.00c', entry.zaid )

            entry = chunk.entry( '92235.00c' );
            self.assertEqual( '92235.00c', entry.zaid )

            entry = chunk.entry( '92000.00p' );
            self.assertEqual( '92000.00p', entry.zaid )

            # verify string
            self.assertEqual( self.chunk_without_datapath, chunk.to_string() )

        # the data is given explicitly
        chunk = Xsdir( datapath = '/some/path/to/Data',
                       ratios = {

                               1 :   1.00000000,
                            1000 :   0.99931697,
                            1001 :   0.99916733,
                            1002 :   1.99679968,
                            1003 :   2.99013997,
                            1004 :   3.99320563,
                           92000 : 235.98412800,
                           92235 : 233.02478975,
                         1092235 : 233.02478975
                       },
                       entries = [

                         XsdirEntry( '92234.00c', 234., 'file', 5, 1000, 2.53e-8, False ),
                         XsdirEntry( '92235.00c', 235., 'file2', 3, 2000, 2.53e-8, True ),
                         XsdirEntry( '92000.00p', 233., 'file3', 4, 3000 )
                       ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Xsdir.from_string( self.chunk )

        verify_chunk( self, chunk )

        # the data is read from a string with some upper case keywords
        chunk = Xsdir.from_string( self.chunk_with_upper_case )

        verify_chunk( self, chunk )

        # the data is given explicitly without a datapath
        chunk = Xsdir( ratios = {

                               1 :   1.00000000,
                            1000 :   0.99931697,
                            1001 :   0.99916733,
                            1002 :   1.99679968,
                            1003 :   2.99013997,
                            1004 :   3.99320563,
                           92000 : 235.98412800,
                           92235 : 233.02478975,
                         1092235 : 233.02478975
                       },
                       entries = [

                         XsdirEntry( '92234.00c', 234., 'file', 5, 1000, 2.53e-8, False ),
                         XsdirEntry( '92235.00c', 235., 'file2', 3, 2000, 2.53e-8, True ),
                         XsdirEntry( '92000.00p', 233., 'file3', 4, 3000 )
                       ] )

        verify_chunk_without_datapath( self, chunk )

        # the data is read from a string
        chunk = Xsdir.from_string( self.chunk_without_datapath )

        verify_chunk_without_datapath( self, chunk )

if __name__ == '__main__' :

    unittest.main()
