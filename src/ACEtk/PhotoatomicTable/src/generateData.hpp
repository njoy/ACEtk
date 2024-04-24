Data generateData( unsigned int z,
                   std::vector< unsigned int > za, std::vector< double > awr,
                   photoatomic::ESZG&& eszg, photoatomic::JINC&& jinc,
                   photoatomic::JCOH&& jcoh, photoatomic::LHNM&& lhnm,
                   std::optional< photoatomic::JFLO >&& jflo,
                   std::optional< electron::EPS >&& eps,
                   std::optional< photoatomic::SWD >&& swd,
                   std::optional< electron::SUBSH >&& subsh,
                   std::optional< photoatomic::SPHEL >&& sphel,
                   std::optional< electron::XPROB >&& xprob,
                   std::optional< electron::ESZE >&& esze,
                   std::optional< electron::EXCIT >&& excit,
                   std::optional< electron::ELAS >&& elas,
                   std::vector< electron::EION >&& eion,
                   std::optional< electron::BREME >&& breme,
                   std::optional< electron::BREML >&& breml,
                   std::optional< electron::SELAS >&& selas ) {

  std::array< int32_t, 16 > iz;
  std::array< double, 16 > aw;
  std::array< int64_t, 16 > nxs;
  std::array< int64_t, 32 > jxs;
  iz.fill( 0 );
  aw.fill( 0. );
  nxs.fill( 0 );
  jxs.fill( 0 );
  std::vector< double > xss;

  // assign za values
  for ( unsigned int i = 0; i < za.size(); ++i ) {

    iz[i] = za[i];
    aw[i] = awr[i];
  }

  // determine data type
  unsigned int nepr = ( subsh.has_value() ? ( selas.has_value() ? 3 : 1 ) : 0 );

  // some size values
  unsigned int nes = eszg.NES();
  unsigned int nsh = swd.has_value() ? swd->NSH() : 0;
  unsigned int nflo = jflo.has_value() ? jflo->NFLO() : 0;
  unsigned int nssh = nepr > 0 ? subsh->NSSH() : 0;
  unsigned int ne = nepr > 0 ? esze->NE() : 0;
  unsigned int nxl = nepr > 0 ? excit->NXL() : 0;
  unsigned int na = nepr > 0 ? elas->NA() : 0;
  unsigned int nb = nepr > 0 ? breme->NB() : 0;
  unsigned int nbl = nepr > 0 ? breml->NBL() : 0;
  unsigned int ninc = nepr > 1 ? jinc.NM() : 0;
  unsigned int ncoh = nepr > 1 ? jcoh.NM() : 0;

  // verify some stuff:
  //  - same number of ZA and atomic mass values
  //  - ESZG, LHNM and SPHEL use the same number of incident energy values
  //  - SUBSH, XPROB, ESZE and EION use the same number of subshells for nepr > 0
  if ( za.size() != awr.size() ) {

    Log::error( "Inconsistent number of ZA and atomic mass values" );
    Log::info( "Number of ZA values = {}", za.size() );
    Log::info( "Number of atomic mass values = {}", awr.size() );
    throw std::exception();
  }
  bool sphelsize = sphel.has_value() ? nes != sphel->NES() : false;
  if ( ( nes != lhnm.NES() ) || sphelsize ) {

    Log::error( "Inconsistent NES between the different blocks" );
    Log::info( "ESZG NES value = {}", eszg.NES() );
    Log::info( "LHNM NES value = {}", lhnm.NES() );
    throw std::exception();
  }
  if ( nepr > 0 ) {

    if ( ( nssh != xprob->NSSH() ) || ( nssh != esze->NSSH() ) ||
         ( nssh != eion.size() ) ) {

      Log::error( "Inconsistent NSSH between the different blocks" );
      Log::info( "SUBSH NSSH value = {}", subsh->NSSH() );
      Log::info( "XPROB NSSH value = {}", xprob->NSSH() );
      Log::info( "ESZE NSSH value = {}", esze->NSSH() );
      Log::info( "EION NSSH value = {}", eion.size() );
      throw std::exception();
    }
  }
  if ( nepr == 3 ) {

    if ( ne != selas->NE() ) {

      Log::error( "Inconsistent NE between the different blocks" );
      Log::info( "ESZE NE value = {}", esze->NE() );
      Log::info( "SELAS NE value = {}", selas->NE() );
      throw std::exception();
    }
  }

  // generate the xss array and set the locators in the jxs array as we go
  jxs[0] = 1;
  xss.insert( xss.end(), eszg.begin(), eszg.end() );
  jxs[1] = xss.size() + 1;
  xss.insert( xss.end(), jinc.begin(), jinc.end() );
  jxs[2] = xss.size() + 1;
  xss.insert( xss.end(), jcoh.begin(), jcoh.end() );
  jxs[3] = xss.size() + 1;
  if ( jflo.has_value() ) {

    xss.insert( xss.end(), jflo->begin(), jflo->end() );
  }
  jxs[4] = xss.size() + 1;
  xss.insert( xss.end(), lhnm.begin(), lhnm.end() );
  if ( eps.has_value() ) {

    jxs[5] = xss.size() + 1;
    jxs[6] = xss.size() + nsh + 1;
    jxs[7] = xss.size() + 2 * nsh + 1;
    xss.insert( xss.end(), eps->begin(), eps->end() );
  }
  if ( swd.has_value() ) {

    jxs[8] = xss.size() + 1;
    jxs[9] = xss.size() + nsh + 1;
    xss.insert( xss.end(), swd->begin(), swd->end() );
  }
  if ( nepr > 0 ) {

    jxs[10] = xss.size() + 1;
    jxs[11] = jxs[10] + nssh;
    jxs[12] = jxs[11] + nssh;
    jxs[13] = jxs[12] + nssh;
    jxs[14] = jxs[13] + nssh;
    xss.insert( xss.end(), subsh->begin(), subsh->end() );
    jxs[15] = xss.size() + 1;
    xss.insert( xss.end(), sphel->begin(), sphel->end() );
    jxs[16] = xss.size() + 1;
    jxs[17] = jxs[16] + nssh;
    xss.insert( xss.end(), xprob->begin(), xprob->end() );
    jxs[18] = xss.size() + 1;
    xss.insert( xss.end(), esze->begin(), esze->end() );
    jxs[19] = xss.size() + 1;
    xss.insert( xss.end(), excit->begin(), excit->end() );
    jxs[20] = xss.size() + 1;
    jxs[21] = jxs[20] + 3 * na;
    xss.insert( xss.end(), elas->begin(), elas->end() );
    jxs[22] = xss.size() + 1;
    unsigned int l = xss.size();
    xss.insert( xss.end(), 3 * nssh, 0.0 );
    for ( auto&& block : eion ) {

      xss[l] = block.NB();
      xss[l + nssh] = xss.size() + 1;
      xss[l + 2 * nssh] = xss.size() + 3 * block.NB() + 1;
      xss.insert( xss.end(), block.begin(), block.end() );
      ++l;
    }
    jxs[23] = xss.size() + 1;
    jxs[24] = jxs[23] + 3 * nb;
    xss.insert( xss.end(), breme->begin(), breme->end() );
    jxs[25] = xss.size() + 1;
    xss.insert( xss.end(), breml->begin(), breml->end() );
    if ( nepr == 3 ) {

      jxs[26] = xss.size() + 1;
      xss.insert( xss.end(), selas->begin(), selas->end() );
    }
  }

  // set the nxs values for the continuous energy table
  // NXS(1) = length
  // NXS(2) = Z
  // NXS(3) = NES
  // NXS(4) = NFLO
  // NXS(5) = NSH
  // NXS(6) = NEPR
  // NXS(7) = NSSH
  // NXS(8) = NE
  // NXS(9) = NXL
  // NXS(10) = NA
  // NXS(11) = NB
  // NXS(12) = NBL
  // NXS(13) = NINC
  // NXS(14) = NCOH
  nxs[0] = xss.size();
  nxs[1] = z;
  nxs[2] = nes;
  nxs[3] = nflo;
  nxs[4] = nsh;
  nxs[5] = nepr;
  nxs[6] = nssh;
  nxs[7] = ne;
  nxs[8] = nxl;
  nxs[9] = na;
  nxs[10] = nb;
  nxs[11] = nbl;
  nxs[12] = ninc;
  nxs[13] = ncoh;

  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}
