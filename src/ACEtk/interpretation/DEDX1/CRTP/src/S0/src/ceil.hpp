auto ceil(DenT density) const {
  
  if ( this->out_of_bounds(density) ){    
    njoy::Log::error( "Could not find density in range" );
    throw std::domain_error("Could not find density in range");
  }
  auto value = std::log(density.value);
  auto end_it = ranges::next(this->begin(), nDensities);    
  auto it =
    ranges::lower_bound(this->begin(), end_it, value, std::less<>{},
			&StoppingPower::logDensity);
  int distance = ranges::distance(this->begin(), it);
  auto result =
    *this | ranges::view::drop_exactly(distance) | ranges::view::stride(nDensities);
  auto logTemperature = [](const StoppingPower& stoppingPower){
    return stoppingPower.logTemperature();
  };        
  using Projection = decltype(logTemperature);    
  return S1<decltype(result), TempT, Projection>{logTemperature, std::move(result)};
}

auto ceil(TempT temperature) const {

  if ( this->out_of_bounds(temperature) ){
    njoy::Log::error( "Could not find value in range" );
    throw std::domain_error("Could not find temperature in range");      
  }

  auto value = std::log(temperature.value);

  auto it = ranges::lower_bound(this->begin(), this->end(), value, std::less<>{},
				&StoppingPower::logTemperature);
  auto distance = ranges::distance(this->begin(), it);
  auto result =
    *this | ranges::view::slice(distance, distance+nDensities);
  auto logDensity = [](const StoppingPower& stoppingPower){
    return stoppingPower.logDensity();
  };
  using Projection = decltype(logDensity);
  return S1<decltype(result), DenT, Projection>{logDensity, std::move(result)};
}
