template< typename Ostream >
void print( Ostream& ostream ) const {

  using namespace njoy::tools::disco;

  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

  using Line1 = Record< Character< 10 >,
                        FixedPoint< 12, 6>,
                        Scientific< 12, 4 >,
                        Column< 1 >,
                        Character< 10 > >;

  Line1::write( it, right( this->ZAID(), 10 ), this->AWR(), this->TEMP(),
                right( this->date(), 10 ) );

  using Line2 = Record< Character< 70 >, Character< 10 > >;
  Line2::write( it, left( this->title(), 70 ), right( this->material(), 10 ) );
}
