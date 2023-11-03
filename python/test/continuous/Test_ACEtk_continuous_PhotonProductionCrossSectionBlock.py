# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import PhotonProductionCrossSectionBlock
from ACEtk.continuous import PhotonProductionCrossSectionData
from ACEtk.continuous import TabulatedSecondaryParticleMultiplicity

class Test_ACEtk_PhotonProductionCrossSectionBlock( unittest.TestCase ) :
    """Unit test for the PhotonProductionCrossSectionBlock class."""

    chunk = [                 1,               103,
                             13,                 1,
                             99, 1.71740100000E+01, 1.21438600000E+01, 7.68045500000E+00,
              5.43090500000E+00, 3.84022400000E+00, 2.42878300000E+00, 1.71741500000E+00,
              1.21440300000E+00, 7.68079300000E-01, 5.43155100000E-01, 3.84154600000E-01,
              3.41606100000E-01, 2.43218100000E-01, 1.72502100000E-01, 1.23265800000E-01,
              7.76319400000E-02, 5.42665800000E-02, 3.83593600000E-02, 2.41345500000E-02,
              1.69157900000E-02, 1.19330400000E-02, 7.52588100000E-03, 5.30147700000E-03,
              3.74241900000E-03, 2.35974500000E-03, 1.66085400000E-03, 1.16578800000E-03,
              8.12732500000E-04, 7.21302100000E-04, 6.54483800000E-04, 5.59372400000E-04,
              4.93876600000E-04, 3.90771200000E-04, 3.28387200000E-04, 2.08326100000E-04,
              1.81663500000E-04, 1.55085200000E-04, 1.24126000000E-04, 1.03786200000E-04,
              7.45175200000E-05, 5.92842800000E-05, 4.46076700000E-05, 3.82766600000E-05,
              3.52914400000E-05, 3.38996200000E-05, 3.33423900000E-05, 3.32443400000E-05,
              3.34022300000E-05, 3.36990500000E-05, 3.44554600000E-05, 3.52169900000E-05,
              3.58729500000E-05, 3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05,
              3.71598700000E-05, 3.72143000000E-05, 3.71976900000E-05, 3.71253600000E-05,
              3.70102000000E-05, 3.68628700000E-05, 3.66920200000E-05, 3.65045600000E-05,
              3.63059900000E-05, 3.61006300000E-05, 3.58918300000E-05, 3.56821800000E-05,
              3.54736400000E-05, 3.52677000000E-05, 3.47705000000E-05, 3.43050800000E-05,
              3.38741800000E-05, 3.34769900000E-05, 3.31108400000E-05, 3.27723300000E-05,
              3.24578800000E-05, 3.21640000000E-05, 3.18874900000E-05, 3.16254500000E-05,
              3.13753100000E-05, 3.11348500000E-05, 3.09021400000E-05, 3.06755200000E-05,
              3.04536000000E-05, 3.02351800000E-05, 3.00192800000E-05, 2.98050700000E-05,
              2.95919000000E-05, 2.93792000000E-05, 2.91665600000E-05, 2.89536300000E-05,
              2.87401800000E-05, 2.85260300000E-05, 2.83110700000E-05, 2.80952300000E-05,
              2.78785100000E-05, 2.76609500000E-05, 2.74425900000E-05, 2.72235400000E-05,
                             12,                 4,                 0,                 7,
              7.74238100000E-01, 8.00000000000E-01, 9.00000000000E-01, 1.00000000000E+00,
              1.09000000000E+00, 1.09000100000E+00, 2.00000000000E+01, 0.00000000000E+00,
              1.00000000000E-02, 7.11000000000E-02, 1.19000000000E-01, 1.23300000000E-01,
              0.00000000000E+00, 0.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 122, chunk.length )
            self.assertEqual( "SIGP", chunk.name )

            self.assertEqual( 2, chunk.NTRP )
            self.assertEqual( 2, chunk.number_photon_production_reactions )
            self.assertEqual( 2, len( chunk.data ) )

            self.assertEqual( 1, chunk.LSIG(1) )
            self.assertEqual( 103, chunk.LSIG(2) )
            self.assertEqual( 1, chunk.cross_section_locator(1) )
            self.assertEqual( 103, chunk.cross_section_locator(2) )

            self.assertEqual( True, isinstance( chunk.cross_section_data(1), PhotonProductionCrossSectionData ) )
            self.assertEqual( True, isinstance( chunk.cross_section_data(2), TabulatedSecondaryParticleMultiplicity ) )

            self.assertEqual( True, isinstance( chunk.data[0], PhotonProductionCrossSectionData ) )
            self.assertEqual( True, isinstance( chunk.data[1], TabulatedSecondaryParticleMultiplicity ) )

            xs = chunk.cross_section_data(1)
            self.assertEqual( 13, xs.MFTYPE )
            self.assertEqual( 13, xs.type )
            self.assertEqual( 1, xs.energy_index )
            self.assertEqual( 99, xs.number_values )
            self.assertEqual( 99, len( xs.cross_sections ) )
            self.assertAlmostEqual( 17.17401, xs.cross_sections[0] )
            self.assertAlmostEqual( 2.72235400000E-05, xs.cross_sections[-1] )

            xs = chunk.cross_section_data(2)
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

            xs = chunk.data[0]
            self.assertEqual( 13, xs.MFTYPE )
            self.assertEqual( 13, xs.type )
            self.assertEqual( 1, xs.energy_index )
            self.assertEqual( 99, xs.number_values )
            self.assertEqual( 99, len( xs.cross_sections ) )
            self.assertAlmostEqual( 17.17401, xs.cross_sections[0] )
            self.assertAlmostEqual( 2.72235400000E-05, xs.cross_sections[-1] )

            xs = chunk.data[1]
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

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotonProductionCrossSectionBlock(
                  xs = [ PhotonProductionCrossSectionData(
                           index = 1,
                           values = [                    1.71740100000E+01, 1.21438600000E+01, 7.68045500000E+00,
                                      5.43090500000E+00, 3.84022400000E+00, 2.42878300000E+00, 1.71741500000E+00,
                                      1.21440300000E+00, 7.68079300000E-01, 5.43155100000E-01, 3.84154600000E-01,
                                      3.41606100000E-01, 2.43218100000E-01, 1.72502100000E-01, 1.23265800000E-01,
                                      7.76319400000E-02, 5.42665800000E-02, 3.83593600000E-02, 2.41345500000E-02,
                                      1.69157900000E-02, 1.19330400000E-02, 7.52588100000E-03, 5.30147700000E-03,
                                      3.74241900000E-03, 2.35974500000E-03, 1.66085400000E-03, 1.16578800000E-03,
                                      8.12732500000E-04, 7.21302100000E-04, 6.54483800000E-04, 5.59372400000E-04,
                                      4.93876600000E-04, 3.90771200000E-04, 3.28387200000E-04, 2.08326100000E-04,
                                      1.81663500000E-04, 1.55085200000E-04, 1.24126000000E-04, 1.03786200000E-04,
                                      7.45175200000E-05, 5.92842800000E-05, 4.46076700000E-05, 3.82766600000E-05,
                                      3.52914400000E-05, 3.38996200000E-05, 3.33423900000E-05, 3.32443400000E-05,
                                      3.34022300000E-05, 3.36990500000E-05, 3.44554600000E-05, 3.52169900000E-05,
                                      3.58729500000E-05, 3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05,
                                      3.71598700000E-05, 3.72143000000E-05, 3.71976900000E-05, 3.71253600000E-05,
                                      3.70102000000E-05, 3.68628700000E-05, 3.66920200000E-05, 3.65045600000E-05,
                                      3.63059900000E-05, 3.61006300000E-05, 3.58918300000E-05, 3.56821800000E-05,
                                      3.54736400000E-05, 3.52677000000E-05, 3.47705000000E-05, 3.43050800000E-05,
                                      3.38741800000E-05, 3.34769900000E-05, 3.31108400000E-05, 3.27723300000E-05,
                                      3.24578800000E-05, 3.21640000000E-05, 3.18874900000E-05, 3.16254500000E-05,
                                      3.13753100000E-05, 3.11348500000E-05, 3.09021400000E-05, 3.06755200000E-05,
                                      3.04536000000E-05, 3.02351800000E-05, 3.00192800000E-05, 2.98050700000E-05,
                                      2.95919000000E-05, 2.93792000000E-05, 2.91665600000E-05, 2.89536300000E-05,
                                      2.87401800000E-05, 2.85260300000E-05, 2.83110700000E-05, 2.80952300000E-05,
                                      2.78785100000E-05, 2.76609500000E-05, 2.74425900000E-05, 2.72235400000E-05 ] ),
                         TabulatedSecondaryParticleMultiplicity(
                           mftype = 12, mt = 4,
                           energies = [ 7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,
                                        1.00000000000E+00,   1.09000000000E+00,   1.09000100000E+00,
                                        2.00000000000E+01 ],
                           multiplicities = [ 0.00000000000E+00,   1.00000000000E-02,   7.11000000000E-02,
                                              1.19000000000E-01,   1.23300000000E-01,   0.00000000000E+00,
                                              0.00000000000E+00 ] ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
