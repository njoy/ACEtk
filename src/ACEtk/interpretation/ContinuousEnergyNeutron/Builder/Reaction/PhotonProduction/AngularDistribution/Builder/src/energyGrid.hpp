template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& energyGrid( Range&& grid ){
  try{
    this-> energyGrid_ = 
        details::verify::positive( details::verify::sorted( grid ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "energy grid must be all positive" );
    throw e;
  }
}
