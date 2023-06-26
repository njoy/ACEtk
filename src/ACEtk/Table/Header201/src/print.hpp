template< typename Ostream >
void print( Ostream& ostream ) const {

  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

  using Line1 = disco::Record< disco::Character< 10 >,
                               disco::ColumnPosition< 1 >,
                               disco::Character< 24 >,
                               disco::ColumnPosition< 1 >,
                               disco::Character< 24 > >;

  Line1::write( it, left( this->version(), 10 ),
                    right( this->ZAID(), 24 ),
                    right( this->source(), 24 ) );

  using Line2 = Record< disco::FixedPoint< 12, 6 >,
                        disco::ColumnPosition< 1 >,
                        disco::Scientific< 12, 4 >,
                        disco::ColumnPosition< 1 >,
                        disco::Character< 10 >,
                        disco::ColumnPosition< 1 >,
                        disco::Integer< 10 > >;

  Line2::write( it, this->AWR(), this->TEMP(),
                right( this->date(), 10 ), this->comments().size() );

  for ( auto&& line : this->comments() ) {

    ostream << line << std::endl;
  }
}
