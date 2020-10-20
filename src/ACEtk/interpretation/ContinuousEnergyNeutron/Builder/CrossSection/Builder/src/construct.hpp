CrossSection construct(){
  try{
    details::verify::equalSize( this->values_.value(), 
                                this->energyGrid_.value() );
    return CrossSection{ energyGrid_.value(),
                        std::move( this->values_.value() )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a CrossSection object" );
    Log::info( "Some component has not been defined" );
    throw;
  } catch( std::range_error& e){
    Log::info( "energy grid size must equal the size of the cross section" );
    throw;
  }

}
