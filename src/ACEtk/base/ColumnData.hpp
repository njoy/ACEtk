#ifndef NJOY_ACETK_BASE_COLUMNDATA
#define NJOY_ACETK_BASE_COLUMNDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Column data: a number of columns of fixed length
 */
class ColumnData : protected Base {

  /* fields */

  std::size_t nc_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< std::vector< double > >&& columns ) {

    std::vector< double > xss;
    const auto nc = columns.size();
    const auto ne = columns[0].size();
    xss.reserve( 1 + ne * nc );
    xss.push_back( static_cast< double >( ne ) );

    for ( unsigned int i = 0; i < nc; ++i ) {

      if ( columns[i].size() != ne ) {

        Log::error( "The size of the column with index {} is not equal to the "
                    "expected value", i + 1 );
        Log::info( "Expected size = {}", ne );
        Log::info( "Found size = {}", columns[i].size() );
        throw std::exception();
      }
      xss.insert( xss.end(), columns[i].begin(), columns[i].end() );
    }

    return xss;
  }

  static std::vector< double >
  generateXSS( std::vector< double >&& column1,
               std::vector< double >&& column2 ) {

    std::vector< std::vector< double > > columns;
    columns.emplace_back( std::move( column1 ) );
    columns.emplace_back( std::move( column2 ) );
    return generateXSS( std::move( columns ) );
  }

  static std::vector< double >
  generateXSS( std::vector< double >&& column1,
               std::vector< double >&& column2,
               std::vector< double >&& column3 ) {

    std::vector< std::vector< double > > columns;
    columns.emplace_back( std::move( column1 ) );
    columns.emplace_back( std::move( column2 ) );
    columns.emplace_back( std::move( column3 ) );
    return generateXSS( std::move( columns ) );
  }

  static void verifySize( Iterator begin, Iterator end,
                          std::size_t ne, std::size_t nc ) {

    std::size_t size = std::distance( begin, end );
    if ( size != 0 ) {

      std::size_t minimum = 1 + ne * nc;
      if ( size < minimum ) {

        Log::error( "The size of the XSS subrange in the column data should be at "
                    "equal to 1 + NE * NC" );
        Log::info( "NE: {}", ne );
        Log::info( "NC: {}", nc );
        Log::info( "XSS.size(): {}", size );
        throw std::exception();
      }
    }
  }

public:

  /* constructor */

  ColumnData() = default;

  ColumnData( const ColumnData& ) = default;
  ColumnData( ColumnData&& ) = default;

  ColumnData& operator=( const ColumnData& ) = default;
  ColumnData& operator=( ColumnData&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] name           the name of the data
   *  @param[in] columns        the columns
   */
  ColumnData( std::string name, std::vector< std::vector< double > > columns ) :
    Base( std::move( name ), generateXSS( std::move( columns ) ) ),
    nc_( columns.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name           the name of the data
   *  @param[in] column1        the first column
   *  @param[in] column2        the second column
   */
  ColumnData( std::string name, std::vector< double > column1,
              std::vector< double > column2 ) :
    Base( std::move( name ),
          generateXSS( std::move( column1 ), std::move( column2 ) ) ),
    nc_( 2 ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name           the name of the data
   *  @param[in] column1        the first column
   *  @param[in] column2        the second column
   *  @param[in] column3        the third column
   */
  ColumnData( std::string name, std::vector< double > column1,
              std::vector< double > column2, std::vector< double > column3 ) :
    Base( std::move( name ),
          generateXSS( std::move( column1 ), std::move( column2 ),
                       std::move( column3 ) ) ),
    nc_( 3 ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name     the name for this data piece
   *  @param[in] begin    the begin iterator of the SIG block in the XSS array
   *  @param[in] end      the end iterator of the SIG block in the XSS array
   *  @param[in] nc       the number of columns
   */
  ColumnData( std::string name, Iterator begin, Iterator end, std::size_t nc ) :
    Base( std::move( name ), begin, end ), nc_( nc ) {

    verifySize( this->begin(), this->end(),
                this->begin() == this->end() ? 0 : *( this->begin() ), nc );
  }

  /**
   *  @brief Return the number of columns
   */
  std::size_t NC() const { return this->nc_; }

  /**
   *  @brief Return the number of columns
   */
  std::size_t numberColumns() const { return this->NC(); }

  /**
   *  @brief Return the number of elements in a column
   */
  std::size_t N() const { return this->empty() ? 0 : this->IXSS( 1 ); }

  /**
   *  @brief Return the number of elements in a column
   */
  std::size_t numberElements() const { return this->N(); }

  /**
   *  @brief Return the column
   *
   *  @param[in] column     the column index (one-based)
   */
  auto C( std::size_t column ) const {

    auto number = this->N();
    return this->XSS( 2 + ( column - 1 ) * number, number );
  }

  /**
   *  @brief Return the column
   *
   *  @param[in] column     the column index (one-based)
   */
  auto column( std::size_t column ) const { return this->C( column ); }

  /**
   *  @brief Return a value
   *
   *  @param[in] column     the column index (one-based)
   *  @param[in] index      the index in the column (one-based)
   */
  double value( std::size_t column, std::size_t index ) const {

    auto number = this->N();
    return this->XSS( 2 + ( column - 1 ) * number + index - 1 );
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
