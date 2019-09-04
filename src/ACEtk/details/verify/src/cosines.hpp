inline void cosine( const double& c ){
  if( std::abs( c ) > 1 ){
    Log::error( "Invalid cosine parameter: {}", c );
    throw details::verify::exceptions::InvalidCosine();
  }
}

template< typename Range, 
          utility::Require< false, IsSorted, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
inline void cosines( Range&& cs ){
  try{
    ranges::for_each( cs, cosine );
  } catch( details::verify::exceptions::InvalidCosine& c ){
    Log::info( "Invalid cosine value found in array" );
    throw c;
  }
}

template< typename Range, 
          utility::Require< false, IsCosineBins, Range > = true,
          utility::Require< true, IsSorted, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
inline void cosines( Range&& cs ){
  try{
    if( cs.empty() ){ return; }

    cosine( cs.front() );
    cosine( cs.back() );
  } catch( details::verify::exceptions::InvalidCosine& c ){
    Log::info( "Invalid cosine value found in array" );
    throw c;
  }
}
