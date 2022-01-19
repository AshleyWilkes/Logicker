#pragma once

#include "undef.h"

namespace Logicker::Transformation {
  template<typename Trans, typename... Args>
  struct AllOfImpl;

  template<typename Trans, typename Arg>
  //musi byt splneno, ze Trans::OutputT<Arg::ElementT> je bool; takto zapsana podminka
  //  overuje zaroven i to, ze Arg je Set<Trans::InputT>, pokud ovsem Trans splnuje svuj kontrakt,
  //  namely obsahuje OutputT<Arg> pouze pro Argy vhodneho typu
  requires( std::is_same_v< typename Trans::template OutputT< typename Arg::value_type >, bool > )
  struct AllOfImpl< Trans, Arg > {
    using OutputT = bool;
  };

  template<typename Trans, typename Arg>
    requires( std::is_same_v< typename Trans::template OutputT< std::ranges::range_value_t< Arg > >, bool > )
  struct AllOfImpl< Trans, Arg > {
    using OutputT = bool;
  };

  template<typename Trans>
  struct AllOf {
    template<typename... Args>
    using OutputT = typename AllOfImpl<Trans, Args...>::OutputT;

    template<typename InputT>
    OutputT<InputT> operator()( const InputT& input ) { 
      //InputT je range, vsechny jeho prvky chci po jednom prohnat Transem a vratit AND vsech vysledku
      //undef<decltype( *( input.begin() ) )> b;
      //auto c = *( input.begin() );
      //return Trans{}( 1 );
      //return Trans{}( *(input.begin() ) );
      return std::ranges::all_of( input.begin(), input.end(), Trans{} );
    }
  };
}//namespace Logicker::Transformation
