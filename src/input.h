#pragma once

#include <ranges>

namespace Logicker::core {
  template<typename...>
  class SlotInput;

  enum class SlotInputBase { KeyBased, StreamBased };

  template<typename T>
  class SlotInput<T> {
    public:
      static constexpr SlotInputBase base = SlotInputBase::StreamBased;
      using Type = T;
      using Iterator = typename std::vector<std::optional<T>>::const_iterator;
      virtual Iterator begin() const = 0;
      virtual Iterator end() const = 0;
      virtual ~SlotInput() = default;
  };

  template<typename K, typename V>
  class SlotInput<K, V> {
    public:
      static constexpr SlotInputBase base = SlotInputBase::KeyBased;
      virtual std::optional<V> get( const K& ) const = 0;
      virtual ~SlotInput() = default;
  };

  template<typename InputKeyT = std::string>
  class DataInput {
    public:
      template<typename T>
      std::optional<SlotInput<T>> getSlotInput( const InputKeyT& = {} );

      template<typename K, typename V>
      std::optional<SlotInput<K, V>> getSlotInput( const InputKeyT& = {} );
  };
};
