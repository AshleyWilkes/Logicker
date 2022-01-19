#include "gmock/gmock.h"
#include "gtest/gtest.h"

//#define DEBUG_Puzzle_h

#include "checker.h"
#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"
#include "Transformation/Assert.h"
#include "Transformation/Contents.h"
#include "Transformation/FilterIn.h"
#include "Transformation/NarrowBottom.h"
#include "Transformation/NarrowTop.h"
#include "Transformation/Pairs.h"
#include "../data_input_for_tests.h"

template<int i>
class Constant;

class Equal;

namespace {
  struct Puzzle_Heyawake_BlacksNoTouch {
    using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
    using Grids_ = Grids<Grid_>;
    using AreaIds_ = Slot<CentersFieldId, AreaId, Index, Scalar>;
    using Values_ = Slot<CentersFieldId, Value, BlackOrWhite, Scalar>;
    using BlackCounts_ = Slot<AreaId, BlackCount, Count, Scalar>;
    using Slots_ = Slots<AreaIds_, Values_, BlackCounts_>;
    using Constraints_ = Constraints<
      Constraint<
        Transform<
          NarrowTop<CentersFieldId>,
          NarrowBottom<RowId, ColumnId, Value>,
          ContentsA,
          Pairs,
          FilterIn<Neighbors<E, S>>
        >, Assert<
          CountOf<Value, Black>,
          LessOrEqual,
          Constant<1>
        >
    > >;
  };

  using SizeInputData = SlotInputData<Size, Singleton, Count>;
  using AreaIdInputData = SlotInputData<AreaId, Index>;
  using ValueInputData = SlotInputData<Value, BlackOrWhite>;
  using BlackCountInputData = SlotInputData<BlackCount, Index, Count>;
  using TestDataInputT = 
    TestDataInput<SizeInputData, AreaIdInputData, ValueInputData, BlackCountInputData>;
  //a b b c c   0 1 0 0 0
  //a b b c c   0 0 1 0 0
  //a d e c c   1 0 0 1 0
  //a d e f f   0 1 0 0 0
  //g g g f f   0 0 0 0 0
  //a,c -- contain 1 black
  //e,f -- contain 0 blacks
  //b,d,g -- not given
  TEST( Heyawake_BlacksNoTouch, ok ) {
    SizeInputData sizeInputData {{
      { Singleton{}, 5 },
      { Singleton{}, 5 }
    }};
    AreaIdInputData areaIdInputData {{
      1, 2, 2, 3, 3,
      1, 2, 2, 3, 3,
      1, 4, 5, 3, 3,
      1, 4, 5, 6, 6,
      7, 7, 7, 6, 6 }};
    ValueInputData valueInputData {{
      0, 1, 0, 0, 0,
      0, 0, 1, 0, 0,
      1, 0, 0, 1, 0,
      0, 1, 0, 0, 0,
      0, 0, 0, 0, 0 }};
    BlackCountInputData blackCountInputData {{
      { 1, 1 },
      { 3, 1 },
      { 5, 0 },
      { 6, 0 }
    }};
    TestDataInputT assignmentInput{ sizeInputData, areaIdInputData, {}, blackCountInputData };
    TestDataInputT solutionInput{ sizeInputData, areaIdInputData, valueInputData, blackCountInputData };

    using Heyawake_BlacksNoTouchT = Puzzle<Puzzle_Heyawake_BlacksNoTouch>;
    Checker::Checker<Heyawake_BlacksNoTouchT> checker;
    Heyawake_BlacksNoTouchT assignment, solution;
    assignment << assignmentInput;
    solution << solutionInput;
    //ASSERT_EQ( checker.checkSanity( assignment, solution ), true );
    ASSERT_EQ( checker.checkValidity( solution ), true );
  }
}//namespace
