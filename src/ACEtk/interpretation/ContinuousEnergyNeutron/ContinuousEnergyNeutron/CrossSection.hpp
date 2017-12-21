class CrossSection {
  const Table& table;
  const int MT;
  const int reactionIndex;

public:
  CrossSection( const Table& table, int ID ):
    table( table ),
    MT( ID ),
    reactionIndex( getReactionIndex( table ) )
  { }

  int ID() const { return this->MT; }
};
