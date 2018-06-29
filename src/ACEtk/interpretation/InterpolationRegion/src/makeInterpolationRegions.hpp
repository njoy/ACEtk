template< typename xRange, typename yRange, typename E >
auto makeInterpolationRegions( E&& e, xRange& x, yRange& y ){

  return e | ranges::view::transform(
    [ &x, &y ]( auto&& e ){ 
      return InterpolationRegion< xRange, yRange >{ e.scheme(),
        x | ranges::view::slice( e.indices().begin(), e.indices().end() ),
        y | ranges::view::slice( e.indices().begin(), e.indices().end() )
        };
      }
    );
}
