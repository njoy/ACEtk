auto mu( ) const {
  const auto length = this->table.data.NXS( 3 ) * this->order;
  const auto start = this->start + this->table.data.NXS( 3 );
  return this->table.data.XSS( start, length )
    | ranges::view::chunk( this->order );  
}

auto cdf( ) const {
  const auto length = this->table.data.NXS( 3 ) * this->order;
  const auto start = this->start + this->table.data.NXS( 3 ) + length;
  return this->table.data.XSS( start, length )
    | ranges::view::chunk( this->order );    
}  
