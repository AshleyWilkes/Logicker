// Textual description
//
//Draw a single continuous loop by connecting neighboring dots along the dotted lines. The numbers indicate how many edges of a cell are used for the loop. Small cell edges are counted also around bigger cells. The loop may not touch or cross itself and it does not need to touch all the dots.
//
//
//  Example assignment
//
//Topologie je Rectangle 6x6, v pravem dolnim rohu jsou 4 policka sjednocena do jednoho vetsiho.
//
//Width: 6
//Height: 6
//
//Large fields: {
//  { [5, 5], [5, 6], [6, 5], [6, 6] }
//}
//
//Grid: 
//  for large fields the same number is given in each constituent cell
//
//  3 1 - - 3 1
//  - - 3 - - -
//  0 - - - 2 -
//  - 3 - 2 - -
//  - - 2 - 6 6
//  3 3 - - 6 6
//
//
//  Example solution
//I for fields inside the loop, O for fields outside
//
//  I I I I I O
//  O I O I O O
//  O O O I I O
//  O I O O I O
//  I I I O I I
//  I O I I I I
//
//
//  Real assignment -- not given
