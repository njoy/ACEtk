template< typename Iterator >
Header201 parse( State< Iterator >& state ) {

  using Line1 = Record< Character< 10 >,
                        ColumnPosition< 1 >,
                        Character< 24 >,
                        ColumnPosition< 1 >,
                        Character< 24 > >;

  std::string szaid;
  std::string version;
  std::string source;

  Line1::read( state.position, state.end, version, szaid, source );
  ++state.lineNumber;

  if ( strip( version ) != "2.0.1" ) {

    Log::error( "The header version is not as expected" );
    Log::info( "Expected version: \'{}\'", "2.0.1" );
    Log::info( "Found version: \'{}\'", strip( version ) );
    throw std::exception();
  }

  using Line2 = Record< Scientific< 12, 6 >,
                        ColumnPosition< 1 >,
                        Scientific< 12, 6 >,
                        ColumnPosition< 1 >,
                        Character< 10 >,
                        ColumnPosition< 1 >,
                        Integer< 10 > >;

  double awr;
  double temp;
  std::string date;
  int number;

  Line2::read( state.position, state.end, awr, temp, date, number );
  ++state.lineNumber;

  if ( awr < 0.0 ) {

    Log::error("Encountered non-physical atomic weight ratio");
    throw std::exception();
  }

  if ( temp < 0.0 ) {

    Log::error("Encountered non-physical temperature");
    throw std::exception();
  }

  if ( number < 0 ) {

    Log::error("Encountered a negative number of comment lines");
    throw std::exception();
  }

  using Line = Record< Character< 80 > >;

  std::vector< std::string > comments;
  std::string line;
  auto notspace = [] ( char c ) { return !std::isspace( c ); };
  for ( unsigned int i = 0; i < static_cast< unsigned int >( number ); ++i ) {

    Line::read( state.position, state.end, line );
    auto back = std::find_if( line.rbegin(), line.rend(), notspace );
    line.erase( back.base(), line.end() );
    comments.push_back( line );
  }

  return  Header201( std::move( szaid ), std::move( source ), awr, temp,
                     std::move( date ), std::move( comments ) );
}
