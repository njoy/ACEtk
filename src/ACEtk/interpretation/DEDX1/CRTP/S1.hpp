template<typename SubRange, typename Unit, typename Projection>
class S1 : public SubRange, protected Projection {

  std::size_t size_;

  #include "ACEtk/interpretation/DEDX1/CRTP/S1/src/computeBounds.hpp"
  #include "ACEtk/interpretation/DEDX1/CRTP/S1/src/lowerBound.hpp"  
  
public:
  template<typename...Args>
  S1(std::size_t size_, Projection proj, Args&&... args) :
    SubRange(std::forward<Args>(args)...),
    Projection(std::move(proj)),
    size_(size_) {}  

  auto floor(Unit parameter) const {
    auto range = static_cast<const SubRange&>(*this);
    const auto& projection = static_cast<const Projection&>(*this);    
    auto it = this->lowerBound(range, parameter);
    const bool match = projection(*it) == parameter;
    return *(ranges::prev(it, not match));
  }

  auto ceil(Unit parameter) {
    auto range = static_cast<const SubRange&>(*this);    
    return *(this->lowerBound(range, parameter));
  }
};
