template< typename Iterator >
static Header parseLegacy( State<Iterator>& state ) {

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
static Header parse( State< Iterator >& state ) {

  auto begin = state.position;

  std::string firstField;
  Record< Character<10>, RetainCarriage >::read( state.position, state.end,
					                                       firstField );

  const std::regex versionPattern( "\\s*\\d+\\.\\d+\\.\\d+\\s*" );
  if ( !std::regex_match( firstField, versionPattern ) ) {

    state.position = begin;
    return parseLegacy( state );
  }
  else {

    // skip two lines
    using Line = Record< Character< 80 > >;
    std::string comment;
    state.position = begin;
    Line::read( state.position, state.end, comment );
    Line::read( state.position, state.end, comment );

    return parseLegacy( state );
  }
}

template< typename Iterator >
static Header parse( State< Iterator >&& state ) {

  return parse( state );
}
