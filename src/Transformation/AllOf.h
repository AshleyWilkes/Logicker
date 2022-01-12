#pragma once

#include "undef.h"

namespace Logicker::Transformation {
  template<typename Trans, typename... Args>
  struct AllOfImpl;

  template<typename Trans, typename Arg>
  //musi byt splneno, ze Trans::OutputT<Arg::ElementT> je bool; takto zapsana podminka
  //  overuje zaroven i to, ze Arg je Set<Trans::InputT>, pokud ovsem Trans splnuje svuj kontrakt,
  //  namely obsahuje OutputT<Arg> pouze pro Argy vhodneho typu
  requires( std::is_same_v< typename Trans::template OutputT< typename Arg::ElementT >, bool > )
  struct AllOfImpl< Trans, Arg > {
    using OutputT = bool;
  };

  /*template<typename Trans, typename Arg>
  struct AllOfImpl< Trans, Arg > {
    undef< typename Arg::ElementT > a;
    undef<typename Trans::OutputT< typename Arg::ElementT> > b;
    undef<Trans> c;
  };*/

  template<typename Trans>
  struct AllOf {
    template<typename... Args>
    using OutputT = typename AllOfImpl<Trans, Args...>::OutputT;

    template<typename InputT>
    OutputT<InputT> operator()( const InputT& ) { return false; }
  };
}//namespace Logicker::Transformation
