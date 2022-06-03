# standard imports
import unittest

# third party imports

# local imports
from ACEtk import IncoherentScatteringFunctionBlock

class Test_ACEtk_IncoherentScatteringFunctionBlock( unittest.TestCase ) :
    """Unit test for the IncoherentScatteringFunctionBlock class."""

    chunk = [                                                                                  0,
               1.104680000000E-03,  4.409660000000E-03,  1.033110000000E-01,  3.425650000000E-01,
               5.887310000000E-01,  7.688390000000E-01,  9.368610000000E-01,  9.829840000000E-01,
               9.950160000000E-01,  9.983740000000E-01,  9.994100000000E-01,  9.997650000000E-01,
               9.998980000000E-01,  9.999530000000E-01,  9.999980000000E-01,                   1,
                                1,                   1,                   1,                   1 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 21, chunk.length )
            self.assertEqual( "JINC", chunk.name )

            self.assertEqual( 21, chunk.NM )
            self.assertEqual( 21, chunk.number_values )

            self.assertEqual( 21, len( chunk.momentum ) )
            self.assertAlmostEqual( 0.  , chunk.momentum[0] )
            self.assertAlmostEqual( .005, chunk.momentum[1] )
            self.assertAlmostEqual( .01 , chunk.momentum[2] )
            self.assertAlmostEqual( .05 , chunk.momentum[3] )
            self.assertAlmostEqual( .1  , chunk.momentum[4] )
            self.assertAlmostEqual( .15 , chunk.momentum[5] )
            self.assertAlmostEqual( .2  , chunk.momentum[6] )
            self.assertAlmostEqual( .3  , chunk.momentum[7] )
            self.assertAlmostEqual( .4  , chunk.momentum[8] )
            self.assertAlmostEqual( .5  , chunk.momentum[9] )
            self.assertAlmostEqual( .6  , chunk.momentum[10] )
            self.assertAlmostEqual( .7  , chunk.momentum[11] )
            self.assertAlmostEqual( .8  , chunk.momentum[12] )
            self.assertAlmostEqual( .9  , chunk.momentum[13] )
            self.assertAlmostEqual( 1.  , chunk.momentum[14] )
            self.assertAlmostEqual( 1.5 , chunk.momentum[15] )
            self.assertAlmostEqual( 2.  , chunk.momentum[16] )
            self.assertAlmostEqual( 3.  , chunk.momentum[17] )
            self.assertAlmostEqual( 4.  , chunk.momentum[18] )
            self.assertAlmostEqual( 5.  , chunk.momentum[19] )
            self.assertAlmostEqual( 8.  , chunk.momentum[20] )

            self.assertEqual( 21, len( chunk.values ) )
            self.assertAlmostEqual( 0, chunk.values[0] )
            self.assertAlmostEqual( 1.104680000000E-03, chunk.values[1] )
            self.assertAlmostEqual( 4.409660000000E-03, chunk.values[2] )
            self.assertAlmostEqual( 1.033110000000E-01, chunk.values[3] )
            self.assertAlmostEqual( 3.425650000000E-01, chunk.values[4] )
            self.assertAlmostEqual( 5.887310000000E-01, chunk.values[5] )
            self.assertAlmostEqual( 7.688390000000E-01, chunk.values[6] )
            self.assertAlmostEqual( 9.368610000000E-01, chunk.values[7] )
            self.assertAlmostEqual( 9.829840000000E-01, chunk.values[8] )
            self.assertAlmostEqual( 9.950160000000E-01, chunk.values[9] )
            self.assertAlmostEqual( 9.983740000000E-01, chunk.values[10] )
            self.assertAlmostEqual( 9.994100000000E-01, chunk.values[11] )
            self.assertAlmostEqual( 9.997650000000E-01, chunk.values[12] )
            self.assertAlmostEqual( 9.998980000000E-01, chunk.values[13] )
            self.assertAlmostEqual( 9.999530000000E-01, chunk.values[14] )
            self.assertAlmostEqual( 9.999980000000E-01, chunk.values[15] )
            self.assertAlmostEqual( 1, chunk.values[16] )
            self.assertAlmostEqual( 1, chunk.values[17] )
            self.assertAlmostEqual( 1, chunk.values[18] )
            self.assertAlmostEqual( 1, chunk.values[19] )
            self.assertAlmostEqual( 1, chunk.values[20] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = IncoherentScatteringFunctionBlock(
                  values = [                                                                                 0,
                             1.104680000000E-03,  4.409660000000E-03,  1.033110000000E-01,  3.425650000000E-01,
                             5.887310000000E-01,  7.688390000000E-01,  9.368610000000E-01,  9.829840000000E-01,
                             9.950160000000E-01,  9.983740000000E-01,  9.994100000000E-01,  9.997650000000E-01,
                             9.998980000000E-01,  9.999530000000E-01,  9.999980000000E-01,                   1,
                                              1,                   1,                   1,                   1 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
