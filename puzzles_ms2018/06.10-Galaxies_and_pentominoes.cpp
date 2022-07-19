// Textual description
//
//Place in the grid all 12 different pentominoes. They can be rotated and/or reflected, but they may not touch each other not even diagonally. The numbers on the left and on top indicate the number of cells occupied by pentominoes in the given row/column. The numbers on the right and at the bottom indicate the number of different pentominoes in the given row/column. Divide the remaining cells in galaxies. Galaxy is a region with central symmetry. The points of symmetry of all the galaxies are already given.
//
//  Example assignment
//
//Width: 7
//Height: 7
//
//Centers of symmetry:
//  [1-2, 1-2], [1-2, 4-5], [4, 6], [4-5, 2], [5-6, 4], [7, 6-7]
//
//Rows:
//  2 1
//  2 2
//  4 2
//  2 2
//  2 2
//  5 2
//  3 2
//
//Columns:
//  3 1
//  3 2
//  3 1
//  1 1
//  3 1
//  2 2
//  5 2
//
//
//  Example solution
//
//  1 1 2 2 2 L L
//  1 1 X 2 2 2 L
//  3 X X X 4 4 L
//  3 3 X 5 5 4 L
//  P 3 3 5 T 4 4
//  P P 3 5 T T T
//  P P 5 5 T 6 6
//
//
//  Real assignment -- not done
