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

static Xsdir parse( std::istream& in ) {

  auto position = in.tellg();
  std::string current;

  // read a line and verify for the datapath
  std::optional< std::string > datapath = std::nullopt;
  std::getline( in, current );
  trim( current );
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

  // read lines till you find the directory
  while ( current != "directory" ) {

    std::getline( in, current );
    trimToLowerCase( current );
    if ( in.fail() ) {

      in.clear();
      in.seekg( position );
      in.setstate( std::ios::failbit );

      Log::error( "Could not find \'directory\' in the xsdir file" );
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
