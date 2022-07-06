// Textual description
//
//Place numbers from 1-N and one mirror in every row so that they do not repeat in any row and column. These numbers represent heights of the buildings. The numbers around the grid indicate the number of buildings you can see from the given viewpoint. The building is visible only when it is higher than all the buildings in front of it, both in front of the mirror and reflected by the mirror.
//Variants are:
//  The mirrors are given (puzzles 1, 2)
//  Only the positions of the mirrors are marked, but you have to find their orientation (puzzles 3, 4)
//  You have to find both the positions of the mirrors and their orientation (puzzle 5)
//
//
//  Example assignment
//
//Size and N
//
//  N: 3
//  size: 4
//
//Now for each row and column specify given numbers as pairs;
//
//  Rows: [2, 1], [2, 1], [1, 2], [1, 2]
//  Columns: [3, 1], [1, 2], [2, 2], [2, 3]
//
//Now give mirrors in the grid; 0 for main-diagonal-split, 1 for anti-diagonal-split
//
//  - - - 1
//  - 1 - -
//  0 - - -
//  - - 0 -
//
//
//  Example solution
//
//  1 3 2 -
//  2 - 1 3
//  - 1 3 2
//  3 2 - 1
//
//
//  Real assignment -- not done
