// Textual description
//
//Divide the grid into domino tiles from the given set. All the domino tiles must be used. The numbers may not repeat in rows and columns. The hints denote the sums of the numbers to the right or down from the hint cell (before the grid border or next hint cell).
//
//
//  Example assignment
//
//Dominoes:
// 12 13 14 23 24 34
//
//Width: 6
//Height: 5
//
//Grid: xxx for empty cell (letter differ to denote domino areas), a/b for cell with hints (a-right, b-down) -- 0 for no hint given
//
//  0/0 0/7 0/6 0/0 0/0 0/0
//  4/0 aaa bbb 0/9 0/0 0/0
//  9/0 aaa bbb ccc 0/0 0/4
//  7/0 ddd ddd ccc 0/0 eee
//  0/0 0/0 7/0 fff fff eee
//
//
//  Example solution
//
//  - - - - - -
//  - 1 3 - - -
//  - 4 2 3 - -
//  - 2 1 4 - 3
//  - - - 2 4 1
//
//
//  Real assignment -- not done
