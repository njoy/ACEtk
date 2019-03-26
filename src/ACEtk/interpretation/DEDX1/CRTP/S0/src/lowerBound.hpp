template<typename Func>
auto lowerBound(const Range& range, DenT density, Func&& func) const {
  auto variesWithDensity =
    range | ranges::view::slice( std::size_t(0), this->nDensities );
  
  {  
    const auto min = variesWithDensity.front().density();
    const auto max = variesWithDensity.back().density();
    const bool ob = outOfBounds(density, min, max);
  }
  
  auto it = 
    func( ranges::lower_bound( variesWithDensity,
			       density,
			       std::less<void>{},
			       &StoppingPower::density ) );

  const auto distance = ranges::distance( variesWithDensity.begin(), it );

  auto result =
    range
    | ranges::view::drop_exactly( distance )
    | ranges::view::stride( this->nDensities );

  auto projection =
    [](auto&& stoppingPower){ return stoppingPower.temperature(); };

  const auto nTemperatures = ranges::size( range ) / this->nDensities;

  using SubTable = S1<decltype(result), TempT, decltype(projection)>;
  
  return SubTable{nTemperatures, projection, std::move(result)};
  
}
