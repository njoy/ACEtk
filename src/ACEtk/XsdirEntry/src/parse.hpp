template < typename Istream >
static XsdirEntry parse( Istream& in ) {

  auto position = in.tellg();

  // read a line and verify for continue on the next line
  std::string line;
  std::string next;
  std::getline( in, line );
  auto iter = std::find_if( line.rbegin(), line.rend(),
                            [] ( char c )
                               { return !std::isspace( c ); } );

  while ( *iter == '+' ) {

    *iter = ' ';
    std::getline( in, next );
    line += next;
    iter = std::find_if( line.rbegin(), line.rend(),
                         [] ( char c )
                            { return !std::isspace( c ); } );
  }

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

  if ( !xsdir.fail() ) {

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

    in.clear();
    in.seekg( position );
    in.setstate( std::ios::failbit );

    Log::info( "Error encountered while parsing an xsdir entry from a stream" );
    throw std::exception();
  }
}
