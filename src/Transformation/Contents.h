#pragma once

#include "undef.h"

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

template<typename InputTree>
struct ContentsValue;

template<typename Grid, typename InputTree>
struct ContentsValue<ContentsView<Grid, InputTree>> {
  public:
    using Names = typename TreeToTuple<InputTree, 0>::value;
    using Values = typename TreeToTuple<InputTree, 2>::value;

    template<typename Name>
    struct NameToValueT {
      static constexpr size_t Index = tuple_type_to_index_v<Name, Names>;
      using type = typename std::tuple_element_t<Index, Values>;
    };

    template<typename Name>
    using NameToValueT_t = typename NameToValueT<Name>::type;
  private:
    Values values; 
  public:
    ContentsValue() = default;
    ContentsValue( const Values& values_ ) : values{ values_ }{}

    template<typename Name, typename ValueT=NameToValueT_t<Name>>
    requires( std::is_same_v<ValueT, NameToValueT_t<Name>> )
    void set( const ValueT& value ) {
      std::get<ValueT>( values ) = value;
    }

    template<typename Name, typename ValueT=NameToValueT_t<Name>>
    requires( std::is_same_v<ValueT, NameToValueT_t<Name>> )
    ValueT get() {
      return std::get<ValueT>();
    }

    friend bool operator<( const ContentsValue& lhs, const ContentsValue& rhs ) {
      return lhs.values < rhs.values;
    }

    friend bool operator==( const ContentsValue& lhs, const ContentsValue& rhs ) {
      return lhs.values == rhs.values;
    }

    friend std::ostream& operator<<( std::ostream& os, const ContentsValue& ) {
      os << "Ahoj from Transformation/Contents.h";
      return os;
    }
};

template<typename>
struct ContentsImpl;

//takze co se tady kudla ma presne stat:
//prectu si prvni node v InputTree, o nem rovnou vim, ze ma typ root_value apod. 
//Zajimava informace jsou descendanti.
//Prectu si node odpovidajici prvnimu descendantovi, ten se nejak jmenuje a na toto jmeno
//se muzu zeptat Gridu, a to bud s klicem, pokud jsem ho dostal, pak jako odpoved dostanu
//jednu hodnotu, nebo bez klice, pak je odpovedi range.
//Takze, a to je mi pekne, ono je to tak, ze iterator vznika, jen kdyz rootova hodnota neni
//predana, pokud je, pak dostavam vzdy prave 1 hodnotu a tu muzu proste vyplnit do DataT objektu,
//ktery za tim ucelem dostanu, a nemusim nic kopirovat sem a tam. Lze si predstavit hypotetickou
//situaci, kdy k jedne hodnote je prirazeno nekolik hodnot (kodobr, tapa), ale nevidim situaci,
//kdy by k takovymto hodnotam bylo jeste prirazeno neco nejak dal, a celkove to dela dojem,
//ze v takove situaci se ma vratit hodnota prislusneho typu (Set, Sequence) a ne vracet to
//po jednom v ruznych objektech vraceneho range.
//
//Takze znovu, lepe: Mam 3 operace: konstruktor, dereferenci a advance. Dereference ma vytvorit
//DataT objekt a naplnit ho daty podle aktualni hodnoty vnitrniho iteratoru, advance posune 
//vnitrni iterator na novou hodnotu a konstruktor to cele inicializuje. Vsechno tedy nasvedcuje 
//tomu, ze skutekne chci pro kazdeho descendenta prvniho nodu v InputTree vytvorit dve veci:
//- instanci vnitrniho iteratoru, tj. iterator pres range, jejz vraci grid.template get()
//- nejakou fill metodu, ktera dostane na vstupu aktualni hodnotu dereference vnitrniho iteratoru
//a DataT objekt a naplni ten DataT objekt sobe prislusnou podmnozinou dat, odpovidajicih
//te dereferenci vnitrniho iteratoru!
template<typename, typename>
struct InnerIterator;

template<typename SlotPart, typename Grid, typename InputTree>
struct InnerIterator<SlotPart, ContentsView<Grid, InputTree>> {
  using SlotName = typename std::tuple_element<0, SlotPart>::type;
  using SubTree = typename InputTree::template subtree<SlotName>;
  using GridView = ContentsView<Grid, InputTree>;
  //using IteratorT = decltype( std::declval<GridView>().get_grid_p()->template values<SlotName>().begin() );
  using IteratorT = decltype( std::declval<Grid>().template values<SlotName>().begin() );
  using SentinelT = decltype( std::declval<Grid>().template values<SlotName>().end() );
  const Grid* grid_p;
  IteratorT begin, current;
  SentinelT end;

  InnerIterator() = default;
  InnerIterator( const GridView& grid ) : grid_p{ grid.get_grid_p() }, 
      begin{ grid_p->template values<SlotName>().begin() }, current{ begin }, 
      end{ grid_p->template values<SlotName>().end() } {}

  friend bool operator==( const InnerIterator& lhs, const InnerIterator& rhs ) {
    return lhs.current == rhs.current && lhs.begin == rhs.begin && lhs.end == rhs.end;
  }

  bool can_increment() const { return current != end; }

  void increment() { current++; }

  void reset() { current = begin; }

  template<typename>
  struct FillSlot;

  template<typename Name, typename Ancestor, typename Value, typename... Descendants>
  struct FillSlot<std::tuple<Name, Ancestor, Value, Descendants...>> {
    template<typename DataT>
    void fill( DataT& data, const Grid* grid_p ) {
      //precist hodnotu data<Ancestor>
      auto ancestor = data.template get<Ancestor>();
      //precist grid_p<Name>( ancestor ); ta je typu Value
      Value value = grid_p->template get<Name>( ancestor );
      //zapsat do data<Name>
      //data.template set<Name>( value );
      data.template set<Name>( "asd" );
    }
  };

  template<typename>
  struct FillSlots;

  template<typename TreeRoot, typename Root, typename... Slots>
  struct FillSlots<types_tree::__detail::types_tree_impl<std::tuple<TreeRoot, Root, Slots...>>> {
    template<typename DataT>
    static void fill( DataT& data, const Grid* grid_p ) {
      //SubTree ma tu vlastnost, ze obsahuje jen prime a neprime descendanty SlotPartu; prochazet 
      //  tedy po rade SubTree a pro kazdy slot se gridu zeptat na hodnotu valueParty a pote ji zapsat
      //prvni node v SubTree je root; druhej je Slot, na kterej ukazuje current
      //teprve od tretiho, pokud existuji, se skutecne neco deje, mam
      //  Name, AncestorName, Value
      ( FillSlot<Slots>::fill( data, grid_p ), ... );
    }
  };

  template<typename TreeRoot, typename Root>
  struct FillSlots<types_tree::__detail::types_tree_impl<std::tuple<TreeRoot, Root>>> {
    template<typename DataT>
    static void fill( DataT&, const Grid* ) {}
  };
  
  template<typename DataT>
  void fill( DataT& data ) const {
    //undef<SlotPart> as;
    //undef<SubTree> a;
    //undef<DataT> asd;
    //na spravne misto v data zapsat hodnotu, na niz ukazuje current
    data.template set<SlotName>( **current );
    FillSlots<SubTree>::fill( data, grid_p );
  }
};

//najit nejvyssi index innerIteratora, pro kterej current != end
//pokud zadnej neexistuje, je to error
//pokud existuje, zavolat na tomto indexu++ a na vsech vyssich indexech reset
template<typename Iterators, int Index>
struct Incrementer {
  template<typename IteratorsT>
  static void increment( IteratorsT& iterators ) {
    auto& current = std::get<Index>( iterators );
    if ( current.can_increment() ) {
      current.increment();
    } else {
      Incrementer<Iterators, Index - 1>::increment( iterators );
      current.reset();
    }
  }
};

template<typename Iterators>
struct Incrementer<Iterators, -1> {
  template<typename IteratorsT>
  static void increment( IteratorsT& ) {}
};

template<typename, typename>
struct InnerIterators;

template<typename... Nodes, typename GridView>
struct InnerIterators<std::tuple<Nodes...>, GridView> {
  using IteratorsT = std::tuple<InnerIterator<Nodes, GridView>...>;
  IteratorsT innerIterators;

  InnerIterators() = default;
  InnerIterators( const GridView& grid ) : innerIterators{ InnerIterator<Nodes, GridView>{ grid }... } {}

  InnerIterators& operator++() {
    Incrementer<IteratorsT, sizeof...( Nodes ) - 1>::increment( innerIterators );
    return *this;
  }
  InnerIterators& operator++(int) {
    return ++(*this);
  }

  friend bool operator==( const InnerIterators& lhs, const InnerIterators& rhs ) {
    return lhs.innerIterators == rhs.innerIterators || ( ! lhs.canIncrement() && ! rhs.canIncrement() );
  }

  template<typename DataT>
  void fill( DataT& data ) const {
    ( std::get<InnerIterator<Nodes, GridView>>( innerIterators ).fill( data ), ... );
  }

  bool canIncrement() const {
    return ( std::get<InnerIterator<Nodes, GridView>>( innerIterators ).can_increment() || ... );
  }
};

template<typename Grid, typename InputTree>
struct ContentsImpl<ContentsView<Grid, InputTree>> {
  //using DataT = typename ContentsValue<ContentsView<Grid, InputTree>>::Values;
  using DataT = ContentsValue<ContentsView<Grid, InputTree>>;
  struct OutputIt {
    using difference_type = std::ptrdiff_t;

    using gridRoots = typename InputTree::get_roots;
    static_assert( std::tuple_size_v<gridRoots> == 1 );
    using rootsNode = typename std::tuple_element<0, gridRoots>::type;
    using rootsName = typename std::tuple_element<0, rootsNode>::type;
    using roots = typename InputTree::template get_descendants<rootsName>;

    InnerIterators<roots, ContentsView<Grid, InputTree>> innerIterators;

    OutputIt() = default;
    OutputIt( const ContentsView<Grid, InputTree>& grid ) : innerIterators{ grid } {}

    constexpr DataT operator*() const {
      DataT result;
      innerIterators.fill( result );
      return result;
    }

    constexpr OutputIt& operator++() {
      innerIterators++;
      return *this;
    }
    constexpr OutputIt& operator++( int ) { return ++(*this); }

    friend bool operator==( const OutputIt& lhs, const OutputIt& rhs ) {
      return lhs.innerIterators == rhs.innerIterators;
    }
  };
  using OutputT = std::ranges::subrange<OutputIt>;

  static OutputT make_range( const ContentsView<Grid, InputTree>& gridView ) {
    return { OutputIt{ gridView }, OutputIt{} }; 
  }
};

struct Contents {
  template<typename InputView>
  using DataT = typename ContentsImpl<InputView>::DataT;

  template<typename InputView>
  using OutputT = typename ContentsImpl<InputView>::OutputT;

  /*template<typename InputView>
  using OutputIt = typename ContentsImpl<InputView>::OutputIt;*/

  template<typename InputT>//InputT je ContentsView<Grid, InputTree>, kde Grid poskytuje data
      //a InputTree obsahuje info o tom, ktere sloty me zajimaji
  OutputT<InputT> operator()( const InputT& gridView ) { 
    return ContentsImpl<InputT>::make_range( gridView );
  }
  //tedy tento operator ma generovat range tech ContentsValues
  //zdehle se vyplni root hodnoty: pro kazdej SlotPart, kterej nema "viditelnyho" predka, je tom
  //doufam, z principu vytvareni Singleton, ten tam jde rvat natvrdo. Neni-li to aktualne nutne
  //Singleton, zaridit, aby tomu tak bylo.
  //Pote volat rekurzivni sablonu, ktera vyplni zbytek OutputT. Ta ma prinejmensim dva template
  //  parametry: celej slotTree a current node. Podiva se na current node; nacte si z OutputT
  //  aktualni hodnotu klice current nodu, z input Gridu si zjisti vsechny mozne hodnoty value
  //  current nodu pro aktualni klic. Pokud current node nema zadne potomky, vyplnuje postupne
  //  jednotlive mozne hodnoty do OutputT a tim generuje range vysledku. Pokud potomky ma,
  //  zavola si rekurzivne sama sebe s prislusnymi novymi current nody, ziskane range
  //  skalarne nasobi mezi sebou a tim generuje range vysledku.
  //Trochu problem je jak konkretne vytvaret tu instanci OutputT, ktera bude soucasti vystupniho
  //  range. Nutny je, aby kazdy advance na iteratoru z range vedl na dosud nepouzitou
  //  instanci; uzivatel muze chtit pouzivat obe soucasne, a tudiz neni mozny, aby se pri
  //  advancu prepsala hodnota v drive vracenem dereferenci; jelikoz OutputT jsou const objekty,
  //  zda se mozne, aby OutputT hodnota bya soucasti objektu iteratoru a kazde jeho dereferencovani
  //  by vracelo const referenci na tento objekt; no ale ne, pak by mohlo dochazet k dangling
  //  referencim, dereference necht vraci kopii instance OutputT.
  //
  //musi se to delat rekurzivne; musi existovat range generator, jenz bere na vstupu subtree of 
  //  types_tree a hodnotu roota toho subtree a vraci odpovidajici range, tj. dvojici iteratoru.
  //  tj. potrebuju, aby types_tree umel subtree, coz ted neumi, ale je to vlastne skoro totez, 
  //  co dela NarrowTop, takze by to melo jit celkem snadno.
  /*template<typename types_tree, typename InputT>
  OutputIt<types_tree> get_contents( const types_tree::root& root_value, const InputT& grid );*/

  //prvni Node v types_tree ma potomky
  /*template<typename name, typename ancestor, typename value, typename... descendants, 
    typename... further_nodes, typename InputT, 
    typename types_tree = std::tuple< 
      std::tuple<name, ancestor, value, descendants...>, further_nodes...>, InputT>
  OutputIt<types_tree> get_contents<types_tree> ( 
      const types_tree::root& root_value, const InputT& grid ) {*/
    //tady je treba rekurzivne se zavolat pro kazdyho potomka a z vysledku udelat
    //  skalarni soucin
    //cili OutputIt v sobe ma mit ty jednotlive range, ktery vraci values, a jeho operace
    //  maji adekvatnim zpusobem s temito ranges pracovat, generujice novej range
    //  o kus nadrazenejsich OutputTs.
    //kazdej OutputT je ContentsValue, odpovidajici svemu types_tree, cili v nem jde
    //  vyhledavat podle jmen slotu; po jednom vsechny hodnoty prekopcim do aktualne
    //  vytvareneho noveho ContentsValue
  //}
  
  //prvni Node v types_tree nema potomky
  /*template<typename name, typename ancestor, typename value, 
    typename... further_nodes, typename InputT, 
    typename types_tree = std::tuple< 
      std::tuple<name, ancestor, value>, further_nodes...>, InputT>
  OutputIt<types_tree> get_contents<types_tree> ( 
      const types_tree::root& root_value, const InputT& grid ) {*/
    //tady je treba z gridu dostat values prvniho Nodu a vratit je jako range<OutputT<types_tree>
    //cili OutputIt v sobe ma mit ten range, kterej vraci values, a jeho operace se maji forwardovat
    //  na ten inner range
  //}
};
