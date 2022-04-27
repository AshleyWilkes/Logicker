#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "checker.h"
#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"
#include "../data_input_for_tests.h"
#include "../heyawake_for_tests.h"

namespace {
  TEST( Heyawake_Checker_CheckSanity, ok ) {
    using Heyawake_NoConstraintT = Puzzle<TestHeyawake<>>;
    Checker::Checker<Heyawake_NoConstraintT> checker;
    Heyawake_NoConstraintT assignment = TestHeyawakeBuilder<>{}.makeAssignment();
    Heyawake_NoConstraintT solution = TestHeyawakeBuilder<>{}.makeSolution_ok();
    ASSERT_EQ( checker.checkSanity( assignment, solution ), true );
  }

  TEST( Heyawake_Checker_CheckSanity, nok_solutionMissesAKey ) {
    ASSERT_EQ( true, false );
  }

  TEST( Heyawake_Checker_CheckSanity, nok_solutionHasValueNotConsistentWithAssignment ) {
    ASSERT_EQ( true, false );
  }
}
