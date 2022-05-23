#include "transformation.hpp"

#include "../image/gray_image.hpp"
#include "../image/rgb_image.hpp"
#include "../image/rgba_image.hpp"
#include "../image/hsv_image.hpp"

template <typename image_type>
point<int> bound_point(image_type *input, point<int> p) {
    if (p.x < 0)
        p.x = 0;
    if (p.y < 0)
        p.y = 0;
    if (p.x >= input->width)
        p.x = input->width - 1;
    if (p.y >= input->height)
        p.y = input->height - 1;
    return p;
}

template point<int> bound_point(gray_image *, point<int>);
template point<int> bound_point(rgb_image *, point<int>);
template point<int> bound_point(rgba_image *, point<int>);
template point<int> bound_point(hsv_image *, point<int>);