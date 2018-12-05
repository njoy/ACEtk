Builder& crossSection( std::vector< double >&& xs, Slice energyGrid ){

  try{
    details::verify::equalSize( xs, energyGrid );
    this->crossSection_ = std::move( details::verify::positive( xs ) );
    this->energyGrid_ = energyGrid;
    return *this;

  } catch( std::range_error& e){
    Log::info( "energy grid size must equal the size of the cross section" );
    throw;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "crossSection must be all positive" );
    throw;
  }
}

Builder& crossSection( std::vector< double >&& xs ){
  return crossSection( std::move( xs ), this->parent.get().energyGrid() );
}

