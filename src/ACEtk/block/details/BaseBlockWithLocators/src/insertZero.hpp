std::vector< Data >
insertElastic( Data&& zero,
               std::vector< Data >&& data ) {

  data.insert( data.begin(), std::move( zero ) );
  return data;
}
