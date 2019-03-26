auto ceil(DenT density) const {
  auto range = static_cast<const Range&>( *this );
  auto identity = [](auto&& it){ return std::forward<decltype(it)>(it); };
  return this->lowerBound(range, density, identity);
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
