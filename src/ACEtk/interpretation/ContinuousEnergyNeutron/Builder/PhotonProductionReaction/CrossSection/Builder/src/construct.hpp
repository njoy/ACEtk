ContinuousEnergyNeutron::Builder::CrossSection construct(){
  try{
    details::verify::equalSize( this->values_.value(), 
                                this->energyGrid_.value() );
  } catch( std::range_error& e){
    Log::info( "energy grid size must equal the size of the cross section" );
    throw;
  }

  return ContinuousEnergyNeutron::Builder::CrossSection{ 
    energyGrid_.value(),
    std::move( this->values_.value() )
  };
}

