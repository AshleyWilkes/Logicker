#pragma once

//mno toto neni tak jednoduchoucky, jak jsem mel za to
//PairsGenerator je sam o sobe transformace, ktera dela podobnou vec,
//  akorat s mensimi prvky na vstupu/vystupu
//InputSet musi mit prvky, ktere PairsGenerator sezere, a Pairs
//  pak dela tedy to, ze vysledky z PairsGeneratoru, ktere jsou tvoreny
//  dvojicemi "zmensenych" prvku, zase "rozsiri" na prvky, ktere byly na vstupu
//tohle prozatim staci jako popis i jako test, soon enough tu budu zpatky :-/

template<typename... PairsGenerator>
struct Pairs {
  template<typename InputSet>
  using OutputT = Pair<typename InputSet::ElementT>;

  template<typename InputT>
  OutputT<InputT> operator()( const InputT& ) { return {}; }
};
