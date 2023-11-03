# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import SecondaryParticleProductionBlock

class Test_ACEtk_continuous_SecondaryParticleProductionBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleProductionBlock class."""

    chunk = [                 1,
                              3, 1.71740100000E+01, 1.21438600000E+01, 2.72235400000E+02,
              3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 8, chunk.length )
            self.assertEqual( "HPD", chunk.name )

            self.assertEqual( 1, chunk.energy_index )
            self.assertEqual( 3, chunk.number_values )

            self.assertEqual( 3, len( chunk.total_production ) )
            self.assertAlmostEqual( 17.17401, chunk.total_production[0] )
            self.assertAlmostEqual( 272.2354, chunk.total_production[-1] )

            self.assertEqual( 3, len( chunk.heating ) )
            self.assertAlmostEqual( 3.63894900000E-05, chunk.heating[0] )
            self.assertAlmostEqual( 3.70168600000E-05, chunk.heating[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleProductionBlock(
                    index = 1,
                    production = [ 1.71740100000E+01, 1.21438600000E+01, 2.72235400000E+02 ],
                    heating = [ 3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
