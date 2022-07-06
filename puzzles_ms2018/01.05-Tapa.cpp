// Textual description
//
//Blacken some empty cells in a way that all black cells are orthogonally connected and no 2x2 area is completely black. The numbers in the cells give hints in how to blacken the surrounding cells (even diagonally). Each number represents a group of horizontally or vertically adjacent cells; groups around a hint-cell have to be separated by at least one white cell. The order of the numbers is unimportant.
//
//
//  Example assignment
//
//For some field the given numbers are given as such: grid is rectangle; first it's width and height are given
//
//  width: 6
//  height: 6
//
//Now for some field we get [row, column] - { all given numbers for that cell }
//
//  [1, 6] - { 2 }
//  [2, 3] - { 1, 1, 1, 1 }
//  [5, 4] - { 1, 3, 1 }
//  [6, 1] - { 2 }
//
//
//  Example solution
//
//0 for white cells, 1 for black cells
//
//  1 1 0 1 1 0
//  1 0 0 0 1 0
//  1 1 0 1 1 0
//  0 1 1 0 1 1
//  0 1 0 0 0 1
//  0 1 1 1 1 1
//
//
//  Real assignment -- not done
