// The Derived class can override this function to generate a data block (like
// a cross section data block from the SIG block) that cannot use the basic
// constructor of a left an right iterator (e.g. when the data block is a
// variant).
static Data generateData( std::size_t locator, Iterator left, Iterator right ) {

  if ( locator == 0 ) {

    Log::warning( "Detected a locator = 0 that may not be properly handled" );
  }

  return { left, right };
}
