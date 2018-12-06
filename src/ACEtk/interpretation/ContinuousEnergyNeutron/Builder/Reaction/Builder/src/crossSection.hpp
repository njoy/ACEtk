template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& crossSection( Range&& xs, Slice energyGrid ){

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

template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& crossSection( Range&& xs ){
  return crossSection( std::move( xs ), this->parent.get().energyGrid() );
}

