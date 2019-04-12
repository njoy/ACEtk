Table construct(){

  this->tableData_ = Table::Data{};
  auto& tableData = this->tableData_.value();

  auto nonMT2Reactions = this->reactions_
    | ranges::view::filter( [](auto& pair ){ return pair.first != 2; } );

  int NTR = ranges::distance( nonMT2Reactions );
  tableData.NXS()[ 3 ] = NTR;

  this->ESZ();
  this->NU();
  this->MTR( 2, nonMT2Reactions );
  this->LQR( 3, nonMT2Reactions );
  this->TYR( 4, nonMT2Reactions );
  this->SIG( 5, NTR, nonMT2Reactions );

  auto nonMT2PhotonReactions = this->photonProductionReactions_
    | ranges::view::filter( [](auto& pair ){ return pair.first != 2; } );

  int NTRP = ranges::distance( nonMT2PhotonReactions );
  tableData.NXS()[ 5 ] = NTRP;
  // this->MTR( 12, nonMT2PhotonReactions );
  // this->SIG( 14, NTRP, nonMT2PhotonReactions );

  try{
    tableData.NXS()[ 0 ] = tableData.XSS().size();
    
    return 
      Table{ 
        std::move( this->header_.value() ), 
        std::move( this->tableData_.value() )
      };

  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a Continous Energy Neutron Table" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
