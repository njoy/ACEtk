template<typename Func>
auto lowerBound(const Range& range,
		DenT density,
		Func&& conditionalIncrement) const {
  auto variesWithDensity =
    range | ranges::view::slice( std::size_t(0), this->nDensities );
  
  {  
    const auto min = variesWithDensity.front().density();
    const auto max = variesWithDensity.back().density();
    const bool ob = outOfBounds(density, min, max);
  }
  
  auto it = 
    conditionalIncrement( ranges::lower_bound( variesWithDensity,
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

template<typename Func>
auto lowerBound(const Range& range,
		TempT temperature,
		Func&& conditionalIncrement) const {
  auto variesWithTemp = range | ranges::view::stride( this->nDensities );

  {
    const auto last = this->nTemperatures - 1;   
    auto it = variesWithTemp.begin();
    decltype(auto) front = it[0];
    decltype(auto) back = it[last];

    const auto min = front.temperature();
    const auto max = back.temperature();    
    const bool ob = outOfBounds(temperature, min, max);
  }
  
  auto it =
    conditionalIncrement(ranges::lower_bound( variesWithTemp,
					      temperature,
					      std::less<void>{},
					      &StoppingPower::temperature ));

  // std::size_t distance = ranges::distance( range.begin(), it.base() );
  std::size_t distance = ranges::distance( ranges::begin( variesWithTemp ), it ) * this->nDensities;

  auto result =
    range | ranges::view::slice( distance, distance + this->nDensities );

  auto projection = [](auto&& stoppingPower){
    return stoppingPower.density();
  };
  
  return S1<decltype(result), DenT, decltype(projection)>
    {this->nDensities, projection, std::move(result)};
}
