template< typename Iterator >
static Header parseLegacyHeader( State<Iterator>& state ) {

  using Line1 = Record< Character< 10 >,
                        Scientific< 12, 6 >,
                        Scientific< 12, 6 >,
                        ColumnPosition< 1 >,
                        Character< 10 > >;

  std::string zaid;
  double awr;
  double temp;
  std::string date;

  Line1::read( state.position, state.end, zaid, awr, temp, date );
  ++state.lineNumber;

  if ( awr < 0.0 ) {

    Log::error("Encountered non-physical atomic weight ratio");
    throw std::exception();
  }

  if ( temp < 0.0 ) {

    Log::error("Encountered non-physical temperature");
    throw std::exception();
  }

  using Line2 = Record< Character< 70 >, Character< 10 > >;

  std::string title;
  std::string material;

  Line2::read( state.position, state.end, title, material );
  ++state.lineNumber;

  return  Header( std::move( zaid ), awr, temp, std::move( date ),
                  std::move( title ), std::move( material ) );
}

template< typename Iterator >
static bool hasNewHeader( State< Iterator >& state ) {

  // read a line, reset state
  using Line = Record< Character< 80 > >;
  std::string line;
  auto begin = state.position;
  Line::read( state.position, state.end, line );
  state.position = begin;

  // extract the first substring
  std::istringstream input( line );
  std::string version;
  input >> version;

  // compare to regex
  const std::regex pattern( "\\s*\\d+\\.\\d+\\.\\d+\\s*" );
  return std::regex_match( version, pattern );
}

template< typename Iterator >
static Header parse( State< Iterator >& state ) {

  if ( !hasNewHeader( state ) ) {

    return parseLegacyHeader( state );
  }
  else {

    // skip two lines and read the number of comment lines that follow
    using Line = Record< Character< 80 > >;
    std::string line;
    Line::read( state.position, state.end, line );
    Line::read( state.position, state.end, line );
    std::istringstream input( line );
    std::string temp;
    unsigned int number;
    input >> temp >> temp >> temp >> number;

    // skip all but the last two lines
    for ( unsigned int i = 0; i < number - 2; ++i ) {

      Line::read( state.position, state.end, line );
    }

    // parse the legacy header
    return parseLegacyHeader( state );
  }
}
