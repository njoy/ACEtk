protected:

template< typename Iterator >
static Header parse( Version<1,0,0>,
                     SZAID&& szaid,
                     State<Iterator>& state ){
  
  auto begin = std::prev( state.position, 10 );

  try{
    using Line1 = Record< Scientific<12,6>,
                          Scientific<12,6>,
                          ColumnPosition<1>,
                          Character<10> >;

    double atomicWeightRatio;
    double temperature;
    std::string dateString;
    
    Line1::read( state.position, state.end,
                 atomicWeightRatio, temperature, dateString );
    
    if ( atomicWeightRatio < 0.0 ){
      state.position = std::next( begin, 10 );
      auto fieldEnd = std::next( state.position, 12 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered non-physical atomic weight ratio");
      throw std::exception();
    }

    if ( temperature < 0.0 ){
      state.position = std::next( begin, 22 );
      auto fieldEnd = std::next( state.position, 12 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered non-physical temperature");
      throw std::exception();
    }
    
    if ( not std::regex_match( dateString,
                               std::regex( "\\s*[[:d:]]{2}"    // month
                                           "[-/][[:d:]]{2}"    // day
                                           "[-/][[:d:]]{2,4}", // year
                                           std::regex::optimize
                                           | std::regex::nosubs ) ) ){
      state.position = std::next( begin, 34 );
      auto fieldEnd = std::next( state.position, 10 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered unrecognized date format");
      Log::info("The date field is required to be in one of the following formats:\n"
                "    MM-DD-YY\n"
                "    MM-DD-YYYY\n"
                "    MM/DD/YY\n"
                "    MM/DD/YYYY");
      throw std::exception();
    }
    
    const auto date = [&]{
      std::regex integer("[[:d:]]+");

      std::regex_iterator<std::string::iterator>
      fields( dateString.begin(), dateString.end(), integer );
      
      const int m = std::stoi( fields->str() ); ++fields;
      const int d = std::stoi( fields->str() ); ++fields;
      const int y = [&]{
        auto yr = std::stoi( fields->str() );
        return yr > 100 ? yr :
               yr > 70  ? yr + 1900 : yr + 2000;
        }();
      return date::year{y}/m/d;
    }();

    if ( not date.ok() ){
      state.position = std::next( begin, 34 );
      auto fieldEnd = std::next( state.position, 10 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered invalid date");
      throw std::exception();
    }
    begin = state.position;
    ++state.lineNumber;
    
    using Line2 = Record< Character<70>, Character<10> >;
    std::string comment; 
    std::string mat;
    
    Line2::read( state.position, state.end, comment, mat );
    ++state.lineNumber;
    
    return [&]{
      Header header( date,
                     temperature * mega(electronVolts),
                     atomicWeightRatio,
                     SZAID( std::move(szaid) ),
                     std::vector< Comment >{ Comment(std::move(comment)) } );
      header.mat = MAT(mat);
      return header;
    }(); // allow for return value optimization
  } catch ( std::exception& e ){
    utility::echoErroneousLine( begin, state.position, state.end, state.lineNumber );
    throw e;
  }
}

template< typename Iterator >
static Header parse( Version<2,0,1>, State<Iterator>& state ){
  auto trim = []( auto& s ){
    auto begin = std::find_if( s.begin(), s.end(),
			       []( auto&& c ){ return not std::isspace(c); } );
    auto end = std::find_if( s.rbegin(), s.rend(),
			     []( auto&& c ){ return not std::isspace(c); } ).base();
    return std::decay_t<decltype(s)>( begin, end );
  };
  
  auto begin = std::prev( state.position, 10 );
  try{
    std::string source;
    const SZAID szaid = [&]{
      std::string sink;
      using Line1 =
        Record< ColumnPosition< 1 >, Character< 24 >,
                ColumnPosition< 1 >, Character< 24 > >;
      Line1::read( state.position, state.end, sink, source );
      return trim(sink);
    }();
    begin = state.position;
    ++state.lineNumber;
    
    double atomicWeightRatio;
    double temperature;
    std::string dateString;
    int nCommentLines;
    using Line2 =
      Record< Scientific< 12, 6 >, ColumnPosition< 1 >,
              Scientific< 12, 6 >, ColumnPosition< 1 >,
              Character< 10 >, ColumnPosition< 1 >,
              Integer< 4 > >;

    Line2::read
      ( state.position, state.end,
        atomicWeightRatio, temperature, dateString, nCommentLines );

    if ( atomicWeightRatio < 0.0 ){
      state.position = begin;
      auto fieldEnd = std::next( state.position, 12 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered non-physical atomic weight ratio");
      throw std::exception();
    }

    if ( temperature < 0.0 ){
      state.position = std::next( begin, 13 );
      auto fieldEnd = std::next( state.position, 12 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered non-physical temperature");
      throw std::exception();
    }

    if ( not std::regex_match( dateString,
                               std::regex( "\\s*[[:d:]]{4}"  // year
                                           "[-/][[:d:]]{2}"  // month
                                           "[-/][[:d:]]{2}", // day
                                           std::regex::optimize
                                           | std::regex::nosubs ) ) ){
      state.position = std::next( begin, 26 );
      auto fieldEnd = std::next( state.position, 10 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered unrecognized date format");
      Log::info("The date field is required to be in one of the following formats:\n"
                "    YYYY-MM-DD\n"
                "    YYYY/MM/DD");
      throw std::exception();
    }

    const auto date = [&]{
      std::regex integer("[[:d:]]+");

      std::regex_iterator<std::string::iterator>
      fields( dateString.begin(), dateString.end(), integer );
      
      const int y = std::stoi( fields->str() ); ++fields;
      const int m = std::stoi( fields->str() ); ++fields;
      const int d =  std::stoi( fields->str() );
      return date::year{y}/m/d;
    }();

    if ( not date.ok() ){
      state.position = std::next( begin, 26 );
      auto fieldEnd = std::next( state.position, 10 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("Encountered invalid date");
      throw std::exception();
    }
    
    if ( nCommentLines < 0 ){
      state.position = std::next( begin, 37 );
      auto fieldEnd = std::next( state.position, 4 );
      state.position =
        std::find_if_not( state.position, fieldEnd,
                          []( auto ch ){ return ch == ' '; } );
      Log::error("The number of comment lines must be non-negative");
      throw std::exception();
    }
    begin = state.position;
    ++state.lineNumber;

    std::vector< Comment > comments; comments.reserve( nCommentLines );
    using CommentLine = Record< Character< 70 > >;
    while ( nCommentLines-- ){
      std::string comment;
      CommentLine::read( state.position, state.end, comment );
      comments.emplace_back( std::move(comment) );
      begin = state.position;
      ++state.lineNumber;
    }

    return [&]{ 
      Header header( date,
		     temperature * mega(electronVolts),
		     atomicWeightRatio,
		     SZAID( std::move(szaid) ),
		     std::move(comments) );
      header.source = Source(source);
      return header;
    }();
  } catch ( std::exception& e ){
    utility::echoErroneousLine( begin,
				state.position, state.end, state.lineNumber );
    throw e;
  }
}

template< int... values, typename... Args >
static Header parse( Args&&... args ){
  return parse( Version<values...>(), std::forward<Args>(args)... );
}

public:

template< typename Iterator >
static Header parse( State<Iterator>& state ){
  const auto begin = state.position;
  
  try {
    std::string firstField;
    Record< Character<10>, RetainCarriage >::read( state.position,
						   state.end,
						   firstField );
    {
      const std::regex 
      versionPattern( "\\s*[[:d:]]+\\.[[:d:]]+\\.[[:d:]]+",
                      std::regex::optimize|std::regex::nosubs ); 

      if ( not std::regex_match( firstField, versionPattern ) ){
        return parse<1,0,0>( SZAID( std::move(firstField) ), state );
      }
    }

    const std::array<int, 3> version = [&]{
      auto regex = std::regex("[[:d:]]+");
      auto field =[ iterator = std::sregex_iterator( firstField.begin(),
						     firstField.end(),
						     regex ) ]
      () mutable {
	const auto sub = std::stoi( iterator->str() );
	++iterator;
        return sub;
      };
      const auto major = field();
      const auto minor = field();
      const auto revision = field();
      return std::array<int, 3>{{ major, minor, revision }};
    }();
    
    if ( version == std::array<int, 3>{{2,0,1}} ){
      return parse<2,0,1>( state );
    }
    
    const auto fieldEnd = std::next( begin, 10 );
    state.position = std::find_if_not( begin, fieldEnd,
				       []( auto ch ){ return ch == ' '; } );

    Log::error("Unrecognized version number");
    utility::echoErroneousLine( begin,
				state.position, state.end, state.lineNumber );
    Log::info("Permitted version numbers:\n"
	      "    1.0.0\n"
	      "    2.0.1");
    throw std::exception();
  } catch ( std::exception& e){
    Log::info("Error while parsing ACE Table Header");
    throw e;
  }
}
