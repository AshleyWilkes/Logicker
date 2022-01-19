#pragma once

template<typename Id>
struct TestTopology {
  public:
    using Root_ = SlotPart<Id>;
    using Value_ = Slot<Root_, Value, Count, Scalar>;
    using Slots_ = Slots<Value_>;
};

template<typename... Constrs>
struct TestPuzzle {
  using Grid_ = Grid<TestTopology<DefaultGridId>>;
  using Grids_ = Grids<Grid_>;
  using Slots_ = Slots<>;
  using Constraints_ = Constraints<Constrs...>;
};

template<typename... Constraints>
using TestPuzzleT = Puzzle<TestPuzzle<Constraints...>>;

template<typename... Constraints>
Puzzle<TestPuzzle<Constraints...>> makeTestPuzzle() {
  TestPuzzleT<Constraints...> puzzle;
  using ValueInputData = SlotInputData<Value, Count>;
  using TestDataInputT = TestDataInput<ValueInputData>;

  ValueInputData valueInputData{{ 832 }};
  TestDataInputT testInput{ valueInputData };
  puzzle << testInput;
  return puzzle;
}
