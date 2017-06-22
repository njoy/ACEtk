template< typename Iterator >
static auto
IZAW( State<Iterator>& state ){
  std::array< std::pair< int, double >, 16 > result;

  using Line = Record< Integer<7>, Scientific<11, 0>,
		       Integer<7>, Scientific<11, 0>,
		       Integer<7>, Scientific<11, 0>,
		       Integer<7>, Scientific<11, 0> >;
  
  auto remainingLines = 4;
  auto begin = state.position;
  try{
    auto iterator = result.begin();
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
  } catch( std::exception& e ) {
    Log::info("Error encountered while parsing IZAW block");
    utility::echoErroneousLine( begin, state.position,
				state.end, state.lineNumber );
    throw e;
  }
  return result;
}
