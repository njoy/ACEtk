static std::unordered_map< std::string, std::size_t >
indices( const std::vector< XsdirEntry > entries ) {

  std::unordered_map< std::string, std::size_t > indices;
  for ( unsigned int i = 0; i < entries.size(); ++i ) {

    indices[ entries[i].ZAID() ] = i;
  }
  return indices;
}
