/**
 *  @brief Constructor
 *
 *  @param[in] header   the header information
 *  @param[in] data     the ACE data
 */
Table( HeaderVariant&& header, Data&& data ) :
  data_( std::move(data) ), header_( std::move(header) ){}

protected:

/**
 *  @brief Private constructor
 */
template< typename Iterator >
Table( HeaderVariant&& header, State< Iterator >& state ) :
  Table( std::move( header ), Data( state ) ){}

public:

Table( const Table& ) = default;
Table( Table&& ) = default;

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator   a buffer iterator
 *
 *  @param[in] state   the buffer state
 */
template< typename Iterator >
Table( State< Iterator >& state )
  try: Table( parse( state ), state ) {}
  catch( std::exception& e ) {

    Log::info("Error while constructing ACE Table");
    throw e;
  }

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator   a buffer iterator
 *
 *  @param[in] state   the buffer state
 */
template< typename Iterator >
Table( State< Iterator >&& state ) : Table( state ) {}
