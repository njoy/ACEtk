static std::vector< DistributionData >
insertZero( DistributionData&& zero, std::vector< DistributionData >&& data ) {

  data.insert( data.begin(), std::move( zero ) );
  return data;
}
