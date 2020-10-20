Builder&
addTable( Table&& table ){
  if( this->tables_.size() > 0 ){
    try {
      details::verify::equalSize( this->tables_[ 0 ].CDFs, table.CDFs );
    } catch( std::range_error& ){
      Log::info( "The length of the probability table (M) must be the same "
                "for each table." );
      throw;
    }
  }

  this->tables_.emplace_back( std::move( table ) );
  return *this;
}
