auto floor(DenT density) const {

  if ( this->out_of_bounds(density) ){    
    njoy::Log::error( "Could not find value in range" );
    throw std::domain_error("Could not find density in range");      
  }
  
  auto value = density;  
  auto end_it = ranges::next(this->begin(), nDensities);
  auto it =
    ranges::lower_bound(this->begin(), end_it, value, std::less<>{},
			&StoppingPower::density);
  const bool match = (*it).density() == value;
  it = ranges::prev(it, not match);
  int distance = ranges::distance(this->begin(), it);
  auto result =
    *this | ranges::view::drop_exactly(distance) | ranges::view::stride(nDensities);
  auto temperature = [](const StoppingPower& stoppingPower){
    return stoppingPower.temperature();
  };
  using Projection = decltype(temperature);
  return S1<decltype(result), TempT, Projection>{temperature, std::move(result)};    
}

auto floor(TempT temperature) const {

  if ( this->out_of_bounds(temperature) ){
    njoy::Log::error( "Could not find temperature in range" );
    throw std::domain_error("Could not find temperature in range");      
  }      
  auto value = temperature;
  auto it = ranges::lower_bound(*this, value, std::less<>{},
				&StoppingPower::temperature);

  int distance = ranges::distance(this->begin(), it);
  if( (*it).temperature() != value) { distance -= nDensities; }
  auto result =
    *this | ranges::view::slice(distance, distance+nDensities);
  auto density = [](const StoppingPower& stoppingPower){
    return stoppingPower.density();
  };        
  using Projection = decltype(density);    
  return S1<decltype(result), DenT, Projection>{density, std::move(result)};
}  
