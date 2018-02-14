static
CrossSection makeCrossSection( const Table& ACETable, int MT ){

  Log::info( "MT: {}", MT );
  int index;
  int LXS;
  int lxs2;
  try{
    // Look first in the neutron reactions
    index = getReactionIndex( neutronReactionIDs( ACETable ), MT );
    LXS = ACETable.data.JXS( 
        NeutronHeaderIndices::Locators::crossSection.jxs ) + index;
    lxs2 = ACETable.data.JXS( NeutronHeaderIndices::crossSection.jxs );
  } catch( const std::exception& e ){
    try{
      // If you can't find it amongst the neutron reactions, look in the photon
      // production reactions
      index = getReactionIndex( photonProductionReactionIDs( ACETable ), MT );
      LXS = ACETable.data.JXS( 
          PhotonProductionHeaderIndices::Locators::crossSection.jxs ) + index;
      lxs2 = ACETable.data.JXS( 
          PhotonProductionHeaderIndices::crossSection.jxs );
    } catch( const std::exception& e ){
      njoy::Log::info( 
          "Can't make a CrossSection because the Reaction can't be found." );
      throw std::exception();
    }
  }

  auto LOCA = ACETable.data.XSS( LXS );
  auto IE = ACETable.data.XSS( lxs2 + LOCA - 1);
  auto NE = ACETable.data.XSS( lxs2 + LOCA );

  auto energies = EnergyGrid( ACETable ).energies( IE, NE );
  auto sigma = ACETable.data.XSS( LXS + LOCA + 1, NE );

  return CrossSection( energies, sigma );
}

Reaction makeCrossSection( int MT ) const {
  return makeCrossSection( this->table, MT );
}
