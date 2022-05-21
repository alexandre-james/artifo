#pragma once

template <typename image_type>
image_type *rescale(image_type *input, int height, int is_average);

template <typename image_type>
image_type *pixelize(image_type *input, int height, int is_average);