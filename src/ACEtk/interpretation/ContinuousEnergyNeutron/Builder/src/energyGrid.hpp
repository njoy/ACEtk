template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& energyGrid( Range&& grid ){
  try{
    this->energyGrid_ = std::move( grid );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "energy grid values must be all positive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "energy grid values must be sorted" );
    throw;
  }
}

auto energyGrid(){ return Table::slice( energyGrid_.value() ); }
