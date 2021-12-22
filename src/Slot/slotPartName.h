#pragma once

class SlotPartName {};

template<typename T>
concept CSlotPartName = std::is_base_of_v<SlotPartName, T>;

class DefaultGridId : public SlotPartName {};

class AreaId : public SlotPartName {};
class BlackCount : public SlotPartName {};

class Value : public SlotPartName {};
class CentersFieldId : public SlotPartName {};
class Height : public SlotPartName {};
class Size : public SlotPartName {};
class Width : public SlotPartName {};
class RowId : public SlotPartName {};
class ColumnId : public SlotPartName {};

