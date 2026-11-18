struct Parse {

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

template< typename Iterator, typename Range >
static void
JXS( State<Iterator>& state, Range& result ) {

  using namespace njoy::tools::disco;

  using Line = Record< Integer<9>, Integer<9>,
                       Integer<9>, Integer<9>,
                       Integer<9>, Integer<9>,
                       Integer<9>, Integer<9> >;

  auto remainingLines = 4;
  auto begin = state.position;
  try {

    auto iterator = result.begin();
    while ( remainingLines-- ){
      Line::read( state.position, state.end,
                  iterator[0], iterator[1], iterator[2], iterator[3],
                  iterator[4], iterator[5], iterator[6], iterator[7] );
      std::advance( iterator, 8 );
      ++( state.lineNumber );
      begin = state.position;
    }
  }
  catch ( std::exception& e ) {

    Log::error( "Error encountered while parsing JXS block on line {}", state.lineNumber );
    Log::info( "Data: {}", std::string( begin, std::find( state.position, state.end, '\n') ) );
    throw e;
  }
}


template< typename Iterator >
static auto
JXS( State<Iterator>& state ) {

  std::array< int64_t, 32 > result;
  JXS( state, result );
  return result;
}

template< typename Iterator, typename Range >
static void
XSS( State<Iterator>& state, Range& result ) {

  using namespace njoy::tools::disco;

  using Line = Record< Scientific< 20, 0 >,
                       Scientific< 20, 0 >,
                       Scientific< 20, 0 >,
                       Scientific< 20, 0 > >;

  auto remainingLines = result.size() / 4;
  auto remainingEntries = result.size() % 4;
  auto begin = state.position;
  auto iterator = result.begin();
  try {

    while ( remainingLines-- ) {

      Line::read( state.position, state.end,
                  iterator[0], iterator[1], iterator[2], iterator[3] );
      std::advance( iterator, 4 );
      ++( state.lineNumber );
      begin = state.position;
    }
    if ( remainingEntries ) {

      while( remainingEntries-- ) {

        *iterator++ =
          Scientific< 20, 0 >::read( state.position, state.end );
      }
      Record<>::read( state.position, state.end );
      ++( state.lineNumber );
    }
  }
  catch ( std::exception& e ) {

    Log::error( "Error encountered while parsing XSS block on line {}", state.lineNumber );
    Log::info( "Data: {}", std::string( begin, std::find( state.position, state.end, '\n') ) );

    throw e;
  }
}

template< typename Iterator >
static auto
XSS( State<Iterator>& state, const std::int64_t size ) {

  std::vector<double> result;
  result.resize( size );
  XSS( state, result );
  return result;
}

};
