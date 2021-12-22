#pragma once

//cili zde ma byt easy-to-use mechanismus na tvorbu DataInputu, takto objektu, jejz lze
//  poslat Puzzlu pomoci operatoru<<
//ma jit snadno zadat, jake vsechny SlotInputy DataInput podporuje
//SlotInputy ma jit snadno inicializovat MockSlotInputem; chybi-li tato inicializace,
//  ma se SlotInput automaticky vracet jako prazdny std::optional
//MockSlotInputu ma jit snadno zadat obsah (skutecna data), jejz ma vracet, a to jak pro
//  KeyBased, tak pro StreamBased SlotInputy; oba druhy MockSlotInputu maji rovnez automaticky
//  mit nastavene vhodne EXPECT_CALLy

using Logicker::core::SlotInput;

template<typename...>
class SlotInputData;

template<typename Name_, typename ValueT_>
class SlotInputData<Name_, ValueT_> {
  private:
    std::vector<std::optional<ValueT_>> values_;
  public:
    using Name = Name_;

    SlotInputData() = default;
    SlotInputData( const std::vector<ValueT_>& values ) {
      for ( auto v : values ) {
        values_.push_back( v );
      }
    }

    typename SlotInput<ValueT_>::Iterator begin() { return values_.begin(); }
    typename SlotInput<ValueT_>::Iterator end() { return values_.end(); }
};

template<typename Name_, typename Key_, typename Value_>
class SlotInputData<Name_, Key_, Value_> {
  private:
    using DataT = std::vector<std::pair<Key_, Value_>>;
    DataT data_;
  public:
    using Name = Name_;

    SlotInputData( const DataT& expectedCalls ) : data_{ expectedCalls } {}

    const DataT& getData() { return data_; }
};

template<typename>
class MockSlotInput;

template<typename>
class HasMockSlot;

template<typename Name_, typename ValueT_>
class MockSlotInput<SlotInputData<Name_, ValueT_>> : public SlotInput<ValueT_> {
  private:
    using SlotData = SlotInputData<Name_, ValueT_>;
    SlotData slotData;
  public:
    MockSlotInput( std::optional<SlotData>& slotData_ ) {
      if ( slotData_.has_value() ) {
        slotData = slotData_.value();
        EXPECT_CALL( *this, begin() )
          .WillOnce( testing::Return( slotData.begin() ));
        EXPECT_CALL( *this, end() )
          .WillRepeatedly( testing::Return( slotData.end() ));
      }
    }

    MOCK_METHOD( typename SlotInput<ValueT_>::Iterator, begin, (), ( const override ) );
    MOCK_METHOD( typename SlotInput<ValueT_>::Iterator, end, (), ( const override ) );
};

template<typename Name_, typename ValueT_>
class HasMockSlot<SlotInputData<Name_, ValueT_>> {
  private:
    using SlotData = SlotInputData<Name_, ValueT_>;
    bool exists;
    std::optional<MockSlotInput<SlotData>> mockSlot;
    std::optional<MockSlotInput<SlotData>> emptySlot;
  public:
    HasMockSlot( std::optional<SlotData>& slotData ) : 
      exists{ slotData.has_value() }, mockSlot{ slotData } {}

    const std::optional<MockSlotInput<SlotData>>& getAsMockSlotInput() const { 
      if ( exists ) {
        return mockSlot; 
      } else {
        return emptySlot;
      }
    }
};

template<typename Name_, typename KeyT_, typename ValueT_>
class MockSlotInput<SlotInputData<Name_, KeyT_, ValueT_>> : public SlotInput<KeyT_, ValueT_> {
  private:
    using SlotData = SlotInputData<Name_, KeyT_, ValueT_>;
  public:
    MockSlotInput( std::optional<SlotData>& slotData ) {
      if ( slotData.has_value() ) {
        EXPECT_CALL( *this, get( testing::_ ) )
          .WillRepeatedly( testing::Return( std::optional<ValueT_>{} ) );
        for ( const auto& expCall : slotData.value().getData() ) {
          EXPECT_CALL( * this, get( std::get<0>( expCall ) ))
            .WillRepeatedly( testing::Return( std::get<1>( expCall ) ));
        }
      }
    }

    MOCK_METHOD( std::optional<ValueT_>, get, ( const KeyT_& ), ( const override ) );
};

template<typename Name_, typename KeyT_, typename ValueT_>
class HasMockSlot<SlotInputData<Name_, KeyT_, ValueT_>> {
  private:
    using SlotData = SlotInputData<Name_, KeyT_, ValueT_>;
    bool exists;
    std::optional<MockSlotInput<SlotData>> mockSlot;
    std::optional<MockSlotInput<SlotData>> emptySlot;
  public:
    HasMockSlot( std::optional<SlotData>& slotData ) : 
      exists{ slotData.has_value() }, mockSlot{ slotData }{}

    const std::optional<MockSlotInput<SlotData>>& getAsMockSlotInput() const { 
      if ( exists ) {
        return mockSlot; 
      } else {
        return emptySlot;
      }
    }
};

template<typename... SlotInputData>
class TestDataInput : public HasMockSlot<SlotInputData>... {
  public:
    //TestDataInput( std::optional<SlotInputData>... slotInputData ) : HasMockSlot<SlotInputData>{ std::move( slotInputData ) }... {}
    TestDataInput( std::optional<SlotInputData>... slotInputData ) : HasMockSlot<SlotInputData>{ slotInputData }... {}

  template<typename KeySlotPart, typename ValueSlotPart>
  const auto& getSlotInput() const {
    return getSlotInputImpl<KeySlotPart, ValueSlotPart, SlotInputData...>();
  }

  template<typename KeySlotPart, typename ValueSlotPart, typename CurrentSlot, typename... FurtherSlots>
  const auto& getSlotInputImpl() const {
    if constexpr( std::is_same_v<typename ValueSlotPart::Name, typename CurrentSlot::Name> ) {
      return HasMockSlot<CurrentSlot>::getAsMockSlotInput();
    } else {
      return getSlotInputImpl<KeySlotPart, ValueSlotPart, FurtherSlots...>();
    }
  }
};
