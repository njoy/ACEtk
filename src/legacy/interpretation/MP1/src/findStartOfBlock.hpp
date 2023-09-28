static auto availableOrders( const Table& table ) {
  auto start = table.data().JXS( 1 );
  auto length = table.data().NXS( 5 );
  return table.data().XSS( start, length );
}

static auto startOfDiscreteBlock( const Table& table ) {
  auto start = table.data().JXS( 1 ) + table.data().NXS( 5 );
  auto length = table.data().NXS( 5 );
  return table.data().XSS( start, length );
}

static auto findStartOfBlock( const Table& table , const int order ) {

  auto lrnd = []( const auto x ){ return std::lround( x ); };
  auto orders = availableOrders( table )
    | ranges::cpp20::views::transform( lrnd );

  auto starts = startOfDiscreteBlock( table )
    | ranges::cpp20::views::transform( lrnd );

  auto zipOrdersWithStart = ranges::views::zip( orders, starts );

  auto foundIfThisIsTrue =
    [ order ]( const auto pair ) { return ( order == pair.first ); };

  auto pairContainingIndex = ranges::cpp20::find_if( zipOrdersWithStart,
					      foundIfThisIsTrue );

  if( pairContainingIndex == ranges::end( zipOrdersWithStart ) ){
    std::runtime_error r( "Could not find the requested order in ACE file.\n"
			  "order requested: " + std::to_string( order ) );
    njoy::Log::error( r.what() );
    throw r;
  }

  return (*pairContainingIndex).second;
}
