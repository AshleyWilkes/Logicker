#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "puzzle.h"
#include "../data_input_for_tests.h"
#include "Topology/Rectangle/rectangle.h"
#include "Transformation/Contents.h"
#include "Transformation/Pairs.h"
#include "Transformation/FilterIn.h"

namespace {
  struct IsOdd {
    public:
      static bool apply( int i ) { return i % 2 == 1; }
  };

  TEST( Filter, TheSimplestFilter ) {
    std::vector<int> inputs{ 1, 2, 3, 4, 5, 6 };
    auto filtered = FilterIn<IsOdd>{}( inputs );

    using DataSet = std::set<typename decltype( filtered.begin() )::value_type>;
    DataSet actualData;
    std::ranges::copy( filtered, std::inserter( actualData, actualData.begin() ));
    DataSet expectedData { 1, 3, 5 };
    ASSERT_EQ( actualData, expectedData );
  }

  TEST( Filter, SimpleFilter2x2 ) {
  //- vytvorit tree jako typ podle predpokladu testu
    struct TestGrid {
      using Grid_ = Grid<Rectangle<DefaultGridId, Centers>>;
      using Grids_ = Grids<Grid_>;
      using Values_ = Slot<CentersFieldId, Value, Count, Scalar>;
      using Slots_ = Slots<Values_>;
      using Constraints_ = Constraints<>;
    };
  //- vytvorit grid, ktery umi obsahovat tree data 
    using Puzzle_ = Puzzle<TestGrid>;
    Puzzle_ puzzle;
    using SizeInputData = SlotInputData<Size, Singleton, Count>;
    using ValueInputData = SlotInputData<Value, Count>;
    using TestDataInputT = TestDataInput<SizeInputData, ValueInputData>;

    SizeInputData sizeInputData {{
      { Singleton{}, 2 },
      { Singleton{}, 2 }
    }};
    ValueInputData valueInputData {{
      23, 42, 
       1, 988
    }};
    TestDataInputT testInput{ sizeInputData, valueInputData };
    puzzle << testInput;

  //- pomoci Contents vytvorit range, odpovidajici datum v gridu
    auto contents = Contents<typename Puzzle_::SlotsTypesTree_>( 
        std::ranges::single_view{ puzzle.getGrid() } );

  //- pomoci Pairs vytvorit range, odpovidajici parum hodnot z gridu
    auto pairs = Pairs{}( contents );

  //- pomoci Filter vyfiltrovat ty pary, ktere obsahuji sousedni policka
    auto filtered = FilterIn<Neighbors<E, S>>{}( pairs );

  //- overit, ze range obsahuje ocekavana data
    using DataPair = decltype( filtered.begin() )::value_type;
    using DataSet = std::set<DataPair>;
    DataSet actualData;
    std::ranges::copy( filtered, std::inserter( actualData, actualData.begin() ));

    using DataValue = typename DataPair::ElementT;
    DataValue v1 = std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 1 }, Index{ 1 }, Index{ 1 }, Count{ 23 } );
    DataValue v2 = std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 2 }, Index{ 1 }, Index{ 2 }, Count{ 42 } );
    DataValue v3 = std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 3 }, Index{ 2 }, Index{ 1 }, Count{ 1 } );
    DataValue v4 = std::make_tuple<>( types_tree::__detail::root_value{}, Singleton{}, 
          CountPair( std::make_pair<Count, Count>( Count{ 2 }, Count { 2 } ) ), Count{ 2 }, 
          Count{ 2 }, Index{ 4 }, Index{ 2 }, Index{ 2 }, Count{ 988 } );
    DataSet expectedData {
      Pair{ v1, v2 }, Pair{ v1, v3 }, Pair{ v2, v4 }, Pair{ v3, v4 }
    };
    ASSERT_EQ( actualData, expectedData );
  }
}

