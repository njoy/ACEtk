template< typename Ostream >
void print( Ostream& ostream ) const {

  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

  using Line1 = disco::Record< disco::Character< 10 >,
                               disco::FixedPoint< 12, 6>,
                               disco::Scientific< 12, 4 >,
                               disco::ColumnPosition< 1 >,
                               disco::Character< 10 > >;

  Line1::write( it, right( this->zaid_, 10 ), this->awr_, this->temp_,
                right( this->date_, 10 ) );

  using Line2 = disco::Record< disco::Character< 80 > >;
  Line2::write( it, this->comments_[0] );
}
