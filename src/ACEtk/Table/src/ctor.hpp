/**
 *  @brief Constructor
 *
 *  @param[in] header   the header information
 *  @param[in] data     the ACE data
 */
Table( Header&& header, Data&& data ) :
  data_( std::move(data) ), header_( std::move(header) ){}

protected:

/**
 *  @brief Private constructor
 */
template< typename Iterator >
Table( Header&& header, State< Iterator >& state ) :
  Table( std::forward< decltype(header) >( header ), Data( state ) ){}

public:

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator   a buffer iterator
 *
 *  @param[in] state   the buffer state
 */
template< typename Iterator >
Table( State< Iterator >& state )
  try: Table( Header( state ), state ) {}
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

/**
 *  @brief Constructor (from a range)
 *
 *  @param[in] range   the buffer given as a range (e.g. a string)
 */
template< typename Range,
          typename... Args,
          typename = utility::void_t
          < decltype( std::declval< Range >().begin() ),
            decltype( std::declval< Range >().end() ) > >
Table( Range&& range, Args&&... ) :
  Table( State< decltype( range.begin() ) >{ 1, range.begin(), range.end() } ) {}
