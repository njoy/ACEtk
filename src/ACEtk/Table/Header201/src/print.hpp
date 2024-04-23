template< typename Ostream >
void print( Ostream& ostream ) const {

  using namespace njoy::tools::disco;

  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

  using Line1 = Record< Character< 10 >,
                        Column< 1 >,
                        Character< 24 >,
                        Column< 1 >,
                        Character< 24 > >;

  Line1::write( it, left( this->version(), 10 ),
                    right( this->ZAID(), 24 ),
                    right( this->source(), 24 ) );

  using Line2 = Record< FixedPoint< 12, 6 >,
                        Column< 1 >,
                        Scientific< 12, 4 >,
                        Column< 1 >,
                        Character< 10 >,
                        Column< 1 >,
                        Integer< 10 > >;

  Line2::write( it, this->AWR(), this->TEMP(),
                right( this->date(), 10 ), this->comments().size() );

  for ( auto&& line : this->comments() ) {

    ostream << line << std::endl;
  }
}
