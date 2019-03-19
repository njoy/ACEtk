template<typename SubRange,
	 typename Unit,
	 typename Projection>
struct S1 : protected Projection, public SubRange {

  template<typename...Args>
  S1(Projection proj, Args&&... args)
    : Projection(proj), SubRange(std::forward<Args>(args)...) {}
    
  auto floor(Unit parameter) const {
    /*
    if ( this->out_of_bounds(parameter) ){
      njoy::Log::error( "Could not find value in range" );
      throw std::domain_error("Could not find value in range");      
    } 
    */

    auto value = parameter;
    const auto& projection = static_cast<const Projection&>(*this);
    auto range = *this;
    auto it = ranges::lower_bound(range, value, std::less<>{}, projection);
    
    const bool match = projection(*it) == value;      
    it = ranges::prev(it, not match);
    
    return *it;
  }    

  auto ceil(Unit parameter) const {

    /*
    if ( this->out_of_bounds(parameter) ){
      njoy::Log::error( "Could not find value in range" );
      throw std::domain_error("Could not find value in range");      
    }
    */
    auto value = parameter;
    auto range = *this;
    auto it = ranges::lower_bound(range, value, std::less<>{},
				  static_cast<const Projection&>(*this));
    return *it;
  }

};
