// Textual description
//
//Place in the grid all 7 different tetrominoes. They can be rotated but not reflected. They may not touch each other not even diagonally. The numbers on the left and on top indicate the number of cells occupied by tetrominoes in the given row/column. The numbers on the right and at the bottom indicate the number of different tetrominoes in the given row/column. Divide the remaining cells in galaxies. Galaxy is a region with central symmetry. The points of symmetry of all the galaxies are already given.
//
//
//  Example assignment
//
//Number of tetrominoes: 2
//
//Width: 6
//Height: 6
//
//Centers of symmetry:
//  [1, 6], [1-2, 5], [2, 3], [3-4, 5-6], [4, 2-3], [5-6, 3], [6, 1-2]
//
//Rows:
//  1 1
//  1 1
//  2 1
//  0 0
//  3 1
//  1 1
//
//Columns:
//  3 1
//  1 1
//  0 0
//  1 1
//  1 1
//  2 1
//  
//
//  Example solution
//
//  L 1 1 2 2 3
//  L 1 1 1 2 2
//  L L 1 1 4 4
//  5 5 5 5 4 4
//  6 6 6 L L L
//  7 7 6 6 6 L
//
//
//  Real assignment -- not done
