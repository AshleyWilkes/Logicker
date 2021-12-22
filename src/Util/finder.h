#pragma once

#include <tuple>

template<typename Name>
class SlotPartHasName {
  public:
    template<typename SlotPart>
    constexpr static bool isSatisfiedBy = std::is_same_v<Name, typename SlotPart::Name>;
};

template<typename Name>
class ValueSlotPartHasName {
  public:
    template<typename Slot>
    constexpr static bool isSatisfiedBy = std::is_same_v<Name, typename Slot::ValuePart::Name>;
};

template<typename... Ts>
class Finder;

template<typename CurrentT, typename... Ts, typename Predicate>
requires ( Predicate::template isSatisfiedBy<CurrentT> )
class Finder<std::tuple<CurrentT, Ts...>, Predicate> {
  public:
    using type = CurrentT;
};

template<typename CurrentT, typename... Ts, typename Predicate>
class Finder<std::tuple<CurrentT, Ts...>, Predicate> {
  public:
    using type = typename Finder<std::tuple<Ts...>, Predicate>::type;
};

template<typename Predicate>
class Finder<std::tuple<>, Predicate> {};

