#pragma once

//ContentsValue je "mapa": "nazev nodu" -> "hodnota type value nodu"
//cili problem 1: jak z types_tree udelat tu mapu, resp. jak ma vubec ta mapa byt implementovana
//(tato mapa je runtime zalezitost, jeji typ slouzi jen jako prechodovy typ v ramci retezu transformaci)
//neboli mapy se dotazuju takto:
//map.get<NazevNodu>() -> hodnota
//slo by to i
//get<NazevNodu>(map) -> hodnota

#include "undef.h"

template<typename InputTree>
struct ContentsValue{};

struct Contents {
  template<typename>
  struct ContentsImpl;

  template<typename Grid, typename InputTree>
  struct ContentsImpl<ContentsView<Grid, InputTree>> {
    using OutputT = Set<ContentsValue<InputTree>>;
  };

  template<typename InputView>
  using OutputT = typename ContentsImpl<InputView>::OutputT;

  template<typename InputT>
  OutputT<InputT> operator()( const InputT& ) { return {}; }
};
