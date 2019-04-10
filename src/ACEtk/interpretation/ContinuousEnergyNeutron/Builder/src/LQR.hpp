void LQR(){
  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& nxs = tData.NXS();
  auto& jxs = tData.JXS();

  auto SLQR = xss.size() + 1;
  jxs[ 3 ] = SLQR;

  int MT{ 0 };
  for( const auto& reac : this->reactions_ ){

    MT = reac.first;
    if( MT == 2 ) continue;
    xss.push_back( reac.second.Q );

  }
}
