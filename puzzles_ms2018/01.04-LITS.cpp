// Textual description
//
//Blacken some of the cells so that exactly four contiguous cells are blackened in each area, al lblack cells are orthogonally connected and no 2x2 area is completelly blackened. If one considers tha black cells in the areas as tetrominos, then the same tetrominos (also rotated or mirrored) must not touch horizontally or vertically.
//
//
//  Example assignment
//
//For each field an id of it's area is given as an int; same ints for field in the same area, different ones for fields in different areas.
//
//  1 1 1 2 2 2
//  1 3 4 4 2 2
//  1 3 4 5 5 2
//  3 3 4 4 5 5
//  3 4 4 5 5 6
//  3 6 6 6 6 6
//
//
//  Example solution
//
//0 for empty fields, 1 for black fields
//
//  1 1 1 1 1 1
//  1 0 1 0 1 0
//  0 0 1 1 1 0 
//  1 1 1 0 1 1
//  1 0 1 0 0 1
//  1 0 0 1 1 1
//
//
//  Real assignment -- not done
