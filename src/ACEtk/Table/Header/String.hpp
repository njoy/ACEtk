template< int maxLength, bool flushRight = false >
class String : public std::string {
  template< bool value >
  using Bool = std::integral_constant< bool, value >;

  void align( std::false_type ){
    this->resize( maxLength, ' ');
  }

  void align( std::true_type ){
    const auto pivot = this->size();
    this->align( std::false_type() );
    std::rotate( this->begin(),
                 std::next( this->begin(), pivot ),
                 this->end() );
  }
  
public:
  String() : std::string( maxLength, ' ' ){}
  
  template< typename... Arg >
  String( Arg... args ) : std::string( std::forward<Arg>(args)... ){
    if ( this->length() > maxLength ){
      Log::error( "Argument string exceeds maximum size for the field" );
      Log::info( "field size: {}", this->length() );
      Log::info( "maximum field size: {}", maxLength );
      throw std::exception();
    }
    if ( this->size() < maxLength ){
      this->align( Bool< flushRight >() );
    }
  }
};
