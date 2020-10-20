Builder& addTabulated( Tabulated&& tab ){
  this->representations_.emplace_back( std::move( tab ) );
  return *this;
}
