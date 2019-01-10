template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& outgoingEnergyTable( Range&& eout ){
  if( this->outgoingEnergyTables_.size() ){
    auto back = this->outgoingEnergyTables_.back();
    try{
      details::verify::equalSize( back, eout );
    } catch( std::range_error& e){
      Log::info( "All outgoing energy tables must have the same size" );
      throw;
    }
  }
  this->outgoingEnergyTables_.emplace_back( eout | ranges::to_vector );
  return *this;
}
