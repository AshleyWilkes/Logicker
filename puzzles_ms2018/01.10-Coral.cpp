// Textual description
//
//Blacken some of the cells in the grid to create a coral. All black cells in the coral must be orthogonally connected. There must be no 2x2 squares of black cells. And all white cells must be connected to the edge of the grid. The numbers on the edge indicate the lengths of successive blocks of coral cells, but not necessarily in the correct order. There must be at least one black cell between two blocks.
//
//
//  Example assignment
//
//For rows and columns the given numbers are given as sets in order; empty set stands for no given number.
//
//  Rows: {3}, {1, 1}, {2, 2}, {4}, {1, 2}, {2}
//  Columns: {3}, {1, 1, 2}, {1, 3}, {1}, {3}, {1, 2}
//
//
//  Example solution
//
//0 for white cells, 1 for black cells
//
//  1 1 1 0 0 0
//  1 0 1 1 0 1
//  1 0 0 1 1 1
//  0 0 0 1 0 0
//  0 0 1 1 1 0
//  0 1 1 0 1 0 
//
//
//  Real assignment -- not done
