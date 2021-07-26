static std::vector< double >
generateXSS( std::vector< long >&& boundaries,
             std::vector< long >&& interpolants,
             std::vector< double >&& x,
             std::vector< double >&& y ) {

  std::vector< double > xss = { 2 };
  TabulatedData table( std::move( boundaries ), std::move( boundaries ),
                       std::move( x ), std::move( y ) );
  xss.insert( xss.end(), table.begin(), table.end() );
  return xss;
}
