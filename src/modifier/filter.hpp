#pragma once

template <typename image_type>
image_type *average(image_type *input, int width = 3, int height = 3);

template <typename image_type>
image_type *gaussian(image_type *input, int size, float sigma);

template <typename image_type>
image_type *sobel(image_type *input);

template <typename image_type>
image_type *laplacian(image_type *input);

template <typename image_type>
image_type *laplacian_sharp(image_type *input);

template <typename image_type>
image_type *laplacian_of_gaussian(image_type *input, int size, float sigma);