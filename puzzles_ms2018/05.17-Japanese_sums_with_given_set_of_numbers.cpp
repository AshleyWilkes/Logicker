// Textual description
//
//Blacken some of the cells in the grid and place numbers from the given set into the other cells, so that no number appears more often in any row and column than is given by the set. The numbers at the borders give the sum of consecutive digits (without black cells in between) in the order. Single digits are also given.
//
//
//  Example assignment
//
//Set: 1 1 2 3
//size: 6
//
//Givens as sets of ints
//
//  Rows: {
//    { 1, 3, 3 },
//    { 3, 2, 1 },
//    { 2, 3, 2 },
//    { 2, 1, 3 },
//    { 2, 2 },
//    { 3, 3 }
//  }
//
//  Columns: {
//    { 1, 3 },
//    { 4, 2 },
//    { 3, 1, 2 },
//    { 5, 2 },
//    { 2, 4 },
//    { 4, 3 }
//  }
//
//
//  Example solution
//
//  1 - 3 - 2 1
//  - 3 - 2 - 1
//  1 1 - 3 - 2
//  2 - 1 - 3 -
//  - 2 - 1 1 -
//  - - 2 1 - 3
//
//
//  Real assignment -- not done
