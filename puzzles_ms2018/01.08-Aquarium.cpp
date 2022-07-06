// Textual description
//
//Fill some cells with water so that the numbers at the borders indicate how many cells in the corresponding row or column contain water. Within an area the cells must be filled up from the bottom up. Within a row of an area, all cells must always be filled with water or none (even if there are other areas in between).
//
//
//  Example assignment
//
//For rows and columns the given numbers are presented in order; 0 stands for no given number.
//
//  Rows: 2 3 3 3 3 2
//  Columns: 3 3 3 2 3 2
//
//Now areaIds are given for each cell as an int; same int for same area, different ints for different areas
//
//   1  2  2  2  3  3
//   1  4  5  5  5  3
//   1  4  6  7  7  7
//   8  4  6  9 10 10
//   8  8  6  9 11 10
//  12 12 12  9 11 11
//
//
//  Example solution
//
//0 for cells with no water, 1 for filled cells
//
//  0 1 1 1 0 0
//  0 0 1 1 1 0
//  0 0 0 1 1 1
//  1 1 0 0 0 0
//  1 1 1 0 0 0
//  0 0 0 0 1 1
//
//
//  Real assignment -- not done
