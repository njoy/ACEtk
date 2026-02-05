# standard imports
import unittest

# third party imports

# local imports
from ACEtk.multigroup import MomentumTransferBlock

class Test_ACEtk_multigroup_MomentumTransferBlock( unittest.TestCase ) :
    """Unit test for the MomentumTransferBlock class."""

    chunk = [   3.227570000000E-05,  7.312440000000E-05,  2.343740000000E-04,  1.240120000000E-03,
                6.713940000000E-03,  2.068860000000E-02,  1.217780000000E-01,  1.038050000000E-01,
                1.194360000000E-01,  1.214190000000E-01,  1.115690000000E-01,  1.706130000000E-01,
                1.047060000000E-01,  5.813530000000E-02,  3.017230000000E-02,  2.257480000000E-02,
                5.273470000000E-03,  1.190540000000E-03,  2.672500000000E-04,  5.953610000000E-05,
                1.335350000000E-05,  2.976410000000E-06,  6.642330000000E-07,  1.480150000000E-07,
                3.305130000000E-08,  7.385720000000E-09,  1.644490000000E-09,  3.702850000000E-10,
                8.187100000000E-11,  2.337520000000E-11]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 30, chunk.length )
            self.assertEqual( "MOM", chunk.name )

            self.assertEqual( 30, len( chunk.xss_array ) )

            self.assertEqual( 30, len( chunk.momentum_transfer ) )

            self.assertAlmostEqual( 3.227570000000E-05, chunk.momentum_transfer[0] )
            self.assertAlmostEqual( 2.337520000000E-11, chunk.momentum_transfer[-1] )
            self.assertAlmostEqual( 3.227570000000E-05, chunk.MOMTR[0] )
            self.assertAlmostEqual( 2.337520000000E-11, chunk.MOMTR[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = MomentumTransferBlock(
          momentum_transfer =  [3.227570000000E-05,  7.312440000000E-05,  2.343740000000E-04,  1.240120000000E-03,
                                6.713940000000E-03,  2.068860000000E-02,  1.217780000000E-01,  1.038050000000E-01,
                                1.194360000000E-01,  1.214190000000E-01,  1.115690000000E-01,  1.706130000000E-01,
                                1.047060000000E-01,  5.813530000000E-02,  3.017230000000E-02,  2.257480000000E-02,
                                5.273470000000E-03,  1.190540000000E-03,  2.672500000000E-04,  5.953610000000E-05,
                                1.335350000000E-05,  2.976410000000E-06,  6.642330000000E-07,  1.480150000000E-07,
                                3.305130000000E-08,  7.385720000000E-09,  1.644490000000E-09,  3.702850000000E-10,
                                8.187100000000E-11,  2.337520000000E-11] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
