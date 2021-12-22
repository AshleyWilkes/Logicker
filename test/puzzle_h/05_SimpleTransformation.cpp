#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"
#include "../data_input_for_tests.h"

namespace {
  //GridTrans<Out> ma OutputT = Out, prave kdyz InputSlots je std::tuple
  //Trans<In, Out> ma OutputT = Out, prave kdyz InputSlots == In
  //jinak receno mam transformaci z Gridu( std::tuple<Slots> ) a mam transformaci mezi dvema typy
  //z nich vytvarim dva PuzzleT, jeden Ok, jeden NOk a testuju, ze ten prvni jde pouzit jako
  //  Puzzle<PuzzleT> a ten druhy nejde
  //
  //soucasna implementace resi pouze navaznosti v ramci Constraint::Transformation, Constraint::Assert
  //se zcela ignoruje. Melo by to byt tak, ze se predpoklada, ze Transformation konci std::tuplem
  //a Assert zacina jednotlivym prvkem toho tuplu a konci boolem
  //coz by tedy melo jit vyresit tim, ze by se mezi Transformation a Assert vlozila transformace
  //AllOf a tim by vznikla jedna rada transformaci vedouci od Gridu k vyslednemu booleanu
  //tim by byla pripravena cesta k checkeru
  //takze tech NOku bude treba pripravit jeste alespon 1, kterej bude resit navaznost mezi Transform
  //a Assert, a pak 1, kterej bude resit, ze koncime boolem
  //hm, boolem proste konci AllOf, co jineho by vracel; ten teda musi overovat, ze jeho Transform
  //zacina spravnym typem prvku a konci boolem
  template<typename...>
  struct TuplesOnly;

  template<typename... Ts, typename Out>
  struct TuplesOnly<std::tuple<Ts...>, Out> {
    using OutputT = Out;
  };

  template<typename Out>
  struct GridTrans {
    template<typename InputSlots>
    using OutputT = typename TuplesOnly<InputSlots, Out>::OutputT;
  };

  template<typename In, typename Input, typename Out>
  struct InOnly;

  template<typename In, typename Out>
  struct InOnly<In, In, Out> {
    using OutputT = Out;
  };

  template<typename In, typename Out>
  struct Trans {
    template<typename InputSlots>
    using OutputT = typename InOnly<In, InputSlots, Out>::OutputT;
  };

  struct PuzzleWithSimpleTransformationOk {
    using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
    using Grids_ = Grids<Grid_>;
    using Values_ = Slot<CentersFieldId, Value, BlackOrWhite, Scalar>;
    using Slots_ = Slots<Values_>;
    using Constraints_ = Constraints<
      Constraint<
        Transform<
          GridTrans<int>,
          Trans<int, std::tuple<int>>
        >,
        Trans<int, bool>
      >
    >;
  };

  struct PuzzleWithSimpleTransformationNOk {
    using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
    using Grids_ = Grids<Grid_>;
    using Values_ = Slot<CentersFieldId, Value, BlackOrWhite, Scalar>;
    using Slots_ = Slots<Values_>;
    using Constraints_ = Constraints<
      Constraint<
        Transform<
          GridTrans<int>,
          Trans<long, std::tuple<int>>
        >,
        Trans<int, bool>
      >
    >;
  };

  template<typename T>
  struct CompilesAsPuzzle : public std::false_type {};
  template<typename T>
  requires( exists<typename Puzzle<T>::Constraints_> )
  struct CompilesAsPuzzle<T> : public std::true_type {};

  TEST( SimpleTransformation, SimpleTransformationOK_1 ) {
    static_assert( CompilesAsPuzzle<PuzzleWithSimpleTransformationOk>::value, "This should compile" );
    static_assert( ! CompilesAsPuzzle<PuzzleWithSimpleTransformationNOk>::value, "This should not compile" );
  }
}//namespace
