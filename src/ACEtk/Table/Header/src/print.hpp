template< typename Ostream >
void print( Ostream& ostream ) const {

  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

  using Line1 = disco::Record< disco::Character< 10 >,
                               disco::FixedPoint< 12, 6>,
                               disco::Scientific< 12, 4 >,
                               disco::ColumnPosition< 1 >,
                               disco::Character< 10 > >;

  Line1::write( it, right( this->ZAID(), 10 ), this->AWR(), this->TEMP(),
                right( this->date(), 10 ) );

  using Line2 = disco::Record< disco::Character< 70 >, disco::Character< 10 > >;
  Line2::write( it, left( this->title(), 70 ), right( this->material(), 10 ) );
}
