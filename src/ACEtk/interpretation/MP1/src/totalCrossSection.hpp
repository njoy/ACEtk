auto totalCrossSection( ) const {
  const auto length = this->table.data.NXS( 3 );
  return
    this->table.data.XSS( this->start, length )
    | ranges::view::transform( []( auto&& entry )
			       { return entry * centi( meters ) * centi( meters ); } );    
}

