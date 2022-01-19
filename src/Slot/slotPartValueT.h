#pragma once

class SlotPartValueT {};

template<typename T>
concept CSlotPartValueT = std::is_base_of_v<SlotPartValueT, T>;

class Singleton : public SlotPartValueT {};
inline std::ostream& operator<<( std::ostream& os, Singleton ) { return os << "Singleton"; }
inline bool operator<( const Singleton&, const Singleton& ) { return false; }
inline bool operator==( const Singleton&, const Singleton& ) { return true; }

class Index : public SlotPartValueT { //positive integer higher than 0; [ 1 .. ]
  private:
    int value_;
  public:
    Index() = default;
    Index( int value ) : value_{ value } {}
    operator int() const { return value_; }
};

class Count : public SlotPartValueT { //non-negative integer including 0; [ 0 .. ]
  private:
    int value_;
  public:
    Count() = default;
    Count( int value ) : value_{ value } {}
    operator int() const { return value_; }
};

template<typename T>
class Pair : public SlotPartValueT {
  private:
    std::pair<T, T> value_;
  public:
    using ElementT = T;

    Pair() = default;
    Pair( const std::pair<T, T>& value ) : value_{ value } {}
    Pair( T v1, T v2 ) : value_{ v1, v2 } {}

    std::pair<T, T> getValue() const { return value_; }

    friend bool operator<( const Pair& lhs, const Pair& rhs ) {
      return lhs.value_ < rhs.value_;
    }

    friend bool operator==( const Pair& lhs, const Pair& rhs ) {
      return lhs.value_ == rhs.value_;
    }

    friend std::ostream& operator<<( std::ostream& os, const Pair& pair ) {
      return os << "[" << std::get<0>( pair.value_ ) << ", " << std::get<1>( pair.value_ ) << "]";
    }
};

using CountPair = Pair<Count>;

class Black;
class White;
class BlackOrWhite : public SlotPartValueT { //boolean value: false - white, true - Black
  private:
    bool value_;
  public:
    BlackOrWhite() = default;
    BlackOrWhite( bool value ) : value_{ value } {}
    operator bool() const { return value_; }
};

template<typename T>
struct Set {
  private:
    std::set<T> set_;
  public:
    using ElementT = T;
    std::set<T> toSet() { return set_; }
};
