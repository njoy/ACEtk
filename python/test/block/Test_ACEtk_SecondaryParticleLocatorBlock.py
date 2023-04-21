# standard imports
import unittest

# third party imports

# local imports
from ACEtk import SecondaryParticleLocatorBlock

class Test_ACEtk_SecondaryParticleLocatorBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleLocatorBlock class."""

    chunk = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              101, 102, 103, 104, 105, 106, 107, 108, 109, 110 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 20, chunk.length )
            self.assertEqual( "IXS", chunk.name )

            self.assertEqual( 2, chunk.NTYPE )
            self.assertEqual( 2, chunk.number_additional_secondary_particle_types )

            self.assertEqual( 1, chunk.LLOC(1,1) )
            self.assertEqual( 2, chunk.LLOC(1,2) )
            self.assertEqual( 3, chunk.LLOC(1,3) )
            self.assertEqual( 4, chunk.LLOC(1,4) )
            self.assertEqual( 5, chunk.LLOC(1,5) )
            self.assertEqual( 6, chunk.LLOC(1,6) )
            self.assertEqual( 7, chunk.LLOC(1,7) )
            self.assertEqual( 8, chunk.LLOC(1,8) )
            self.assertEqual( 9, chunk.LLOC(1,9) )
            self.assertEqual( 10, chunk.LLOC(1,10) )
            self.assertEqual( 101, chunk.LLOC(2,1) )
            self.assertEqual( 102, chunk.LLOC(2,2) )
            self.assertEqual( 103, chunk.LLOC(2,3) )
            self.assertEqual( 104, chunk.LLOC(2,4) )
            self.assertEqual( 105, chunk.LLOC(2,5) )
            self.assertEqual( 106, chunk.LLOC(2,6) )
            self.assertEqual( 107, chunk.LLOC(2,7) )
            self.assertEqual( 108, chunk.LLOC(2,8) )
            self.assertEqual( 109, chunk.LLOC(2,9) )
            self.assertEqual( 110, chunk.LLOC(2,10) )

            self.assertEqual( 1, chunk.HPD(1) )
            self.assertEqual( 2, chunk.MTRH(1) )
            self.assertEqual( 3, chunk.TYRH(1) )
            self.assertEqual( 4, chunk.LSIGH(1) )
            self.assertEqual( 5, chunk.SIGH(1) )
            self.assertEqual( 6, chunk.LANDH(1) )
            self.assertEqual( 7, chunk.ANDH(1) )
            self.assertEqual( 8, chunk.LDLWH(1) )
            self.assertEqual( 9, chunk.DLWH(1) )
            self.assertEqual( 10, chunk.YP(1) )
            self.assertEqual( 101, chunk.HPD(2) )
            self.assertEqual( 102, chunk.MTRH(2) )
            self.assertEqual( 103, chunk.TYRH(2) )
            self.assertEqual( 104, chunk.LSIGH(2) )
            self.assertEqual( 105, chunk.SIGH(2) )
            self.assertEqual( 106, chunk.LANDH(2) )
            self.assertEqual( 107, chunk.ANDH(2) )
            self.assertEqual( 108, chunk.LDLWH(2) )
            self.assertEqual( 109, chunk.DLWH(2) )
            self.assertEqual( 110, chunk.YP(2) )

            with self.assertRaises( Exception ) :

                index = chunk.index(1)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleLocatorBlock(
                  locators = [ [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ],
                               [ 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 ] ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
