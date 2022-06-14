Data generateData( unsigned int z, unsigned int a,
                   block::MTR&& mtr, block::LQR&& lqr,
                   block::SIG&& sig ) {

  std::array< int32_t, 16 > iz;
  std::array< double, 16 > aw;
  std::array< int64_t, 16 > nxs;
  std::array< int64_t, 32 > jxs;
  iz.fill( 0 );
  aw.fill( 0. );
  nxs.fill( 0 );
  jxs.fill( 0 );
  std::vector< double > xss;

  // some size values
  unsigned int ntr = mtr.NTR();

  // verify some stuff:
  //  - MTR, LQR and SIG have the same NTR
  if ( ( ntr != lqr.NTR() ) || ( ntr != sig.NTR() ) ) {

    Log::error( "Inconsistent NTR between the different blocks" );
    Log::info( "MTR NTR value = {}", mtr.NTR() );
    Log::info( "LQR NTR value = {}", lqr.NTR() );
    Log::info( "SIG NTR value = {}", sig.NTR() );
    throw std::exception();
  }

  // generate the xss array and set the locators in the jxs array as we go
//  jxs[0] = 1;
//  jxs[1] = 1;
//  jxs[2] = 1;
//  jxs[3] = 1;
//  jxs[4] = 1;
//  xss.insert( xss.end(), esz.begin(), esz.end() );
  jxs[5] = xss.size() + 1;
  xss.insert( xss.end(), mtr.begin(), mtr.end() );
  jxs[6] = xss.size() + 1;
  xss.insert( xss.end(), lqr.begin(), lqr.end() );
  jxs[7] = xss.size() + 1;
  jxs[8] = xss.size() + ntr + 1;
  xss.insert( xss.end(), sig.begin(), sig.end() );
//  if ( ptype ) {
//
//    std::vector< unsigned int > numbers;
//    for ( const auto& element : mtrh.value() ) {
//
//      numbers.push_back( element.NTR() );
//    }
//    block::NTRO ntro( std::move( numbers ) );
//
//    jxs[29] = xss.size() + 1;
//    xss.insert( xss.end(), ptype->begin(), ptype->end() );
//    jxs[30] = xss.size() + 1;
//    xss.insert( xss.end(), ntro.begin(), ntro.end() );
//    jxs[31] = xss.size() + 1;
//
//    auto size = ntype * 10;
//    auto ixs_position = xss.size();
//    std::vector< std::array< unsigned int, 10 > > ixs( ntype );
//
//    for ( std::size_t index = 0; index < ntype; ++index ) {
//
//      auto number = mtrh.value()[index].NTR();
//
//      ixs[index][0] = xss.size() + size + 1;
//      xss.insert( xss.end(), hpd.value()[index].begin(), hpd.value()[index].end() );
//      ixs[index][1] = xss.size() + size + 1;
//      xss.insert( xss.end(), mtrh.value()[index].begin(), mtrh.value()[index].end() );
//      ixs[index][2] = xss.size() + size + 1;
//      xss.insert( xss.end(), tyrh.value()[index].begin(), tyrh.value()[index].end() );
//      ixs[index][3] = xss.size() + size + 1;
//      ixs[index][4] = xss.size() + size + number + 1;
//      xss.insert( xss.end(), sigh.value()[index].begin(), sigh.value()[index].end() );
//      ixs[index][5] = xss.size() + size + 1;
//      ixs[index][6] = xss.size() + size + number + 1;
//      xss.insert( xss.end(), andh.value()[index].begin(), andh.value()[index].end() );
//      ixs[index][7] = xss.size() + size + 1;
//      ixs[index][8] = xss.size() + size + number + 1;
//      xss.insert( xss.end(), dlwh.value()[index].begin(), dlwh.value()[index].end() );
//      ixs[index][9] = xss.size() + size + 1;
//      xss.insert( xss.end(), yh.value()[index].begin(), yh.value()[index].end() );
//    }
//
//    block::IXS locators( std::move( ixs ) );
//    xss.insert( xss.begin() + ixs_position, locators.begin(), locators.end() );
//  }

  // set the nxs values for the continuous energy table
  // NXS(1) = length
  // NXS(2) = za
  // NXS(3) = NES (number energies)
  // NXS(4) = NTR (total number of reactions)
  // NXS(5) = NTYPE (number of secondary particle types)
  nxs[0] = xss.size();
  nxs[1] = z * 1000 + a;
//  nxs[2] = esz.energies().size();
  nxs[3] = ntr;
//  nxs[4] = ntype;

  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}
