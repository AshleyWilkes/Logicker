#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "checker.h"
#include "puzzle.h"

//ted jsem tedy AFAIK pripravenej sepsat checker; pro jeho testovani je napred
//  treba rozhodnout, jakej Puzzle pouzit k prvnimu testu, resp. jaky pro nej
//  pouzit Transformace, aby byl test co nejjednodussi; no anebo bych mohl jit
//  rovnou testovat Heyawake, no akorat ze to by nebyl unit test, ale integracni test
//
//sanity check:
//Assignment a Solution maji stejne sloty -- ??vyplyva to z toho, ze jsou obe instance stejneho
//  CPuzzle confirmant typu, ne-li??
//pro kazdy slot
//  range klicu v Assignmentu je podmnozina range klicu v Solution
//  pro kazdy klic v Assignmentu v danem slotu plati, ze pokud ma Assignment k tomuto klici
//    prirazenou hodnotu, pak Solution ma k tomuto klici prirazenou tutez hodnotu
//
//validity check:
//pro kazdy Constraint 
//  vytvorim Checker::Constraint
//  zavolam jeho operator(), kam jako argument poslu Solution
//  plati, ze dostanu hodnotu true
//
//reportovani se dela pomoci listeneru: Checker umoznuje povesit na sebe Listener na kazdy
//  zajimavy druh eventu (nejspis tedy na kazdy mozny typ chyby)
//
//mel by existovat concept CPuzzle, jenz overi, ze Puzzle splnuje svuj (zatim ne zcela finalizovany)
//  kontrakt. Neco jako ze vsechny Puzzle::Slots jsou opravdu pouzitelne v metodach get(), range()
//  apod. a ze vsechny Puzzle::Constraints jsou validni transformace vedouci z kompletniho Gridu
//  na bool. (Ono se to jisteze implicitne overi tim, ze nejaky checker jde zkompilovat, ale
//  conpcept by umoznil earlier error detection.)
//
//A ted jake jsou detaily tech transformaci z pohledu runtime: predstava je, ze kazda dilci transformace
//  je implementovana jako RangeAdaptor, mozna presneji receno je kazda dilci transformace svazana
//  s objektem implementujicim view_interface (tj. vracejicim vystupni range) a inicializovanym krom
//  pripadnych jinych parametru vstupnim rangem. Vyjimecne (nabizi se AllOf, jimz konci +- kazda
//  constrainta) nemusi vstupem nebo vystupem byt range, coz neni domyslene, takze nevim, jestli
//  mi to nevadi, nebo jestli to radsi prevedu na jednoprvkove range. O co mi predevsim jde v tuto
//  chvili, je datovy typ, jehoz instance jsou prvky tech rangu. 
//Napr. zabyvejme se podminkou z Heyawaku, ze sousedni pole nesmeji byt obe cerna. Uvodni transformace 
//  (ta ktera ma na vstupu cely Grid) musi asi vracet neco jako jeden prvek, jejz tvori skalarni 
//  soucin Width x Height x Size x Fields, kde Fields jsou range prvku, ktere tvori skalarni souciny
//  FieldId x RowId x ColumnId x Value x AreaId. Na toto chci aplikovat narrowovaci transformaci, 
//  jejimz vysledkem bude range prvku, jez tvori skalarni souciny FieldId x RowId x ColumnId x Value.
//  Na toto se aplikuje Pair, ten vrati range, tvoreny dvojicemi of Value. Coz je Sequence<Value>
//  a to je snad dobre pochopena situace, kde s datovym typem prvku rangu neni problem.
//Ted ta myslenka skalarniho soucinu je velmi podobna stavajici implementaci Slotu v ramci Puzzlu,
//  Puzzle je vlastne skalarnim soucinem HasSlots<Slot>. Tam pouzity Slot je ale vyrazne 
//  komplikovanejsi nez to, co potrebuju udelat zde, kde skalarne nasobim dvojice <Name, ValueT>
//  a pozaduju pouze pristup k (optional) hodnote typu Value na zaklade zadaneho typu Name.
//  Cili by to melo byt trivialni na implementaci a nejvetsi problem, ktery vidim, je jak tu tridu
//  pojmenovat.
//

struct Key{};
//struct Value{};

template<typename Arg>
struct NOP_Constraint {
  using InputT = Arg;
  using OutputT = Arg;
  struct TransformationT {
    OutputT operator()( const InputT& input ) { return input; }
  };
};

template<typename KeyT_, typename ValueT_, typename Constraints>
class CheckerTestPuzzleImpl {
  private:
    std::map<KeyT_, ValueT_> values_;
  public:
    struct Slot{
      struct KeyPart{
        using Name = Key;
        using ValueT = KeyT_; 
      };
      struct ValuePart{
        using Name = Value;
        using ValueT = ValueT_;
      };
    };
    using Slots_ = std::tuple<Slot>;

    using Constraints_ = Constraints;
    CheckerTestPuzzleImpl( std::vector<std::pair<KeyT_, ValueT_>> values ) 
      : values_{ values.begin(), values.end() } {}

    template<typename>
    const std::optional<ValueT_>
    get( const KeyT_& key ) const {
      return values_.at( key );
    }

    template<typename Name>
    auto
    values() const {
      if constexpr( std::is_same_v<Name, Key> ) {
        return values_ | std::views::keys;
      } else if constexpr( std::is_same_v<Name, Value> ) {
        return values_ | std::views::values;
      }
    }

    template<typename Name>
    auto 
    unique_values() const {
      return values<Name>();
    }

    //tato metoda je Singleton -> bool, protoze je specializovana na jediny use case, ktery byl 
    //  predpokladan
    //nicmene cely test potrebuje aktualizaci, protoze vznikl v dobe, kdy se nevedelo,
    //  ze retez transformaci musi zacit with ContentsView
    bool getContents() const {
      return values_.at( Singleton{} );
    }
};

//template<typename KeyT, typename ValueT>
struct SanityTestPuzzleId{};
//template<typename KeyT, typename ValueT>
//class PuzzleT<CheckerTestPuzzleType<KeyT, ValueT>> {
template<>
class PuzzleT<SanityTestPuzzleId> {
  public:
    using type = CheckerTestPuzzleImpl<int, int, std::tuple<std::tuple<>>>;
};

struct ValidityEmptyConstraintsTestPuzzleId{};
template<>
class PuzzleT<ValidityEmptyConstraintsTestPuzzleId> {
  public:
    using type = CheckerTestPuzzleImpl<Singleton, bool, std::tuple<std::tuple<>>>;
};

struct ValidityNOPConstraintTestPuzzleId{};
template<>
class PuzzleT<ValidityNOPConstraintTestPuzzleId> {
  public:
    using type = CheckerTestPuzzleImpl<Singleton, bool, std::tuple<std::tuple<NOP_Constraint<bool>>>>;
};

namespace {
  //using PuzzleT = Puzzle<CheckerTestPuzzleType<int, int>>;
  using SanityTestPuzzleT = Puzzle<SanityTestPuzzleId>;
  Checker::Checker<SanityTestPuzzleT> sanityTestChecker;
  TEST( checker, sanityOk ) {
    SanityTestPuzzleT assignment{{{ 1231, 5322 }}}, solution {{{ 1231, 5322 }}};
    ASSERT_EQ( sanityTestChecker.checkSanity( assignment, solution ), true );
  }

  TEST( checker, sanityNOk_missing_key ) {
    SanityTestPuzzleT assignment{{{ 1, 219 }, { 2, 31 }}}, solution{{{ 1, 219 }}};
    ASSERT_EQ( sanityTestChecker.checkSanity( assignment, solution ), false );
  }

  TEST( checker, sanityNOk_wrong_value ) {
    SanityTestPuzzleT assignment{{{ 1, 219 }, { 2, 31 }}}, solution{{{ 1, 219 }, { 2, 133 }}};
    ASSERT_EQ( sanityTestChecker.checkSanity( assignment, solution ), false );
  }

  using ValidityEmptyConstraintsTestPuzzleT = Puzzle<ValidityEmptyConstraintsTestPuzzleId>;
  Checker::Checker<ValidityEmptyConstraintsTestPuzzleT> validityEmptyConstraintsTestChecker;
  TEST( checker, validityNoTransformationOk ) {
    ValidityEmptyConstraintsTestPuzzleT solution{{{ Singleton{}, true }}};
    ASSERT_EQ( validityEmptyConstraintsTestChecker.checkValidity( solution ), true );
  }

  TEST( checker, validityNoTransformationNOk ) {
    ValidityEmptyConstraintsTestPuzzleT solution{{{ Singleton{}, false }}};
    ASSERT_EQ( validityEmptyConstraintsTestChecker.checkValidity( solution ), false );
  }

  using ValidityNOPConstraintTestPuzzleT = Puzzle<ValidityNOPConstraintTestPuzzleId>;
  Checker::Checker<ValidityNOPConstraintTestPuzzleT> validityNOPConstraintTestChecker;
  TEST( checker, validityNOPConstraintOk ) {
    ValidityNOPConstraintTestPuzzleT solution{{{ Singleton{}, true }}};
    ASSERT_EQ( validityNOPConstraintTestChecker.checkValidity( solution ), true );
  }

  TEST( checker, validityNOPConstraintNOk ) {
    ValidityNOPConstraintTestPuzzleT solution{{{ Singleton{}, false }}};
    ASSERT_EQ( validityNOPConstraintTestChecker.checkValidity( solution ), false );
  }
}//namespace
