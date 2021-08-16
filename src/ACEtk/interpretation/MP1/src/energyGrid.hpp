auto energyGrid() const {
  const auto length = this->table.data().NXS( 4 );
  const auto start  = this->table.data().JXS( 2 );
  return
    this->table.data().XSS( start, length )
    | ranges::cpp20::views::transform( []( auto&& entry )
			       { return entry * mega(electronVolt); } );
}
