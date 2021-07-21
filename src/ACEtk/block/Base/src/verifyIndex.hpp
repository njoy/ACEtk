void verifyIndex( const std::size_t index ) const {

  if ( ( index < 1 ) || ( index > this->length_ ) ) {

    Log::error( "Illegal relative index argument into {} block", this->name_ );
    Log::info( "Index value: {}", index );
    Log::info( "{} may be indexed with values between 1 and {} inclusively",
               this->name_, this->length_ );
    throw std::out_of_range( this->name_ );
  }
}
