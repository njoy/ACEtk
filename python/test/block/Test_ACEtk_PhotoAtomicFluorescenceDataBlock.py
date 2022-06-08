# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoAtomicFluorescenceDataBlock

class Test_ACEtk_PhotoAtomicFluorescenceDataBlock( unittest.TestCase ) :
    """Unit test for the PhotoAtomicFluorescenceDataBlock class."""

    chunk = [ 1.294500000000E-03,  1.294500000000E-03,  8.180862310960E-02,  1.000000000000E+00,
              0.000000000000E+00,  2.542671170140E-02,  0.000000000000E+00,  1.238156190380E-03 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 8, chunk.length )
            self.assertEqual( "JFLO", chunk.name )

            self.assertEqual( 8, len( chunk.xss_array ) )

            self.assertEqual( 2, chunk.NFLO )
            self.assertEqual( 2, chunk.number_fluorescence_edges )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.PHI ) )
            self.assertEqual( 2, len( chunk.Y ) )
            self.assertEqual( 2, len( chunk.F ) )
            self.assertEqual( 2, len( chunk.fluorescence_edge_energies ) )
            self.assertEqual( 2, len( chunk.relative_ejection_probabilities ) )
            self.assertEqual( 2, len( chunk.yields ) )
            self.assertEqual( 2, len( chunk.fluorescent_energies ) )

            self.assertAlmostEqual( 1.294500000000E-03, chunk.E[0] )
            self.assertAlmostEqual( 1.294500000000E-03, chunk.E[-1] )
            self.assertAlmostEqual( 8.180862310960E-02, chunk.PHI[0] )
            self.assertAlmostEqual( 1.000000000000E+00, chunk.PHI[-1] )
            self.assertAlmostEqual( 0.000000000000E+00, chunk.Y[0] )
            self.assertAlmostEqual( 2.542671170140E-02, chunk.Y[-1] )
            self.assertAlmostEqual( 0.000000000000E+00, chunk.F[0] )
            self.assertAlmostEqual( 1.238156190380E-03, chunk.F[-1] )
            self.assertAlmostEqual( 1.294500000000E-03, chunk.fluorescence_edge_energies[0] )
            self.assertAlmostEqual( 1.294500000000E-03, chunk.fluorescence_edge_energies[-1] )
            self.assertAlmostEqual( 8.180862310960E-02, chunk.relative_ejection_probabilities[0] )
            self.assertAlmostEqual( 1.000000000000E+00, chunk.relative_ejection_probabilities[-1] )
            self.assertAlmostEqual( 0.000000000000E+00, chunk.yields[0] )
            self.assertAlmostEqual( 2.542671170140E-02, chunk.yields[-1] )
            self.assertAlmostEqual( 0.000000000000E+00, chunk.fluorescent_energies[0] )
            self.assertAlmostEqual( 1.238156190380E-03, chunk.fluorescent_energies[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoAtomicFluorescenceDataBlock(
                  edges = [ 1.294500000000E-03,  1.294500000000E-03 ],
                  probabilities = [ 8.180862310960E-02,  1.000000000000E+00 ],
                  yields = [ 0.000000000000E+00,  2.542671170140E-02 ],
                  energies = [ 0.000000000000E+00,  1.238156190380E-03 ] )

        print( chunk.xss_array.to_list() )
        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
