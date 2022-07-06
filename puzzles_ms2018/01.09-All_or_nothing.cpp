// Textual description
//
//Blacken some areas so that the numbers on the edge indicate how many cells in the corresponding row or column are black. Within an area either all cells must be black or none.
//
//
//  Example assignment
//
//For rows and columns the given numbers are presented in order; 0 stands for no given number.
//
//  Rows: 0 4 3 2 3 0
//  Columns: 0 3 0 0 3 0
//
//Now areaIds are given for each cell as an int; same int for same area, different ints for different areas
//
//   1  1  2  2  3  3
//   1  4  4  2  3  3
//   5  4  6  6  7  7
//   5  5  6  6  8  7
//   9  9 10  8  8 11
//   9  9 10 10 11 11
//
//
//  Example solution
//
//O for white cells, 1 for black cells
//
//  1 1 0 0 0 0
//  1 1 1 0 0 0
//  1 1 0 0 1 1 
//  1 1 0 0 1 1
//  0 0 1 1 1 0
//  0 0 1 1 0 0
//
//
//  Real assignment -- not done
