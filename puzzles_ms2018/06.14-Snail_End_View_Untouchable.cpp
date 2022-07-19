// Textual description
//
//Place letters A, B, C in the grid so that each letter appears exactly once in every row and column. The same letters may not touch each other not even diagonally. Reading the letters from the top left corner and going to the center the same sequence must repeat. The order of the sequence is for you to determine. The letters around the grid denote the second letter visible from the given direction in the given row or column.
//
//
//  Example assignment
//
//Letters: A B
//
//Snail:
//
//  1  2  3  4  5  6
// 20 21 22 23 24  7
// 19 32 33 34 25  8
// 18 31 36 35 26  9
// 17 30 29 28 27 10
// 16 15 14 13 12 11
//
//Some cells must be empty:
//  [3, 5], [4, 3]
//  
//Rows:
//  A B A B A B
//
//Columns:
//  B B A B A A
//
//
//  Example solution
//
//  - - B A - -
//  A - - - - B
//  B - - - - A
//  - A - - B -
//  - B - - A -
//  - - A B - -
//
//
//  Real assignment -- not done
