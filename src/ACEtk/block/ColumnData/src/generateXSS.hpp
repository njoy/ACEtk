static std::vector< double >
generateXSS( std::vector< std::vector< double > >&& columns ) {

  std::vector< double > xss;
  auto nc = columns.size();
  auto ne = columns[0].size();
  xss.reserve( 1 + ne * nc );
  xss.push_back( ne );

  for ( unsigned int i = 0; i < nc; ++i ) {

    if ( columns[i].size() != ne ) {

      Log::error( "The size of the column with index {} is not equal to the "
                  "expected value", i + 1 );
      Log::info( "Expected size = {}", ne );
      Log::info( "Found size = {}", columns[i].size() );
      throw std::exception();
    }
    xss.insert( xss.end(), columns[i].begin(), columns[i].end() );
  }

  return xss;
}

static std::vector< double >
generateXSS( std::vector< double >&& column1,
             std::vector< double >&& column2 ) {

  std::vector< std::vector< double > > columns;
  columns.emplace_back( std::move( column1 ) );
  columns.emplace_back( std::move( column2 ) );
  return generateXSS( std::move( columns ) );
}

static std::vector< double >
generateXSS( std::vector< double >&& column1,
             std::vector< double >&& column2,
             std::vector< double >&& column3 ) {

  std::vector< std::vector< double > > columns;
  columns.emplace_back( std::move( column1 ) );
  columns.emplace_back( std::move( column2 ) );
  columns.emplace_back( std::move( column3 ) );
  return generateXSS( std::move( columns ) );
}
