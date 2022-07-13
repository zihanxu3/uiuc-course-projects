#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

// modify this code by fusing loops together
void
filter_fusion(pixel_t **image1, pixel_t **image2) {
    for (int i = 1; i < SIZE - 1; i ++) {
        filter1(image1, image2, i);
        if (i >= 2 && i < SIZE - 2) {
            filter2(image1, image2, i);
        }
        if (i >= 6) {
            filter3(image2, i - 5);
        }
    }

    // for (int i = 2; i < SIZE - 2; i ++) {
    //     filter2(image1, image2, i);
    // }

    // for (int i = 1; i < SIZE - 5; i ++) {
    //     filter3(image2, i);
    // }
}

// modify this code by adding software prefetching
void
filter_prefetch(pixel_t **image1, pixel_t **image2) {
    for (int i = 1; i < SIZE - 1; i ++) {
        __builtin_prefetch(image1[i + 30], 0);
        __builtin_prefetch(image2[i + 30], 1, 0);
        filter1(image1, image2, i);
    }

    for (int i = 2; i < SIZE - 2; i ++) {
        __builtin_prefetch(image1[i + 30], 0);
        __builtin_prefetch(image2[i + 30], 1, 0);
        filter2(image1, image2, i);
    }

    for (int i = 1; i < SIZE - 5; i ++) {
        __builtin_prefetch(image2[i + 30], 0, 1);
        __builtin_prefetch(image2[i + 30], 1, 1);
        filter3(image2, i);
    }
}

// modify this code by adding software prefetching and fusing loops together
void
filter_all(pixel_t **image1, pixel_t **image2) {
     for (int i = 1; i < SIZE - 1; i ++) {
        __builtin_prefetch(image1[i + 30], 0, 3);
        __builtin_prefetch(image2[i + 30], 0, 3);
        __builtin_prefetch(image2[i + 30], 1, 3);
        filter1(image1, image2, i);
        if (i >= 2 && i < SIZE - 2) {
            filter2(image1, image2, i);
        }
        if (i >= 6) {
            filter3(image2, i - 5);
        }
    }
}
