# standard imports
import unittest

# third party imports

# local imports
from ACEtk import XsdirEntry

class Test_ACEtk_XsdirEntry( unittest.TestCase ) :
    """Unit test for the XsdirEntry class."""

    chunk = ( ' 92235.00c   235.000000 file 0 1 5 1000 0 0 2.530000e-08 ptable\n' )
    chunk_with_split = ( ' 92235.00c   235.000000 filenamethatiswaaaaaaaaaaaaaaaaaaaaaaaaaytoolong +\n'
                         '     accessnamethatisevenwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaylonger 1 5 1000 0 0 2.530000e-08 +\n'
                         '     ptable\n' )
    chunk_7_entries = ( ' 92235.00c   235.000000 file 0 1 5 1000\n' )
    chunk_10_entries = ( ' 92235.00c   235.000000 file 0 1 5 1000 0 0 2.530000e-08\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assert_equal( '92235.00c', chunk.zaid )
            self.assert_equal( 235., chunk.awr )
            self.assert_equal( 235., chunk.atomic_weight_ratio )
            self.assert_equal( 'file', chunk.file_name )
            self.assert_equal( std::nullopt, chunk.access_route )
            self.assert_equal( 1, chunk.file_type )
            self.assert_equal( 5, chunk.address )
            self.assert_equal( 1000, chunk.table_length )
            self.assert_equal( std::nullopt, chunk.record_length )
            self.assert_equal( std::nullopt, chunk.entries_per_record )
            self.assert_equal( std::nullopt != chunk.temperature )
            self.assert_equal( 2.53e-8, Achunk.temperature )
            self.assert_equal( true, chunk.ptable )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string() )

        # the data is given explicitly
        XsdirEntry chunk( zaid = '92235.00c', awr = 235., filename = 'file',
                          address = 5, tablelength = 1000,
                          temperature = 2.53e-8, ptable = true );

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = XsdirEntry.from_string( self.chunk )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
