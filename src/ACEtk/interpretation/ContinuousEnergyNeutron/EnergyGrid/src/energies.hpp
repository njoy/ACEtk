auto energies() const {
  return this->table.data.XSS( this->table.data.JXS( 1 ), this->size() );
}

auto energies( std::size_t index, std::size_t length ) const{
  return this->table.data.XSS(index, length);
}
