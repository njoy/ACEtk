static void trim( std::string& string ) {

  // useful lambdas
  auto isNotSpace = [] ( const auto& c ) { return !std::isspace( c ); };

  // trim front and back whitespace
  string.erase( string.begin(),
                std::find_if( string.begin(), string.end(), isNotSpace ) );
  string.erase( std::find_if( string.rbegin(), string.rend(), isNotSpace ).base(),
                string.end() );
}

static void toLowerCase( std::string& string ) {

  std::transform( string.begin(), string.end(), string.begin(),
                  [] ( const auto& c ) { return std::tolower( c ); } );
}

static void trimToLowerCase( std::string& string ) {

  trim( string );
  toLowerCase( string );
}

static std::string getline( std::istream& in, std::istream::pos_type& position ) {

  // a line is a comment line if the first character on it is '#'
  auto isCommentLine = [] ( const auto& line ) {

    if ( line.size() > 0 ) {

      return line[0] == '#' ? true : false;
    }
    return false;
  };

  std::string current;

  position = in.tellg();
  std::getline( in, current );
  while ( isCommentLine( current ) ) {

    position = in.tellg();
    std::getline( in, current );
  }

  // trim the line and return it
  trim( current );
  return current;
}

static Xsdir parse( std::istream& in ) {

  auto position = in.tellg();
  std::string current;

  // read lines skipping over comment lines
  // and verify for the presence of a datapath
  std::optional< std::string > datapath = std::nullopt;
  current = getline( in, position );
  if ( current.size() != 0 ) {

    std::string path = current.substr( 0, 8 );
    toLowerCase( path );
    if ( path != "datapath" ) {

      in.clear();
      in.seekg( position );
      in.setstate( std::ios::failbit );

      Log::error( "Expected \'datapath\' but found \'{}\'", path );
      throw std::exception();
    }
    current = current.erase( 0, 8 );
    trim( current );
    if ( current.size() != 0 ) {

      if ( current[0] == '=' ) {

        current.erase( 0, 1 );
        if ( current.size() != 0 ) {

          datapath = current;
        }
      }
    }
  }

  // read a line and verify for the atomic weight ratios
  current = getline( in, position );
  toLowerCase( current );
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
  current = getline( in, position );
  while ( current != "directory" ) {

    //! @todo we do not verify duplicates or completeness
    std::istringstream input( current );
    while ( input >> za >> awr ) {

      ratios[ za ] = awr;
    }

    // read the next line
    current = getline( in, position );
    toLowerCase( current );
    if ( in.fail() ) {

      in.clear();
      in.seekg( position );
      in.setstate( std::ios::failbit );

      Log::error( "Unexpected error while reading atomic weights" );
      throw std::exception();
    }
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

    Log::error( "Something went wrong while reading an xsdir entry" );
    if ( entries.size() > 0 ) {

      Log::error( "Last entry read: {}", entries.back().ZAID() );
    }
    throw std::exception();
  }

  return Xsdir( std::move( ratios ), std::move( entries ),
                std::move( datapath ) );
}
