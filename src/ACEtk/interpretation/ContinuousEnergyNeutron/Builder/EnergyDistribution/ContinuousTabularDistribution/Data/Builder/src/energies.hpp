template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& energies( Range&& energies ){
  this->energies_ = std::move( energies );
  return *this;
}

