# standard imports
import unittest

# third party imports

# local imports
from ACEtk import Header201

class Test_ACEtk_Header201( unittest.TestCase ) :
    """Unit test for the Header class."""

    chunk = ( '2.0.1                   92238.800nc            ENDF/B-VIII.0\n'
              '  236.005800   2.5301E-08 2018-05-01          2\n'
              ' 92238.80c  236.005800  2.5301E-08   12/13/12\n'
              'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( '2.0.1', chunk.VERS )
            self.assertEqual( '2.0.1', chunk.version )
            self.assertEqual( '92238.800nc', chunk.zaid )
            self.assertEqual( 236.005800, chunk.AWR )
            self.assertEqual( 236.005800, chunk.atomic_weight_ratio )
            self.assertEqual( 2.5301E-08, chunk.TEMP )
            self.assertEqual( 2.5301E-08, chunk.temperature )
            self.assertEqual( '2018-05-01', chunk.date )
            self.assertEqual( ' 92238.80c  236.005800  2.5301E-08   12/13/12',
                              chunk.comments[0] )
            self.assertEqual( 'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237',
                              chunk.comments[1] )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string() )

        # the data is read from a string
        chunk = Header201( szaid = '92238.800nc', source = 'ENDF/B-VIII.0',
                           awr = 236.0058, temperature = 2.5301E-08,
                           date = '2018-05-01',
                           comments = [ ' 92238.80c  236.005800  2.5301E-08   12/13/12',
                                        'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237' ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
