class Base {
protected: 
  const Table& table;
  const int MT;
  const int reactionIndex;

  Base( const Table& table, int ID, int rIndex ):
      table( table ),
      MT( ID ),
      reactionIndex( rIndex )
  { }

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Reaction/Base/src/getReactionIndex.hpp"
  int ID() const { return this->MT; }
  int Index() const { return this-> reactionIndex; }
};
