#pragma once

#include <random>
#include <delynoi/models/basic/Point.h>

std::vector<Point>
poisson_disk_sampling(double width, double height, double r, int k = 30,
    unsigned int seed = std::random_device{}() );

