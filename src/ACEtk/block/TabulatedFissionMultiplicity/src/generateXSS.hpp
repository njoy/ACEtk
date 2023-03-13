static std::vector< double >
generateXSS( std::vector< long >&& boundaries,
             std::vector< long >&& interpolants,
             std::vector< double >&& x,
             std::vector< double >&& y ) {

  std::vector< double > xss = { 2. };
  const details::BaseTabulatedData data( "TabulatedFissionMultiplicity",
                                         std::move( boundaries ),
                                         std::move( interpolants ),
                                         std::move( x ),
                                         std::move( y ) );
  xss.insert( xss.end(), data.begin(), data.end() );
  return xss;
}
