#include "structure.hpp"

#include <cmath>
#include <algorithm>

mask *structuring_element(int width, int height) {
    int i, j;
    int r = 0, c = 0;
    double inv_r2 = 0;

    r = height/2;
    c = width/2;
    inv_r2 = r ? 1./((double)r*r) : 0;

    mask *elem = new mask(width, height);

    for( i = 0; i < height; i++ )
    {
        int j1 = 0, j2 = 0;
        int dy = i - r;
        if( std::abs(dy) <= r )
        {
            int dx = c*std::sqrt((r*r - dy*dy)*inv_r2);
            j1 = std::max( c - dx, 0 );
            j2 = std::min( c + dx + 1, width );
        }

        for( j = 0; j < j1; j++ )
            elem->values[i * width + j] = false;
        for( ; j < j2; j++ )
            elem->values[i * width + j] = true;
        for( ; j < height; j++ )
            elem->values[i * width + j] = false;
    }

    return elem;
}