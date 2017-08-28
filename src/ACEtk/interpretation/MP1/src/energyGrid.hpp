auto energyGrid() const {
  const auto length = this->table.data.NXS( 3 );
  const auto start  = this->table.data.JXS( 1 );
  return
    this->table.data.XSS( start, length )
    | ranges::view::transform( []( auto&& entry )
			       { return entry * mega(electronVolt); } );
}  
