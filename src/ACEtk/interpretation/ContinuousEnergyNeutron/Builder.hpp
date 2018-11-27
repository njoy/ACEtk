class Builder{
protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"

  // std::vector< Reaction > reactions_;
  tsl::hopscotch_map< int, Reaction > reactions_;

  friend Reaction::Builder;
  Builder& addReaction( Reaction&& reaction ){
    if( reactions_.insert( 
            std::make_pair( reaction.MT, std::move( reaction ) ) ).second ){
      return *this;
    }
    else{
      njoy::Log::error( 
          "Duplicate reaction number (MT): {} added.", reaction.MT );
      throw std::exception();
    }
  }

public:
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ MT, *this }; }

};
