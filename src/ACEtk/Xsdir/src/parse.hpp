static Xsdir parse( std::istream& in ) {

  auto position = in.tellg();

  // useful lambdas
  auto isNotSpace = [] ( const auto& c ) { return !std::isspace( c ); };
  auto toLower = [] ( const auto& c ) { return std::tolower( c ); };

  // read a line and verify for directory
  std::string directory;
  std::getline( in, directory );
  directory.erase( directory.begin(),
                   std::find_if( directory.begin(), directory.end(), isNotSpace ) );
  directory.erase( std::find_if( directory.rbegin(), directory.rend(),
                                 isNotSpace ).base(),
                   directory.end() );
  std::transform( directory.begin(), directory.end(), directory.begin(), toLower );
  if ( directory != "directory" ) {

    in.clear();
    in.seekg( position );
    in.setstate( std::ios::failbit );

    Log::error( "Expected \'directory\' but found \'{}\'", directory );
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

  return Xsdir( std::move( entries ) );
}
