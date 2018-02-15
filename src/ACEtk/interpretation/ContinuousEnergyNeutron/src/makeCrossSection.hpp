static
CrossSection makeCrossSection( const Table& ACETable, int index ){

  int NTR = ACETable.data.NXS( NeutronHeaderIndices::MTs.nxs );
  if( ( index > NTR ) or ( index < 0 ) ){
    Log::error( "Index ({}) is outside the range of number of reactions ({}).",
               index, NTR );
    throw std::exception();
  }

  int LXS = ACETable.data.JXS( 
      NeutronHeaderIndices::Locators::crossSection.jxs ) + index;
  int lxs2 = ACETable.data.JXS( NeutronHeaderIndices::crossSection.jxs );
  auto LOCA = ACETable.data.XSS( LXS );
  auto IE = ACETable.data.XSS( lxs2 + LOCA - 1);
  auto NE = ACETable.data.XSS( lxs2 + LOCA );

  auto energies = EnergyGrid( ACETable ).energies( IE, NE );
  auto sigma = ACETable.data.XSS( LXS + LOCA + 1, NE );

  return CrossSection( energies, sigma );
}

Reaction makeCrossSection( int index ) const {
  return makeCrossSection( this->table, index );
}
