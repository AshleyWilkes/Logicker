#pragma once
#include "slotPartName.h"
#include "slotPartValueT.h"
#include "SlotPartImplT/scalar.h"

class SlotPartT {};

template<typename...>
class SlotPart;

template<typename T>
concept CSlotPart = std::is_base_of_v<SlotPartT, T>;

template<CSlotPartName Name_>
class SlotPart<Name_> : public SlotPartT{
  public:
    using Name = Name_;
};

template<CSlotPartName Name_, CSlotPartValueT ValueT_>
class SlotPart<Name_, ValueT_> : public SlotPartT{
  public:
    using Name = Name_;
    using ValueT = ValueT_;
    using SlotImplT = Scalar;
};

template<CSlotPartName Name_, CSlotPartValueT ValueT_, CSlotPartImplT ImplT_>
class SlotPart<Name_, ValueT_, ImplT_> : public SlotPartT{
  public:
    using Name = Name_;
    using ValueT = ValueT_;
    using SlotImplT = ImplT_;
};

class SlotT {};

template<typename...>
class Slot;

template<CSlotPartName KeyName, CSlotPartName ValueName>
class Slot<KeyName, ValueName> : SlotT {};

template<CSlotPartName KeyName_, CSlotPartName ValueName, CSlotPartValueT ValueT, CSlotPartImplT ImplT>
class Slot<KeyName_, ValueName, ValueT, ImplT> : SlotT {
  public:
    using KeyName = KeyName_;
    using ValuePart = SlotPart<ValueName, ValueT, ImplT>;
};

template<CSlotPart KeySlotPart, CSlotPartName ValueName, CSlotPartValueT ValueT>
class Slot<KeySlotPart, ValueName, ValueT> : SlotT {
  public:
    using KeyPart = KeySlotPart;
    using ValuePart = SlotPart<ValueName, ValueT>;
};

template<CSlotPart KeySlotPart, CSlotPartName ValueName, CSlotPartValueT ValueT, CSlotPartImplT ImplT>
class Slot<KeySlotPart, ValueName, ValueT, ImplT> : SlotT {
  public:
    using KeyPart = KeySlotPart;
    using ValuePart = SlotPart<ValueName, ValueT, ImplT>;
};

template<CSlotPart KeySlotPart_, CSlotPart ValueSlotPart_>
class Slot<KeySlotPart_, ValueSlotPart_> : SlotT {
  public:
    using KeyPart = KeySlotPart_;
    using ValuePart = ValueSlotPart_;
};

template<typename T>
concept CSlot = std::is_base_of_v<SlotT, T>;

template<typename... Ts>
using Slots = std::tuple<Ts...>;
