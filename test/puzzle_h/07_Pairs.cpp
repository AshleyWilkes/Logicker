#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "puzzle.h"
#include "../data_input_for_tests.h"
#include "Topology/Rectangle/rectangle.h"
#include "Transformation/Contents.h"
#include "Transformation/Pairs.h"

namespace {
  TEST( Pairs, TheSimplestPairs ) {
    std::vector<int> inputs{ 1, 2, 3 };

    auto pairs = Pairs{}( inputs );
    using DataSet = std::set<typename decltype( pairs.begin() )::value_type>;
    DataSet actualData;
    std::ranges::copy( pairs, std::inserter( actualData, actualData.begin() ));
    DataSet expectedData { Pair{ 1, 1 }, Pair{ 1, 2 }, Pair{ 1, 3 }, Pair{ 2, 1 },
      Pair{ 2, 2 }, Pair{ 2, 3 }, Pair{ 3, 1 }, Pair{ 3, 2 }, Pair{ 3, 3 } };
    ASSERT_EQ( actualData, expectedData );
  }

  TEST( Pairs, SimplePairs2x2 ) {
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

  //- overit, ze range obsahuje ocekavana data
    using DataPair = decltype( pairs.begin() )::value_type;
    using DataSet = std::set<DataPair>;
    DataSet actualData;
    std::ranges::copy( pairs, std::inserter( actualData, actualData.begin() ));

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
      Pair{ v1, v1 }, Pair{ v1, v2 }, Pair{ v1, v3 }, Pair{ v1, v4 },
      Pair{ v2, v1 }, Pair{ v2, v2 }, Pair{ v2, v3 }, Pair{ v2, v4 },
      Pair{ v3, v1 }, Pair{ v3, v2 }, Pair{ v3, v3 }, Pair{ v3, v4 },
      Pair{ v4, v1 }, Pair{ v4, v2 }, Pair{ v4, v3 }, Pair{ v4, v4 }
    };
    ASSERT_EQ( actualData, expectedData );
  }
}
