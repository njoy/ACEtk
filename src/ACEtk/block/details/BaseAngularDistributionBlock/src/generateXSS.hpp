static std::vector< double >
generateXSS( std::vector< DistributionData >&& distributions ) {

  std::size_t nr = distributions.size();
  std::vector< double > xss( nr );
  std::size_t index = 0;
  for ( const auto& distribution : distributions ) {

    std::visit(

      utility::overload{

        [ &xss, index ] ( const FullyIsotropicDistribution& value ) {

          xss[index] = 0;
        },
        [ &xss, index ] ( const DistributionGivenElsewhere& value ) {

          xss[index] = -1;
        },
        [ &xss, index, nr ] ( const AngularDistributionData& value ) {

          xss[index] = xss.size() - nr + 1;

          // remake the internal xss array with the proper locators
          AngularDistributionData temp(
              std::move( value.distributions() ),
              xss[index] );
          xss.insert( xss.end(), temp.begin(), temp.end() );
        }
      },
      distribution
    );
    ++index;
  }

  return xss;
}
