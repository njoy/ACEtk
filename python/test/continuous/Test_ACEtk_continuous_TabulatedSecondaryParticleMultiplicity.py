# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import TabulatedSecondaryParticleMultiplicity

class Test_ACEtk_TabulatedSecondaryParticleMultiplicity( unittest.TestCase ) :
    """Unit test for the TabulatedSecondaryParticleMultiplicity class."""

    chunk = [                 12,                   4,                   0,                   7,
               7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,   1.00000000000E+00,
               1.09000000000E+00,   1.09000100000E+00,   2.00000000000E+01,   0.00000000000E+00,
               1.00000000000E-02,   7.11000000000E-02,   1.19000000000E-01,   1.23300000000E-01,
               0.00000000000E+00,   0.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 18, chunk.length )
            self.assertEqual( "TabulatedSecondaryParticleMultiplicity", chunk.name )

            self.assertEqual( 12, chunk.MFTYPE )
            self.assertEqual( 12, chunk.type )
            self.assertEqual( 4, chunk.MT )
            self.assertEqual( 4, chunk.reaction_number )

            self.assertEqual( 0, chunk.interpolation_data.NB )
            self.assertEqual( 0, chunk.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.interpolation_data.INT ) )
            self.assertEqual( 0, len( chunk.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( chunk.interpolation_data.NBT ) )
            self.assertEqual( 0, len( chunk.interpolation_data.boundaries ) )

            self.assertEqual( 0, chunk.NB )
            self.assertEqual( 0, chunk.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.INT ) )
            self.assertEqual( 0, len( chunk.interpolants ) )
            self.assertEqual( 0, len( chunk.NBT ) )
            self.assertEqual( 0, len( chunk.boundaries ) )

            self.assertEqual( 7, chunk.NE )
            self.assertEqual( 7, chunk.number_values )

            self.assertEqual( 7, len( chunk.energies ) )
            self.assertAlmostEqual( 0.7742381, chunk.energies[0] )
            self.assertAlmostEqual( 1., chunk.energies[3] )
            self.assertAlmostEqual( 20., chunk.energies[-1] )

            self.assertEqual( 7, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 0., chunk.multiplicities[0] )
            self.assertAlmostEqual( 0.119, chunk.multiplicities[3] )
            self.assertAlmostEqual( 0., chunk.multiplicities[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = TabulatedSecondaryParticleMultiplicity(
                  mftype = 12, mt = 4,
                  energies = [ 7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,
                               1.00000000000E+00,   1.09000000000E+00,   1.09000100000E+00,
                               2.00000000000E+01 ],
                  multiplicities = [ 0.00000000000E+00,   1.00000000000E-02,   7.11000000000E-02,
                                     1.19000000000E-01,   1.23300000000E-01,   0.00000000000E+00,
                                     0.00000000000E+00 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
