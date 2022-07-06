// Textual description
//
//The grid is made up of magnetic and non-magnetic plates. Each magnetic plate has two halves: one positive (+) and one negative (-). Halves with the same symbol can not be horizontally or vertically adjacent. The numbers outside the grid indicate how many magnetic hlaves of each kind can be found in that row or column.
//
//
//  Example assignment
//
//First give plates as areaIds
//
//   1  1  2  2  3  3
//   4  5  5  6  6  7
//   4  8  8  9  9  7
//  10 10 11 11 12 12
//  13 14 14 15 16 16
//  13 17 17 15 18 18
//
//Now for rows and columns give givens as pairs of ints [+s, -s]; 0 for none given
//
//  Rows: [2, 2], [1, 2], [2, 1], [3, 3], [1, 2], [3, 2]
//  Columns: [2, 1], [1, 3], [3, 2], [2, 1], [2, 2], [2, 3]
//
//
//  Example solution
//
//For each field 0-nonmagetic, + or -
//
//  0 0 - + - +
//  0 - + 0 0 -
//  0 0 0 + - +
//  + - + - + -
//  - + - 0 0 0
//  + - + 0 + -
//
//
//  Real assignment -- not done
