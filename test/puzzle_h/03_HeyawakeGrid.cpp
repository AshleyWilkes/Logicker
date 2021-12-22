#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <tuple>

#include "puzzle.h"
#include "Topology/Rectangle/rectangle.h"

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

  class MockSizeInput : public Logicker::core::SlotInput<Singleton, Count> {
    public:
      MOCK_METHOD( std::optional<Count>, get, ( const Singleton& ), ( const override ) );
  };

  class MockAreaIdInput : public Logicker::core::SlotInput<Index> {
    public:
      MOCK_METHOD( typename Logicker::core::SlotInput<Index>::Iterator, begin, (), ( const override ) );
      MOCK_METHOD( typename Logicker::core::SlotInput<Index>::Iterator, end, (), ( const override ) );
  };

  class MockValueInput : public Logicker::core::SlotInput<BlackOrWhite> {
    public:
      MOCK_METHOD( typename Logicker::core::SlotInput<BlackOrWhite>::Iterator, 
          begin, (), ( const override ) );
      MOCK_METHOD( typename Logicker::core::SlotInput<BlackOrWhite>::Iterator, 
          end, (), ( const override ) );
  };

  class MockBlackCountInput : public Logicker::core::SlotInput<Index, Count> {
    public:
      MOCK_METHOD( std::optional<Count>, get, ( const Index& ), ( const override ) );
  };

  template<typename MockInputStreamT, typename T = MockInputStreamT::Type>
  class TestInputStream {
    private:
      std::vector<std::optional<T>> values_;
    public:
      TestInputStream( const MockInputStreamT& stream, const std::vector<T>& values ) : values_{} {
        for ( auto v : values ) {
          values_.push_back( v );
        }
        EXPECT_CALL( stream, begin() )
          .WillOnce( testing::Return( values_.begin() ));
        EXPECT_CALL( stream, end() )
          .WillRepeatedly( testing::Return( values_.end() ));
      }
  };

  class TestDataAssignmentInput {
    private:
      std::optional<MockSizeInput> sizeInput{ std::in_place };
      std::optional<TestInputStream<MockAreaIdInput>> areaIds;
      std::optional<MockAreaIdInput> areaIdInput{ std::in_place };
      std::optional<MockValueInput> valueInput{};
      std::optional<MockBlackCountInput> blackCountInput{ std::in_place };
    public:
      TestDataAssignmentInput();
      const std::optional<MockSizeInput>& getSizeInput() const { return sizeInput; }
      const std::optional<MockAreaIdInput>& getAreaIdInput() const { return areaIdInput; }
      const std::optional<MockBlackCountInput>& getBlackCountInput() const { return blackCountInput; }

      template<typename KeySlotPart, typename ValueSlotPart>
      const auto& getSlotInput() const {
        if constexpr( std::is_same_v<typename ValueSlotPart::Name, Size> ) {
          return getSizeInput();
        } else if constexpr( std::is_same_v<typename ValueSlotPart::Name, AreaId> ) {
          return getAreaIdInput();
        } else if constexpr( std::is_same_v<typename ValueSlotPart::Name, Value> ) {
          return valueInput;
        } else if constexpr( std::is_same_v<typename ValueSlotPart::Name, BlackCount> ) {
          return getBlackCountInput();
        } 
      }
  };

  //a b b c c   0 1 0 0 0
  //a b b c c   0 0 1 0 0
  //a d e c c   1 0 0 1 0
  //a d e f f   0 1 0 0 0
  //g g g f f   0 0 0 0 0
  //a,c -- contain 1 black
  //e,f -- contain 0 blacks
  //b,d,g -- not given
  TestDataAssignmentInput::TestDataAssignmentInput() {
    EXPECT_CALL( sizeInput.value(), get( Singleton{} ) )
      .WillOnce( testing::Return( 5 ))
      .WillOnce( testing::Return( 5 ));
    areaIds = TestInputStream<MockAreaIdInput>{areaIdInput.value(), {
      1, 2, 2, 3, 3,
      1, 2, 2, 3, 3,
      1, 4, 5, 3, 3,
      1, 4, 5, 6, 6,
      7, 7, 7, 6, 6 }};
    EXPECT_CALL( blackCountInput.value(), get( Index{ 1 } ) )
      .WillOnce( testing::Return( 1 ) );
    EXPECT_CALL( blackCountInput.value(), get( Index{ 2 } ) )
      .WillRepeatedly( testing::Return( std::optional<Count>{} ) );
    EXPECT_CALL( blackCountInput.value(), get( Index{ 3 } ) )
      .WillOnce( testing::Return( 1 ) );
    EXPECT_CALL( blackCountInput.value(), get( Index{ 4 } ) )
      .WillRepeatedly( testing::Return( std::optional<Count>{} ) );
    EXPECT_CALL( blackCountInput.value(), get( Index{ 5 } ) )
      .WillOnce( testing::Return( 0 ) );
    EXPECT_CALL( blackCountInput.value(), get( Index{ 6 } ) )
      .WillOnce( testing::Return( 0 ) );
    EXPECT_CALL( blackCountInput.value(), get( Index{ 7 } ) )
      .WillRepeatedly( testing::Return( std::optional<Count>{} ) );
  }

  class TestDataSolutionInput {
    private:
      std::optional<MockValueInput> valueInput{ std::in_place };
      TestInputStream<MockValueInput> is;
    public:
      TestDataSolutionInput( const std::vector<BlackOrWhite>& values ) : is{ valueInput.value(), values } {}
      const std::optional<MockValueInput>& getValueInput() const { return valueInput; }

      template<typename KeySlotPart, typename ValueSlotPart>
      const auto& getSlotInput() const {
        if constexpr( std::is_same_v<typename ValueSlotPart::Name, Size> ) {
          return {};
        } else if constexpr( std::is_same_v<typename ValueSlotPart::Name, AreaId> ) {
          return {};
        } else if constexpr( std::is_same_v<typename ValueSlotPart::Name, Value> ) {
          return getValueInput();
        } else if constexpr( std::is_same_v<typename ValueSlotPart::Name, BlackCount> ) {
          return {};
        } 
      }
  };

  TEST( puzzle, HeyawakeGrid ) {
    Puzzle<HeyawakeGrid> puzzle;
    TestDataAssignmentInput dataAssignmentInput;
    puzzle << dataAssignmentInput;
    auto range = puzzle.unique_values<CentersFieldId>();
    ASSERT_EQ( range.size(), 25 );
    auto areaIdRange = puzzle.unique_values<AreaId>();
    ASSERT_EQ( areaIdRange.size(), 7 );
  }

}//namespace
