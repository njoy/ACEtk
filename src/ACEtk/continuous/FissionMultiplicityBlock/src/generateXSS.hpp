static std::vector< double >
generateXSS( FissionMultiplicityData&& prompt ) {

  std::vector< double > xss;
  std::visit( [&xss] ( auto&& data )
                     { xss.insert( xss.end(), data.begin(), data.end() ); },
               prompt );
  return xss;
}

static std::vector< double >
generateXSS( FissionMultiplicityData&& prompt,
             FissionMultiplicityData&& total ) {

  std::vector< double > xss(1);
  std::visit( [&xss] ( auto&& data )
                     { xss.insert( xss.end(), data.begin(), data.end() ); },
              prompt );
  xss[0] = -static_cast< double >( xss.size() - 1 );
  std::visit( [&xss] ( auto&& data )
                     { xss.insert( xss.end(), data.begin(), data.end() ); },
              total );
  return xss;
}
