#ifndef NJOY_ACETK_CONTINUOUS_FISSIONMULTIPLICITYBLOCK
#define NJOY_ACETK_CONTINUOUS_FISSIONMULTIPLICITYBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/PolynomialFissionMultiplicity.hpp"
#include "ACEtk/continuous/TabulatedFissionMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy NU block with the fission multiplicity data
 */
class FissionMultiplicityBlock : protected base::Base {

public:

  /* type aliases */

  using FissionMultiplicityData = std::variant< PolynomialFissionMultiplicity,
                                                TabulatedFissionMultiplicity >;

private:

  /* fields */

  FissionMultiplicityData prompt_;
  std::optional< FissionMultiplicityData > total_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( FissionMultiplicityData&& prompt ) {

    std::vector< double > xss;
    std::visit( [&xss] ( auto&& data )
                       { xss.insert( xss.end(), data.begin(), data.end() ); },
                 prompt );
    return xss;
  }

  static std::vector< double >
  generateXSS( FissionMultiplicityData&& prompt,
               FissionMultiplicityData&& total ) {

    std::vector< double > xss(1);
    std::visit( [&xss] ( auto&& data )
                       { xss.insert( xss.end(), data.begin(), data.end() ); },
                prompt );
    xss[0] = -static_cast< double >( xss.size() - 1 );
    std::visit( [&xss] ( auto&& data )
                       { xss.insert( xss.end(), data.begin(), data.end() ); },
                total );
    return xss;
  }

  template < typename Iterator >
  static FissionMultiplicityData generateData( Iterator begin, Iterator end ) {

    unsigned int LNU = static_cast< unsigned int >( std::round( *begin ) );
    switch (LNU) {

      case 1: return PolynomialFissionMultiplicity( begin, end );
      case 2: return TabulatedFissionMultiplicity( begin, end );
      default: {

        Log::error( "Illegal fission multiplicity representation LNU = {}", LNU );
        Log::info( "Only LNU = 1 (polynomial) or LNU = 2 (tabulated) are allowed" );
        throw std::exception();
      }
    }
  }

  void generateBlocks() {

    if ( this->length() > 0 ) {

      Iterator begin = this->begin();
      Iterator end = this->end();

      bool both = this->XSS( 1 ) < 0;
      if ( both ) {

        auto knu = static_cast<unsigned int>( std::abs( std::round( *begin ) ) ) + 1;
        end = std::next( begin, knu );
        begin = std::next( begin );
      }

      this->prompt_ = generateData( begin, end );
      this->total_ = both ? std::make_optional( generateData( end, this->end() ) )
                          : std::nullopt;
    }
  }

public:

  /* constructor */

  FissionMultiplicityBlock() = default;

  FissionMultiplicityBlock( const FissionMultiplicityBlock& base ) :
    Base( base ),
    prompt_( base.prompt_ ), total_( base.total_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  FissionMultiplicityBlock( FissionMultiplicityBlock&& base ) :
    Base( base ),
    prompt_( std::move( base.prompt_ ) ), total_( std::move( base.total_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  FissionMultiplicityBlock& operator=( const FissionMultiplicityBlock& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->prompt_ = base.prompt_;
      this->total_ = base.total_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  FissionMultiplicityBlock& operator=( FissionMultiplicityBlock&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->prompt_ = std::move( base.prompt_ );
      this->total_ = std::move( base.total_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] prompt    the prompt fission multiplicity data
   */
  FissionMultiplicityBlock( FissionMultiplicityData prompt ) :
    Base( "NU", generateXSS( std::move( prompt ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] prompt    the prompt fission multiplicity data
   *  @param[in] total     the total fission multiplicity data
   */
  FissionMultiplicityBlock( FissionMultiplicityData prompt,
                            FissionMultiplicityData total ) :
    Base( "NU", generateXSS( std::move( prompt ), std::move( total ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the NU block in the XSS array
   *  @param[in] end      the end iterator of the NU block in the XSS array
   */
  FissionMultiplicityBlock( Iterator begin, Iterator end ) :
    Base( "NU", begin, end ) {

    this->generateBlocks();
  }

  /* methods */

  /**
   *  @brief Return whether or not prompt and total fission multiplicity are
   *         present
   */
  bool hasPromptAndTotalFissionMultiplicity() const {

    return this->total_.has_value();
  }

  /**
   *  @brief Return the multiplicity
   *
   *  This returns the prompt fission multiplicity when both prompt and total
   *  are given or just the available multiplicity data if only one of these is
   *  given (the ACE format does not indicate which is present).
   */
  const FissionMultiplicityData& multiplicity() const {

    return this->prompt_;
  }

  /**
   *  @brief Return the total fission multiplicity
   *
   *  This returns the total fission multiplicity when both prompt and total
   *  are given or just the available multiplicity data if only one of these is
   *  given (the ACE format does not indicate which is present).
   */
  const std::optional< FissionMultiplicityData >& totalFissionMultiplicity() const {

    return this->total_;
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using NU = FissionMultiplicityBlock;
using DNU = FissionMultiplicityBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
