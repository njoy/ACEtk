static void trimToLowerCase( std::string string ) {

  // useful lambdas
  auto isNotSpace = [] ( const auto& c ) { return !std::isspace( c ); };
  auto toLower = [] ( const auto& c ) { return std::tolower( c ); };

  // trim front and back whitespace
  string.erase( string.begin(),
                std::find_if( string.begin(), string.end(), isNotSpace ) );
  string.erase( std::find_if( string.rbegin(), string.rend(), isNotSpace ).base(),
                string.end() );

  // to lower case
  std::transform( string.begin(), string.end(), string.begin(), toLower );
}

static Xsdir parse( std::istream& in ) {

  auto position = in.tellg();
  std::string current;

  // read a line and verify for the atomic weight ratios
  std::getline( in, current );
  trimToLowerCase( current );
  if ( current != "atomic weight ratios" ) {

    in.clear();
    in.seekg( position );
    in.setstate( std::ios::failbit );

    Log::error( "Expected \'atomic weight ratios\' but found \'{}\'", current );
    throw std::exception();
  }

  // read ZA, AWR pairs
  unsigned int za;
  double awr;
  std::map< unsigned int, double > ratios;
  while ( in >> za >> awr ) {

    //! @todo we do not verify duplicates or completeness
    ratios[ za ] = awr;
  }
  in.clear();

  // read a line and verify for directory
  std::getline( in, current );
  trimToLowerCase( current );
  if ( current != "directory" ) {

    in.clear();
    in.seekg( position );
    in.setstate( std::ios::failbit );

    Log::error( "Expected \'directory\' but found \'{}\'", current );
    throw std::exception();
  }

  // read entries from this point forward
  XsdirEntry entry;
  std::vector< XsdirEntry > entries;
  while ( in >> entry ) {

    entries.emplace_back( std::move( entry ) );
  }

  if ( !in.eof() ) {

    in.clear();
    in.seekg( position );
    in.setstate( std::ios::failbit );
  }

  return Xsdir( std::move( ratios ), std::move( entries ) );
}
