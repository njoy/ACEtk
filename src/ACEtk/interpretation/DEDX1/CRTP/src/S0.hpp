template<typename Range>
class S0 : public Range {

  int nDensities;
  DenT min_den; 
  DenT max_den;
  TempT min_temp;
  TempT max_temp;
  
protected:
  using StoppingPower =
    std::decay_t<decltype(std::declval<const Range&>().front())>;

  bool out_of_bounds(TempT value) const {
    return not (this->min_temp < value && value < this->max_temp);
  }

  bool out_of_bounds(DenT value) const {
    return not (this->min_den < value && value < this->max_den);
  }  
 
  #include "ACEtk/interpretation/DEDX1/CRTP/src/S1.hpp"
  
public:
  template<typename... Args>
  S0(int nDensities,
     DenT min_den,
     DenT max_den,
     TempT min_temp,
     TempT max_temp,
     Args&&... args)
    : Range(std::forward<Args>(args)...),
      nDensities(nDensities),
      min_den(min_den),
      max_den(max_den),
      min_temp(min_temp),
      max_temp(max_temp) {}

  #include "ACEtk/interpretation/DEDX1/CRTP/src/S0/src/floor.hpp"
  #include "ACEtk/interpretation/DEDX1/CRTP/src/S0/src/ceil.hpp"    

};

template<typename Range>
auto makeS0(int N,
	    DenT mind,
	    DenT maxd,
	    TempT mint,
	    TempT maxt,
	    Range&& range ) const {
  using Parent = std::decay_t<decltype(range)>;
  return S0<Parent>{N, mind, maxd, mint, maxt, std::forward<Range>(range)};
}
