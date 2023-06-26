template< typename Iterator >
static std::string readVersion( State< Iterator >& state ) {

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
  return version;
}

template< typename Iterator >
static HeaderVariant parse( State< Iterator >& state ) {

  std::string version = readVersion( state );
  if ( ( version == "2.0.0" ) || ( version == "2.0.1" ) ) {

    return Header201( state );
  }
  else{

    return Header( state );
  }
}
