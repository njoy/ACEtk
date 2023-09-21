void verifyDataIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->NSSH() ) ) {

    Log::error( "Illegal subshell index argument into the photoatomic table" );
    Log::info( "Index value: {}", index );
    Log::info( "The photoatomic table accepts an index between 1 and {} inclusively",
               this->NSSH() );
    throw std::out_of_range( "PhotoatomicTable" );
  }
}
