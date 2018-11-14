CoupledDensityFunctions( Table::Slice PDF, Table::Slice CDF ):
    PDF_( PDF ),
    CDF_( CDF )
{
  try{
    details::verify::equalSize( PDF_, CDF_ );
  } catch( std::range_error& e ){
    njoy::Log::info( "PDF and CDF must be the same size" );
    throw;
  }
}

template< typename Range >
CoupledDensityFunctions( Range& PDF, Range& CDF ):
  CoupledDensityFunctions(
    Table::Slice{ PDF.begin(), PDF.end() },
    Table::Slice{ CDF.begin(), CDF.end() } )
{
}
