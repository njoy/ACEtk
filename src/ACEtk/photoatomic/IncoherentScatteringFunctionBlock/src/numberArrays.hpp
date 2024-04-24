static unsigned int numberArrays( Iterator begin, Iterator end ) {

  return std::distance( begin, end ) == 21 ? 1 : 2;
}
