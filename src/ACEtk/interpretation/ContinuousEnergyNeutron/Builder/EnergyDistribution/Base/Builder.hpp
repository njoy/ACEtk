template< typename Derived, typename ParentBuilder >
class Builder {

protected:
  std::reference_wrapper< ParentBuilder > parent;
  double probability_;

public:
  Builder( double probability, ParentBuilder& parent ):
    probability_( probability ),
    parent( parent )
  { }

};
