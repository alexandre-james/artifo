#pragma once

#include <initializer_list>

class mask {
    private:
        void print_row(int i);

    public:
        int width, height;
        float *values;

        mask(int width, int height);
        mask(std::initializer_list<std::initializer_list<float>> init);
        ~mask();

        mask *transpose();
        
        void print();
};