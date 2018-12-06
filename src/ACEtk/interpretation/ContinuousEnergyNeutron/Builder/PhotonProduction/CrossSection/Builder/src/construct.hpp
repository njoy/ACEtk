CrossSection construct(){
  if( not this->energyGrid_ ){
    this->energyGrid_ = parent.get().energyGrid();
  }

  try{
    details::verify::equalSize( this->values_.value(), 
                                this->energyGrid_.value() );
  } catch( std::range_error& e){
    Log::info( "energy grid size must equal the size of the cross section" );
    throw;
  }
  return CrossSection{
    this->MT,
    energyGrid_.value(),
    std::move( this->values_.value() )
  };
}
