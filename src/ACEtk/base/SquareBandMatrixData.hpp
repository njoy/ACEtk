#ifndef NJOY_ACETK_BASE_SQUAREBANDMATRIXDATA
#define NJOY_ACETK_BASE_SQUAREBANDMATRIXDATA

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/Base.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief A block of data given as a square matrix with a defined number of
 *         super-diagonals and sub-diagonals (default is zero for each)
 */
class SquareBandMatrixData : protected Base {

  /* fields */
  unsigned int size_;
  unsigned int nsuper_ = 0;
  unsigned int nsub_ = 0;

public:


  #include "ACEtk/base/SquareBandMatrixData/src/matrixIndices.hpp"


private:
  
  /* auxiliary functions */
  #include "ACEtk/base/SquareBandMatrixData/src/verifyIndex.hpp"
  #include "ACEtk/base/SquareBandMatrixData/src/generateXSS.hpp"
  #include "ACEtk/base/SquareBandMatrixData/src/listIndices.hpp"
  #include "ACEtk/base/SquareBandMatrixData/src/verifySize.hpp"
  
public:

  /* constructor */
  #include "ACEtk/base/SquareBandMatrixData/src/ctor.hpp"
  
  /* methods */

  /**
   *  @brief Return the matrix size (number of rows/columns)
   */
  unsigned int size() const { return this->size_; }

  /**
   *  @brief Return the number of rows (first index)
   */
  unsigned int M() const { return this->size_; }

  /**
   *  @brief Return the number of rows (first index)
   */
  unsigned int numberRows() const { return this->M(); }

  /**
   *  @brief Return the number of columns (second index)
   */
  unsigned int N() const { return this->size_; }

  /**
   *  @brief Return the number of columns (second index)
   */
  unsigned int numberColumns() const { return this->N(); }

  /**
   *  @brief Return the number of super-diagonals
   */
  unsigned int NSUP() const { return this->nsuper_; }

  /**
   *  @brief Return the number of super-diagonals
   */
  unsigned int numberSuperDiagonals() const { return this->NSUP(); }

  /**
   *  @brief Return the number of sub-diagonals
   */
  unsigned int NSUB() const { return this->nsub_; }


  /**
   *  @brief Return the number of sub-diagonals
   */
  unsigned int numberSubDiagonals() const { return this->NSUB(); }


  /**
   *  @brief Return the length of the block
   */
  unsigned int blockLength() const { 
    
    return ( this->size() * ( 1 + this->NSUB() + this->NSUP() )) - ( ( this->NSUB() * ( 1 + this->NSUB() ) ) + ( this->NSUP() * ( 1 + this->NSUP() ) ) ) / 2; 
  }

  /**
   *  @brief Return the matrix as a 1-D array
   */
  auto matrixList() const {
    
    return this->XSS( );
  }

  /**
   *  @brief Return the number of super-diagonal bands for a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowSuperDiagonals( unsigned int row ) const {

    return this->rowEnd( row ) - row;
  }

  /**
   *  @brief Return the number of sub-diagonal bands for a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowSubDiagonals( unsigned int row ) const {

    return  row - this->rowStart( row ) ;
  }

  /**
   *  @brief Return the value at a location given by the row and
   *         column indices (one-based) in the matrix.
   *
   *  The function will return zero if:
   *    - the element isn't part of the list (the row and column 
   *      correspond to an element outside the given bands)
   *    - if the element is outside the bounds of the matrix
   *
   *  @param[in] row     the row index (one-based)
   *  @param[in] col     the row index (one-based)
   */
  double matrixValue( unsigned int row, unsigned int col ) const {
    
    // if this element isn't in the matrix or in the list, 
    // return zero 
    
    if ( this->verifyIndex( row, col ) ) {

      unsigned int index = this->listIndex( row, col );
      return this->XSS( index ) ; 
    }
    else {
      
      return 0.;
    }

    
  }

  /**
   *  @brief Return a row of the matrix
   *
   *  If the row is out of bounds, an array of all
   *  zeros will be returned
   *
   *  @param[in] row     the row index (one-based)
   */
   auto matrixRow( unsigned int row ) const {

      std::vector< double > v;

      for (unsigned int col = 1; col <= this->M(); ++col ) {

        v.push_back( this-> matrixValue( row, col ) ) ;
      }

    return v;
    }

  /**
   *  @brief Return the matrix
   *
   */
   auto matrix( ) const {

      std::vector<  std::vector < double > > v;

      for (unsigned int row = 1; row <= this->size(); ++row ){

        v.push_back( {} );
        for (unsigned int col = 1; col <= this->size(); ++col ) {
          
          v.back().push_back( this-> matrixValue( row, col ) ) ;
        }
      }

    return v;
    }


  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
