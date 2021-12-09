std::vector< DistributionData >
insertElastic( DistributionData&& elastic,
               std::vector< DistributionData >&& distributions ) {

  distributions.insert( distributions.begin(), std::move( elastic ) );
  return distributions;
}
