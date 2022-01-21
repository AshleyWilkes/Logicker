#pragma once
#include "Slot/slotPartImplT.h"
#include "input.h"

template<typename T>
struct Type{ using type = Singleton; };

template<typename T>
requires( std::is_void_v<typename T::ValueT> || ! std::is_void_v<typename T::ValueT> )
struct Type<T>{ using type = typename T::ValueT; };

template<typename KeySlotPart, typename ValueSlotPart>
class ScalarImpl {
  private:
    using KeyT = typename Type<KeySlotPart>::type;
    using ValueT = typename ValueSlotPart::ValueT;
    std::map<KeyT, std::optional<ValueT>> map_;
    mutable std::set<ValueT> unique_values_;
    decltype( map_ | std::views::values ) values_ = map_ | std::views::values;
  public:
    template<typename Puzzle>
    auto getKeysRange( const Puzzle& puzzle ) {
      if constexpr ( std::is_same_v<KeyT, Singleton> ) {
        return std::vector<Singleton>{ Singleton{} };
      } else {
        return puzzle.template unique_values<typename KeySlotPart::Name>();
      }
    }

    template<typename Puzzle, typename SlotInput>
    requires( SlotInput::base == Logicker::core::SlotInputBase::KeyBased )
    bool readSlotInput( const Puzzle& puzzle, const SlotInput& slotInput ) {
      auto keysRange = getKeysRange( puzzle );
      bool result = false;
      for ( auto key : keysRange ) {
        auto valueIt = map_.find( key );
        if ( valueIt == map_.end() || ! valueIt->second ) {
          auto newValueOpt = slotInput.get( key );
          if ( newValueOpt ) {
            map_[ key ] = *newValueOpt;
            result = true;
          }
        }
      }
      return result;
    }

    template<typename Puzzle, typename SlotInput>
    requires( SlotInput::base == Logicker::core::SlotInputBase::StreamBased )
    bool readSlotInput( const Puzzle& puzzle, const SlotInput& slotInput ) {
      auto keysRange = getKeysRange( puzzle );
      auto inputIt = slotInput.begin();
      bool result = false;
      for ( auto key : keysRange ) {
        if ( inputIt == slotInput.end() ) throw 1;
        assert( inputIt != slotInput.end() );
        auto valueIt = map_.find( key );
        if ( valueIt == map_.end() || ! valueIt->second ) {
          auto newValueOpt = *inputIt;
          if ( newValueOpt ) {
            map_[ key ] = *newValueOpt;
            result = true;
          }
        }
        ++inputIt;
      }
      values_ = map_ | std::views::values;
      return result;
    }

    template<typename Puzzle, typename DataInput>
    bool tryInput( const Puzzle& puzzle, const DataInput& dataInput ) {
      auto keysRange = getKeysRange( puzzle );
      if ( std::ranges::all_of( keysRange, [ &map_ = map_ ]( auto key ) {
            auto valueIt = map_.find( key );
            return ( valueIt != map_.end() && valueIt->second );
          } ) ) {//all keys exist in map_ and have a value (are not empty optional )
        return false;
      }

      const auto& slotInputOpt = dataInput.template getSlotInput<KeySlotPart, ValueSlotPart>();
      if ( slotInputOpt.has_value() ) {
        return readSlotInput( puzzle, slotInputOpt.value() );
      } else {
        return false;
      }
    }

    std::optional<typename ValueSlotPart::ValueT>
    get( const KeyT& key ) const {
      if ( map_.contains( key ) ) {
        //std::cout << "YES key " << key << " in ScalarImpl.map_\n";
        return map_.at(key); 
      } else {
        //std::cout << "No key " << key << " in ScalarImpl.map_\n";
        return std::optional<typename ValueSlotPart::ValueT>{};
      }
    }

    const auto&
    values() const {
      return values_;
    }

    const auto&
    unique_values() const {
      for ( auto opt_val : values() ) {
        if ( opt_val.has_value() ) {
          unique_values_.insert( *opt_val );
        }
      }
      return unique_values_;
    }
};

class Scalar : public SlotPartImplT {
  public:
    template<typename KeySlotPart, typename ValueSlotPart>
    using Impl = ScalarImpl<KeySlotPart, ValueSlotPart>;
};

