auto ceil(DenT density) const {
  auto range = static_cast<const Range&>( *this );
  auto variesWithDensity =
    range | ranges::view::slice( std::size_t(0), this->nDensities );
  
  {  
    const auto min = variesWithDensity.front().density();
    const auto max = variesWithDensity.back().density();
    const bool ob = outOfBounds(density, min, max);
  }

  const auto it =
    ranges::lower_bound( variesWithDensity,
			 density,
			 std::less<void>{},
			 &StoppingPower::density );
  
  const auto distance = ranges::distance( variesWithDensity.begin(), it );

  auto result =
    range
    | ranges::view::drop_exactly( distance )
    | ranges::view::stride( this->nDensities );

  auto projection =
    [](auto&& stoppingPower){ return stoppingPower.temperature(); };

  using SubTable = S1<decltype(result), TempT, decltype(projection)>;

  const auto nTemperatures = ranges::size( range ) / this->nDensities;

  return SubTable{nTemperatures, projection, std::move(result)};
}

auto ceil(TempT temperature) const {
  auto range = static_cast<const Range&>( *this );
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
  
  auto it = ranges::lower_bound( variesWithTemp,
				 temperature,
				 std::less<void>{},
				 &StoppingPower::temperature );
  
  std::size_t distance = ranges::distance( range.begin(), it.base() );

  auto result =
    range | ranges::view::slice( distance, distance + this->nDensities );

  auto projection = [](auto&& stoppingPower){
    return stoppingPower.density();
  };
  
  return S1<decltype(result), DenT, decltype(projection)>
    {this->nDensities, projection, std::move(result)};
}
