Data generateData( std::vector< unsigned int > za,
                   block::ITIE&& itie, block::ITXE&& itxe,
                   std::optional< block::ITCE >&& itce,
                   std::optional< block::ITCA >&& itca,
                   std::optional< block::ITCEI >&& itcei,
                   std::optional< block::ITCAI >&& itcai ) {

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
  }

  // some size values
  unsigned int ne = itie.NE();
  int ncl = 0;
  int ncli = 0;

  // some options
  unsigned int idpnc = 0;
  if ( itce || itcei ) {

    if ( itce && itcei ) {

      idpnc = 5;
      ncl = itca ? itca->NCL() : -1;
      ncli = itcai->NCL();
    }
    else {

      if ( itce ) {

        idpnc = 4;
        ncl = itca ? itca->NCL() : -1;
      }
      else {

        idpnc = 3;
        ncl = itcai->NCL();
      }
    }
  }

  // verify some stuff:
  //  - ITIE and ITXE use the same numbeer of incident energy values
  if ( ne != itxe.NE() ) {

    Log::error( "Inconsistent NE between the different blocks" );
    Log::info( "ITIE NE value = {}", itie.NE() );
    Log::info( "ITXE NE value = {}", itxe.NE() );
    throw std::exception();
  }

  // generate the xss array and set the locators in the jxs array as we go
  jxs[0] = 1;
  jxs[1] = jxs[0] + ne + 1;
  xss.insert( xss.end(), itie.begin(), itie.end() );
  jxs[2] = xss.size() + 1;
  xss.insert( xss.end(), itxe.begin(), itxe.end() );
  if ( idpnc ) {

    if ( idpnc == 3 ) {

      jxs[3] = xss.size() + 1;
      jxs[4] = jxs[3] + itcei->NE() + 1;
      xss.insert( xss.end(), itcei->begin(), itcei->end() );
      jxs[5] = xss.size() + 1;
      xss.insert( xss.end(), itcai->begin(), itcai->end() );
    }
    if ( ( idpnc == 4 ) || ( idpnc == 5 ) ) {

      jxs[3] = xss.size() + 1;
      jxs[4] = jxs[3] + itce->NE() + 1;
      xss.insert( xss.end(), itce->begin(), itce->end() );
      if ( itca ) {

        jxs[5] = itca->empty() ? 0 : xss.size() + 1;
        xss.insert( xss.end(), itca->begin(), itca->end() );
      }
    }
    if ( idpnc == 5 ) {

      jxs[6] = xss.size() + 1;
      jxs[7] = jxs[6] + itcei->NE() + 1;
      xss.insert( xss.end(), itcei->begin(), itcei->end() );
      jxs[8] = xss.size() + 1;
      xss.insert( xss.end(), itcai->begin(), itcai->end() );
    }
  }

  // set the nxs values for the continuous energy table
  // NXS(1) = length
  // NXS(2) = IDPNI
  // NXS(3) = NIL
  // NXS(4) = NIEB
  // NXS(5) = IDPNC
  // NXS(6) = NCL
  // NXS(7) = IFENG
  // NXS(8) = NCLI
  nxs[0] = xss.size();
  nxs[1] = 3;
  nxs[2] = itxe.NIL();
  nxs[3] = itxe.IFENG() < 2 ? itxe.NIEB( 1 ) : 0;
  nxs[4] = idpnc;
  nxs[5] = ncl;
  nxs[6] = itxe.IFENG();
  nxs[7] = ncli;

  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}
