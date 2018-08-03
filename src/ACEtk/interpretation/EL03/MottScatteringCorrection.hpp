class MottScatteringCorrection {
  const Table& table;

  auto data() const {
    constexpr int num_angles = 5;
    const auto length = num_angles * this->table.data.NXS( 4 );
    const auto start  = this->table.data.JXS( 3 ) + this->table.data.NXS( 4 );
    return this->table.data.XSS( start, length );
  }
  
public:
  MottScatteringCorrection( const Table& table ) : table(table) {}

  auto energies() const {
    const auto length = this->table.data.NXS( 4 );
    const auto start  = this->table.data.JXS( 3 );
    return this->table.data.XSS( start, length )
      | ranges::view::reverse
      | ranges::view::transform ( [] ( auto && entry )
				  { return entry * mega(electronVolt); } );
  }

  auto values() const {

    const auto num_energies = this->table.data.NXS( 4 );
    
    auto transpose = ranges::make_pipeable( [ num_energies ] ( auto&& ror ){ 
      auto indices = ranges::view::iota( 0, num_energies );
      auto get_entry = [](auto index){
	return [index](auto&& range)->decltype(auto){ return range[index]; };
      };
	
      return indices | ranges::view::transform( [ror, get_entry ]( auto index ){
	  return ror | ranges::view::transform( get_entry(index) ); } );
      } );
    
    return this->data() | ranges::view::chunk( num_energies )
      | ranges::view::transform( ranges::view::reverse )
      | transpose;
    
  }
};
