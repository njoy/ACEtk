template<typename Range>
class S0 : public Range {

  int nDensities;
protected:
  using StoppingPower = std::decay_t<decltype(std::declval<const Range&>().front())>;

  template<typename SubRange,
	   typename Unit>
  struct S1 : public SubRange {

    template<typename...Args>
    S1(Args&&... args)
      : SubRange(std::forward<Args>(args)...) {}
    
    auto floor(TempT parameter) const {
      auto value = std::log(parameter.value);
      auto range = *this;
      auto it = ranges::lower_bound(range, value, std::less<>{}, &StoppingPower::logTemperature_);
      std::cout << std::exp((*it).logTemperature()) * mev << std::endl;
      const bool match = (*it).logTemperature_ == value;
      return match ? *it : *(--it);
    }

    auto floor(DenT parameter) const {
      auto value = std::log(parameter.value);
      auto it = ranges::lower_bound(*this, value, std::less<>{}, &StoppingPower::logDensity_);
      const bool match = (*it).logDensity_ == value;      
      it = ranges::prev(it, not match);
      return *it;
    }    
    
    auto ceil(TempT parameter) const {
      auto value = std::log(parameter.value);
      auto range = *this;
      auto it = ranges::lower_bound(range, value, std::less<>{}, &StoppingPower::logTemperature_);
      return *it;
    }

    auto ceil(DenT parameter) const {
      auto value = std::log(parameter.value);
      auto it = ranges::lower_bound(*this, value, std::less<>{}, &StoppingPower::logDensity_);      
      return *it;
    }        
    
  };
  
public:
  template<typename... Args>
  S0(int nDensities, Args&&... args)
    : Range(std::forward<Args>(args)...), nDensities(nDensities) {}

  auto floor(DenT density) const {
    auto value = std::log(density.value);
    auto it = ranges::lower_bound(this->begin(),
				  ranges::next(this->begin(), nDensities),
				  value,
				  std::less<>{},
				  &StoppingPower::logDensity_);
    if ( it == this->end() ) { throw("Did not find value"); }
    const bool match = (*it).logDensity_ == value;
    it = ranges::prev(it, not match);
    int distance = ranges::distance(this->begin(), it);
    auto result =
      *this | ranges::view::drop_exactly(distance) | ranges::view::stride(nDensities);
    
    return S1<decltype(result), TempT>{std::move(result)};    
  }

  auto ceil(DenT density) const {
    auto it = ranges::lower_bound(this->begin(),
				  ranges::next(this->begin(), nDensities),
				  std::log(density.value),
				  std::less<>{},
				  &StoppingPower::logDensity_);
    int distance = ranges::distance(this->begin(), it);
    auto result =
      *this | ranges::view::drop_exactly(distance) | ranges::view::stride(nDensities);
    return S1<decltype(result), TempT>{std::move(result)};
  }

  auto floor(TempT temperature) const {
    auto value = std::log(temperature.value);
    auto it = ranges::lower_bound(this->begin(),
				  this->end(),
				  value,
				  std::less<>{},
				  &StoppingPower::logTemperature_);
    if ( it == this->end() ) { throw("Did not find value"); }
    int distance = ranges::distance(this->begin(), it);
    if( (*it).logTemperature_ != value) { distance -= nDensities; }
    auto result =
      *this | ranges::view::slice(distance, distance+nDensities);      

    return S1<decltype(result), DenT>{std::move(result)};
  }  

  auto ceil(TempT temperature) const {
    auto it = ranges::lower_bound(this->begin(),
				  this->end(),
				  std::log(temperature.value),
				  std::less<>{},
				  &StoppingPower::logTemperature_);

    auto distance = ranges::distance(this->begin(), it);
    auto result =
      *this | ranges::view::slice(distance, distance+nDensities);

    return S1<decltype(result), DenT>{std::move(result)};
  }
  
};

template<typename Range>
auto makeS0(int N, Range&& range) const {
  using Parent = std::decay_t<decltype(range)>;
  return S0<Parent>{N, std::forward<Range>(range)};
}


