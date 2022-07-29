// Textual description
//
//Blacken some empty cells in a way that all black cells are connected horizontally and vertically and no 2x2 area is completely black. The numbers in the cells give hints on how to blacken the surrounding cells (even diagonally): The numbers give the number of directly connected black cells. Each number represents a group of horizontally or vertically adjacent cells; groups around a hint-cell have to be separated by at least one white cell. The order of the numbers is unimportant. All the hints are replaced by questionmarks, each qestionmark represents one number.
//
//
//  Example assignment
//
//Size: 6
//
//Hints:
//  [1,1]: ??
//  [1,6]: ?
//  [2,3]: ??
//  [3,5]: ?
//  [4,2]: ??
//  [5,4]: ?
//  [6,1]: ??
//  [6,6]: ?
//
//
//  Example solution
//
//  - X X X X -
//  X - - - X X
//  X X X X - X
//  X - - X X X
//  X - X - X -
//  - X X X X -
//
//
//  Real assignment -- not done
