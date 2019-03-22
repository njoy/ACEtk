auto ceil(DenT density) const {
  const auto& r = static_cast<const Range&>(*this);
  auto min_ = r.front().density();
  auto max_ = ranges::back(r|ranges::view::bounded).density();  
  if ( not (min_ < density  && density < max_) ){    
    njoy::Log::error( "Could not find density in range" );
    throw std::domain_error("Could not find density in range");
  }
  auto value = density;
  auto end_it = ranges::next(this->begin(), nDensities);    
  auto it =
    ranges::lower_bound(this->begin(), end_it, value, std::less<>{},
			&StoppingPower::density);
  int distance = ranges::distance(this->begin(), it);
  auto result =
    *this | ranges::view::drop_exactly(distance) | ranges::view::stride(nDensities);
  auto temperature = [](const StoppingPower& stoppingPower){
    return stoppingPower.temperature();
  };        
  using Projection = decltype(temperature);    
  return S1<decltype(result), TempT, Projection>{temperature, std::move(result)};
}

auto ceil(TempT temperature) const {
  const auto& r = static_cast<const Range&>(*this);
  auto min_ = r.front().temperature();
  auto max_ = ranges::back(r|ranges::view::bounded).temperature();    
  if ( not (min_ < temperature  && temperature < max_) ){
    njoy::Log::error( "Could not find value in range" );
    throw std::domain_error("Could not find temperature in range");      
  }

  auto value = temperature;
  auto it = ranges::lower_bound(this->begin(), this->end(), value, std::less<>{},
				&StoppingPower::temperature);
  auto distance = ranges::distance(this->begin(), it);
  auto result =
    *this | ranges::view::slice(distance, distance+nDensities);
  auto density = [](const StoppingPower& stoppingPower){
    return stoppingPower.density();
  };
  using Projection = decltype(density);
  return S1<decltype(result), DenT, Projection>{density, std::move(result)};
}
