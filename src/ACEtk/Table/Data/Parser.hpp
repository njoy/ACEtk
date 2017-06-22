struct Parse {

  template< typename Iterator >
  static auto
  IZAW( State<Iterator>& state ){
    std::array< std::pair< int, double > > result;

    using Line = Record< Integer<7>, Scientific<11, 0>,
                         Integer<7>, Scientific<11, 0>,
                         Integer<7>, Scientific<11, 0>,
                         Integer<7>, Scientific<11, 0> >;
  
    auto remainingLines = 4;
    auto begin = state.position;
    try{
      auto iterator = result.begin()
      while( remainingLines-- ){
        Line::read( state.position, state.end,
                    iterator[0].first, iterator[0].second,
                    iterator[1].first, iterator[1].second,
                    iterator[2].first, iterator[2].second,
                    iterator[3].first, iterator[3].second );
        std::advance( iterator, 4 );
        ++(state.lineNumber);
        begin = state.position;
      }
    } catch( std::exception& e ){
      Log::info("Error encountered while parsing IZAW block")
      utility::echoErroneousLine( begin, state.position,
                                  state.end, state.lineNumber );
      throw e;
    }
    return result;
  }

  template< typename Iterator >
  static auto
  NXS( State<Iterator>& state ){
    std::array< int64_t, 16 > result;

    using Line = Record< Integer<9>, Integer<9>,
                         Integer<9>, Integer<9>,
                         Integer<9>, Integer<9>,
                         Integer<9>, Integer<9> >;
  
    auto remainingLines = 2;
    auto begin = state.position;
    try{
      auto iterator = result.begin();
      while ( remainingLines-- ){
        Line::read( state.position, state.end,
                    iterator[0], iterator[1], iterator[2], iterator[3],
                    iterator[4], iterator[5], iterator[6], iterator[7] );
        std::advance( iterator, 8 );
        ++( state.lineNumber );
        begin = state.position;
      }
    } catch ( std::exception& e ){
      Log::info("Error encountered while parsing NXS block")
      utility::echoErroneousLine( begin, state.position,
                                  state.end, state.lineNumber );
      throw e;
    }
    return result;
  }

  template< typename Iterator >
  static auto
  JXS( State<Iterator>& state ){
    std::array< int64_t, 16 > result;

    using Line = Record< Integer<9>, Integer<9>,
                         Integer<9>, Integer<9>,
                         Integer<9>, Integer<9>,
                         Integer<9>, Integer<9> >;
  
    auto remainingLines = 4;
    auto begin = state.position;
    try{
      auto iterator = result.begin();
      while ( remainingLines-- ){
        Line::read( state.position, state.end,
                    iterator[0], iterator[1], iterator[2], iterator[3],
                    iterator[4], iterator[5], iterator[6], iterator[7] );
        std::advance( iterator, 8 );
        ++( state.lineNumber );
        begin = state.position;
      }
    } catch ( std::exception& e ){
      Log::info("Error encountered while parsing JXS block")
      utility::echoErroneousLine( begin, state.position,
                                  state.end, state.lineNumber );
      throw e;
    }
    return result;
  }

  template< typename Iterator >
  static auto
  XSS( State<Iterator>& state, const std::size_t size ){
    std::vector<double> result; result.resize( size, 0.0 );

    using Line = Record< Scientific< 20, 0 >,
                         Scientific< 20, 0 >,
                         Scientific< 20, 0 >,
                         Scientific< 20, 0 > >;
    auto remainingLines = size / 4;
    auto remainingEntries = size % 4;
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
      if ( remainingEntries ){
        while( remainingEntries-- ){
          *iterator++ =
            Scientific< 20, 0 >::read( state.position, state.end );
        }
        Record<>::read( state.position, state.end );
        ++( state.lineNumber );
      }
    } catch ( std::exception& e ){
      Log::info("Error encountered while parsing XSS block")
      utility::echoErroneousLine( begin, state.position,
                                  state.end, state.lineNumber );
      throw e;
    }
    return result;
  }
  
};
