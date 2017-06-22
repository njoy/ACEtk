template< typename Iterator >
static auto
JXS( State<Iterator>& state ){
  std::array< int64_t, 32 > result;

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
  } catch ( std::exception& e ) {
    Log::info("Error encountered while parsing JXS block");
    utility::echoErroneousLine( begin, state.position,
				state.end, state.lineNumber );
    throw e;
  }
  return result;
}
