template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& T( Range&& T ){
  this->T_ = std::move( T );
  return *this;
}
