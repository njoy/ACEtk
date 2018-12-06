template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& energyGrid( Range&& grid ){
  this->energyGrid_ = std::move( grid );
  return *this;
}

Slice energyGrid(){ return Table::slice( energyGrid_.value() ); }
