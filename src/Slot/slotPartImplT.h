#pragma once

class SlotPartImplT {};

template<typename T>
concept CSlotPartImplT = std::is_base_of_v<SlotPartImplT, T>;
