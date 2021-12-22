#pragma once

class SlotPartValueT {};

template<typename T>
concept CSlotPartValueT = std::is_base_of_v<SlotPartValueT, T>;

class Singleton : public SlotPartValueT {};

inline bool operator<( const Singleton&, const Singleton& ) { return false; }
inline bool operator==( const Singleton&, const Singleton& ) { return true; }

class Index : public SlotPartValueT { //positive integer higher than 0; [ 1 .. ]
  private:
    int value_;
  public:
    Index( int value ) : value_{ value } {}
    operator int() const { return value_; }
};

class Count : public SlotPartValueT { //non-negative integer including 0; [ 0 .. ]
  private:
    int value_;
  public:
    Count( int value ) : value_{ value } {}
    operator int() const { return value_; }
};

class CountPair : public SlotPartValueT {
  private:
    std::pair<Count, Count> value_;
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
