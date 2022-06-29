# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotonuclearSecondaryParticleLocatorBlock

class Test_ACEtk_PhotonuclearSecondaryParticleLocatorBlock( unittest.TestCase ) :
    """Unit test for the PhotonuclearSecondaryParticleLocatorBlock class."""

    chunk = [                                                    1,                   2,
                     543,                 635,                 727,                 729,
                     731,                 733,                1085,                1087,
                    1087,                1089,                   2,                   1,
                  198198,              198290,              198382,              198383,
                  198384,              198385,              198569,              198570,
                  198570,              198571,                   9,                   1,
                  282208,              282288,              282368,              282369,
                  282370,              282371,              282543,              282544,
                  282544,              282545,                  31,                   1,
                  428550,              428623,              428696,              428697,
                  428698,              428699,              428869,              428870,
                  428870,              428871,                  32,                   1,
                  575293,              575364,              575435,              575436,
                  575437,              575438,              575604,              575605,
                  575605,              575606,                  33,                   1,
                  719700,              719769,              719838,              719839,
                  719840,              719841,              720009,              720010,
                  720010,              720011,                  34,                   1,
                  863286,              863378,              863470,              863471,
                  863472,              863473,              863657,              863658,
                  863658,              863659 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 84, chunk.length )
            self.assertEqual( "IXSU", chunk.name )

            self.assertEqual( 7, chunk.NTYPE )
            self.assertEqual( 7, chunk.number_additional_secondary_particle_types )

            self.assertEqual( 1, chunk.IP( 1 ) )
            self.assertEqual( 2, chunk.IP( 2 ) )
            self.assertEqual( 9, chunk.IP( 3 ) )
            self.assertEqual( 31, chunk.IP( 4 ) )
            self.assertEqual( 32, chunk.IP( 5 ) )
            self.assertEqual( 33, chunk.IP( 6 ) )
            self.assertEqual( 34, chunk.IP( 7 ) )

            self.assertEqual( 2, chunk.NP( 1 ) )
            self.assertEqual( 1, chunk.NP( 2 ) )
            self.assertEqual( 1, chunk.NP( 3 ) )
            self.assertEqual( 1, chunk.NP( 4 ) )
            self.assertEqual( 1, chunk.NP( 5 ) )
            self.assertEqual( 1, chunk.NP( 6 ) )
            self.assertEqual( 1, chunk.NP( 7 ) )

            self.assertEqual( 543, chunk.PXS( 1 ) )
            self.assertEqual( 635, chunk.PHN( 1 ) )
            self.assertEqual( 727, chunk.MTRH( 1 ) )
            self.assertEqual( 729, chunk.TYRH( 1 ) )
            self.assertEqual( 731, chunk.LSIGH( 1 ) )
            self.assertEqual( 733, chunk.SIGH( 1 ) )
            self.assertEqual( 1085, chunk.LANDH( 1 ) )
            self.assertEqual( 1087, chunk.ANDH( 1 ) )
            self.assertEqual( 1087, chunk.LDLWH( 1 ) )
            self.assertEqual( 1089, chunk.DLWH( 1 ) )

            self.assertEqual( 863286, chunk.PXS( 7 ) )
            self.assertEqual( 863378, chunk.PHN( 7 ) )
            self.assertEqual( 863470, chunk.MTRH( 7 ) )
            self.assertEqual( 863471, chunk.TYRH( 7 ) )
            self.assertEqual( 863472, chunk.LSIGH( 7 ) )
            self.assertEqual( 863473, chunk.SIGH( 7 ) )
            self.assertEqual( 863657, chunk.LANDH( 7 ) )
            self.assertEqual( 863658, chunk.ANDH( 7 ) )
            self.assertEqual( 863658, chunk.LDLWH( 7 ) )
            self.assertEqual( 863659, chunk.DLWH( 7 ) )

            with self.assertRaises( Exception ) :

                index = chunk.index(1)

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotonuclearSecondaryParticleLocatorBlock(
                  types = [ 1, 2, 9, 31, 32, 33, 34 ],
                  numbers = [ 2, 1, 1, 1, 1, 1, 1 ],
                  locators = [ [ 543,                 635,                 727,                 729,
                                 731,                 733,                1085,                1087,
                                 1087,                1089 ],
                               [ 198198,              198290,              198382,              198383,
                                 198384,              198385,              198569,              198570,
                                 198570,              198571 ],
                               [ 282208,              282288,              282368,              282369,
                                 282370,              282371,              282543,              282544,
                                 282544,              282545 ],
                               [ 428550,              428623,              428696,              428697,
                                 428698,              428699,              428869,              428870,
                                 428870,              428871 ],
                               [ 575293,              575364,              575435,              575436,
                                 575437,              575438,              575604,              575605,
                                 575605,              575606 ],
                               [ 719700,              719769,              719838,              719839,
                                 719840,              719841,              720009,              720010,
                                 720010,              720011 ],
                               [ 863286,              863378,              863470,              863471,
                                 863472,              863473,              863657,              863658,
                                 863658,              863659 ] ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
