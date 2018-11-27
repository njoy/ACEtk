class Builder{
protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"

  std::vector< Reaction > reactions_;

  friend Reaction::Builder;
  Builder& addReaction( Reaction&& reaction ){
    reactions_.push_back( std::move( reaction ) );
    return *this;
  }

public:
  Reaction::Builder reaction(){ return Reaction::Builder{ *this }; }
  
};
