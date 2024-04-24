# standard imports
import unittest

# third party imports

# local imports
from ACEtk import Header

class Test_ACEtk_Header( unittest.TestCase ) :
    """Unit test for the Header class."""

    chunk = ( ' 92238.80c  236.005800  2.5301E-08   12/13/12\n'
              'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( '1.0.0', chunk.VERS )
            self.assertEqual( '1.0.0', chunk.version )
            self.assertEqual( '92238.80c', chunk.zaid )
            self.assertEqual( 236.005800, chunk.AWR )
            self.assertEqual( 236.005800, chunk.atomic_weight_ratio )
            self.assertEqual( 2.5301E-08, chunk.TEMP )
            self.assertEqual( 2.5301E-08, chunk.temperature )
            self.assertEqual( '12/13/12', chunk.date )
            self.assertEqual( 'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)',
                              chunk.title )
            self.assertEqual( 'mat9237', chunk.material )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string() )

        # the data is read from a string
        chunk = Header( zaid = '92238.80c', awr = 236.0058,
                        temperature = 2.5301E-08, date = '12/13/12',
                        title = 'U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)',
                        material = 'mat9237' )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
