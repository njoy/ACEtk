class ProbabilityTable {

protected:
  Slice table_;

public:
  ProbabilityTable( Slice values ):
    table_( values )
  { }

  auto CDF() const       { return table_[ 0 ]; }
  auto totalXS() const   { return table_[ 1 ]; }
  auto elasticXS() const { return table_[ 2 ]; }
  auto fissionXS() const { return table_[ 3 ]; }
  auto captureXS() const { return table_[ 4 ]; }
  auto heating() const   { return table_[ 5 ]; }

  auto parameter( int index ) const{ return table_.at( index - 1 ); }
};
