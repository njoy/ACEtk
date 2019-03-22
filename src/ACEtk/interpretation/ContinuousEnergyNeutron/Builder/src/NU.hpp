void NU(){
  auto foundPrompt = (
      fissionMultiplicity_.find( "prompt" ) != fissionMultiplicity_.end() );
  auto foundTotal = (
      fissionMultiplicity_.find( "total" ) != fissionMultiplicity_.end() );

  auto& xss = this->tableData_.value().XSS();
  auto& jxs = this->tableData_.value().JXS();

  // auto nuVisitor = [&](auto& nubar ) -> void
  // {
  //   xss |= ranges::action::push_back( nubar.ACEify( this->tableData_ ) );
  // };

  // auto size = xss.size() + 1;
  // jxs[ 1 ] = size;
  // if( foundPrompt ){
  //   auto prompt = this->fissionMultiplicity_[ "prompt" ];

  //   std::visit( nuVisitor, prompt );
  //   auto promptSize = xss.size();

  //   if( foundTotal ){
  //     auto total = this->fissionMultiplicity_[ "total" ];

  //     std::visit( nuVisitor, total );

  //     auto totalSize = xss.size() - promptSize;
  //     xss.insert( xss.begin() + size, -1*totalSize );
  //   }
  // }
  // else if( foundTotal ){
  //     auto total = this->fissionMultiplicity_[ "total" ];
  //     std::visit( nuVisitor, total );
  // }
  // else{
  //   jxs[ 1 ] = 0;
  // }

  // if( not this->delayedPrecursors_.empty() ){
  // }
}
