static std::string strip( const std::string& string ) {

  std::string result = string;
  auto notspace = [] ( char c ) { return !std::isspace( c ); };

  auto front = std::find_if( result.begin(), result.end(), notspace );
  result.erase( result.begin(), front );
  auto back = std::find_if( result.rbegin(), result.rend(), notspace );
  result.erase( back.base(), result.end() );
  return result;
}

static std::string left( const std::string& string, std::size_t length ) {

  std::string result = string;
  result.resize( length, ' ' );
  return result;
}

static std::string right( const std::string& string, std::size_t length ) {

  std::string result = string;
  const auto pivot = result.size();
  result = left( result, length );
  std::rotate( result.begin(),
               std::next( result.begin(), pivot ),
               result.end() );
  return result;
}
