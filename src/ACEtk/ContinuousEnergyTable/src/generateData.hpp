Data generateData( unsigned int z, unsigned int a,
                   block::ESZ&& esz, std::optional< block::NU >&& nu,
                   block::MTR&& mtr, block::LQR&& lqr, block::TYR&& tyr,
                   block::SIG&& sig, block::AND&& ang, block::DLW&& dlw ) {

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
  //  - MTR, LQR, TYR and SIG have the same NTR
  //  - AND and DLW have the same NR
  unsigned int ntr = mtr.NTR();
  unsigned int nr = ang.NR();
  if ( ( ntr != lqr.NTR() ) || ( ntr != tyr.NTR() ) ||
       ( ntr != sig.NTR() ) ) {

    Log::error( "Inconsistent NTR between the different blocks" );
    Log::info( "MTR NTR value = {}", mtr.NTR() );
    Log::info( "LQR NTR value = {}", lqr.NTR() );
    Log::info( "TYR NTR value = {}", tyr.NTR() );
    Log::info( "SIG NTR value = {}", sig.NTR() );
    throw std::exception();
  }
  if ( ( nr != ang.NR() ) || ( ntr != dlw.NR() ) ) {

    Log::error( "Inconsistent NR between the different blocks" );
    Log::info( "AND NTR value = {}", ang.NR() );
    Log::info( "DLW NTR value = {}", dlw.NR() );
    throw std::exception();
  }

  // generate the xss array and set the locators in the jxs array as we go
  jxs[0] = 1;
  xss.insert( xss.end(), esz.begin(), esz.end() );
  if ( nu ) {

    jxs[1] = xss.size() + 1;
    xss.insert( xss.end(), nu.value().begin(), nu.value().end() );
  }
  jxs[2] = xss.size() + 1;
  xss.insert( xss.end(), mtr.begin(), mtr.end() );
  jxs[3] = xss.size() + 1;
  xss.insert( xss.end(), lqr.begin(), lqr.end() );
  jxs[4] = xss.size() + 1;
  xss.insert( xss.end(), tyr.begin(), tyr.end() );
  jxs[5] = xss.size() + 1;
  jxs[6] = xss.size() + ntr + 1;
  xss.insert( xss.end(), sig.begin(), sig.end() );
  jxs[7] = xss.size() + 1;
  jxs[8] = xss.size() + nr + 1;
  xss.insert( xss.end(), ang.begin(), ang.end() );
  jxs[9] = xss.size() + 1;
  jxs[10] = xss.size() + nr + 1;
  xss.insert( xss.end(), dlw.begin(), dlw.end() );

  // set the nxs values for the dosimetry table
  // NXS(1) = length
  // NXS(2) = za
  // NXS(4) = NTR
  nxs[0] = xss.size();
  nxs[1] = z * 1000 + a;
  nxs[3] = ntr;
  nxs[4] = nr;

  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}