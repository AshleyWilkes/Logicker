#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "checker.h"
#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"
#include "Transformation/Assert.h"
#include "Transformation/Contents.h"
#include "../data_input_for_tests.h"
#include "../topology_for_tests.h"

namespace {
  TEST(SimplePuzzleWithAConstraint, SanityTestForTestPuzzle) {
    auto puzzle = makeTestPuzzle<>();
    ASSERT_EQ( puzzle.get<Value>().value(), Count( 832 ) );
  }

  using SimpleConstraint_ = 
    Constraint<
      Transform<
        ContentsA
      >, Assert<
        CountOf<Value, Constant<832>>,
        Equal,
        Constant<1>
      >
    >;
  TEST(SimplePuzzleWithAConstraint, SimpleConstraintWithTestPuzzle) {
    auto puzzle = makeTestPuzzle<SimpleConstraint_>();

    Checker::Checker<TestPuzzleT<SimpleConstraint_>> checker;
    ASSERT_EQ( checker.checkValidity( puzzle ), true );
  }

  TEST(SimplePuzzleWithAConstraint, SimpleConstraintWithRectangle1x1) {
    struct SimpleConstraintWithRectanglePuzzle {
      using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
      using Grids_ = Grids<Grid_>;
      using Values_ = Slot<CentersFieldId, Value, Count, Scalar>;
      using Slots_ = Slots<Values_>;
      using Constraints_ = Constraints<SimpleConstraint_>;
    };

    using SizeInputData = SlotInputData<Size, Singleton, Count>;
    using ValueInputData = SlotInputData<Value, Count>;
    using TestDataInputT = TestDataInput<SizeInputData, ValueInputData>;
    SizeInputData sizeInputData {{
      { Singleton{}, 1 },
      { Singleton{}, 1 }
    }};
    ValueInputData valueInputData {{
      832, 45,
       23, 91}};
    TestDataInputT input{ sizeInputData, valueInputData };

    using SimpleConstraintWithRectanglePuzzleT = Puzzle<SimpleConstraintWithRectanglePuzzle>;
    SimpleConstraintWithRectanglePuzzleT puzzle;
    puzzle << input;

    Checker::Checker<SimpleConstraintWithRectanglePuzzleT> checker;
    ASSERT_EQ( checker.checkValidity( puzzle ), true );
  }
}
