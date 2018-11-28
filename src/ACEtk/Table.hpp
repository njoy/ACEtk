class Table {
public:
  /* nested classes */
  #include "ACEtk/Table/Header.hpp"
  #include "ACEtk/Table/Data.hpp"

  Data data;
  Header header;
 
  Table( Header&& header, Data&& data ) :
    data( std::move(data) ), header( std::move(header) ){}

protected:
  /* api methods */
  template< typename Iterator >
  Table( State<Iterator>& state, Header&& header ) :
    Table( std::forward< decltype(header) >(header), Data(state) ){}

public:
  template< typename Iterator >
  Table( State<Iterator>& state )
    try:
      Table( state, Header::parse( state ) ){
    } catch( std::exception& e ) {
      Log::info("Error while constructing ACE Table");
      throw e;
    }

  template< typename Iterator >
  Table( State<Iterator>&& state ) : Table( state ){}

  template< typename Range,
            typename... Args,
            typename = utility::void_t
            < decltype( std::declval< Range >().begin() ),
              decltype( std::declval< Range >().end() ) > >
  Table( Range&& range, Args&&... ) :
    Table( State< decltype( range.begin() ) >
           { 1, range.begin(), range.end() } ){}

  template< typename Istream,
            typename = std::enable_if_t
                       < std::is_base_of< std::istream,
                                          std::decay_t< Istream > >::value > >
  Table( Istream&& istream ) :
    Table( std::string{ std::istreambuf_iterator< char >{ istream },
                        std::istreambuf_iterator< char >{} } ){}
  
public:
  #include "ACEtk/Table/src/print.hpp"

  using Slice = decltype( std::declval< const Data >().XSS( 1, 2 ) );

  static Slice slice( const std::vector< double >& S ){ 
    return { S.begin(), S.end() }; 
  }

  template< typename Range,
            typename iterator = typename std::decay_t< Range >::iterator,
            utility::Require< true, std::is_constructible, Slice, 
                              iterator, iterator > = true
          >
  static Slice slice( Range&& S ){ 
    return { S.begin(), S.end() }; 
  }

};
