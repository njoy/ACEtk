Table construct(){

  this->tableData_ = Table::Data{};
  auto tableData = this->tableData_.value();

  this->ESZ();
  this->NU();

  try{
    tableData.NXS()[ 0 ] = tableData.XSS().size();
    
    return 
      Table{ 
        std::move( this->header_.value() ), 
        std::move( this->tableData_.value() ) };

  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a Continous Energy Neutron ACE Table" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
