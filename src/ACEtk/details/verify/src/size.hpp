template< typename R1, typename R2 >
inline bool equalSize( R1& a1, R2& a2 ){
  if( a1.size() != a2.size() ){
    njoy::Log::error( "array sizes are not the same" );
    njoy::Log::info( "size1: {}, size2: {}", a1.size(), a2.size() );
    return false;
  }
  return true;
}
