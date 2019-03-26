template<typename SubRange, typename Unit, typename Projection>
class S1 : public SubRange, protected Projection {

  std::size_t size_;
  
public:
  template<typename...Args>
  S1(std::size_t size_, Projection proj, Args&&... args) :
    SubRange(std::forward<Args>(args)...),
    Projection(std::move(proj)),
    size_(size_) {}  

  auto floor(Unit parameter) const {
    auto range = static_cast<SubRange>(*this);    
    const auto& projection = static_cast<const Projection&>(*this);

    {
      auto it = range.begin();
      decltype(auto) front = it[0];
      decltype(auto) back = it[this->size_ - 1];
      const auto min = projection(front);
      const auto max = projection(back);
      const bool ob = outOfBounds(parameter, min, max);
    }
    
    const auto it = ranges::lower_bound(range, parameter, std::less<void>{}, projection);
    const bool match = projection(*it) == parameter;
    return *(ranges::prev(it, not match));
  }    

  auto ceil(Unit parameter) {
    auto range = static_cast<SubRange>(*this);    
    const auto& projection = static_cast<const Projection&>(*this);
    
    {
      auto it = range.begin();
      decltype(auto) front = it[0];
      decltype(auto) back = it[this->size_ - 1];
      const auto min = projection(front);
      const auto max = projection(back);
      const bool ob = outOfBounds(parameter, min, max);      
    }

    return *(ranges::lower_bound(range, parameter, std::less<void>{}, projection));
  }
};
