/**
 *  @brief operator>> for an xsdir
 *
 *  @param[in] in       the input stream
 *  @param[in] entry    the xsdir
 *
 *  @return the input stream
 */
inline std::istream &operator>>( std::istream& in, Xsdir& xsdir ) {

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
  }

  // read entries from this point forward
  XsdirEntry entry;
  std::vector< XsdirEntry > entries;
  while ( in >> entry ) {

    entries.emplace_back( std::move( entry ) );
  }

  xsdir = Xsdir( std::move( entries ) );
  
  return in;
}

/**
 *  @brief operator<< for an xsdir
 *
 *  @param[in] in       the output stream
 *  @param[in] xsdir    the xsdir
 *
 *  @return the input stream
 */
//inline std::ostream &operator<<( std::ostream& out, Xsdir& xsdir ) {
//
//  xsdir.print( out );
//  return out;
//}
