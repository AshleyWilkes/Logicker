#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"
#include "../data_input_for_tests.h"

namespace {
  struct HeyawakeGrid {
    using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
    using Grids_ = Grids<Grid_>;
    using AreaIds_ = Slot<CentersFieldId, AreaId, Index, Scalar>;
    using Values_ = Slot<CentersFieldId, Value, BlackOrWhite, Scalar>;
    using BlackCounts_ = Slot<AreaId, BlackCount, Count, Scalar>;
    using Slots_ = Slots<AreaIds_, Values_, BlackCounts_>;
    using Constraints_ = Constraints<>;
  };

  TEST( HeyawakeGridWithTestDataInput, HeyawakeGrid ) {
    Puzzle<HeyawakeGrid> puzzle;
    using SizeInputData = SlotInputData<Size, Singleton, Count>;
    using AreaIdInputData = SlotInputData<AreaId, Index>;
    using ValueInputData = SlotInputData<Value, BlackOrWhite>;
    using BlackCountInputData = SlotInputData<BlackCount, Index, Count>;
    using TestDataInputT = 
      TestDataInput<SizeInputData, AreaIdInputData, ValueInputData, BlackCountInputData>;

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
    puzzle << assignmentInput;
    auto range = puzzle.unique_values<CentersFieldId>();
    ASSERT_EQ( range.size(), 25 );
    auto areaIdRange = puzzle.unique_values<AreaId>();
    ASSERT_EQ( areaIdRange.size(), 7 );
  }
}


