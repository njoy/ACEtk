struct Indices {
  long begin_;
  long end_;

  auto begin() const { return begin_; }
  auto end() const { return end_; }
};

static auto makeIndices( double begin, double end ){ 
  return Indices{ std::lround( begin ), std::lround( end ) };
}

struct Parameters {
  int scheme_;
  Indices indices_;
  
  int scheme() const { return scheme_; }
  Indices indices() const { return indices_; }
};

static auto makeParameters( int scheme, Indices indices ){ 
  return Parameters{ scheme, indices }; 
}

auto range(){

  auto leadingIndices = ranges::view::concat( ranges::view::single( 0 ), 
        NBT_
          | ranges::view::take( NBT_.size() ?
                                NBT_.size() - 1 : 
                                0 )
          | ranges::view::transform( []( auto i ){ return i-1; } ) );

  auto indexPairs = ranges::view::zip_with( makeIndices, leadingIndices, NBT_ );

  return ranges::view::zip_with( makeParameters, schemes_, indexPairs );
}
