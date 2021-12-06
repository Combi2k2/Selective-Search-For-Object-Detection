/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#ifndef SEGMENT_GRAPH
#define SEGMENT_GRAPH

#include <algorithm>
#include <cmath>
#include "disjoint-set.h"

// threshold function
#define THRESHOLD(size, c) (c/size)

typedef struct  {
    int a, b;
    float w;
}   edge;

bool operator < (const edge&a, const edge&b)  {
    return  a.w < b.w;
}

/*
 * Segment a graph
 *
 * Returns a disjoint-set forest representing the segmentation.
 *
 * num_vertices: number of vertices in graph.
 * num_edges: number of edges in graph
 * edges: array of edges.
 * c: constant for treshold function.
 */

universe *segment_graph(int num_vertices, int num_edges, edge *edges, float c) {
    std::sort(edges, edges + num_edges);
    universe *u = new universe(num_vertices); // create the forest

    //init threshold
    float *threshold = new float[num_vertices];

    for(int i = 0 ; i < num_vertices ; ++i)
        threshold[i] = THRESHOLD(1, c);

    // for each edge, in non-decreasing weight order...

    for(int i = 0 ; i < num_edges ; ++i)  {
        edge *e = &edges[i];
        //components connected by this edge

        int a = u -> find(e -> a);
        int b = u -> find(e -> b);

        if (a != b && (e -> w <= threshold[a]) && (e -> w <= threshold[b])) {
            u -> join(a, b);
            a = u -> find(a);
            threshold[a] = (e -> w) + THRESHOLD(u -> size(a), c);
        }
    }
    delete [] threshold;
    return u;
}

#endif
