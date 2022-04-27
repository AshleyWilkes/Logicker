#include "gmock/gmock.h"
#include "gtest/gtest.h"

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
#include "../heyawake_for_tests.h"

namespace {
  using BlacksNoTouchConstraint = 
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
    >;

  TEST( Heyawake_BlacksNoTouch, ok ) {
    using Heyawake_BlacksNoTouchT = Puzzle<TestHeyawake<BlacksNoTouchConstraint>>;
    Checker::Checker<Heyawake_BlacksNoTouchT> checker;
    Heyawake_BlacksNoTouchT solution = TestHeyawakeBuilder<BlacksNoTouchConstraint>{}.makeSolution_ok();
    ASSERT_EQ( checker.checkValidity( solution ), true );
  }

  TEST( Heyawake_BlacksNoTouch, nok ) {
    using Heyawake_BlacksNoTouchT = Puzzle<TestHeyawake<BlacksNoTouchConstraint>>;
    Checker::Checker<Heyawake_BlacksNoTouchT> checker;
    Heyawake_BlacksNoTouchT solution = TestHeyawakeBuilder<BlacksNoTouchConstraint>{}.makeSolution_nok_1();
    ASSERT_EQ( checker.checkValidity( solution ), false );
  }
}//namespace
