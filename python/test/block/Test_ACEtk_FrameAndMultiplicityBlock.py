# standard imports
import unittest

# third party imports

# local imports
from ACEtk import FrameAndMultiplicityBlock
from ACEtk import ReferenceFrame

class Test_ACEtk_FrameAndMultiplicityBlock( unittest.TestCase ) :
    """Unit test for the FrameAndMultiplicityBlock class."""

    chunk = [ -2, 0, 0 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 3, chunk.length )
            self.assertEqual( "TYR", chunk.name )

            self.assertEqual( 3, chunk.NTR )
            self.assertEqual( 3, chunk.number_reactions )

            self.assertAlmostEqual( ReferenceFrame.CentreOfMass, chunk.reference_frame(1) )
            self.assertAlmostEqual( ReferenceFrame.Laboratory, chunk.reference_frame(2) )
            self.assertAlmostEqual( ReferenceFrame.Laboratory, chunk.reference_frame(3) )

            self.assertAlmostEqual( 2, chunk.multiplicity(1) )
            self.assertAlmostEqual( 0., chunk.multiplicity(2) )
            self.assertAlmostEqual( 0., chunk.multiplicity(3) )

            self.assertEqual( 3, len( chunk.reference_frames ) )
            self.assertAlmostEqual( ReferenceFrame.CentreOfMass, chunk.reference_frames[0] )
            self.assertAlmostEqual( ReferenceFrame.Laboratory, chunk.reference_frames[1] )
            self.assertAlmostEqual( ReferenceFrame.Laboratory, chunk.reference_frames[2] )

            self.assertEqual( 3, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 2, chunk.multiplicities[0] )
            self.assertAlmostEqual( 0, chunk.multiplicities[1] )
            self.assertAlmostEqual( 0, chunk.multiplicities[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = FrameAndMultiplicityBlock(
                    frames = [ ReferenceFrame.CentreOfMass,
                               ReferenceFrame.Laboratory,
                               ReferenceFrame.Laboratory ],
                   multiplicities = [ 2, 0, 0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
