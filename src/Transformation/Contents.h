#pragma once

template<typename, int>
struct TreeToTuple;

template<typename... Types, int Index>
struct TreeToTuple<types_tree::__detail::types_tree_impl<std::tuple<Types...>>, Index> {
  using value = std::tuple< typename std::tuple_element<Index, Types>::type...>;
};

template<typename, typename>
struct tuple_type_to_index;

template<typename T, typename... Ts>
struct tuple_type_to_index<T, std::tuple<T, Ts...>> {
  static constexpr std::size_t value = 0;
};

template<typename T, typename First, typename... Rest> 
struct tuple_type_to_index<T, std::tuple<First, Rest...>> {
  static constexpr std::size_t value = tuple_type_to_index<T, std::tuple<Rest...>>::value + 1;
};

template<typename T>
struct tuple_type_to_index<T, std::tuple<>> {
  static constexpr std::size_t value = 0;
};

template<typename... Ts>
constexpr std::size_t tuple_type_to_index_v = tuple_type_to_index<Ts...>::value;

template<typename Grid, typename InputTree>
struct ContentsValue {
  public:
    using Names = typename TreeToTuple<InputTree, 0>::value;
    using Values = typename TreeToTuple<InputTree, 2>::value;

    template<typename Name>
    struct NameToIndex {
      static constexpr size_t value = tuple_type_to_index_v<Name, Names>;
    };

    template<typename Name>
    static constexpr size_t NameToIndex_v = NameToIndex<Name>::value;
  private:
    Values values; 
  public:
    ContentsValue() = default;
    ContentsValue( const Values& values_ ) : values{ values_ }{}

    template<typename Name, size_t Index = NameToIndex_v<Name>, 
        typename ValueT=std::tuple_element_t<Index, Values>>
    void set( const ValueT& value ) {
      std::get<Index>( values ) = value;
    }

    template<typename Name, size_t Index = NameToIndex_v<Name>, 
        typename ValueT=std::tuple_element_t<Index, Values>>
    ValueT get() const {
      return std::get<Index>( values );
    }

    friend bool operator<( const ContentsValue& lhs, const ContentsValue& rhs ) {
      return lhs.values < rhs.values;
    }

    friend bool operator==( const ContentsValue& lhs, const ContentsValue& rhs ) {
      return lhs.values == rhs.values;
    }

    //ten NextIndex zdehle je vysledek historickeho vyvoje, patri dat
    //  pryc a v miste pouziti normalne pouzit odcitani
    template<std::size_t Index, std::size_t NextIndex = Index - 1>
    friend void printValues( std::ostream& os, const ContentsValue& values ) {
      if constexpr( Index > 1 ) {
        printValues<NextIndex>( os, values );
      }
      using Name = std::tuple_element_t<Index - 1, Names>;
      os << typeid(Name).name() << ": " << values.template get<Name>() << '\n';
    }

    friend std::ostream& operator<<( std::ostream& os, const ContentsValue& values ) {
      printValues<std::tuple_size_v<Names>>( os, values );
      return os;
    }
};

template<typename GridSingleView, typename SlotsTypesTree>
class ContentsImpl : public std::ranges::view_interface<ContentsImpl<GridSingleView, SlotsTypesTree>> {
  private:
    using Grid = std::ranges::range_value_t<GridSingleView>;
    Grid m_grid;
  public:
    //predpokladam, ze grid je single_view a m_grid je jeho obsah
    ContentsImpl( GridSingleView&& gridSingleView ) : m_grid{ *(gridSingleView.begin()) } {}

    //no hele implementace InnerIter a InnerIters je sice humus, ale nechci tady stravit mladi,
    //  upravim ji nekdy jindy
    template<typename SlotPart>
    class InnerIter {
      using SlotName = typename std::tuple_element<0, SlotPart>::type;
      using SubTree = typename SlotsTypesTree::template subtree<SlotName>;
      using SubTreeTuple = typename SubTree::tuple;
      //using ValuesT = decltype( std::declval<Grid>().template values<SlotName>() );
      using IteratorT = decltype( std::declval<Grid>().template values<SlotName>().begin() );
      using SentinelT = decltype( std::declval<Grid>().template values<SlotName>().end() );

      public:
        ContentsImpl* m_parent;
        //ValuesT m_range;
        IteratorT m_begin, m_current;
        SentinelT m_end;

        InnerIter() = default;
        //InnerIter( ContentsImpl* parent ) : m_range{ parent->m_grid.template values<SlotName>() },
          //m_begin{ m_range.begin() }, m_current{ m_begin }, m_end{ m_range.end() } {}
        InnerIter( ContentsImpl* parent ) : m_parent{ parent },
          m_begin{ parent->m_grid.template values<SlotName>().begin() },
          m_current{ m_begin }, m_end{ parent->m_grid.template values<SlotName>().end() } {}

        InnerIter& operator++() { m_current++; return *this; }
        InnerIter& operator++( int ) { return ++*this; }

        template<std::size_t Index, typename ContentsV>
        void fillSlot( ContentsV& output ) const {
          using Slot = std::tuple_element_t<Index, SubTreeTuple>;
          using Name = std::tuple_element_t<0, Slot>;
          using Ancestor = std::tuple_element_t<1, Slot>;
          auto ancestor = output.template get<Ancestor>();
          using Value = std::tuple_element_t<2, Slot>;
          std::optional<Value> valueOpt = m_parent->m_grid.template get<Name>( ancestor );
          output.template set<Name>( *valueOpt );
          if constexpr ( Index < std::tuple_size_v<SubTreeTuple> - 1 ) {
            fillSlot<Index + 1>( output );
          }
        }

      template<typename ContentsV>
      friend ContentsV& operator<<( ContentsV& output, const InnerIter& input ) {
        output.template set<SlotName>( **(input.m_current) );
        //0 je TreeRoot, 1 je Root, ani jeden neni treba vyplnit, proto 2
        if constexpr ( std::tuple_size_v<SubTreeTuple> > 2 ) {
          input.fillSlot<2>( output );
        }
        return output;
      }
    };

    template<typename>
    class InnerIters;

    template<typename... Nodes>
    class InnerIters<std::tuple<Nodes...>> {
      ContentsImpl* m_parent;
      std::tuple<InnerIter<Nodes>...> m_iters;

      public:
        InnerIters() = default;
        InnerIters( ContentsImpl* parent ) : m_parent{ parent }, 
          m_iters{ InnerIter<Nodes>{ m_parent }... } {}

        template<size_t Index>
        void incrementIters() {
          auto& current = std::get<Index>( m_iters );
          current++;

          if ( current.m_current == current.m_end ) {
            if constexpr( Index > 0 ) {
              current.m_current = current.m_begin;
              incrementIters<Index - 1>();
            }
          }
        }
        InnerIters& operator++() { incrementIters<sizeof...( Nodes ) - 1>(); return *this; }
        InnerIters& operator++( int ) { return ++*this; }

      template<typename ContentsV>
      friend ContentsV& operator<<( ContentsV& output, const InnerIters& input ) {
        return ( output << ... << std::get<InnerIter<Nodes>>( input.m_iters ) );
      }
    
      template<std::size_t Index>
      friend const auto& get( const InnerIters& iters ) {
        return std::get<Index>( iters.m_iters );
      }
    };

    class OuterSent {};
    class OuterIter {
      private:
        //humus
        using gridRoots = typename SlotsTypesTree::get_roots;
        static_assert( std::tuple_size_v<gridRoots> == 1 );
        using rootsNode = typename std::tuple_element<0, gridRoots>::type;
        using rootsName = typename std::tuple_element<0, rootsNode>::type;
        using roots = typename SlotsTypesTree::template get_descendants<rootsName>;

        ContentsImpl* m_parent;
        InnerIters<roots> m_current;
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = ContentsValue<Grid, SlotsTypesTree>;

        OuterIter() = default;
        OuterIter( ContentsImpl& parent ) : m_parent{ &parent }, m_current{ m_parent }{}

        value_type operator*() const { value_type result; return result << m_current; }
        OuterIter& operator++() { m_current++; return *this; }
        OuterIter& operator++(int) { return ++*this; }

        friend constexpr bool operator==( const OuterIter& lhs, const OuterIter& rhs) { 
          return lhs.m_current == rhs.m_current; 
        }
        friend constexpr bool operator==( const OuterIter& lhs, const OuterSent& ) {
          const auto& current_0 = get<0>( lhs.m_current );
          return current_0.m_current == current_0.m_end;
        }
        friend constexpr bool operator!=( const OuterIter& lhs, const OuterIter& rhs) { 
          return !( lhs == rhs ); 
        }
    };
    OuterIter begin() { return { *this }; }
    OuterSent end() { return {}; }
};

template<typename SlotsTypesTree>
inline constexpr std::views::__adaptor::_RangeAdaptorClosure Contents
  = [] <typename Grid> ( Grid&& grid ) {
    return ContentsImpl<Grid, SlotsTypesTree>{ std::forward<Grid>( grid ) };
  };

template<typename Grid, typename SlotsTypesTree>
inline constexpr bool std::ranges::enable_borrowed_range<ContentsImpl<Grid, SlotsTypesTree>> = true;
