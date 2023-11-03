static continuous::TYR generateTYR( const continuous::DLW& dlw, std::size_t ntr ) {

  auto entries = dlw.tyrMultiplicities();
  std::vector< ReferenceFrame > frames = dlw.referenceFrames();
  std::vector< unsigned int > multiplicities( entries.begin(),
                                              entries.begin() + dlw.NR() );
  for ( unsigned int i = dlw.NR(); i < ntr; ++i ) {

    frames.push_back( ReferenceFrame::Laboratory );
    multiplicities.push_back( 0 );
  }
  return { std::move( frames ), std::move( multiplicities ) };
}

static std::optional< std::vector< continuous::TYRH > >
generateTYRH( const std::optional< std::vector< continuous::DLWH > >& dlwh ) {

  std::optional< std::vector< continuous::TYRH > > tyrh = std::nullopt;
  if ( dlwh.has_value() ) {

    tyrh = std::vector< continuous::TYRH >{};
    for ( const auto& element : dlwh.value() ) {

      std::vector< ReferenceFrame > frames;
      std::transform( element.referenceFrames().begin(),
                      element.referenceFrames().end(),
                      std::back_inserter( frames ),
                      [] ( auto&& optional ) -> ReferenceFrame
                         { return optional.value(); } );
      tyrh->emplace_back( frames );
    }
  }
  return tyrh;
}

Data generateData( unsigned int z, unsigned int a,
                   continuous::ESZ&& esz, std::optional< continuous::NU >&& nu,
                   continuous::MTR&& mtr, continuous::LQR&& lqr,
                   continuous::SIG&& sig, continuous::AND&& ang,
                   continuous::DLW&& dlw,
                   std::optional< continuous::GPD >&& gpd,
                   std::optional< continuous::MTRP >&& mtrp,
                   std::optional< continuous::SIGP >&& sigp,
                   std::optional< continuous::ANDP >&& andp,
                   std::optional< continuous::DLWP >&& dlwp,
                   std::optional< continuous::YP >&& yp,
                   std::optional< continuous::UNR >&& unr,
                   std::optional< continuous::DNU >&& dnu,
                   std::optional< continuous::BDD >&& bdd,
                   std::optional< continuous::DNED >&& dned,
                   std::optional< continuous::PTYPE >&& ptype,
                   std::optional< std::vector< continuous::HPD > >&& hpd,
                   std::optional< std::vector< continuous::MTRH > >&& mtrh,
                   std::optional< std::vector< continuous::SIGH > >&& sigh,
                   std::optional< std::vector< continuous::ANDH > >&& andh,
                   std::optional< std::vector< continuous::DLWH > >&& dlwh,
                   std::optional< std::vector< continuous::YH > >&& yh ) {

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
  unsigned int nr = ang.NR();
  unsigned int ntrp = mtrp ? mtrp->NTR() : 0;
  unsigned int ntype = ptype ? ptype->NTYPE() : 0;
  unsigned int npcr = bdd ? bdd->NPCR() : 0;

  // generate blocks we don't have yet
  continuous::TYR tyr = generateTYR( dlw, ntr );
  std::optional< std::vector< continuous::TYRH > > tyrh = generateTYRH( dlwh );

  // verify some stuff:
  //  - MTR, LQR, TYR and SIG have the same NTR
  //  - AND and DLW have the same NR
  //  - when fission is present, the NU block should be defined
  //  - when one of the photon production blocks is defined, all of them should be
  //  - ANDP and DLWP have the same NTRP
  //  - when delayed nubar is defined, it can only be tabulated
  //  - when one of the delayed neutron blocks is defined, all of them should be
  //  - BDD and DNED have the same NPCR
  //  - when one of the secondary particle blocks is defined, all of them should be
  //  - the number of secondary particle production blocks is correct
  if ( ( ntr != lqr.NTR() ) || ( ntr != tyr.NTR() ) ||
       ( ntr != sig.NTR() ) ) {

    Log::error( "Inconsistent NTR between the different blocks" );
    Log::info( "MTR NTR value = {}", mtr.NTR() );
    Log::info( "LQR NTR value = {}", lqr.NTR() );
    Log::info( "TYR NTR value = {}", tyr.NTR() );
    Log::info( "SIG NTR value = {}", sig.NTR() );
    throw std::exception();
  }
  if ( ( nr != ang.NR() ) || ( nr != dlw.NR() ) ) {

    Log::error( "Inconsistent NR between the different blocks" );
    Log::info( "AND NTR value = {}", ang.NR() );
    Log::info( "DLW NTR value = {}", dlw.NR() );
    throw std::exception();
  }
  if ( mtr.hasReactionNumber( 18 ) && !nu ) {

    Log::error( "The fission reaction is defined but the fission multiplicity "
                "block is missing" );
    throw std::exception();
  }
  if ( ( gpd || mtrp || sigp || andp || dlwp || yp ) &&
       !( gpd && mtrp && sigp && andp && dlwp && yp ) ) {

    Log::error( "Not all photon production blocks are defined" );
    Log::info( gpd ? "GPD is defined" : "GPD is not defined" );
    Log::info( mtrp ? "MTRP is defined" : "MTRP is not defined" );
    Log::info( sigp ? "SIGP is defined" : "SIGP is not defined" );
    Log::info( andp ? "ANDP is defined" : "ANDP is not defined" );
    Log::info( dlwp ? "DLWP is defined" : "DLWP is not defined" );
    Log::info( yp ? "YP is defined" : "YP is not defined" );
    throw std::exception();
  }
  if ( gpd.has_value() ) {

    if ( ( ntrp != andp->NR() ) || ( ntrp != dlwp->NR() ) ) {

      Log::error( "Inconsistent NTRP between the different blocks" );
      Log::info( "ANDP NTRP value = {}", andp->NR() );
      Log::info( "DLWP NTRP value = {}", dlwp->NR() );
      throw std::exception();
    }
  }
  if ( dnu.has_value() ) {

    if ( dnu->hasPromptAndTotalFissionMultiplicity() ) {

      Log::error( "The delayed fission neutron multiplicity block has two "
                  "sets of multiplicity data which is not allowed" );
      throw std::exception();
    }
    unsigned int lnu = std::visit( [] ( const auto& nu ) { return nu.LNU(); },
                                   dnu->multiplicity() );
    if ( lnu != 2 ) {

      Log::error( "The delayed fission neutron multiplicity data is not given "
                  "as tabulated data" );
      Log::info( "Expected LNU = 2" );
      Log::info( "Found LNU = {}", lnu );
      throw std::exception();
    }
  }
  if ( ( dnu || bdd || dned ) && !( dnu && bdd && dned ) ) {

    Log::error( "Not all delayed neutron blocks are defined" );
    Log::info( dnu ? "DNU is defined" : "DNU is not defined" );
    Log::info( bdd ? "BDD is defined" : "BDD is not defined" );
    Log::info( dned ? "DNED is defined" : "DNED is not defined" );
    throw std::exception();
  }
  if ( bdd.has_value() ) {

    if ( ( npcr != bdd->NPCR() ) || ( npcr != dned->NR() ) ) {

      Log::error( "Inconsistent NPCR between the different blocks" );
      Log::info( "BDD NPCR value = {}", bdd->NPCR() );
      Log::info( "DNED NPCR value = {}", dned->NR() );
      throw std::exception();
    }
  }
  if ( ( ptype || hpd || mtrh || tyrh || sigh || andh || dlwh || yh ) &&
       !( ptype && hpd && mtrh && tyrh && sigh && andh && dlwh && yh ) ) {

    Log::error( "Not all secondary particle production blocks are defined" );
    Log::info( ptype ? "PTYPE is defined" : "PTYPE is not defined" );
    Log::info( hpd ? "HPD is defined" : "HPD is not defined" );
    Log::info( mtrh ? "MTRH is defined" : "MTRH is not defined" );
    Log::info( tyrh ? "TYRH is defined" : "TYRH is not defined" );
    Log::info( sigh ? "SIGH is defined" : "SIGH is not defined" );
    Log::info( andh ? "ANDH is defined" : "ANDH is not defined" );
    Log::info( dlwh ? "DLWH is defined" : "DLWH is not defined" );
    Log::info( dlwh ? "YH is defined" : "YH is not defined" );
    throw std::exception();
  }
  if ( ptype.has_value() ) {

    if ( ( ntype != hpd->size() ) || ( ntype != mtrh->size() ) ||
         ( ntype != tyrh->size() ) || ( ntype != sigh->size() ) ||
         ( ntype != andh->size() ) || ( ntype != dlwh->size() ) ||
         ( ntype != yh->size() ) ) {

      Log::error( "Inconsistent size between the different secondary "
                  "particle production blocks" );
      Log::info( "PTYPE NTRP value = {}", ntype );
      Log::info( "Number HPD blocks = {}", hpd->size() );
      Log::info( "Number MTRH blocks = {}", mtrh->size() );
      Log::info( "Number TYRH blocks = {}", tyrh->size() );
      Log::info( "Number SIGH blocks = {}", sigh->size() );
      Log::info( "Number ANDH blocks = {}", andh->size() );
      Log::info( "Number DLWH blocks = {}", dlwh->size() );
      Log::info( "Number YH blocks = {}", yh->size() );
      throw std::exception();
    }
  }

  // generate the xss array and set the locators in the jxs array as we go
  jxs[0] = 1;
  xss.insert( xss.end(), esz.begin(), esz.end() );
  if ( nu.has_value() ) {

    jxs[1] = xss.size() + 1;
    xss.insert( xss.end(), nu->begin(), nu->end() );
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
  jxs[8] = xss.size() + ( nr + 1 ) + 1;
  xss.insert( xss.end(), ang.begin(), ang.end() );
  jxs[9] = xss.size() + 1;
  jxs[10] = xss.size() + nr + 1;
  xss.insert( xss.end(), dlw.begin(), dlw.end() );
  if ( unr ) {

    jxs[22] = xss.size() + 1;
    xss.insert( xss.end(), unr->begin(), unr->end() );
  }
  if ( dnu.has_value() ) {

    jxs[23] = xss.size() + 1;
    xss.insert( xss.end(), dnu->begin(), dnu->end() );
    jxs[24] = xss.size() + 1;
    xss.insert( xss.end(), bdd->begin(), bdd->end() );
    jxs[25] = xss.size() + 1;
    jxs[26] = xss.size() + npcr + 1;
    xss.insert( xss.end(), dned->begin(), dned->end() );
  }
  if ( gpd.has_value() ) {

    jxs[11] = xss.size() + 1;
    xss.insert( xss.end(), gpd->begin(), gpd->end() );
    jxs[12] = xss.size() + 1;
    xss.insert( xss.end(), mtrp->begin(), mtrp->end() );
    jxs[13] = xss.size() + 1;
    jxs[14] = xss.size() + ntrp + 1;
    xss.insert( xss.end(), sigp->begin(), sigp->end() );
    jxs[15] = xss.size() + 1;
    jxs[16] = xss.size() + ntrp + 1;
    xss.insert( xss.end(), andp->begin(), andp->end() );
    jxs[17] = xss.size() + 1;
    jxs[18] = xss.size() + ntrp + 1;
    xss.insert( xss.end(), dlwp->begin(), dlwp->end() );
    jxs[19] = xss.size() + 1;
    xss.insert( xss.end(), yp->begin(), yp->end() );
  }
  if ( mtr.hasReactionNumber( 18 ) ) {

    jxs[20] = jxs[6] + sig.crossSectionLocator( mtr.index( 18 ) ) - 1;
  }
  jxs[21] = xss.size();
  if ( ptype.has_value() ) {

    std::vector< unsigned int > numbers;
    for ( const auto& element : mtrh.value() ) {

      numbers.push_back( element.NTR() );
    }
    continuous::NTRO ntro( std::move( numbers ) );

    jxs[29] = xss.size() + 1;
    xss.insert( xss.end(), ptype->begin(), ptype->end() );
    jxs[30] = xss.size() + 1;
    xss.insert( xss.end(), ntro.begin(), ntro.end() );
    jxs[31] = xss.size() + 1;

    auto size = ntype * 10;
    auto ixs_position = xss.size();
    std::vector< std::array< unsigned int, 10 > > ixs( ntype );

    for ( std::size_t index = 0; index < ntype; ++index ) {

      auto number = mtrh.value()[index].NTR();

      ixs[index][0] = xss.size() + size + 1;
      xss.insert( xss.end(), hpd.value()[index].begin(), hpd.value()[index].end() );
      ixs[index][1] = xss.size() + size + 1;
      xss.insert( xss.end(), mtrh.value()[index].begin(), mtrh.value()[index].end() );
      ixs[index][2] = xss.size() + size + 1;
      xss.insert( xss.end(), tyrh.value()[index].begin(), tyrh.value()[index].end() );
      ixs[index][3] = xss.size() + size + 1;
      ixs[index][4] = xss.size() + size + number + 1;
      xss.insert( xss.end(), sigh.value()[index].begin(), sigh.value()[index].end() );
      ixs[index][5] = xss.size() + size + 1;
      ixs[index][6] = xss.size() + size + number + 1;
      xss.insert( xss.end(), andh.value()[index].begin(), andh.value()[index].end() );
      ixs[index][7] = xss.size() + size + 1;
      ixs[index][8] = xss.size() + size + number + 1;
      xss.insert( xss.end(), dlwh.value()[index].begin(), dlwh.value()[index].end() );
      ixs[index][9] = xss.size() + size + 1;
      xss.insert( xss.end(), yh.value()[index].begin(), yh.value()[index].end() );
    }

    continuous::IXS locators( std::move( ixs ) );
    xss.insert( xss.begin() + ixs_position, locators.begin(), locators.end() );
  }

  // set the nxs values for the continuous energy table
  // NXS(1) = length
  // NXS(2) = za
  // NXS(3) = NES (number energies)
  // NXS(4) = NTR (total number of reactions)
  // NXS(5) = NR (number of reactions with angular and energy distribution data,
  //              excluding elastic)
  // NXS(6) = NTRP (number of photon production reactions)
  // NXS(7) = NTYPE (number of secondary particle types)
  // NXS(8) = NPCR (number of delayed precursor groups)
  nxs[0] = xss.size();
  nxs[1] = z * 1000 + a;
  nxs[2] = esz.energies().size();
  nxs[3] = ntr;
  nxs[4] = nr;
  nxs[5] = ntrp;
  nxs[6] = ntype;
  nxs[7] = npcr;
  nxs[9] = z;
  nxs[10] = a;

  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}
