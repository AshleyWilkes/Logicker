#include "gtest/gtest.h"

//jsou puzzly, kde givens jsou specialni policka, pro ktera plati jina pravidla, typicky se rovnou vi
//  jakou hodnotu Value maji, a jsou puzzly, kde givens jsou mimo policek s Value
//jsou puzzly, kde topologie je predem dana, protoze jen jedna dava smysl, a jsou puzzly, ktere potrebuji
//  topologii jako parametr
//regions v puzzlech mají trojí původ:
//  jsou jasné z typu úlohy (Hitori)
//  jsou jasné ze zadání úlohy (Sudoku)
//  jsou jasné až z řešení úlohy (Clouds)

/*namespace {
  //musi se specifikovat:
  //topologie Rectangle
  //size je read from input
  //centers jsou given nebo value
  //given je number
  //value je Map<Direction{N, E, S, W}, Bool>
  //conditions:
  //??
  //pocet prilehlych trojuhelniku k poli s cislem
  //kazde pole bez cisla ma 0 nebo 2 Black hodnoty
  //White hodnoty tvori obdelniky, ktere se nedotykaji hranou
  //??
  class Shakashaka : public RectanglePuzzleGivenValue {
    using Given = Number<4>;
    using Value = Map<UnorientedDirection, BlackOrWhite>;
  };
  class Shakashaka : public Puzzle {
    using Topology_ = Rectangle; 
    using Given_ = Number<4>; 
    using Value_ = Map<UnorientedDirection, BlackOrWhite>;
  };
  template<typename Topology = Rectangle, typename Id = "DefaultGridId">
  class Shakashaka {
    using Center = 
      Value<"Given", Number<4>>
      ::or<"Value", Map<Topology::UnorientedDirection, BlackOrWhite>>;
    using Grid = Grid<Id, Topology>
      ::addSlot<Id, "Grid", Value<"Size", Value<"Width", Index>::add<"Height", Index>, SizeInput>>
      ::addSlot<Id, "CenterField", Topology::CenterField::add<Center>>;
  };
}*/

template<typename T>
class MyTest : public testing::Test {};

TYPED_TEST_SUITE_P(MyTest);

//testovani ma bejt parametrizovany; ma existovat jedna sablona, do ktery se narve
//  typ Puzzle, normalizovany Grid, zadani a reseni
//prvni test by mel overit, ze se classa spravne prelozi do normalizovaneho tvaru Puzzlu
TYPED_TEST_P(MyTest, ShortPuzzleTypeCorrectlyTransformsToNormalizedGrid) {
  ::testing::StaticAssertTypeEq<
      typename TypeParam::ShortPuzzleType, typename TypeParam::NormalizedGridType>();
}

//druhy test by mel overit, ze reseni examplu odpovida zadani -- sanity check
//treti test by mel overit, ze reseni examplu je resenim, tedy ze splnuje podminky -- validity check
//ctvry test by mel overit, ze solver vyresi example zadani -- toto ale neni Logicker, nybrz BenoBrok
//
//
REGISTER_TYPED_TEST_SUITE_P(
    MyTest,
    ShortPuzzleTypeCorrectlyTransformsToNormalizedGrid);



struct MyToBeTestedType {
  //using ShortPuzzleType = Shakashaka;
  //using NormalizedGridType = ShakashakaGrid;
  using ShortPuzzleType = int;
  using NormalizedGridType = int;
  static constexpr NormalizedGridType assignment() {
    return 1;
  }
  static constexpr NormalizedGridType solution() {
    return 2;
  }
};

using Implementations = testing::Types<MyToBeTestedType>;
INSTANTIATE_TYPED_TEST_SUITE_P(
    MyTestSuite,
    MyTest,
    Implementations);
