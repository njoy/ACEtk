void TYR(){
  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  auto STYR = xss.size() + 1;
  jxs[ 4 ] = STYR;

  int MT{ 0 };
  for( const auto& reac : this->reactions_ ){

    MT = reac.first;
    if( MT == 2 ) continue;

    xss.push_back( reac.second.neutronYield );

  }
}
