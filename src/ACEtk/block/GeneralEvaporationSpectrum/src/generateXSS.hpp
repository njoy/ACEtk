static std::vector< double >
generateXSS(
  std::vector< long >&& boundaries,
  std::vector< long >&& interpolants,
  std::vector< double >&& energies,
  std::vector< double >&& temperatures,
  std::vector< double >&& bins ) {

  // insert the tabulated data
  std::vector< double > xss;
  details::BaseTabulatedData table( "GeneralEvaporationSpectrum",
                                    std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( energies ),
                                    std::move( temperatures ) );
  xss.insert( xss.end(), table.begin(), table.end() );

  // insert the bin data
  xss.push_back( bins.size() );
  xss.insert( xss.end(), bins.begin(), bins.end() );

  return xss;
}
