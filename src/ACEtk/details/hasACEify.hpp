template< typename T, typename... Args>
struct hasACEify {
  template<typename U = T, typename = void>
  struct nested : std::false_type {};
  
  template<typename U>
  struct nested < U, decltype(
    std::declval< U >().ACEify( std::declval< ACEtk::Table::Data & >(), 
                                std::declval< Args >()... )
      ) > : std::true_type {};

  constexpr static bool value = nested<>::value;
};
