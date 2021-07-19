template< typename Iterator, typename Range,
          utility::Require<true, utility::is_range, Range> = true >
static void
XSS( State<Iterator>& state, Range& result ) {

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

    Log::info("Error encountered while parsing XSS block");
    utility::echoErroneousLine( begin, state.position,
                                state.end, state.lineNumber );
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
