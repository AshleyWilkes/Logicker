#pragma once

template<typename... Conditions>
struct Neighbors { 
  template<typename T>
  static bool apply( const T& pair ) { 
    return ( Conditions::apply( pair ) || ... );
  }
};

template<typename InputRange, typename Predicate>
struct FilterInI : public std::ranges::view_interface<FilterInI<InputRange, Predicate>> {
  private:
    using InnerIterator = std::ranges::iterator_t<InputRange>;
    using InnerSentinel = std::ranges::sentinel_t<InputRange>;
    InnerIterator m_begin;
    InnerSentinel m_end;
  public:
    FilterInI( InputRange&& input ) : m_begin{ input.begin() }, m_end{ input.end() } {}

    class Sentinel {};
    class Iterator {
      private:
        InnerIterator m_current;
        InnerSentinel m_end;
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = std::ranges::range_value_t<InputRange>;

        Iterator() = default;
        Iterator( const FilterInI* parent ) : m_current{ parent->m_begin }, m_end{ parent->m_end } {
          advanceIfNeeded();
        }

        void advanceIfNeeded() {
          while ( m_current != m_end && ( ! Predicate::apply( *m_current ) ) ) {
            ++m_current;
          }
        }

        value_type operator*() const { return *m_current; }
        Iterator& operator++() { ++m_current; advanceIfNeeded(); return *this; }
        Iterator& operator++( int ) { return ++*this; }

        friend constexpr bool operator==( const Iterator& lhs, const Iterator& rhs ) { 
          return lhs.m_current == rhs.m_current; 
        }
        friend constexpr bool operator==( const Iterator& lhs, const Sentinel& ) { 
          return lhs.m_current == lhs.m_end; 
        }
        friend constexpr bool operator!=( const Iterator& lhs, const Iterator& rhs ) {
          return !( lhs == rhs );
        }
    };

    Iterator begin() const { return { this }; }
    Sentinel end() const { return {}; }
};

template<typename Predicate>
inline constexpr std::views::__adaptor::_RangeAdaptorClosure FilterInImpl
  = [] <typename InputRange> ( InputRange&& inputRange ) {
    return FilterInI<InputRange, Predicate>{ 
      std::forward<InputRange>( inputRange ) };
  };

template<typename InputRange, typename Predicate>
inline constexpr bool std::ranges::enable_borrowed_range<FilterInI<InputRange, Predicate>> = true;

template<typename Predicate>
struct FilterIn {
  template<typename InputT>
  auto operator()( const InputT& input ) {
    auto inputRange = std::ranges::subrange{ input.begin(), input.end() };
    return inputRange | FilterInImpl<Predicate>; 
  }

  template<typename InputSet>
  using OutputT = decltype( std::declval<FilterIn>()( std::declval<InputSet>() ) );
};
