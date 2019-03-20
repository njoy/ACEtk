Table construct(){

  this->ESZ();

  try{
    this->nxs[ 0 ] = this->xss.size();
    
    return 
      Table{ std::move( this->header_.value() ),
            Table::Data{
              std::move( this->izaw ),
              std::move( this->nxs ),
              std::move( this->jxs ),
              std::move( this->xss )
            }
      };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a Continous Energy Neutron ACE Table" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
