// Textual description
//
//Place a digit into every cell. Each outlined region must contain each digit from 1 to the number of cells in that region. Identical digits cannot touch, not even diagonally. The digits on the marked diagonal must be all different.
//
//
//  Example assignment
//
//Given areaIds in the grid
//
//  1 1 1 1 2
//  1 3 4 4 2
//  3 3 5 4 2
//  3 5 5 4 2
//  3 5 5 4 2
//
//Now give given numbers in the grid; - for none given
//
//  - 2 - - -
//  - - - - 4
//  2 - - - -
//  - - - - -
//  - - 3 5 -
//
//Now give the extra areas:
//
//  areas: antidiagonal
//
//
//  Example solution
//
//  3 2 5 1 2
//  4 1 4 3 4
//  2 3 5 1 5
//  5 1 4 2 3
//  4 2 3 5 1
//
//
//  Real assignment -- not done
