class Table {
public:
  /* nested classes */
  #include "ACEtk/Table/Header.hpp"
  #include "ACEtk/Table/Data.hpp"

  Data data;
  Header header;
 
  Table( Header&& header, Data&& data ) :
    data( std::move(data) ),
    header( std::move(header) ){}

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

public:
  
  #include "ACEtk/Table/src/print.hpp"
};
