// Textual description
//
//Place numbers from 1-N in all the empty cells so that they do not repeat in rows and columns (do not consider the numbers in grey cells). The numbers in white cells represent skyscrapers. The numbers in the grey cells indicate the number of visible skyscrapers in the direction of the arrow (the grey cells themselves are of zero height). The building is visible only when it is higher than all the buildings in front of it.
//
//
//  Example assignment
//
//  size: 6
//  N: 4
//
//Now for some cells give number and arrow in this format: [row, col]: {number, direction}
//
//  [1, 3]: {2, W}
//  [1, 4]: {2, E}
//  [2, 2]: {1, E}
//  [2, 5]: {2, S}
//  [3, 1]: {2, N}
//  [3, 6]: {4, W}
//  [4, 1]: {2, E}
//  [4, 6]: {2, S}
//  [5, 2]: {2, E}
//  [5, 5]: {1, W}
//  [6, 3]: {1, W}
//  [6, 4]: {2, E}
//
//
//  Example solution
//
//  4 1 - - 2 3 
//  2 - 4 3 - 1
//  - 4 3 2 1 -
//  - 3 2 1 4 -
//  3 - 1 4 - 2
//  1 2 - - 3 4
//
//
//  Real assignment -- not done
