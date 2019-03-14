template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& table( Range&& T ){
  if( this->tables_.size() ){
    auto back = this->tables_.back();
    try{
      details::verify::equalSize( back, T );
    } catch( std::range_error& e){
      Log::info( "All tables must have the same size" );
      throw;
    }
  }
  this->tables_.emplace_back( T | ranges::to_vector );
  return *this;
}
