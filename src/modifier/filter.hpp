#pragma once

template <typename image_type>
image_type *gaussian(image_type *input, int width = 3, int height = 3);

template <typename image_type>
image_type *sobel(image_type *input);

template <typename image_type>
image_type *laplacian(image_type *input);