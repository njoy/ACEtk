// template< typename Range,
//           utility::Require< true, utility::is_range, Range > = true
//         >
void SIG(int indexJXS ){

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  auto LXS = xss.size() + 1;
  jxs[ indexJXS - 1 ] = LXS;

  // All reactions (except MT 2)
  int MT{ 0 };
  for( const auto& reac : this->reactions_ ){

    MT = reac.first;
    if( MT == 2 ) continue;
    reac.second.crossSection.ACEify( tData, this->energyGrid() );

  }
}
