  Data() = default;
  Data( const decltype(izaw)& izaw_,
        const decltype(nxs)& nxs_,
        const decltype(jxs)& jxs_,
        decltype(xss)&& xss_ ) :
    xss( std::move(xss_) ), jxs( jxs_ ), nxs( nxs_ ), izaw( izaw_ ) {}

protected:
  template< typename Iterator >
  Data( State<Iterator>& state,
        const decltype(izaw)& izaw_,
        const decltype(nxs)& nxs_,
        const decltype(jxs)& jxs_ ) :
    Data( izaw_, nxs_, jxs_, Parse::XSS( state, int64_t{nxs_[0]} ) ){}

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
