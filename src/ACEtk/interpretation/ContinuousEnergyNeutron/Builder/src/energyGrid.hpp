Builder& energyGrid( std::vector< double >&& grid ){
  this->energyGrid_ = std::move( grid );
  return *this;
}

Slice energyGrid(){ return Table::slice( energyGrid_.value() ); }
