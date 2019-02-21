Spectrum< S > construct(){

  try{
    return { TabBuilder::construct(), spectrum_.value() };
  } catch( std::bad_optional_access& b ){
    Log::error( "Some component not built." );
    throw;
  }
}
