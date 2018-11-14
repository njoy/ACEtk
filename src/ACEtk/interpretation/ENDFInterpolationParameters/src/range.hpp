auto range(){

  auto leadingIndices = ranges::view::concat( ranges::view::single( 0 ), 
        NBT_
          | ranges::view::take( NBT_.size() ?  NBT_.size() - 1 : 0 )
          | ranges::view::transform( []( auto i ){ return i-1; } ) );

  auto indexPairs = ranges::view::zip_with( makeIndices, leadingIndices, NBT_ );

  return ranges::view::zip_with( makeParameters, schemes_, indexPairs );
}
