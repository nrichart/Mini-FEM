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

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

#define DIM_ELEM 4
#define DIM_NODE 3
#define VALUES_PER_ELEM 16

#define SUCCESS_OR_DIE(f...)                                         \
do                                                                   \
{                                                                    \
    const gaspi_return_t r = f;                                      \
    if (r != GASPI_SUCCESS)                                          \
    {                                                                \
        gaspi_rank_t rank;                                           \
        gaspi_proc_rank(&rank);                                      \
        gaspi_printf ("Error rank %d: '%s' [%s:%i]: %i\n", rank, #f, \
                      __FILE__, __LINE__, r);                        \
        exit (EXIT_FAILURE);                                         \
    }                                                                \
} while (0)

using namespace std;

extern string meshName, operatorName;
extern int *colorToElem;
extern int nbTotalColors;

#endif
