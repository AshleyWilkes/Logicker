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

class CountPair : public SlotPartValueT {
  private:
    std::pair<Count, Count> value_;
  public:
    CountPair() = default;
    CountPair( const std::pair<Count, Count>& value ) : value_{ value } {}

    std::pair<Count, Count> getValue() { return value_; }

    friend bool operator<( const CountPair& lhs, const CountPair& rhs ) {
      return lhs.value_ < rhs.value_;
    }

    friend bool operator==( const CountPair& lhs, const CountPair& rhs ) {
      return lhs.value_ == rhs.value_;
    }

    friend std::ostream& operator<<( std::ostream& os, const CountPair& pair ) {
      return os << "[" << std::get<0>( pair.value_ ) << ", " << std::get<1>( pair.value_ ) << "]";
    }
};

class Black;
class White;
class BlackOrWhite : public SlotPartValueT { //boolean value: false - white, true - Black
  private:
    bool value_;
  public:
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

template<typename T>
struct Pair{
  using ElementT = T;
};
