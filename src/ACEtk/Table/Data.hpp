/**
 *  @class
 *  @brief The data in an ACE table
 *
 *  The data in an ACE table consists of the following arrays:
 *    - the IZAW array which contains 16 integer, double pairs
 *    - the NXS array which contains information needed to properly interpret
 *      the XSS array
 *    - the JXS array which contains 32 locators to specific blocks in the
 *      XSS array (the meaning of the JXS locators depend on the type of the
 *      ACE table)
 *    - the XSS array which contains the actual data
 */
class Data {

  /* fields */
  std::pair< std::array< int32_t, 16 >,
             std::array< double, 16 > > izaw_;
  std::array< int64_t, 16 > nxs_;
  std::array< int64_t, 32 > jxs_;
  std::vector< double > xss_;

  /* type aliases */
  template< int index >
  using Index = std::integral_constant< int, index >;

  /* auxiliary functions */
  #include "ACEtk/Table/Data/src/name.hpp"
  #include "ACEtk/Table/Data/src/verifyIndex.hpp"
  #include "ACEtk/Table/Data/src/fetch.hpp"

protected:

  #include "ACEtk/Table/Data/Parse.hpp"

public:

  #include "ACEtk/Table/Data/src/ctor.hpp"

  /**
   *  @brief Return the IZ array
   */
  const std::array< int32_t, 16 >& IZ() const { return this->izaw_.first; }

  /**
   *  @brief Return the AW array
   */
  const std::array< double, 16 >& AW() const { return this->izaw_.second; }

  /**
   *  @brief Return the NXS array
   */
  const std::array< int64_t, 16 >& NXS() const { return this->nxs_; }

  /**
   *  @brief Return the JXS array
   */
  const std::array< int64_t, 32 >& JXS() const { return this->jxs_; }

  /**
   *  @brief Return the XSS array
   */
  const std::vector< double >& XSS() const { return this->xss_; }

  /**
   *  @brief Return the IZ array
   */
  std::array< int32_t, 16 >& IZ() { return this->izaw_.first; }

  /**
   *  @brief Return the AW array
   */
  std::array< double, 16 >& AW() { return this->izaw_.second; }

  /**
   *  @brief Return the NXS array
   */
  std::array< int64_t, 16 >& NXS() { return this->nxs_; }

  /**
   *  @brief Return the JXS array
   */
  std::array< int64_t, 32 >& JXS() { return this->jxs_; }

  /**
   *  @brief Return the XSS array
   */
  std::vector< double >& XSS() { return this->xss_; }

  /**
   *  @brief Return a value from the IZ array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int32_t& IZ( std::size_t index ) { return fetch( this->izaw_.first, index ); }

  /**
   *  @brief Return a value from the IZ array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int32_t IZ( std::size_t index ) const { return fetch( this->izaw_.first, index ); }

  /**
   *  @brief Return a value from the AW array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  double& AW( std::size_t index ) { return fetch( this->izaw_.second, index ); }

  /**
   *  @brief Return a value from the AW array
   *
   *  @param[in] index    the index (one-based)
   */
  double AW( std::size_t index ) const { return fetch( this->izaw_.second, index ); }

  /**
   *  @brief Return a value from the NXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t& NXS( std::size_t index ) { return fetch( this->nxs_, index ); }

  /**
   *  @brief Return a value from the NXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t NXS( std::size_t index ) const { return fetch( this->nxs_, index ); }

  /**
   *  @brief Return a value from the JXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t& JXS( std::size_t index ) { return fetch( this->jxs_, index ); }

  /**
   *  @brief Return a value from the JXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t JXS( std::size_t index ) const { return fetch( this->jxs_, index ); }

  /**
   *  @brief Return a value from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  double& XSS( std::size_t index ) { return fetch( this->xss_, index ); }

  /**
   *  @brief Return a value from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  double XSS( std::size_t index ) const { return fetch( this->xss_, index ); }

  /**
   *  @brief Return a value from the XSS array as an integer value
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int IXSS( std::size_t index ) const {

    return static_cast< int >( std::round( fetch( this->xss_, index ) ) );
  }

  #include "ACEtk/Table/Data/src/XSS.hpp"

  #include "ACEtk/Table/Data/src/print.hpp"
};
