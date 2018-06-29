template< typename xRange, typename yRange, typename E >
auto makeInterpolationRegions( E&& e, xRange& x, yRange& y ){

  if( x.size() != y.size() ){
    njoy::Log::error(
      "The x and y ranges must be the same size to make InterpolationRegions" );
    njoy::Log::info( "x size: {}, y size: {}", x.size(), y.size() );
    throw std::exception();
  }

  return e | ranges::view::transform(
    [ &x, &y ]( auto&& e ){ 
      return InterpolationRegion< xRange, yRange >{ e.scheme(),
        x | ranges::view::slice( e.indices().begin(), e.indices().end() ),
        y | ranges::view::slice( e.indices().begin(), e.indices().end() )
        };
      }
    );
}
