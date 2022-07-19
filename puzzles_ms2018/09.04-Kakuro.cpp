// Textual description
//
//Place a digit from 1 to 9 into each white cell. The numbers in grey cells indicate the sum of digits in the adjacent "word" across or down. (Across "words" are to the right of their sums, Down "words" are below their sums.) Digits may not repeat within a "word".
//
//
//  Example assignment
//
//Width: 6
//Height: 6
//
//Grid: xxx for empty cell (letter differ to denote domino areas), a/b for cell with hints (a-right, b-down) -- 0 for no hint given
//
//  0/0 0/6 0/18 0/0 0/28 0/8
//  4/0 --- --- 7/9 --- ---
//  15/0 --- --- --- --- ---
//  0/0 23/15 --- --- --- 0/9
//  18/0 --- --- --- --- ---
//  11/0 --- --- 15/0 --- ---
//
//
//  Example solution
//
//  - - - - - -
//  - 1 3 - 2 5
//  - 5 1 2 4 3
//  - - 8 6 9 -
//  - 6 4 1 5 2
//  - 9 2 - 8 7
//
//
//  Real assignment -- not done
