# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import SecondaryParticleProductionCrossSectionBlock
from ACEtk.continuous import PhotonProductionCrossSectionData
from ACEtk.continuous import TabulatedSecondaryParticleMultiplicity

class Test_ACEtk_continuous_SecondaryParticleProductionCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the SecondaryParticleProductionCrossSectionBlock class."""

    chunk = [                 1,                19,
                             12,                 4,                 0,                 7,
              7.74238100000E-01, 8.00000000000E-01, 9.00000000000E-01, 1.00000000000E+00,
              1.09000000000E+00, 1.09000100000E+00, 2.00000000000E+01, 0.00000000000E+00,
              1.00000000000E-02, 7.11000000000E-02, 1.19000000000E-01, 1.23300000000E-01,
              0.00000000000E+00, 0.00000000000E+00,
                             12,               102,                 0,                 2,
              1.00000000000E-05, 2.00000000000E+01, 1.00000000000E+00, 1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 28, chunk.length )
            self.assertEqual( "SIGH", chunk.name )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 2, chunk.number_secondary_particle_production_reactions )
            self.assertEqual( 2, len( chunk.data ) )

            self.assertEqual( 1, chunk.LSIG(1) )
            self.assertEqual( 19, chunk.LSIG(2) )
            self.assertEqual( 1, chunk.cross_section_locator(1) )
            self.assertEqual( 19, chunk.cross_section_locator(2) )

            self.assertEqual( True, isinstance( chunk.data[0], TabulatedSecondaryParticleMultiplicity ) )
            self.assertEqual( True, isinstance( chunk.data[1], TabulatedSecondaryParticleMultiplicity ) )

            xs = chunk.cross_section_data(1)
            self.assertEqual( 12, xs.MFTYPE )
            self.assertEqual( 12, xs.type )
            self.assertEqual( 4, xs.MT )
            self.assertEqual( 4, xs.reaction_number )
            self.assertEqual( 0, xs.interpolation_data.NB )
            self.assertEqual( 0, xs.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( xs.interpolation_data.INT ) )
            self.assertEqual( 0, len( xs.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( xs.interpolation_data.NBT ) )
            self.assertEqual( 0, len( xs.interpolation_data.boundaries ) )
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 0, xs.number_interpolation_regions )
            self.assertEqual( 0, len( xs.INT ) )
            self.assertEqual( 0, len( xs.interpolants ) )
            self.assertEqual( 0, len( xs.NBT ) )
            self.assertEqual( 0, len( xs.boundaries ) )
            self.assertEqual( 7, xs.NE )
            self.assertEqual( 7, xs.number_values )
            self.assertEqual( 7, len( xs.energies ) )
            self.assertAlmostEqual( 0.7742381, xs.energies[0] )
            self.assertAlmostEqual( 1., xs.energies[3] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertEqual( 7, len( xs.multiplicities ) )
            self.assertAlmostEqual( 0., xs.multiplicities[0] )
            self.assertAlmostEqual( 0.119, xs.multiplicities[3] )
            self.assertAlmostEqual( 0., xs.multiplicities[-1] )

            xs = chunk.cross_section_data(2)
            self.assertEqual( 12, xs.MFTYPE )
            self.assertEqual( 12, xs.type )
            self.assertEqual( 102, xs.MT )
            self.assertEqual( 102, xs.reaction_number )
            self.assertEqual( 0, xs.interpolation_data.NB )
            self.assertEqual( 0, xs.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( xs.interpolation_data.INT ) )
            self.assertEqual( 0, len( xs.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( xs.interpolation_data.NBT ) )
            self.assertEqual( 0, len( xs.interpolation_data.boundaries ) )
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 0, xs.number_interpolation_regions )
            self.assertEqual( 0, len( xs.INT ) )
            self.assertEqual( 0, len( xs.interpolants ) )
            self.assertEqual( 0, len( xs.NBT ) )
            self.assertEqual( 0, len( xs.boundaries ) )
            self.assertEqual( 2, xs.NE )
            self.assertEqual( 2, xs.number_values )
            self.assertEqual( 2, len( xs.energies ) )
            self.assertAlmostEqual( 1e-5, xs.energies[0] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertEqual( 2, len( xs.multiplicities ) )
            self.assertAlmostEqual( 1., xs.multiplicities[0] )
            self.assertAlmostEqual( 1., xs.multiplicities[-1] )

            xs = chunk.data[0]
            self.assertEqual( 12, xs.MFTYPE )
            self.assertEqual( 12, xs.type )
            self.assertEqual( 4, xs.MT )
            self.assertEqual( 4, xs.reaction_number )
            self.assertEqual( 0, xs.interpolation_data.NB )
            self.assertEqual( 0, xs.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( xs.interpolation_data.INT ) )
            self.assertEqual( 0, len( xs.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( xs.interpolation_data.NBT ) )
            self.assertEqual( 0, len( xs.interpolation_data.boundaries ) )
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 0, xs.number_interpolation_regions )
            self.assertEqual( 0, len( xs.INT ) )
            self.assertEqual( 0, len( xs.interpolants ) )
            self.assertEqual( 0, len( xs.NBT ) )
            self.assertEqual( 0, len( xs.boundaries ) )
            self.assertEqual( 7, xs.NE )
            self.assertEqual( 7, xs.number_values )
            self.assertEqual( 7, len( xs.energies ) )
            self.assertAlmostEqual( 0.7742381, xs.energies[0] )
            self.assertAlmostEqual( 1., xs.energies[3] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertEqual( 7, len( xs.multiplicities ) )
            self.assertAlmostEqual( 0., xs.multiplicities[0] )
            self.assertAlmostEqual( 0.119, xs.multiplicities[3] )
            self.assertAlmostEqual( 0., xs.multiplicities[-1] )

            xs = chunk.data[1]
            self.assertEqual( 12, xs.MFTYPE )
            self.assertEqual( 12, xs.type )
            self.assertEqual( 102, xs.MT )
            self.assertEqual( 102, xs.reaction_number )
            self.assertEqual( 0, xs.interpolation_data.NB )
            self.assertEqual( 0, xs.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( xs.interpolation_data.INT ) )
            self.assertEqual( 0, len( xs.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( xs.interpolation_data.NBT ) )
            self.assertEqual( 0, len( xs.interpolation_data.boundaries ) )
            self.assertEqual( 0, xs.NB )
            self.assertEqual( 0, xs.number_interpolation_regions )
            self.assertEqual( 0, len( xs.INT ) )
            self.assertEqual( 0, len( xs.interpolants ) )
            self.assertEqual( 0, len( xs.NBT ) )
            self.assertEqual( 0, len( xs.boundaries ) )
            self.assertEqual( 2, xs.NE )
            self.assertEqual( 2, xs.number_values )
            self.assertEqual( 2, len( xs.energies ) )
            self.assertAlmostEqual( 1e-5, xs.energies[0] )
            self.assertAlmostEqual( 20., xs.energies[-1] )
            self.assertEqual( 2, len( xs.multiplicities ) )
            self.assertAlmostEqual( 1., xs.multiplicities[0] )
            self.assertAlmostEqual( 1., xs.multiplicities[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = SecondaryParticleProductionCrossSectionBlock(
                  xs = [ TabulatedSecondaryParticleMultiplicity(
                           mftype = 12, mt = 4,
                           energies = [ 7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,
                                        1.00000000000E+00,   1.09000000000E+00,   1.09000100000E+00,
                                        2.00000000000E+01 ],
                           multiplicities = [ 0.00000000000E+00,   1.00000000000E-02,   7.11000000000E-02,
                                              1.19000000000E-01,   1.23300000000E-01,   0.00000000000E+00,
                                              0.00000000000E+00 ] ),
                         TabulatedSecondaryParticleMultiplicity(
                           mftype = 12, mt = 102,
                           energies = [ 1.00000000000E-05, 2.00000000000E+01 ],
                           multiplicities = [ 1., 1. ] ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
