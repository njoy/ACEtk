Equiprobable( Slice bins ):
  boundaries_( bins )
{   
  assert( boundaries_.size() == 33 );

#ifndef NDEBUG
  if( boundaries_.front() != -1.0 ){
    Log::error( "First cosine bin boundary must be -1.0" );
    Log::info( "Fist bin value is: {}", boundaries_.front() );
    throw std::exception();
  }
  if( boundaries_.back() != 1.0 ){
    Log::error( "Last cosine bin boundary must be 1.0" );
    Log::info( "Last bin value is: {}", boundaries_.back() );
    throw std::exception();
  }
  if( not std::is_sorted( boundaries_.begin(), boundaries_.end() ) ){
    Log::error( "Cosine bins must be monotonically increasing." );
    throw std::exception();
   }
#endif

}

// Need to change this so it's no to specific to std::vector
template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
Equiprobable( Range&& bins ):
  Equiprobable( Table::slice( bins ) )
{   }
