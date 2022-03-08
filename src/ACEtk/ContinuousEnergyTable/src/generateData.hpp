Data generateData( unsigned int z, unsigned int a,
                   block::ESZ&& esz, std::optional< block::NU >&& nu,
                   block::MTR&& mtr, block::LQR&& lqr, block::TYR&& tyr,
                   block::SIG&& sig, block::AND&& ang, block::DLW&& dlw,
                   std::optional< block::GPD >&& gpd,
                   std::optional< block::MTRP >&& mtrp,
                   std::optional< block::SIGP >&& sigp,
                   std::optional< block::ANDP >&& andp,
                   std::optional< block::DLWP >&& dlwp,
                   std::optional< block::YP >&& yp,
                   std::optional< block::UNR >&& unr,
                   std::optional< block::DNU >&& dnu,
                   std::optional< block::BDD >&& bdd,
                   std::optional< block::DNED >&& dned ) {

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
  //  - when fission is present, the NU block should be defined
  //  - when one of the photon production blocks is defined, all of them should be
  //  - ANDP and DLWP have the same NTRP
  //  - when delayed nubar is defined, it can only be tabulated
  //  - when one of the delayed neutron blocks is defined, all of them should be
  //  - BDD and DNED have the same NPCR
  unsigned int ntr = mtr.NTR();
  unsigned int nr = ang.NR();
  unsigned int ntrp = mtrp ? mtrp->NTR() : 0;
  unsigned int ntype = 0;
  unsigned int npcr = bdd ? bdd->NPCR() : 0;
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
                "block is missin" );
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
  if ( gpd ) {

    if ( ( ntrp != andp->NR() ) || ( ntrp != dlwp->NR() ) ) {

      Log::error( "Inconsistent NTRP between the different blocks" );
      Log::info( "ANDP NTRP value = {}", andp->NR() );
      Log::info( "DLWP NTRP value = {}", dlwp->NR() );
      throw std::exception();
    }
  }
  if ( dnu ) {

    if ( dnu->hasPromptAndTotalFissionMultiplicity() ) {

      Log::error( "The delayed fission neutron multiplicity block has two "
                  "sets of multiplicity data which is not allowed" );
      throw std::exception();
    }
    unsigned int lnu = std::visit( [] ( const auto& nu ) { return nu.LNU(); },
                                   dnu->promptFissionMultiplicity() );
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
  if ( bdd ) {

    if ( ( npcr != bdd->NPCR() ) || ( npcr != dned->NR() ) ) {

      Log::error( "Inconsistent NPCR between the different blocks" );
      Log::info( "BDD NPCR value = {}", bdd->NPCR() );
      Log::info( "DNED NPCR value = {}", dned->NR() );
      throw std::exception();
    }
  }

  // generate the xss array and set the locators in the jxs array as we go
  jxs[0] = 1;
  xss.insert( xss.end(), esz.begin(), esz.end() );
  if ( nu ) {

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
  jxs[8] = xss.size() + nr + 1;
  xss.insert( xss.end(), ang.begin(), ang.end() );
  jxs[9] = xss.size() + 1;
  jxs[10] = xss.size() + nr + 1;
  xss.insert( xss.end(), dlw.begin(), dlw.end() );
  if ( gpd ) {

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

    jxs[20] = jxs[8] + sig.crossSectionLocator( mtr.index( 18 ) ) - 1;
  }
  jxs[21] = xss.size() + 1;
  if ( unr ) {

    jxs[22] = xss.size() + 1;
    xss.insert( xss.end(), unr->begin(), unr->end() );
  }
  if ( dnu ) {

    jxs[23] = xss.size() + 1;
    xss.insert( xss.end(), dnu->begin(), dnu->end() );
    jxs[24] = xss.size() + 1;
    xss.insert( xss.end(), bdd->begin(), bdd->end() );
    jxs[25] = xss.size() + 1;
    jxs[26] = xss.size() + npcr + 1;
    xss.insert( xss.end(), dned->begin(), dned->end() );
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

  return { std::move( iz ), std::move( aw ),
           std::move( nxs ), std::move( jxs ), std::move( xss ) };
}
