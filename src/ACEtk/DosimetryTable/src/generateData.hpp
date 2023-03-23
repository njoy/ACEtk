Data generateData( unsigned int z, unsigned int a,
                   block::MTR&& mtr, block::SIGD&& sigd ) {

  std::array< int32_t, 16 > iz;
  std::array< double, 16 > aw;
  std::array< int64_t, 16 > nxs;
  std::array< int64_t, 32 > jxs;
  iz.fill( 0 );
  aw.fill( 0. );
  nxs.fill( 0 );
  jxs.fill( 0 );
  std::vector< double > xss;

  // verify some stuff:
  //  - MTR and SIGD have the same NTR
  if ( mtr.NTR() != sigd.NTR() ) {

    Log::error( "Inconsistent NTR between the MTR and SIGD block" );
    Log::info( "MTR NTR value = {}", mtr.NTR() );
    Log::info( "SIGD NTR value = {}", sigd.NTR() );
    throw std::exception();
  }

  // generate the xss array and set the locators in the jxs array as we go
  jxs[0] = 1;
  jxs[2] = 1;
  xss.insert( xss.end(), mtr.begin(), mtr.end() );
  jxs[5] = xss.size() + 1;
  jxs[6] = xss.size() + mtr.NTR() + 1;
  xss.insert( xss.end(), sigd.begin(), sigd.end() );
  jxs[21] = xss.size();

  // set the nxs values for the dosimetry table
  // NXS(1) = length
  // NXS(2) = za
  // NXS(4) = NTR
  nxs[0] = xss.size();
  nxs[1] = z * 1000 + a;
  nxs[3] = mtr.NTR();

  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}
