static std::vector< double >
generateXSS( unsigned int mftype, unsigned int mt,
             std::vector< long >&& boundaries,
             std::vector< long >&& interpolants,
             std::vector< double >&& x,
             std::vector< double >&& y ) {

  std::vector< double > xss = { static_cast< double >( mftype ),
                                static_cast< double >( mt ) };
  details::BaseTabulatedData data( "TabulatedSecondaryParticleMultiplicity",
                                   std::move( boundaries ),
                                   std::move( interpolants ),
                                   std::move( x ),
                                   std::move( y ) );
  xss.insert( xss.end(), data.begin(), data.end() );
  return xss;
}
