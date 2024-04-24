static void trim( std::string& string ) {

  // useful lambdas
  auto isNotSpace = [] ( const auto& c ) { return !std::isspace( c ); };

  // trim front and back whitespace
  string.erase( string.begin(),
                std::find_if( string.begin(), string.end(), isNotSpace ) );
  string.erase( std::find_if( string.rbegin(), string.rend(), isNotSpace ).base(),
                string.end() );
}

static std::string getline( std::istream& in ) {

  // a line is a comment line if the first character on it is '#'
  auto isCommentLine = [] ( const auto& line ) {

    if ( line.size() > 0 ) {

      return line[0] == '#' ? true : false;
    }
    return false;
  };

  std::string current;

  std::getline( in, current );
  while ( isCommentLine( current ) ) {

    std::getline( in, current );
  }

  // trim the line and return it
  trim( current );
  return current;
}

static XsdirEntry parse( std::istream& in ) {

  auto position = in.tellg();

  // read a line and verify for continue on the next line
  std::string line;
  std::string next;

  line = getline( in );
  while ( line.back() == '+' ) {

    line.back() = ' ';
    next = getline( in );
    line += next;
  }

  if ( !in.eof() ) {

    // data to be read
    std::string zaid;
    double awr;
    std::string filename;
    std::string access;
    unsigned int filetype;
    unsigned int address;
    unsigned int length;
    unsigned int recordlength = 0;
    unsigned int entries = 0;
    double temperature = 0.;
    bool ptable = false;

    // read minimum of 7 entries, then read 3 more and a string after that
    std::istringstream xsdir( line );
    xsdir >> zaid >> awr >> filename >> access >> filetype >> address >> length;
    if ( !xsdir.fail() ) {

      // read the next 3 or 4 entries
      if ( xsdir >> recordlength ) {

        xsdir >> entries >> temperature;
        if ( !xsdir.fail() ) {

          xsdir >> next;
          if ( xsdir.fail() ) {

            xsdir.clear();
          }
          else {

            if ( next == "ptable" ) {

              ptable = true;
            }
            else {

              xsdir.setstate( std::ios::failbit );
            }
          }
        }
      }
      else {

        xsdir.clear();
      }
    }

    if ( xsdir.fail() ) {

      in.clear();
      in.seekg( position );
      in.setstate( std::ios::failbit );

      Log::error( "Something went wrong while reading an xsdir entry" );
      throw std::exception();
    }

    return XsdirEntry( std::move( zaid ), awr, std::move( filename ),
                       filetype, address, length,
                       access == "0"
                         ? std::nullopt
                         : std::optional< std::string >( std::move( access ) ),
                       recordlength == 0
                         ? std::nullopt
                         : std::optional< unsigned int >( recordlength ),
                       entries == 0
                         ? std::nullopt
                         : std::optional< unsigned int >( entries ),
                       temperature == 0
                         ? std::nullopt
                         : std::optional< double >( temperature ),
                       ptable );
  }
  else {

    Log::error( "Expected an additional line but found the end of stream" );
    throw std::exception();
  }
}
