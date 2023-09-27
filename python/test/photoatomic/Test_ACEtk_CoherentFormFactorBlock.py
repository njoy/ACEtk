# standard imports
import unittest

# third party imports

# local imports
from ACEtk import CoherentFormFactorBlock

class Test_ACEtk_CoherentFormFactorBlock( unittest.TestCase ) :
    """Unit test for the CoherentFormFactorBlock class."""

    chunk = [                  0,  9.977954354245E-05,  3.964942506035E-04,  8.824146336660E-04,
              1.545120632092E-03,  2.368152245929E-03,  3.328001096461E-03,  5.572765511802E-03,
              8.114989702569E-03,  1.077179717732E-02,  1.466576582467E-02,  1.814944661202E-02,
              2.013937477439E-02,  2.411608451487E-02,  2.666620748348E-02,  2.820041294244E-02,
              2.910584927642E-02,  2.965656338431E-02,  2.998629154717E-02,  3.018996625751E-02,
              3.031651130261E-02,  3.046055891684E-02,  3.052243640030E-02,  3.055108560889E-02,
              3.056526027755E-02,  3.057267572340E-02,  3.057674989952E-02,  3.057910122834E-02,
              3.058050894259E-02,  3.058138029848E-02,  3.058193578069E-02,  3.058229824481E-02,
              3.058254088417E-02,  3.058270703249E-02,  3.058282312688E-02,  3.058297109240E-02,
              3.058304939092E-02,  3.058309313441E-02,  3.058311867888E-02,  3.058313417771E-02,
              3.058314390105E-02,  3.058315017819E-02,  3.058315433739E-02,  3.058315715668E-02,
              3.058315910726E-02,  3.058316048181E-02,  3.058316146648E-02,  3.058316218275E-02,
              3.058316271112E-02,  3.058316310589E-02,  3.058316340428E-02,  3.058316363221E-02,
              3.058316380808E-02,  3.058316394505E-02,  3.058316405266E-02,                   1,
              9.977930000000E-01,  9.912150000000E-01,  9.803950000000E-01,  9.655420000000E-01,
              9.469360000000E-01,  9.211362223597E-01,  8.688562675564E-01,  8.108240000000E-01,
              7.417575090802E-01,  6.413030000000E-01,  5.408367208541E-01,  4.807920000000E-01,
              3.497490000000E-01,  2.512750000000E-01,  1.768432017447E-01,  1.304470000000E-01,
              9.433736380317E-02,  7.059570000000E-02,  5.268096170336E-02,  4.032720000000E-02,
              2.428650000000E-02,  1.533620000000E-02,  1.009210000000E-02,  6.881610000000E-03,
              4.823560678474E-03,  3.487245440023E-03,  2.578710885266E-03,  1.943646866651E-03,
              1.493850000000E-03,  1.162827750555E-03,  9.190124274641E-04,  7.361567778277E-04,
              5.968016595264E-04,  4.890640000000E-04,  3.363261410460E-04,  2.389537358290E-04,
              1.743218160274E-04,  1.300633951738E-04,  9.902340000000E-05,  7.666272270380E-05,
              6.027975615211E-05,  4.804231924465E-05,  3.875290225804E-05,  3.160620000000E-05,
              2.602556283170E-05,  2.162488034877E-05,  1.811690042231E-05,  1.529276964899E-05,
              1.299850000000E-05,  1.111643855704E-05,  9.563173392213E-06,  8.272100115712E-06,
              7.191840373343E-06,  6.282390000000E-06 ]

    chunk_eprdata = [ 0., 1., 1000., 1e+6, 1e+9,
                      1., 2., 3., 4., 5.,
                      6., 7., 8., 9., 10. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 110, chunk.length )
            self.assertEqual( "JCOH", chunk.name )

            self.assertEqual( 55, chunk.NM )
            self.assertEqual( 55, chunk.number_values )

            self.assertEqual( 55, len( chunk.momentum ) )
            self.assertAlmostEqual( 0.  , chunk.momentum[0] )
            self.assertAlmostEqual( 6.  , chunk.momentum[-1] )

            self.assertEqual( 55, len( chunk.integrated_form_factors ) )
            self.assertAlmostEqual( 0, chunk.integrated_form_factors[0] )
            self.assertAlmostEqual( 3.058316405266E-02, chunk.integrated_form_factors[-1] )

            self.assertEqual( 55, len( chunk.form_factors ) )
            self.assertAlmostEqual( 1., chunk.form_factors[0] )
            self.assertAlmostEqual( 6.282390000000E-06, chunk.form_factors[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        def verify_chunk_eprdata( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 15, chunk.length )
            self.assertEqual( "JCOH", chunk.name )

            self.assertEqual( 5, chunk.NM )
            self.assertEqual( 5, chunk.number_values )

            self.assertEqual( 5, len( chunk.momentum ) )
            self.assertAlmostEqual( 0.  , chunk.momentum[0] )
            self.assertAlmostEqual( 1e+9, chunk.momentum[-1] )

            self.assertEqual( 5, len( chunk.integrated_form_factors ) )
            self.assertAlmostEqual( 1, chunk.integrated_form_factors[0] )
            self.assertAlmostEqual( 5, chunk.integrated_form_factors[-1] )

            self.assertEqual( 5, len( chunk.form_factors ) )
            self.assertAlmostEqual(  6., chunk.form_factors[0] )
            self.assertAlmostEqual( 10., chunk.form_factors[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk_eprdata[index], xss[index] )

        # the data is given explicitly - mcplib style
        chunk = CoherentFormFactorBlock(
                  integrated = [                  0,  9.977954354245E-05,  3.964942506035E-04,  8.824146336660E-04,
                                 1.545120632092E-03,  2.368152245929E-03,  3.328001096461E-03,  5.572765511802E-03,
                                 8.114989702569E-03,  1.077179717732E-02,  1.466576582467E-02,  1.814944661202E-02,
                                 2.013937477439E-02,  2.411608451487E-02,  2.666620748348E-02,  2.820041294244E-02,
                                 2.910584927642E-02,  2.965656338431E-02,  2.998629154717E-02,  3.018996625751E-02,
                                 3.031651130261E-02,  3.046055891684E-02,  3.052243640030E-02,  3.055108560889E-02,
                                 3.056526027755E-02,  3.057267572340E-02,  3.057674989952E-02,  3.057910122834E-02,
                                 3.058050894259E-02,  3.058138029848E-02,  3.058193578069E-02,  3.058229824481E-02,
                                 3.058254088417E-02,  3.058270703249E-02,  3.058282312688E-02,  3.058297109240E-02,
                                 3.058304939092E-02,  3.058309313441E-02,  3.058311867888E-02,  3.058313417771E-02,
                                 3.058314390105E-02,  3.058315017819E-02,  3.058315433739E-02,  3.058315715668E-02,
                                 3.058315910726E-02,  3.058316048181E-02,  3.058316146648E-02,  3.058316218275E-02,
                                 3.058316271112E-02,  3.058316310589E-02,  3.058316340428E-02,  3.058316363221E-02,
                                 3.058316380808E-02,  3.058316394505E-02,  3.058316405266E-02 ],
                  factors = [                                                                                 1,
                              9.977930000000E-01,  9.912150000000E-01,  9.803950000000E-01,  9.655420000000E-01,
                              9.469360000000E-01,  9.211362223597E-01,  8.688562675564E-01,  8.108240000000E-01,
                              7.417575090802E-01,  6.413030000000E-01,  5.408367208541E-01,  4.807920000000E-01,
                              3.497490000000E-01,  2.512750000000E-01,  1.768432017447E-01,  1.304470000000E-01,
                              9.433736380317E-02,  7.059570000000E-02,  5.268096170336E-02,  4.032720000000E-02,
                              2.428650000000E-02,  1.533620000000E-02,  1.009210000000E-02,  6.881610000000E-03,
                              4.823560678474E-03,  3.487245440023E-03,  2.578710885266E-03,  1.943646866651E-03,
                              1.493850000000E-03,  1.162827750555E-03,  9.190124274641E-04,  7.361567778277E-04,
                              5.968016595264E-04,  4.890640000000E-04,  3.363261410460E-04,  2.389537358290E-04,
                              1.743218160274E-04,  1.300633951738E-04,  9.902340000000E-05,  7.666272270380E-05,
                              6.027975615211E-05,  4.804231924465E-05,  3.875290225804E-05,  3.160620000000E-05,
                              2.602556283170E-05,  2.162488034877E-05,  1.811690042231E-05,  1.529276964899E-05,
                              1.299850000000E-05,  1.111643855704E-05,  9.563173392213E-06,  8.272100115712E-06,
                              7.191840373343E-06,  6.282390000000E-06 ] )

        verify_chunk( self, chunk )

        # the data is given explicitly - eprdata style
        chunk = CoherentFormFactorBlock(
                  momentum = [0., 1., 1000., 1e+6, 1e+9 ],
                  integrated = [ 1., 2., 3., 4., 5. ],
                  factors = [ 6., 7., 8., 9., 10.] )

        verify_chunk_eprdata( self, chunk )

if __name__ == '__main__' :

    unittest.main()
