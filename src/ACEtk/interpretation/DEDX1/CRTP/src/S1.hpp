template<typename SubRange,
	 typename Unit,
	 typename Projection>
struct S1 : protected Projection, public SubRange {

  template<typename StoppingPower>
  auto get(TempT, StoppingPower&& sp) const { return sp.temperature(); }
  template<typename StoppingPower>
  auto get(DenT, StoppingPower&& sp) const { return sp.density(); }
  
  template<typename T, typename P>
  bool out_of_bounds(T value, P projection) const {
    auto grrrr = *this;
    auto min_ = this->get(value, ranges::min(grrrr, std::less<T>{}, projection));
    auto max_ = this->get(value, ranges::max(grrrr, std::less<T>{}, projection));
    return not (min_ < value && value < max_);
  }
  
  template<typename...Args>
  S1(Projection proj, Args&&... args)
    : Projection(proj),
      SubRange(std::forward<Args>(args)...){}
    
  auto floor(Unit parameter) const {

    auto value = parameter;
    const auto& projection = static_cast<const Projection&>(*this);
    
    if ( this->out_of_bounds(parameter, projection) ){
      njoy::Log::error( "Could not find value in range" );
      throw std::domain_error("Could not find value in range");      
    } 

    auto range = *this;
    auto it = ranges::lower_bound(range, value, std::less<>{}, projection);
    
    const bool match = projection(*it) == value;      
    it = ranges::prev(it, not match);
    
    return *it;
  }    

  auto ceil(Unit parameter) const {
    auto value = parameter;
    auto projection = static_cast<const Projection&>(*this);
    
    if ( this->out_of_bounds(parameter, projection) ){
      njoy::Log::error( "Could not find value in range" );
      throw std::domain_error("Could not find value in range");      
    }

    auto range = *this;
    auto it = ranges::lower_bound(range, value, std::less<>{}, projection);
    return *it;
  }

};
