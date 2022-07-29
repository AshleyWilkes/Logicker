// Textual description
//
//Dissect the grid into areas and write a number in every cell. The numbers in one area have to be the same and have to tell the number of cells in that area. Areas of same size may not touch horizontally or vertically, but can touch diagonally.
//Given numbers may belong to the same area, and it's possible that there are areas, where no number is given.
//In addition each outlined region contains the same set of numbers. It means the same numbers in the same number of copies.
//
//
//  Example assignment
//
//Size: 6
//
//Givens:
//  - 2 - 4 - 2
//  4 - 4 - 1 -
//  - 4 - 3 - 1
//  2 - 2 - 4 -
//  - 3 - 1 - 2
//  1 - 2 - 4 -
//
//AreaIds:
//  a a a b b b
//  c d a b b b
//  c d a a e e
//  c d d d e e
//  c d f f e e
//  c c f f f f
//
//
//  Example solution
//
//  2 2 4 4 4 2
//  4 1 4 3 1 2
//  4 4 1 3 3 1
//  2 4 2 2 4 2
//  2 3 3 1 4 2
//  1 3 2 2 4 4
//
//
//  Real assignment -- not done
