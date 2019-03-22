template<typename SubRange,
	 typename Unit,
	 typename Projection>
struct S1 : public SubRange, protected Projection {

  template<typename...Args>
  S1(Projection proj, Args&&... args)
    : SubRange(std::forward<Args>(args)...),
      Projection(proj) {}
      

  auto floor(Unit parameter) const {
    const auto& projection = static_cast<const Projection&>(*this);
    const auto& r = static_cast<const SubRange&>(*this);
    //    auto b = r.begin();

    
    /*
    auto min_ = projection(r.front());
    auto max_ = projection(r.back());
    if ( not (min_ < parameter  && parameter < max_) ){
      njoy::Log::error( "Could not find value in range" );
      throw std::domain_error("Could not find value in range");      
    } 
    */
    auto range = *this;
    auto it = ranges::lower_bound(range, parameter, std::less<>{}, projection);
    const bool match = projection(*it) == parameter;      
    it = ranges::prev(it, not match);    
    return *it;
  }    

  auto ceil(Unit parameter) const {
    auto projection = static_cast<const Projection&>(*this);
    /*
    const auto& r = static_cast<const SubRange&>(*this) | ranges::view::bounded;
    auto min_ = projection(r.front());
    auto max_ = projection(r.back());
    if ( not (min_ < parameter  && parameter < max_) ){
      njoy::Log::error( "Could not find value in range" );
      throw std::domain_error("Could not find value in range");      
    }
    */
    auto range = *this;
    auto it = ranges::lower_bound(range, parameter, std::less<>{}, projection);
    return *it;
  }

};
