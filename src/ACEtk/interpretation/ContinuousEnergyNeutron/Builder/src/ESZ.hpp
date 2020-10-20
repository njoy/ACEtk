void ESZ(){
  decltype( auto ) xss = this->tableData_.value().XSS();
  decltype( auto ) nxs = this->tableData_.value().NXS();
  decltype( auto ) jxs = this->tableData_.value().JXS();

  try{
    nxs[ 1 ] = this->SZA_.value();

    nxs[ 2 ] = this->energyGrid_.value().size();
    jxs[ 0 ] = 1;

    xss |= ranges::action::push_back( this->energyGrid_.value() );
    xss |= ranges::action::push_back( this->totalXS_.value() );
    xss |= ranges::action::push_back( this->totalDisappearanceXS_.value() );
    xss |= ranges::action::push_back( 
        this->elasticScattering_.value().crossSection.values );
    xss |= ranges::action::push_back( this->heating_.value() );

  } catch( std::bad_optional_access& b ){
    Log::error( "Some component in the ESZ Block has not been built." );
    throw;
  }
}
