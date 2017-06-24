  Data( const std::array< std::pair< int, double >, 16 >& izaw,
        const std::array< int64_t, 16 >&              nxs,
        const std::array< int64_t, 32 >&              jxs,
        std::vector< double >&&                       xss ) :
    xss( std::move(xss) ), jxs( jxs ), nxs( nxs ), izaw( izaw ) {}

protected:
  template< typename Iterator >
  Data( State<Iterator>& state,
        const decltype(izaw)& izaw_,
        const decltype(nxs)& nxs_,
        const decltype(jxs)& jxs_ ) :
    Data( izaw_, nxs_, jxs_, Parse::XSS( state, nxs_[0] ) ){}
    
  template< typename Iterator >
  Data( State<Iterator>& state,
        const decltype(izaw)& izaw_,
        const decltype(nxs)& nxs_ ) :
    Data( state, izaw_, nxs_, Parse::JXS( state ) ){}
    
  template< typename Iterator >
  Data( State<Iterator>& state,
        const decltype(izaw)& izaw_ ) :
    Data( state, izaw_, Parse::NXS( state ) ){}
    
public:  
  template< typename Iterator >
  Data( State<Iterator>& state )
    try :
      Data( state, Parse::IZAW( state ) ){}
    catch( std::exception& e ) {
      Log::info("Error while constructing ACE Table Data");
      throw e;
    }
