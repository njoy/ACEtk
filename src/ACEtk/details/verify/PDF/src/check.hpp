template< typename Arg,
          utility::Require< true, IsPDF, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsPDF, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  try{
    return positive( std::forward< Arg >( arg ) );
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "PDFs must be all positive" );
    throw exceptions::InvalidPDF( "PDFs must be all positive" );
  }
}
