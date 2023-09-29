static std::vector< double >
generateXSS(
  std::vector< long >&& boundaries,
  std::vector< long >&& interpolants,
  std::vector< double >&& energies,
  std::vector< double >&& temperatures,
  double energy ) {

  // insert the tabulated data
  std::vector< double > xss;
  const BaseTabulatedData table( "DLW::GeneralEvaporationSpectrum",
                                 std::move( boundaries ),
                                 std::move( interpolants ),
                                 std::move( energies ),
                                 std::move( temperatures ) );
  xss.insert( xss.end(), table.begin(), table.end() );

  // insert the restriction energy
  xss.push_back( energy );

  return xss;
}
