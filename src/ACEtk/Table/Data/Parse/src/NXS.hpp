template< typename Iterator, typename Range >
static auto
NXS( State<Iterator>& state, Range& result ) {

  using namespace njoy::tools::disco;

  using Line = Record< Integer<9>, Integer<9>,
                       Integer<9>, Integer<9>,
                       Integer<9>, Integer<9>,
                       Integer<9>, Integer<9> >;

  auto remainingLines = 2;
  auto begin = state.position;
  try {

    auto iterator = result.begin();
    while ( remainingLines-- ) {

      Line::read( state.position, state.end,
                  iterator[0], iterator[1], iterator[2], iterator[3],
                  iterator[4], iterator[5], iterator[6], iterator[7] );
      std::advance( iterator, 8 );
      ++( state.lineNumber );
      begin = state.position;
    }
  }
  catch ( std::exception& e ) {

    Log::error( "Error encountered while parsing NXS block on line {}", state.lineNumber );
    Log::info( "Data: {}", std::string( begin, std::find( state.position, state.end, '\n') ) );
    throw e;
  }
}

template< typename Iterator >
static auto
NXS( State<Iterator>& state ) {

  std::array< int64_t, 16 > result;
  NXS( state, result );
  return result;
}
