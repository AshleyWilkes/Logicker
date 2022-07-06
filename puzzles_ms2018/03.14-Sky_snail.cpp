// Textual description
//
//Place numbers from 1-N in some of the cells so that they do not repeat in rows and columns. Two cells in each row and column remain empty. The numbers represent heights of the buildings. The numbers around the grid indicate the number of buildings you can see from the given viewpoint. The building is visible only when it is higher than all the buildings in front of it.
//In addition the numbers must follow the sequence 1,2,..,N in the direction from the entrance of the maze toward the end inside.
//
//
//  Example assignment
//
//The snail
//
//   1  2  3  4  5
//  16 17 18 19  6
//  15 24 25 20  7
//  14 23 22 21  8
//  13 12 11 10  9
//
//Skyscraper hints
//
//  Rows: [-, -], [2, -], [2, -], [1, -], [-, -]
//  Columns: [-, -], [3, -], [1, -], [2, -], [-, -]
//
//
//  Example solution
//
//  - 1 - 2 3
//  - 2 3 - 1
//  1 3 - - 2
//  3 - 2 1 -
//  2 - 1 3 -
//
//
//  Real assignment -- not done
