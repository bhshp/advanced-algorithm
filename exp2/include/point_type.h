#pragma once

#ifndef POINT_TYPE_H_
#define POINT_TYPE_H_

enum point_type {
    NORMAL = 0,
    BARRIER = 1,
    WATER = 2,
    SAND = 4,
    PATH = 5,
    MID = 6,
    OTHER_PATH = 7,
    START_END = 8
};

#endif  // POINT_TYPE_H_
