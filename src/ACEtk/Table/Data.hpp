class Data {
private:
  std::vector< double > xss;
  std::array< int64_t, 32 > jxs;
  std::array< int64_t, 16 > nxs;
  std::array< std::pair< int, double >, 16 > izaw;
  
  /* helper typedef */
  template< int index >
  using Index = std::integral_constant< int, index >;

  /* helper functions */
  static constexpr const char*
  name( const decltype(xss)& ){ return "XSS"; }

  static constexpr const char*
  name( const decltype(nxs)& ){ return "NXS"; }

  static constexpr const char*
  name( const decltype(jxs)& ){ return "JXS"; }

  static constexpr const char*
  name( const decltype(izaw)&, Index<0> ){ return "IZ"; }

  static constexpr const char*
  name( const decltype(izaw)&, Index<1> ){ return "AW"; }

  template< typename T, typename... Args >
  static void
  verifyIndex( const T& sequence, const std::size_t index, Args&&... args ) {
    if ( ( index < 1 ) || ( index > sequence.size() ) ){
      Log::error( "Illegal index argument" );
      Log::info( "Index value: {}", index );
      Log::info( "{} may be indexed with values between 1 and {} inclusively",
                 Data::name( sequence, std::forward<Args>(args)... ),
		 sequence.size() );
      throw std::out_of_range( name( sequence, std::forward<Args>(args)... ) );
    }
  }
  
  template< typename T >
  static decltype(auto) fetch( T&& value ){ return value; }

  template< typename T, int i >
  static decltype(auto)
  fetch( T&& value, Index<i> ){ return std::get<i>(value); }
  
  template< typename T, typename... Args >
  static decltype(auto)
  fetch( T&& sequence, std::size_t index, Args&&... args ){
    #ifndef NDEBUG
    verifyIndex( sequence, index, std::forward<Args>(args)... );
    #endif
    return fetch( sequence[index - 1], std::forward<Args>(args)... );
  }

protected:
  /* helper classes */
  #include "ACEtk/Table/Data/Parse.hpp"

public:
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
    Data( izaw_, nxs_, Parse::JXS( state ) ){}
    
  template< typename Iterator >
  Data( State<Iterator>& state,
        const decltype(izaw)& izaw_ ) :
    Data( izaw_, Parse::NXS( state ) ){}
    
public:  
  template< typename Iterator >
  Data( State<Iterator>& state )
    try :
      Data( Parse::IZAW( state ) ){}
    catch( std::exception& e ) {
      Log::info("Error while constructing ACE Table Data");
      throw e;
    }
  
  auto& XSS( std::size_t index ){ return fetch(this->xss, index); }
  auto& NXS( std::size_t index ){ return fetch(this->nxs, index); }
  auto& JXS( std::size_t index ){ return fetch(this->jxs, index); }

  auto& IZ( std::size_t index ){
    return fetch( this->izaw, index, Index<0>() );
  }

  auto& AW( std::size_t index ){
    return fetch( this->izaw, index, Index<1>() );
  }

  auto XSS( std::size_t index, std::size_t length ){
    #ifndef NDEBUG
    verifyIndex( this->xss, index );
    verifyIndex( this->xss, index + length - 1 );
    #endif
    const auto left = std::next( this->xss.begin(), index - 1 );
    const auto right = left + length;
    return ranges::make_iterator_range( left, right );
  }

  auto& XSS(){ return this->xss; }
  
#define CONST_OVERLOAD( method )                        \
  auto method( std::size_t index ) const {              \
    return const_cast<Data&>(*this).method(index);      \
  }

  CONST_OVERLOAD( IZ )
  CONST_OVERLOAD( AW )
  CONST_OVERLOAD( NXS )
  CONST_OVERLOAD( JXS )
  CONST_OVERLOAD( XSS )

#undef CONST_OVERLOAD

  auto XSS( std::size_t index, std::size_t length ) const {
    #ifndef NDEBUG
    verifyIndex( this->xss, index );
    verifyIndex( this->xss, index + length - 1 );
    #endif
    const auto left = std::next( this->xss.begin(), index - 1 );
    const auto right = left + length;
    return ranges::make_iterator_range( left, right );
  }

  const auto& XSS() const { return this->xss; }
  
  #include "ACEtk/Table/Data/src/print.hpp"
};
