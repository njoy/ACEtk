# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import FissionMultiplicityBlock
from ACEtk.continuous import TabulatedFissionMultiplicity
from ACEtk.continuous import PolynomialFissionMultiplicity

class Test_ACEtk_continuous_FissionMultiplicityBlock( unittest.TestCase ) :
    """Unit test for the FissionMultiplicityBlock class."""

    chunk = [ 2, 0, 3, 1e-11, 1., 20., 2.5, 2.65, 3.5 ]
    chunk_with_prompt_and_total = [ -9, 2, 0, 3, 1e-11, 1., 20., 2.5, 2.65, 3.5,
                                    1, 2, 2.35, 1e-3 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 9, chunk.length )
            self.assertEqual( "NU", chunk.name )

            self.assertEqual( False, chunk.has_prompt_and_total_fission_multiplicity )

            multiplicity = chunk.multiplicity
            self.assertEqual( 2, multiplicity.LNU )
            self.assertEqual( 2, multiplicity.type )

            self.assertEqual( 0, multiplicity.interpolation_data.NB )
            self.assertEqual( 0, multiplicity.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( multiplicity.interpolation_data.INT ) )
            self.assertEqual( 0, len( multiplicity.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( multiplicity.interpolation_data.NBT ) )
            self.assertEqual( 0, len( multiplicity.interpolation_data.boundaries ) )

            self.assertEqual( 0, multiplicity.NB )
            self.assertEqual( 0, multiplicity.number_interpolation_regions )
            self.assertEqual( 0, len( multiplicity.INT ) )
            self.assertEqual( 0, len( multiplicity.interpolants ) )
            self.assertEqual( 0, len( multiplicity.NBT ) )
            self.assertEqual( 0, len( multiplicity.boundaries ) )

            self.assertEqual( 3, multiplicity.NE )
            self.assertEqual( 3, multiplicity.number_values )

            self.assertEqual( 3, len( multiplicity.energies ) )
            self.assertAlmostEqual( 1e-11, multiplicity.energies[0] )
            self.assertAlmostEqual( 1., multiplicity.energies[1] )
            self.assertAlmostEqual( 20., multiplicity.energies[2] )

            self.assertEqual( 3, len( multiplicity.multiplicities ) )
            self.assertAlmostEqual( 2.5, multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 2.65, multiplicity.multiplicities[1] )
            self.assertAlmostEqual( 3.5, multiplicity.multiplicities[2] )

            self.assertEqual( None, chunk.total_fission_multiplicity )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        def verify_chunk_with_prompt_and_total( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 14, chunk.length )
            self.assertEqual( "NU", chunk.name )

            self.assertEqual( True, chunk.has_prompt_and_total_fission_multiplicity )

            multiplicity = chunk.multiplicity
            self.assertEqual( 2, multiplicity.LNU )
            self.assertEqual( 2, multiplicity.type )

            self.assertEqual( 0, multiplicity.interpolation_data.NB )
            self.assertEqual( 0, multiplicity.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( multiplicity.interpolation_data.INT ) )
            self.assertEqual( 0, len( multiplicity.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( multiplicity.interpolation_data.NBT ) )
            self.assertEqual( 0, len( multiplicity.interpolation_data.boundaries ) )

            self.assertEqual( 0, multiplicity.NB )
            self.assertEqual( 0, multiplicity.number_interpolation_regions )
            self.assertEqual( 0, len( multiplicity.INT ) )
            self.assertEqual( 0, len( multiplicity.interpolants ) )
            self.assertEqual( 0, len( multiplicity.NBT ) )
            self.assertEqual( 0, len( multiplicity.boundaries ) )

            self.assertEqual( 3, multiplicity.NE )
            self.assertEqual( 3, multiplicity.number_values )

            self.assertEqual( 3, len( multiplicity.energies ) )
            self.assertAlmostEqual( 1e-11, multiplicity.energies[0] )
            self.assertAlmostEqual( 1., multiplicity.energies[1] )
            self.assertAlmostEqual( 20., multiplicity.energies[2] )

            self.assertEqual( 3, len( multiplicity.multiplicities ) )
            self.assertAlmostEqual( 2.5, multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 2.65, multiplicity.multiplicities[1] )
            self.assertAlmostEqual( 3.5, multiplicity.multiplicities[2] )

            total = chunk.total_fission_multiplicity
            self.assertEqual( 1, total.LNU )
            self.assertEqual( 1, total.type )

            self.assertEqual( 2, total.NC )
            self.assertEqual( 2, total.number_coefficients )

            self.assertEqual( 2, len( total.coefficients ) )
            self.assertAlmostEqual( 2.35, total.coefficients[0] )
            self.assertAlmostEqual( 1e-3, total.coefficients[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk_with_prompt_and_total[index], xss[index] )

        # the data is given explicitly for a TYR block
        chunk = FissionMultiplicityBlock(
                    prompt = TabulatedFissionMultiplicity(
                               [ 1e-11, 1., 20. ], [ 2.5, 2.65, 3.5 ] ) )

        verify_chunk( self, chunk )

        # the data is given explicitly for a TYRH block
        chunk = FissionMultiplicityBlock(
                    prompt = TabulatedFissionMultiplicity(
                               [ 1e-11, 1., 20. ], [ 2.5, 2.65, 3.5 ] ),
                    total = PolynomialFissionMultiplicity( [ 2.35, 1e-3 ] ) )

        verify_chunk_with_prompt_and_total( self, chunk )

if __name__ == '__main__' :

    unittest.main()
