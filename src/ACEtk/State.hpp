#ifndef NJOY_ACETK_STATE
#define NJOY_ACETK_STATE

// system includes

// other includes

namespace njoy {
namespace ACEtk {

  /**
   *  @class
   *  @brief The current buffer state
   *
   *  The current buffer state contains the current line number, an iterator
   *  to the current position in the buffer and the end iterator of the buffer.
   */
  template< typename Iterator >
  struct State {

    long lineNumber = 1;
    Iterator position;
    const Iterator end;
  };

} // ACEtk namespace
} // njoy namespace

#endif
