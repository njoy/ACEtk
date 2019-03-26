template<typename Range>
class S0 : public Range {

  std::size_t nDensities;
  std::size_t nTemperatures;
  
protected:
  using StoppingPower =
    std::decay_t< decltype( std::declval< const Range& >().front() ) >;

public:
  template<typename... Args>
  S0( int nDensities, int nTemperatures, Args&&... args ) :
    Range( std::forward<Args>(args)... ),
    nDensities( nDensities ),
    nTemperatures( nTemperatures )
  {
    assert( this->nDensities * this->nTemperatures == ranges::size( *this ) &&
	    "Size of stopping power range is not equal to the number of "
	    "densities by the number of temperatures" );
  }

  #include "ACEtk/interpretation/DEDX1/CRTP/S0/src/lowerBound.hpp"  
  #include "ACEtk/interpretation/DEDX1/CRTP/S0/src/floor.hpp"
  #include "ACEtk/interpretation/DEDX1/CRTP/S0/src/ceil.hpp"    

};

template<typename Range>
auto makeS0(int numDens, int numTemps, Range&& range) const {
  using Parent = std::decay_t<decltype(range)>;
  return S0<Parent>{numDens, numTemps, std::forward<Range>(range)};
}
