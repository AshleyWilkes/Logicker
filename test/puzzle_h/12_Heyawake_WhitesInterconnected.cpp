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

#include "../data_input_for_tests.h"

namespace {
  using WhitesInterconnectedConstraint = 
    Constraint<
      Transform<
        NarrowTop<CentersFieldId>,
        NarrowBottom<RowId, ColumnId, Value>,
        ContentsA,
        FilterIn< Assert<Value, Equal, White> >,
        ToSet//vezme range a vrati jednoprvkovy range, obsahujici jako jediny prvek Set, jehoz
            //prvky jsou obsah vstupniho range
            //coz je ale jako drbani se pres hlavu, kdyz to delam jen proto, abych obesel
            //  defaultne vlozeny AllOf; coz ale neni tak uplne pravda, delam to trochu i proto,
            //  abych zkonvertoval range (vysledek Contents | Filter) na Set; ach jo, porad totez
            //  dilema: Range, Sequence, Set, jak se to rymuje? 
            //rymuje se to takto: Range, takto dvojice begin - end, je pouze technicky prostredek,
            //  jimz jsou implementovany Sequence a Set, resp. jimz jsou tyto predavany mezi Transformacemi
            //  API Logickera pro zadavani uloh o Range nic nevi, pracuje jen s pojmy Sequence a Set
            //  Sequence a Set oproti tomu v API Logickera existuje a zadavatel operuje s temito pojmy
      >, Assert<
        Interconnected<E, W, N, S>
      >
    >;

  TEST( Heyawake_WhitesInterconnected, ok ) {
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
