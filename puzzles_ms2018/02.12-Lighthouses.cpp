// Textual description
//
//Place ships (size 1 cell) in the grid so that no ship touches another ship or lighthouse, not even diagonally. The numbers represent lighthouses and indicate how many ships can be seen from the given lighthouse in horizontal and vertical directions. It does not matter if there is another ship or lighthouse between the ship and the lighthouse. All ships can be seen by at least one lighthouse.
//
//
//  Example assignment
//
//Given numbers are given in a grid; 0 for no number, int for a lighthouse with number in it
//
//  0 0 0 0 0 0
//  0 0 1 0 0 0
//  0 0 0 0 0 0
//  0 1 0 0 0 0
//  0 0 0 0 2 0 
//  0 0 0 0 0 0
//
//
//  Example solution
//
//0 for empty cell; 1 for ship
//
//  0 0 0 0 1 0
//  1 0 0 0 0 0
//  0 0 0 0 1 0
//  0 0 0 0 0 0
//  0 0 0 0 0 0
//  0 1 0 0 0 0
//
//
//  Real assignment -- not done
