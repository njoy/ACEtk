# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import TabulatedEnergyDistribution

class Test_ACEtk_TabulatedEnergyDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedEnergyDistribution class."""

    chunk = [                32,                  3,  1.00000000000E-11,  1.00000000000E+00,
              2.00000000000E+01,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
              0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 11, chunk.length )
            self.assertEqual( "TabulatedEnergyDistribution", chunk.name )

            self.assertEqual( 2.1, chunk.energy_or_cosine )
            self.assertEqual( 2, chunk.interpolation )
            self.assertEqual( 3, chunk.number_discrete_photon_lines )
            self.assertEqual( 3, chunk.number_outgoing_energies )

            self.assertEqual( 3, len( chunk.outgoing_energies ) )
            self.assertAlmostEqual( 1e-11, chunk.outgoing_energies[0] )
            self.assertAlmostEqual( 20., chunk.outgoing_energies[-1] )

            self.assertEqual( 3, len( chunk.pdf ) )
            self.assertAlmostEqual( .5, chunk.pdf[0] )
            self.assertAlmostEqual( .5, chunk.pdf[-1] )

            self.assertEqual( 3, len( chunk.cdf ) )
            self.assertAlmostEqual( 0., chunk.cdf[0] )
            self.assertAlmostEqual( 1., chunk.cdf[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = TabulatedEnergyDistribution(
                    value = 2.1,
                    interpolation = 2,
                    cosines = [ 1e-11, 1., 20. ],
                    pdf = [ 0.5, 0.5, 0.5 ],
                    cdf = [ 0.0, 0.5, 1.0 ],
                    discrete = 3 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
