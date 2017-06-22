protected:

template< typename Ostream >
void print( Ostream& ostream, Version< 2,0,1 > ) const {
  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );
  
  using Line1 = disco::Record< disco::Character<10>,     // Format
                               disco::ColumnPosition<1>,
                               disco::Character<24>,     // SZAID
                               disco::ColumnPosition<1>,
                               disco::Character<24> >;   // Source

  Line1::write( it,
                "     2.0.1",
                static_cast< const std::string& >( this->szaid ),
                this->source ?
                static_cast< const std::string& >( *(this->source) ) :
                std::string(24, ' ') );

  using Line2 = disco::Record< disco::FixedPoint<12,6>,   // AWR
                               disco::ColumnPosition<1>,
                               disco::Scientific<12,4>,   // temperature
                               disco::ColumnPosition<1>,
                               disco::Character<10>,      // processing date
                               disco::ColumnPosition<1>,
                               disco::Integer<4> >; // number of comments

  Line2::write( it,
                this->atomicWeightRatio,
                this->processTemperature.value,
                date::format( "%m-%d-%Y", this->processDate ),
                this->comments.size() );

  using CommentLine = disco::Record< disco::Character<70> >;
  for( const auto& comment : this->comments ){
    CommentLine::write( it, static_cast< const std::string& >(comment) );
  }
}

template< typename Ostream >
void print( Ostream& ostream, Version< 1,0,0 > ) const {
  auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

  using Line1 = disco::Record< disco::Character<10>,     // ZAID
                               disco::FixedPoint<12,6>,  // AWR
                               disco::Scientific<12,4>,  // temperature
                               disco::ColumnPosition<1>,
                               disco::Character<10> >;   // processing date

  Line1::write( it,
                static_cast< const std::string& >( this->szaid ),
                this->atomicWeightRatio,
                this->processTemperature.value,
                date::format( "%m/%d/%y", this->processDate ) );

  using Line2 = disco::Record< disco::Character<70>, disco::Character<10> >;
  auto empty = []( int size ){ return std::string(size, ' '); };
  Line2::write( it,
                this->comments.size() ? this->comments.front() : empty(70),
                this->mat ? *(this->mat) : empty(10) );
}

public:

template< int... values, typename Ostream >
void print( Ostream& ostream ) const {
  this->print( ostream, Version< values... >{} );
}
