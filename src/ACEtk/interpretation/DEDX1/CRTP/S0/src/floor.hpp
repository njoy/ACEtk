auto floor(DenT density) const {
  auto range = static_cast<const Range&>( *this );

  auto incrementIfMatch = [=](auto&& it){
    const bool match = (*it).density() == density;
    return ranges::prev(it, not match);
  };
  
  return this->lowerBound(range, density, incrementIfMatch);
}


auto floor(TempT temperature) const {
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

  const bool match = (*it).temperature() == temperature;
  it = ranges::prev(it, not match);
  
  std::size_t distance = ranges::distance( range.begin(), it.base() );

  auto result =
    range | ranges::view::slice( distance, distance + this->nDensities );

  auto projection = [](auto&& stoppingPower){
    return stoppingPower.density();
  };
  
  return S1<decltype(result), DenT, decltype(projection)>
    {this->nDensities, projection, std::move(result)};
}
