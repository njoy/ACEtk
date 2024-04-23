template< typename Iterator, typename IZrange, typename AWrange>
static void
IZAW( State<Iterator>& state, IZrange& izrange, AWrange& awrange ) {

  using namespace njoy::tools::disco;

  using Line = Record< Integer<7>, Scientific<11, 0>,
                       Integer<7>, Scientific<11, 0>,
                       Integer<7>, Scientific<11, 0>,
                       Integer<7>, Scientific<11, 0> >;

  auto remainingLines = 4;
  auto begin = state.position;
  try {

    auto first = std::begin( izrange );
    auto second = std::begin( awrange );
    while( remainingLines-- ) {

      Line::read( state.position, state.end,
                  first[0], second[0],
                  first[1], second[1],
                  first[2], second[2],
                  first[3], second[3] );
      std::advance( first, 4 );
      std::advance( second, 4 );
      ++(state.lineNumber);
      begin = state.position;
    }
  }
  catch( std::exception& e ) {

    Log::error( "Error encountered while parsing IZAW block on line {}", state.lineNumber );
    Log::info( "Data: {}", std::string( begin, std::find( state.position, state.end, '\n') ) );
    throw e;
  }
}

template< typename Iterator >
static auto
IZAW( State<Iterator>& state ) {

  std::pair< std::array< int32_t, 16 >,
             std::array< double, 16 > > result;
  IZAW( state, result.first, result.second );
  return result;
}
