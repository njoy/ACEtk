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
            self.assertEqual( '92235.00c', chunk.zaid )
            self.assertEqual( 235., chunk.awr )
            self.assertEqual( 235., chunk.atomic_weight_ratio )
            self.assertEqual( 'file', chunk.file_name )
            self.assertEqual( None, chunk.access_route )
            self.assertEqual( 1, chunk.file_type )
            self.assertEqual( 5, chunk.address )
            self.assertEqual( 1000, chunk.table_length )
            self.assertEqual( None, chunk.record_length )
            self.assertEqual( None, chunk.entries_per_record )
            self.assertEqual( 2.53e-8, chunk.temperature )
            self.assertEqual( True, chunk.ptable )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string() )

        def verify_chunk_with_split( self, chunk ) :

            # verify content
            self.assertEqual( '92235.00c', chunk.zaid )
            self.assertAlmostEqual( 235., chunk.awr )
            self.assertAlmostEqual( 235., chunk.atomic_weight_ratio )
            self.assertEqual( 'filenamethatiswaaaaaaaaaaaaaaaaaaaaaaaaaytoolong', chunk.file_name )
            self.assertEqual( 'accessnamethatisevenwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaylonger', chunk.access_route )
            self.assertEqual( 1, chunk.file_type )
            self.assertEqual( 5, chunk.address )
            self.assertEqual( 1000, chunk.table_length )
            self.assertEqual( None, chunk.record_length )
            self.assertEqual( None, chunk.entries_per_record )
            self.assertAlmostEqual( 2.53e-8, chunk.temperature )
            self.assertEqual( True, chunk.ptable )

            # verify string
            self.assertEqual( self.chunk_with_split, chunk.to_string() )

        def verify_chunk_7_entries( self, chunk ) :

            # verify content
            self.assertEqual( '92235.00c', chunk.zaid )
            self.assertAlmostEqual( 235., chunk.awr )
            self.assertAlmostEqual( 235., chunk.atomic_weight_ratio )
            self.assertEqual( 'file', chunk.file_name )
            self.assertEqual( None, chunk.access_route )
            self.assertEqual( 1, chunk.file_type )
            self.assertEqual( 5, chunk.address )
            self.assertEqual( 1000, chunk.table_length )
            self.assertEqual( None, chunk.record_length )
            self.assertEqual( None, chunk.entries_per_record )
            self.assertEqual( None, chunk.temperature )
            self.assertEqual( False, chunk.ptable )

            # verify string
            self.assertEqual( self.chunk_7_entries, chunk.to_string() )

        def verify_chunk_10_entries( self, chunk ) :

            # verify content
            self.assertEqual( '92235.00c', chunk.zaid )
            self.assertAlmostEqual( 235., chunk.awr )
            self.assertAlmostEqual( 235., chunk.atomic_weight_ratio )
            self.assertEqual( 'file', chunk.file_name )
            self.assertEqual( None, chunk.access_route )
            self.assertEqual( 1, chunk.file_type )
            self.assertEqual( 5, chunk.address )
            self.assertEqual( 1000, chunk.table_length )
            self.assertEqual( None, chunk.record_length )
            self.assertEqual( None, chunk.entries_per_record )
            self.assertAlmostEqual( 2.53e-8, chunk.temperature )
            self.assertEqual( False, chunk.ptable )

            # verify string
            self.assertEqual( self.chunk_10_entries, chunk.to_string() )

        # the data is given explicitly
        chunk = XsdirEntry( zaid = '92235.00c', awr = 235., filename = 'file',
                            address = 5, length = 1000,
                            temperature = 2.53e-8, ptable = True );

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = XsdirEntry.from_string( self.chunk )

        verify_chunk( self, chunk )

        # the data is given explicitly (with line splits)
        chunk = XsdirEntry( zaid = '92235.00c', awr = 235.,
                            filename = 'filenamethatiswaaaaaaaaaaaaaaaaaaaaaaaaaytoolong',
                            access = 'accessnamethatisevenwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaylonger',
                            address = 5, length = 1000,
                            temperature = 2.53e-8, ptable = True );

        verify_chunk_with_split( self, chunk )

        # the data is read from a string
        chunk = XsdirEntry.from_string( self.chunk_with_split )

        verify_chunk_with_split( self, chunk )

        # the data is given explicitly (7 entries)
        chunk = XsdirEntry( zaid = '92235.00c', awr = 235., filename = 'file',
                            address = 5, length = 1000 );

        verify_chunk_7_entries( self, chunk )

        # the data is read from a string
        chunk = XsdirEntry.from_string( self.chunk_7_entries )

        # the data is given explicitly (10 entries)
        chunk = XsdirEntry( zaid = '92235.00c', awr = 235., filename = 'file',
                            address = 5, length = 1000, temperature = 2.53e-8 );

        verify_chunk_10_entries( self, chunk )

        # the data is read from a string
        chunk = XsdirEntry.from_string( self.chunk_10_entries )

if __name__ == '__main__' :

    unittest.main()
