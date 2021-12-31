#pragma once

//zde se predpoklada, ze oba Operandy jsou transformace, ktere na vstupu berou
//  totez, co cely Assert; jejich vystupy pak maji umoznovat porovnani Operatorem
//  (ktery je transformace ze skalarniho soucinu tech vystupu na bool)
template<typename LhsOperand, typename Operator, typename RhsOperand>
struct Assert {
  template<typename Input>
  struct AssertImpl {
    using LhsOutputT = typename LhsOperand::OutputT<Input>;
    using RhsOutputT = typename RhsOperand::OutputT<Input>;
    using OutputT = typename Operator::OutputT<LhsOutputT, RhsOutputT>;
  };

  template<typename Input>
  using OutputT = typename AssertImpl<Input>::OutputT;
};
