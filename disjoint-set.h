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

#ifndef DISJOINT_SET
#define DISJOINT_SET

// disjoint-set forests using union-by-rank and path compression (sort of).

class universe  {
    private:
        int num;
        int *p, *s;
    public:
        universe(int n) {
            num  = n;
            p = new int[n];
            s = new int[n];

            for(int i = 0 ; i < n ; ++i)
                p[i] = i,
                s[i] = 1;
        }
        ~universe() {
            delete [] p;
            delete [] s;
        }
        int find(int x) const   {   return  x == p[x] ? x : p[x] = find(p[x]);  }
        void join(int x, int y) {
            x = find(x);
            y = find(y);

            if (x == y) return;
            if (s[x] < s[y])    {
                x = x + y;
                y = x - y;
                x = x - y;
            }
            
            p[y] = x;
            s[x] += s[y];

            num--;
        }
        int size(int x) const   {   return  s[find(x)]; }
        int num_sets()  const   {   return  num;    }
};
#endif
