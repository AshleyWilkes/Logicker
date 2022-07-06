// Textual description
//
//All islands have to be connected through bridges (every island has to be reachable from every other island). The bridges may only be built horizontally or vertically and may neither cross other bridges nor islands. Between two islands there are at maximum two bridges. The number in the islands gives the number of bridges that are connected to this island.
//
//
//  Example assignment -- promyslet
//  zadani by bylo hezci napsat jako rectangle s 0 a cisly
//
//Grid is rectangle: first it's width and height are given
//
//  width: 6
//  height: 6
//
//Now for some "cells" the number of bridges is given; these cells are islands and cells where no number is given are water.
//
//  [1, 1] - 4
//  [1, 3] - 3
//  [1, 5] - 2
//  [2, 2] - 3
//  [2, 4] - 2
//  [2, 6] - 1
//  [3, 3] - 3
//  [3, 5] - 2
//  [4, 1] - 5
//  [4, 2] - 3
//  [4, 4] - 2
//  [4, 6] - 4
//  [5, 3] - 4
//  [5, 5] - 1
//  [6, 1] - 1
//  [6, 3] - 4
//  [6, 6] - 3
//
//
//  Example solution -- promyslet
//  reseni by slo psat jako dvojice rectanglich edgu s 0, 1, 2
//
//We get pairs of islands and number of bridges between them; unmention pairs mean no bridges
//
//  [1, 1], [1, 3] - 2
//  [1, 1], [4, 1] - 2
//  [1, 3], [1, 5] - 1
//  [1, 5], [3, 5] - 1
//  [2, 2], [2, 4] - 2
//  [2, 2], [4, 2] - 1
//  [2, 6], [4, 6] - 1
//  [3, 3], [3, 4] - 1
//  [4, 1], [4, 2] - 1
//  [4, 4], [4, 6] - 2
//  [5, 3], [5, 5] - 1
//  [6, 1], [6, 3] - 1
//  [6, 3], [6, 6] - 2
//
//
//  Real assignment -- not done
