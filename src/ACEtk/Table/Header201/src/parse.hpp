template< typename Iterator >
Header201 parse( State< Iterator >& state ) {

  using namespace njoy::tools::disco;

  using Line1 = Record< Character< 10 >,
                        Column< 1 >,
                        Character< 24 >,
                        Column< 1 >,
                        Character< 24 > >;

  std::string szaid;
  std::string version;
  std::string source;

  Line1::read( state.position, state.end, version, szaid, source );
  ++state.lineNumber;

  version = strip( version );
  if ( ( version != "2.0.0" ) && ( version != "2.0.1" ) ) {

    Log::error( "The header version is not as expected" );
    Log::info( "Expected version 2.0.0 or 2.0.1" );
    Log::info( "Found version: \'{}\'", strip( version ) );
    throw std::exception();
  }

  using Line = Record< Character< 80 > >;

  double awr;
  double temp;
  std::string date;
  int number;

  std::string line;
  Line::read( state.position, state.end, line );
  std::istringstream input( line );
  input >> awr >> temp >> date >> number;

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

  std::vector< std::string > comments;
  auto notspace = [] ( char c ) { return !std::isspace( c ); };
  for ( unsigned int i = 0; i < static_cast< unsigned int >( number ); ++i ) {

    Line::read( state.position, state.end, line );
    auto back = std::find_if( line.rbegin(), line.rend(), notspace );
    line.erase( back.base(), line.end() );
    comments.push_back( line );
  }

  return  Header201( std::move( version ), std::move( szaid ),
                     std::move( source ), awr, temp,
                     std::move( date ), std::move( comments ) );
}
