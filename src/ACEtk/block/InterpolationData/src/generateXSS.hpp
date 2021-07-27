static std::vector< std::vector< double > >
generateXSS( std::vector< long >&& boundaries,
             std::vector< long >&& interpolants ) {

  std::vector< std::vector< double > > columns;
  columns.emplace_back( boundaries.begin(), boundaries.end() );
  columns.emplace_back( interpolants.begin(), interpolants.end() );
  return columns;
}
