#include "gmock/gmock.h"
#include "gtest/gtest.h"

//#define DEBUG_Puzzle_h

#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"
#include "../data_input_for_tests.h"
#include "../transformation_for_tests.h"

namespace {
  //v ../transformation_for_tests mam transformaci z Gridu( std::tuple<Slots> ) a 
  //  transformaci mezi dvema typy
  //z nich vytvarim PuzzleTypy, jeden Ok, nekoliki z ruznych duvodu NOk a testuju, ze ten prvni 
  //  jde pouzit jako Puzzle<PuzzleT> a ty ostatni ne; priciny jednotlivych failu jsou popsany
  //  ve static_assertech, ktere tyto faily testuji

  template<typename Trans1, typename Trans2, typename Assert>
  struct PuzzleWithSimpleConstraint {
    using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
    using Grids_ = Grids<Grid_>;
    using Values_ = Slot<CentersFieldId, Value, BlackOrWhite, Scalar>;
    using Slots_ = Slots<Values_>;
    using Constraints_ = Constraints<
      Constraint<
        Transform< Trans1, Trans2 >,
        Assert
    > >;
  };

  using PuzzleWithSimpleTransformationOk = 
    PuzzleWithSimpleConstraint< GridTrans< int >, Trans< int, Set< int > >, Trans< int, bool > >;

  using PuzzleWithSimpleTransformationNOk_Transform = 
    PuzzleWithSimpleConstraint< GridTrans< int >, Trans< long, Set< int > >, Trans< int, bool > >;

  using PuzzleWithSimpleTransformationNOk_AllOf = 
    PuzzleWithSimpleConstraint< GridTrans< int >, Trans< int, int >, Trans< int, bool > >;

  using PuzzleWithSimpleTransformationNOk_AssertIn = 
    PuzzleWithSimpleConstraint< GridTrans< int >, Trans< int, Set< int > >, Trans< bool, bool > >;

  using PuzzleWithSimpleTransformationNOk_AssertOut = 
    PuzzleWithSimpleConstraint< GridTrans< int >, Trans< int, Set< int > >, Trans< int, int > >;

  template<typename T>
  struct CompilesAsPuzzle : public std::false_type {};
  template<typename T>
  requires( exists<Puzzle<T>> )
  struct CompilesAsPuzzle<T> : public std::true_type {};

  TEST( SimpleTransformation, SimpleTransformationOK_1 ) {
    Puzzle<PuzzleWithSimpleTransformationOk> a;
    static_assert( CompilesAsPuzzle<PuzzleWithSimpleTransformationOk>::value, 
        "This should compile" );
    static_assert( ! CompilesAsPuzzle<PuzzleWithSimpleTransformationNOk_Transform>::value, 
        "This should not compile, Trans2 doesn't follow Trans1" );
    static_assert( ! CompilesAsPuzzle<PuzzleWithSimpleTransformationNOk_AllOf>::value, 
        "This should not compile, Trans2 doesn't lead to Set< T >" );
    static_assert( ! CompilesAsPuzzle<PuzzleWithSimpleTransformationNOk_AssertIn>::value, 
        "This should not compile, Assert doesn't take the Set's elements as argument" );
    static_assert( ! CompilesAsPuzzle<PuzzleWithSimpleTransformationNOk_AssertOut>::value, 
        "This should not compile, Assert doesn't lead to bool" );
  }
}//namespace
