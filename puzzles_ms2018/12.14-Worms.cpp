// Textual description
//
//Place numbers from 1-6 resp. 1-7 in all the empty cells in the grid so that the numbers do not repeat in any outlined region and along the four grey lines. The numbers in each region must follow the worm rule of alternating higher and lower values. The same numbers may not touch each other not even diagonally.
//
//
//  Example assignment
//
//Size: 6
//
//AreaIds:
//  1 1 1 1 2 2
//  3 3 3 1 2 4
//  3 5 5 1 2 4
//  3 5 6 2 2 4
//  3 5 6 4 4 4
//  5 5 6 6 6 6
//
//Regions: (Grey lines)
//  {
//  {[1, 1], [1, 2], [1, 3], [1, 4], [1, 5], [1, 6]},
//  {[6, 1], [6, 2], [6, 3], [6, 4], [6, 5], [6, 6]},
//  {[1, 1], [2, 1], [3, 1], [4, 1], [5, 1], [6, 1]},
//  {[1, 6], [2, 6], [3, 6], [4, 6], [5, 6], [6, 6]}
//  }
//
//Givens:
//  - - 3 - - -
//  1 - - - - -
//  - 6 - 5 - -
//  - - 2 - 2 -
//  - - - - - 4
//  - - - 6 - -
//
//
//  Example solution
//  2 6 3 4 5 1
//  1 4 2 1 3 2
//  5 6 3 5 4 6
//  3 1 2 6 2 3
//  6 5 4 5 1 4
//  4 2 1 6 3 5
//
//
//  Real assignment -- not done
