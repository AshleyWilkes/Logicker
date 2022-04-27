#pragma once

template<typename InputRange>
struct PairsI : public std::ranges::view_interface<PairsI<InputRange>> {
  private:
    using IteratorT = std::ranges::iterator_t<InputRange>;
    using SentinelT = std::ranges::sentinel_t<InputRange>;
    IteratorT m_begin;
    SentinelT m_end;
  public:
    PairsI( InputRange&& input ) : m_begin{ input.begin() }, m_end{ input.end() } {}

    class OuterSent {};
    class OuterIter {
      private:
        IteratorT m_begin, m_cur1, m_cur2;
        SentinelT m_end;
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = Pair<std::ranges::range_value_t<InputRange>>;

        OuterIter() = default;
        OuterIter( const PairsI* parent ) : m_begin{ parent->m_begin }, m_cur1{ parent->m_begin }, 
          m_cur2{ parent->m_begin }, m_end{ parent->m_end } {}

        value_type operator*() const { return Pair{ *m_cur1, *m_cur2 }; }
        OuterIter& operator++() { 
          ++m_cur2;
          if ( m_cur2 == m_end ) {
            m_cur2 = m_begin;
            ++m_cur1;
          }
          return *this; 
        }
        OuterIter& operator++( int ) { return ++*this; }

        friend constexpr bool operator==( const OuterIter& lhs, const OuterIter& rhs) { 
          return lhs.m_cur1 == rhs.m_cur1 && lhs.m_cur2 == rhs.m_cur2; 
        }
        friend constexpr bool operator==( const OuterIter& lhs, const OuterSent& ) {
          return lhs.m_cur1 == lhs.m_end;
        }
        friend constexpr bool operator!=( const OuterIter& lhs, const OuterIter& rhs) { 
          return !( lhs == rhs ); 
        }
    };
    OuterIter begin() const { return { this }; }
    OuterSent end() const { return {}; }
};

inline constexpr std::views::__adaptor::_RangeAdaptorClosure PairsImpl
  = [] <typename InputRange> ( InputRange&& inputRange ) {
    return PairsI<InputRange>{ 
      std::forward<InputRange>( inputRange ) };
  };

template<typename InputRange>
inline constexpr bool std::ranges::enable_borrowed_range<PairsI<InputRange>> = true;

struct Pairs {
  template<typename InputT>
  auto operator()( const InputT& input ) { 
    auto inputRange = std::ranges::subrange{ input.begin(), input.end() };
    return inputRange | PairsImpl; 
  }

  template<typename InputSet>
  using OutputT = decltype( std::declval<Pairs>()( std::declval<InputSet>() ) );
};
