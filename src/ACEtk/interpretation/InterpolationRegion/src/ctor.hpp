InterpolationRegion( int INT, xRange&& x, yRange&& y )
try:
  interpolationScheme_( verifyInterpolationScheme( INT ) ),
  x_( x ), y_( y )
{ 
  if( x_.size() != y_.size() ){
    njoy::Log::error( "The x and y components must have the same size" );
    njoy::Log::info( "x size: {}, y size: {}", x_.size(), y_.size() );
    throw std::exception();
  }
} catch ( std::exception& e ){
  njoy::Log::info( "Trouble constructing InterpolationRegion." );
  throw e;
}
