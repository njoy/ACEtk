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
  auto incrementIfMatch = [=](auto&& it){
    const bool match = (*it).temperature() == temperature;
    return ranges::prev(it, not match);
  };  
  return this->lowerBound(range, temperature, incrementIfMatch);
}
