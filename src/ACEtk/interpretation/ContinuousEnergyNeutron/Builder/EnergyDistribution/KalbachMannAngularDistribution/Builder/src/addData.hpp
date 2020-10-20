Builder& addData( Data&& data ){
  data_.emplace_back( std::move( data ) );
  return *this;
}
