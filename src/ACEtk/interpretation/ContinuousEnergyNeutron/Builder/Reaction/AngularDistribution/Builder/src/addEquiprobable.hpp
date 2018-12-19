Builder& addEquiprobable( Equiprobable&& equi ){
  this->representations_.emplace_back( std::move( equi ) );
  return *this;
}

