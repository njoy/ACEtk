auto totalCrossSection( size_t numberOfAngles ) const {
  const auto length = this->table.data.NXS( 3 );
  const auto start  = this->table.data.JXS( this->ACEptr.find( numberOfAngles )->second );
  return
    this->table.data.XSS( start, length )
    | ranges::view::transform( []( auto&& entry )
			       { return entry * centi( meters ) * centi( meters ); } );    
}

