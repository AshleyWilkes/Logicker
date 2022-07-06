// Textual description
//
//Blacken some of the cells in the grid so that no two black cells touch each other horizontally or vertically and all white cells are orthogonally connected. Strips of white cells should not extend horizontally or vertically over more than one area boundary. The numbers in the grid show the number of black cells in the corresponding area. Cells with numbers may be blackened.
//
//
// Example assignment
//
//AreaIds: For each field it's aread id is given as an int; same ints belong to the same area, different
//  ones belong to different areas
//
//  1 2 3 3 3 3
//  1 2 4 4 4 4
//  1 2 5 5 6 7
//  1 2 5 5 6 7
//  8 8 8 8 6 7
//  9 9 9 9 6 7
//
//GivenAreaValues: For some area ids (the number before dash) given values are given after the dash
//  1 - 2
//  3 - 2
//  6 - 1
//  9 - 1
//
//
//  Example solution
//
//0 stands for white cell; 1 stands for black cell
//  1 0 0 1 0 1
//  0 0 1 0 0 0
//  1 0 0 0 1 0
//  0 0 1 0 0 1
//  0 1 0 1 0 0
//  1 0 0 0 0 1
//
//
//  Real assignment -- not done
