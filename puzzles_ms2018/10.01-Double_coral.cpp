// Textual description
//
//Place two corals in the grid. Use X and O to mark the fields occupied by the two corals.
//Coral is orthogonally connected, contains no 2x2 areas and all the cells that do not belong to coral must be connected to the edge of the grid. The numbers on the edge indicate the lengths of successive block of coral cells, but not necessarily in the correct order. There must be at least one other cell between two blocks. All the cells must be filled by at least one of the corals. ALl the cells where the corals overlap are marked. Hints on the right belong to one of the corals, hints below belong to the other one.
//
//
//  Example assignment
//
//Size: 6
//
//Marked cells: [2, 3], [5, 3]
//
//Right hints (Coral: O):
//  3
//  4
//  1 2
//  1 2
//  1 1 1
//  4
//
//Bottom hints (Coral: X):
//  1 1
//  1 4
//  1 3
//  1
//  1 2
//  3
//
//
//  Example solution
//X O for single coral, M for marked cells belonging to both corals
//
//  X X X O O O
//  O O M O X X
//  O X X O O X
//  O X O O X X
//  O X M X X O
//  X X O O O O
//
//
//  Real assignment -- not done
//
