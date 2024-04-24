auto totalCrossSection( ) const {
  const auto length = this->table.data().NXS( 4 );
  return
    this->table.data().XSS( this->start, length )
    | ranges::cpp20::views::transform( []( auto&& entry )
			       { return entry * centi( meters ) * centi( meters ); } );
}
