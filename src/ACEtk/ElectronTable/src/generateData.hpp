Data generateData( unsigned int z,
                   std::vector< unsigned int > za, std::vector< double > awr,
                   electron::EKT&& ekt, electron::RAD&& rad,
                   electron::MOT&& mot, electron::RLY&& rly,
                   std::optional< electron::XSB >&& xsb,
                   std::optional< electron::CRB >&& crb,
                   std::optional< electron::HFB >&& hfb,
                   std::optional< electron::RKT >&& rkt,
                   std::optional< electron::RKA >&& rka,
                   std::optional< electron::OSC >&& osc ) {
  
  std::array< int32_t, 16 > iz;
  std::array< double, 16 > aw;
  std::array< int64_t, 16 > nxs;
  std::array< int64_t, 32 > jxs;
  std::vector< double > xss;
  iz.fill( 0 );
  aw.fill( 0.0 );
  nxs.fill( 0 );
  jxs.fill( 0 );
  
  // assign za values
  if ( za.size() != awr.size() ) {

    Log::error( "Inconsistent number of ZA and atomic mass values" );
    Log::info( "Number of ZA values = {}", za.size() );
    Log::info( "Number of atomic mass values = {}", awr.size() );
    throw std::exception();
  }
  for ( unsigned int i = 0; i < za.size(); ++i ) {

    iz[i] = za[i];
    aw[i] = awr[i];
  }
  
  // determine electron table type (EL or EL03)
  unsigned int nel;
  if ( xsb.has_value() && !crb.has_value() && !hfb.has_value()
       && rkt.has_value() && rka.has_value() && osc.has_value() ) {
    
    nel = 3;
  } else if ( !xsb.has_value() && crb.has_value() && hfb.has_value()
              && !rkt.has_value() && !rka.has_value() && !osc.has_value() ) {
    
    nel = 0;
  } else {
    
    Log::error( "Inconsistent data blocks for electron table type" );
    Log::info( "For EL03 expect: XSB ({}), RKT ({}), RKA ({}), OSC ({})",
               xsb.has_value() ? "yes" : "no",
               rkt.has_value() ? "yes" : "no",
               rka.has_value() ? "yes" : "no",
               osc.has_value() ? "yes" : "no" );
    Log::info( "For EL expect: CRB ({}), HFB ({})",
               crb.has_value() ? "yes" : "no",
               hfb.has_value() ? "yes" : "no" );
    Log::info( "EL and EL03 are mutually exclusive" );
    throw std::exception();
  }
  
  // generate the xss array
  xss.insert( xss.end(), ekt.begin(), ekt.end() );
  xss.insert( xss.end(), rad.begin(), rad.end() );
  xss.insert( xss.end(), mot.begin(), mot.end() );
  xss.insert( xss.end(), rly.begin(), rly.end() );
  if ( nel == 3 ) {
    
    xss.insert( xss.end(), xsb.value().begin(), xsb.value().end() );
    xss.insert( xss.end(), rkt.value().begin(), rkt.value().end() );
    xss.insert( xss.end(), rka.value().begin(), rka.value().end() );
    xss.insert( xss.end(), osc.value().begin(), osc.value().end() );
  } else {
    
    xss.insert( xss.end(), crb.value().begin(), crb.value().end() );
    xss.insert( xss.end(), hfb.value().begin(), hfb.value().end() );
  }
  
  // generate the jxs array
  // offsets to blocks listed below:
  // JXS    EL03    EL
  //  1     1       1
  //  2     RAD     RAD
  //  3     MOT     MOT
  //  4     RLY     RLY
  //  5     XSB     CRB
  //  6     unused  HFB
  //  9     RKT     unused
  // 10     RKA     unused
  // 11     OSC     unused
  jxs[0] = 1;
  jxs[1] = jxs[0] + ekt.length();
  jxs[2] = jxs[1] + rad.length();
  jxs[3] = jxs[2] + mot.length();
  jxs[4] = jxs[3] + rly.length();
  if ( nel == 3 ) {
    
    jxs[8] = jxs[4] + xsb.value().length();
    jxs[9] = jxs[8] + rkt.value().length();
    jxs[10] = jxs[9] + rka.value().length();
  } else {
    
    jxs[5] = jxs[4] + crb.value().length();
  }
  
  // generate the nxs array
  // NXS    EL03    EL
  //  1    .value().length .value().length
  //  2     Z       Z
  //  3     NRAD    NRAD
  //  4     NMOT    NMOT
  //  5     NEB     NCRB
  //  6     NPB     NHFB
  //  9     NRKT    unused
  // 10     NRKA    unused
  // 11     NOSC    unused
  // 16     3       unused
  nxs[0] = xss.size();
  nxs[1] = z;
  nxs[2] = rad.NRAD();
  nxs[3] = mot.NMOT();
  if ( nel == 3 ) {
    
    nxs[4] = xsb.value().NEB();
    nxs[5] = xsb.value().NPB();
    nxs[8] = rkt.value().NRKT();
    nxs[9] = rka.value().NRKA();
    nxs[10] = osc.value().NOSC();
  } else {
    
    nxs[4] = crb.value().NCRB();
    nxs[5] = hfb.value().NHFB();
    nxs[8] = 0;
    nxs[9] = 0;
    nxs[10] = 0;
  }
  nxs[15] = nel;
  
  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}
