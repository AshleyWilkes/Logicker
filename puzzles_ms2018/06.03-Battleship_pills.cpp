// Textual description
//
//Locate the given fleet in the grid. The ships cannot touch each other, not even diagonally. The ships may be rotated. Each ship contains a number that corresponds to its size.
//The numbers on top and on the left give the number of cells occupied by ships in the given row or column. The numbers at the bottom and on the right give the sum of all the ship numbers found inside this row or column. Every ship is counted just once in the sum.
//
//
//  Example assignment
//
//Ship sizes: 1 1 1 2 2 3
//
//Width: 6
//Height: 6
//
//Rows: {
//  { 3, 4 },
//  { 1, 2 },
//  { 3, 3 },
//  { 0, 0 },
//  { 2, 2 },
//  { 1, 1 }
//}
//
//Columns: {
//  { 2, 2 },
//  { 1, 2 },
//  { 2, 5 },
//  { 2, 4 },
//  { 2, 4 },
//  { 1, 1 }
//}
//
//
//  Example solution
//
//  2 - - 1 - 1
//  2 - - - - -
//  - - 3 3 3 -
//  - - - - - -
//  - 2 2 - - -
//  - - - - 1 -
//
//
//  Real assignment -- not done
