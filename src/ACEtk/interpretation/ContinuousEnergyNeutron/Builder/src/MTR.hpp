void MTR(){

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& nxs = tData.NXS();
  auto& jxs = tData.JXS();

  auto LMT = xss.size() + 1;
  jxs[ 2 ] = LMT;
  
  // All reactions (except MT 2)
  auto NMT = this->reactions_.size() - 1;
  nxs[ 3 ] = NMT;

  int MT{ 0 };
  for( const auto& reac : this->reactions_ ){

    MT = reac.first;
    if( MT == 2 ) continue;
    xss.push_back( MT );

  }
}
