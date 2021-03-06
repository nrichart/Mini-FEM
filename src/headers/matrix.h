/*  Copyright 2014 - UVSQ, Dassault Aviation
    Authors list: Loïc Thébault, Eric Petit

    This file is part of Mini-FEM.

    Mini-FEM is free software: you can redistribute it and/or modify it under the terms
    of the GNU Lesser General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option) any later version.

    Mini-FEM is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
    PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    Mini-FEM. If not, see <http://www.gnu.org/licenses/>. */

#ifndef MATRIX_H
#define MATRIX_H

#include <DC.h>

// Create elem to edge array giving the index of each edge of each element
void create_elemToEdge (int *nodeToNodeRow, int *nodeToNodeColumn, int *elemToNode,
                        int *elemToEdge, int nbElem);

// Create node to node arrays from node to element and element to node
void create_nodeToNode (int *nodeToNodeRow, int *nodeToNodeColumn,
                        index_t &nodeToElem, int *elemToNode, int nbNodes);

#endif
