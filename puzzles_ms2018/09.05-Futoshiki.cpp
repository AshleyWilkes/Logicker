// Textual description
//
//Fill the grid with digits 1-6 resp. 1-9 so that each digit appears exactly once in every row and column. Clues inside the grid represent the relations between the digits in the neighbouring cells.
//
//
//  Example assignment
//
//Size: 4
//
//Hints:
//Given as 2 arrays, 1st for rows, 2nd for columns; in each one - for none given, < > for the relation.
//The 1st array has 3 columns and 4 rows and relation XX stands for left XX right; the 2nd array has 4 columns and 3 rows and relation XX stands for upper XX lower.
//
//Rows:
//  - - -
//  - - <
//  - - -
//  - - <
//
//Columns:
//  < - - - 
//  < - > -
//  - < - -
//
//Hints could also be given in one array
//   - - -
//  < - - -
//   - - <
//  < - > -
//   - - -
//  - < - -
//   - - <
//
//
//  Example solution:
//
//  1 2 4 3
//  2 1 3 4
//  4 3 2 1
//  3 4 1 2
//
//
//  Real assignment -- not done
