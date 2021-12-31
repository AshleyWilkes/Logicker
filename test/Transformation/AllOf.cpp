#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../transformation_for_tests.h"
#include "Slot/slotPartValueT.h"
#include "Transformation/AllOf.h"

namespace {
  template<typename AllOf, typename Arg>
  struct no_compile : public std::true_type {};
  template<typename AllOf, typename Arg>
  requires( std::is_same_v< typename AllOf::OutputT< Arg >, bool > )
  struct no_compile< AllOf, Arg > : public std::false_type {};

  template<typename AllOf, typename Arg>
  static constexpr bool no_compile_v = no_compile<AllOf, Arg>::value;

  template<typename AllOf, typename Arg>
  static constexpr bool does_compile_v = ! no_compile_v< AllOf, Arg >;

  TEST( Transformation, AllOf_OutputT ) {
    //mam zde Set<int>, Set<bool>, Set<Set<int>>
    //Trans<int, bool>, Trans<bool, bool, Trans<bool, int>
    //proveruju vsechny kombinace
    using Logicker::Transformation::AllOf;
    static_assert( does_compile_v< AllOf< Trans< int, bool > >, Set< int > > );
    static_assert( no_compile_v< AllOf< Trans< int, bool > >, Set< bool > > );
    static_assert( no_compile_v< AllOf< Trans< int, bool > >, Set< Set< int > > > );


    static_assert( no_compile_v< AllOf< Trans< bool, bool > >, Set< int > > );
    static_assert( does_compile_v< AllOf< Trans< bool, bool > >, Set< bool > > );
    static_assert( no_compile_v< AllOf< Trans< bool, bool > >, Set< Set< int > > > );

    static_assert( no_compile_v< AllOf< Trans< bool, int > >, Set< int > > );
    static_assert( no_compile_v< AllOf< Trans< bool, int > >, Set< bool > > );
    static_assert( no_compile_v< AllOf< Trans< bool, int > >, Set< Set< int > > > );
  }
}//namespace
