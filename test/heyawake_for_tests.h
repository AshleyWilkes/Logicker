#pragma once

template<int i>
class Constant;

class Equal;

namespace {
  template<typename... Constrs>
  struct TestHeyawake {
    using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
    using Grids_ = Grids<Grid_>;
    using AreaIds_ = Slot<CentersFieldId, AreaId, Index, Scalar>;
    using Values_ = Slot<CentersFieldId, Value, BlackOrWhite, Scalar>;
    using BlackCounts_ = Slot<AreaId, BlackCount, Count, Scalar>;
    using Slots_ = Slots<AreaIds_, Values_, BlackCounts_>;
    using Constraints_ = Constraints< Constrs... >;
  };

  //vsecky membery by zde asi mohly byt static constexpr, to avsak vede k errorum, napr. k
  //  "temporary of non-literal type" erroru, ktery ted nehodlam resit
  template<typename... Constrs>
  class TestHeyawakeBuilder {
    private:
      using PuzzleT = Puzzle<TestHeyawake<Constrs...>>;

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
      ValueInputData valueInputData_ok {{
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 0, 0, 0,
        0, 0, 0, 0, 0 }};
      //tady se dotykaji dve cerna pole, bila pole nejsou propojena a area 1 obsahuje vice cernych nez ma
      ValueInputData valueInputData_nok_1 {{
        0, 1, 0, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 0, 0, 0,
        0, 0, 0, 0, 0 }};
      //tady v prvnim radku neni splnena heyawake_triplets podminka
      ValueInputData valueInputData_nok_2 {{
        0, 0, 0, 0, 0,
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

      PuzzleT make( TestDataInputT& input ) {
        Puzzle<TestHeyawake<Constrs...>> result;
        result << input;
        return result;
      }
    public:
      PuzzleT makeAssignment() {
        TestDataInputT assignmentInput{ 
          sizeInputData, areaIdInputData, {}, blackCountInputData };
        return make( assignmentInput );
      }

      PuzzleT makeSolution_ok() {
        TestDataInputT solutionInput{ 
          sizeInputData, areaIdInputData, valueInputData_ok, blackCountInputData };
        return make( solutionInput );
      }

      //tady se dotykaji dve cerna pole, bila pole nejsou propojena a area 1 obsahuje vice cernych nez ma
      PuzzleT makeSolution_nok_1() {
        TestDataInputT solutionInput{ 
          sizeInputData, areaIdInputData, valueInputData_nok_1, blackCountInputData };
        return make( solutionInput );
      }

      //tady v prvnim radku neni splnena heyawake_triplets podminka
      PuzzleT makeSolution_nok_2() {
        TestDataInputT solutionInput{ 
          sizeInputData, areaIdInputData, valueInputData_nok_2, blackCountInputData };
        return make( solutionInput );
      }
  };
}
