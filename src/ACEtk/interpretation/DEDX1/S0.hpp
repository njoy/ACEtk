template<typename Range>
class S0 : public Range {

  int nDensities;
protected:
  using StoppingPower = std::decay_t<decltype(std::declval<const Range&>().front())>;

  template<typename SubRange,
	   typename Unit,
	   typename Projection>
  struct S1 : protected Projection, public SubRange {

    template<typename...Args>
    S1(Projection proj, Args&&... args)
      : Projection(proj), SubRange(std::forward<Args>(args)...) {}
    
    auto floor(Unit parameter) const {
      auto value = std::log(parameter.value);
      const auto& projection = static_cast<const Projection&>(*this);
      auto range = *this;      
      auto it = ranges::lower_bound(range, value, std::less<>{}, projection);
      if ( it == range.end() ){ throw std::domain_error("Could not find value in range"); }
      const bool match = projection(*it) == value;      
      it = ranges::prev(it, not match);
      return *it;
    }    

    auto ceil(Unit parameter) const {
      auto value = std::log(parameter.value);
      auto range = *this;
      auto it = ranges::lower_bound(range, value, std::less<>{},
				    static_cast<const Projection&>(*this));
      if ( it == range.end() ){ throw std::domain_error("Could not find value in range"); }      
      return *it;
    }

  };
  
public:
  template<typename... Args>
  S0(int nDensities, Args&&... args)
    : Range(std::forward<Args>(args)...), nDensities(nDensities) {}

  auto floor(DenT density) const {
    auto value = std::log(density.value);
    auto end_it = ranges::next(this->begin(), nDensities);
    auto it =
      ranges::lower_bound(this->begin(), end_it, value, std::less<>{},
			  &StoppingPower::logDensity);
    if ( it == end_it ){ throw std::domain_error("Could not find density in range"); }
    const bool match = (*it).logDensity_ == value;
    it = ranges::prev(it, not match);
    int distance = ranges::distance(this->begin(), it);
    auto result =
      *this | ranges::view::drop_exactly(distance) | ranges::view::stride(nDensities);
    auto logTemperature = [](const StoppingPower& stoppingPower){
      return stoppingPower.logTemperature();
    };        
    using Projection = decltype(logTemperature);
    return S1<decltype(result), TempT, Projection>{logTemperature, std::move(result)};    
  }

  auto ceil(DenT density) const {
    auto value = std::log(density.value);
    auto end_it = ranges::next(this->begin(), nDensities);    
    auto it =
      ranges::lower_bound(this->begin(), end_it, value, std::less<>{},
			  &StoppingPower::logDensity);
    if ( it == end_it ){ throw std::domain_error("Could not find density in range"); }    
    int distance = ranges::distance(this->begin(), it);
    auto result =
      *this | ranges::view::drop_exactly(distance) | ranges::view::stride(nDensities);
    auto logTemperature = [](const StoppingPower& stoppingPower){
      return stoppingPower.logTemperature();
    };        
    using Projection = decltype(logTemperature);    
    return S1<decltype(result), TempT, Projection>{logTemperature, std::move(result)};
  }

  auto floor(TempT temperature) const {
    auto value = std::log(temperature.value);
    auto it = ranges::lower_bound(this->begin(), this->end(), value, std::less<>{},
				  &StoppingPower::logTemperature);
    if ( it == this->end() ){ throw std::domain_error("Could not find temperature in range"); }
    int distance = ranges::distance(this->begin(), it);
    if( (*it).logTemperature_ != value) { distance -= nDensities; }
    auto result =
      *this | ranges::view::slice(distance, distance+nDensities);
    auto logDensity = [](const StoppingPower& stoppingPower){
      return stoppingPower.logDensity();
    };        
    using Projection = decltype(logDensity);    
    return S1<decltype(result), DenT, Projection>{logDensity, std::move(result)};
  }  

  auto ceil(TempT temperature) const {
    auto value = std::log(temperature.value);
    auto it = ranges::lower_bound(this->begin(), this->end(), value, std::less<>{},
				  &StoppingPower::logTemperature);
    if ( it == this->end() ){ throw std::domain_error("Could not find temperature in range"); }
    auto distance = ranges::distance(this->begin(), it);
    auto result =
      *this | ranges::view::slice(distance, distance+nDensities);
    auto logDensity = [](const StoppingPower& stoppingPower){
      return stoppingPower.logDensity();
    };    
    using Projection = decltype(logDensity);    
    return S1<decltype(result), DenT, Projection>{logDensity, std::move(result)};
  }

};

template<typename Range>
auto makeS0(int N, Range&& range) const {
  using Parent = std::decay_t<decltype(range)>;
  return S0<Parent>{N, std::forward<Range>(range)};
}


