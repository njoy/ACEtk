template<typename Range>
class S0 : public Range {

  int nDensities;
  
protected:
  using StoppingPower =
    std::decay_t<decltype(std::declval<const Range&>().front())>;

public:
  template<typename... Args>
  S0(int nDensities,
     Args&&... args)
    : Range(std::forward<Args>(args)...),
      nDensities(nDensities) {}
  
  #include "ACEtk/interpretation/DEDX1/CRTP/src/S1.hpp"  
  #include "ACEtk/interpretation/DEDX1/CRTP/src/S0/src/floor.hpp"
  #include "ACEtk/interpretation/DEDX1/CRTP/src/S0/src/ceil.hpp"    

};

template<typename Range>
auto makeS0(int N, Range&& range) const {
  using Parent = std::decay_t<decltype(range)>;
  return S0<Parent>{N, std::forward<Range>(range)};
}
