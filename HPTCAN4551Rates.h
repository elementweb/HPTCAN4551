#ifndef CLASS_HPTCAN4551_RATES_H
#define CLASS_HPTCAN4551_RATES_H

// Includes
#include <stdint.h>

/**
 * Timing configuration prefabs; these apply to both nominal and data bit timing configuration.
 * 
 * names go as HPTCAN4551_RATE_<CLOCKFREQ>_<DATARATE>_<SAMPLEPOINT%>_<BRP>
 * values are defined as [BRP, TSEG1, TSEG2, SJW]
 */

// 250kbit @ 20MHz
#define HPTCAN4551_RATE_20M_250K_75_1               1, 59, 20, 20               // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_80_1               1, 63, 16, 16               // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_85_1               1, 67, 12, 12               // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_75_2               2, 29, 10, 10               // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_80_2               2, 31, 8, 8                 // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_85_2               2, 33, 6, 6                 // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_75_4               4, 14, 5, 5                 // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_80_4               4, 15, 4, 4                 // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_85_4               4, 16, 3, 3                 // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_75_5               5, 11, 4, 4                 // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_80_8               8, 7, 2, 2                  // 250kbit @ 20MHz; 80 clocks/bit
#define HPTCAN4551_RATE_20M_250K_75_10              10, 5, 2, 2                 // 250kbit @ 20MHz; 80 clocks/bit

// 500kbit @ 20MHz
#define HPTCAN4551_RATE_20M_500K_75_1               1, 29, 10, 10               // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_80_1               1, 31, 8, 8                 // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_75_2               2, 14, 5, 5                 // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_80_2               2, 15, 4, 4                 // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_85_2               2, 16, 3, 3                 // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_80_4               4, 7, 2, 2                  // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_75_5               5, 5, 2, 2                  // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_80_8               8, 3, 1, 1                  // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_75_10              10, 2, 1, 1                 // 500kbit @ 20MHz; 40 clocks/bit
#define HPTCAN4551_RATE_20M_500K_85_1               1, 33, 6, 6                 // 500kbit @ 20MHz; 40 clocks/bit

// 1-4Mbit @ 20MHz
#define HPTCAN4551_RATE_20M_1M_75_1                 1, 14, 5, 5                 // 1Mbit @ 20MHz; 20 clocks/bit
#define HPTCAN4551_RATE_20M_1M_80_1                 1, 15, 4, 4                 // 1Mbit @ 20MHz; 20 clocks/bit
#define HPTCAN4551_RATE_20M_1M_85_1                 1, 16, 3, 3                 // 1Mbit @ 20MHz; 20 clocks/bit
#define HPTCAN4551_RATE_20M_1M_80_2                 2, 7, 2, 2                  // 1Mbit @ 20MHz; 20 clocks/bit
#define HPTCAN4551_RATE_20M_1M_80_4                 4, 3, 1, 1                  // 1Mbit @ 20MHz; 20 clocks/bit
#define HPTCAN4551_RATE_20M_1M_75_5                 5, 2, 1, 1                  // 1Mbit @ 20MHz; 20 clocks/bit
#define HPTCAN4551_RATE_20M_2M_80_1                 1, 7, 2, 2                  // 2Mbit @ 20MHz; 10 clocks/bit
#define HPTCAN4551_RATE_20M_2M_80_2                 2, 3, 1, 1                  // 2Mbit @ 20MHz; 10 clocks/bit
#define HPTCAN4551_RATE_20M_4M_80_1                 1, 3, 1, 1                  // 4Mbit @ 20MHz; 5 clocks/bit

// 250kbit @ 24MHz
#define HPTCAN4551_RATE_24M_250K_75_1               1, 71, 24, 24               // 250kbit @ 24MHz; 96 clocks/bit
#define HPTCAN4551_RATE_24M_250K_75_2               2, 35, 12, 12               // 250kbit @ 24MHz; 96 clocks/bit
#define HPTCAN4551_RATE_24M_250K_75_3               3, 23, 8, 8                 // 250kbit @ 24MHz; 96 clocks/bit
#define HPTCAN4551_RATE_24M_250K_75_6               6, 11, 4, 4                 // 250kbit @ 24MHz; 96 clocks/bit
#define HPTCAN4551_RATE_24M_250K_75_4               4, 17, 6, 6                 // 250kbit @ 24MHz; 96 clocks/bit
#define HPTCAN4551_RATE_24M_250K_75_12              12, 5, 2, 2                 // 250kbit @ 24MHz; 96 clocks/bit

// 500kbit @ 24MHz
#define HPTCAN4551_RATE_24M_500K_75_2               2, 17, 6, 6                 // 500kbit @ 24MHz; 48 clocks/bit
#define HPTCAN4551_RATE_24M_500K_75_3               3, 11, 4, 4                 // 500kbit @ 24MHz; 48 clocks/bit
#define HPTCAN4551_RATE_24M_500K_75_4               4, 8, 3, 3                  // 500kbit @ 24MHz; 48 clocks/bit
#define HPTCAN4551_RATE_24M_500K_75_6               6, 5, 2, 2                  // 500kbit @ 24MHz; 48 clocks/bit
#define HPTCAN4551_RATE_24M_500K_75_12              12, 2, 1, 1                 // 500kbit @ 24MHz; 48 clocks/bit
#define HPTCAN4551_RATE_24M_500K_75_1               1, 35, 12, 12               // 500kbit @ 24MHz; 48 clocks/bit

// 1-2Mbit @ 24MHz
#define HPTCAN4551_RATE_24M_1M_75_1                 1, 17, 6, 6                 // 1Mbit @ 24MHz; 24 clocks/bit
#define HPTCAN4551_RATE_24M_1M_75_3                 3, 5, 2, 2                  // 1Mbit @ 24MHz; 24 clocks/bit
#define HPTCAN4551_RATE_24M_1M_75_2                 2, 8, 3, 3                  // 1Mbit @ 24MHz; 24 clocks/bit
#define HPTCAN4551_RATE_24M_1M_75_6                 6, 2, 1, 1                  // 1Mbit @ 24MHz; 24 clocks/bit
#define HPTCAN4551_RATE_24M_2M_75_1                 1, 8, 3, 3                  // 2Mbit @ 24MHz; 12 clocks/bit
#define HPTCAN4551_RATE_24M_2M_75_3                 3, 2, 1, 1                  // 2Mbit @ 24MHz; 12 clocks/bit

// 250kbit @ 30MHz
#define HPTCAN4551_RATE_30M_250K_75_1               1, 89, 30, 30               // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_80_1               1, 95, 24, 24               // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_85_1               1, 101, 18, 18              // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_75_2               2, 44, 15, 15               // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_80_2               2, 47, 12, 12               // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_85_2               2, 50, 9, 9                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_75_3               3, 29, 10, 10               // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_80_3               3, 31, 8, 8                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_85_3               3, 33, 6, 6                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_75_6               6, 14, 5, 5                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_80_6               6, 15, 4, 4                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_85_6               6, 16, 3, 3                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_80_4               4, 23, 6, 6                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_75_5               5, 17, 6, 6                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_80_12              12, 7, 2, 2                 // 250kbit @ 30MHz; 120 clocks/bit
#define HPTCAN4551_RATE_30M_250K_75_15              15, 5, 2, 2                 // 250kbit @ 30MHz; 120 clocks/bit

// 500kbit @ 30MHz
#define HPTCAN4551_RATE_30M_500K_80_2               2, 23, 6, 6                 // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_75_3               3, 14, 5, 5                 // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_80_3               3, 15, 4, 4                 // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_85_3               3, 16, 3, 3                 // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_80_4               4, 11, 3, 3                 // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_75_5               5, 8, 3, 3                  // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_80_6               6, 7, 2, 2                  // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_80_12              12, 3, 1, 1                 // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_75_15              15, 2, 1, 1                 // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_75_1               1, 44, 15, 15               // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_80_1               1, 47, 12, 12               // 500kbit @ 30MHz; 60 clocks/bit
#define HPTCAN4551_RATE_30M_500K_85_1               1, 50, 9, 9                 // 500kbit @ 30MHz; 60 clocks/bit

// 1-2Mbit @ 30MHz
#define HPTCAN4551_RATE_30M_1M_80_1                 1, 23, 6, 6                 // 1Mbit @ 30MHz; 30 clocks/bit
#define HPTCAN4551_RATE_30M_1M_80_3                 3, 7, 2, 2                  // 1Mbit @ 30MHz; 30 clocks/bit
#define HPTCAN4551_RATE_30M_1M_80_2                 2, 11, 3, 3                 // 1Mbit @ 30MHz; 30 clocks/bit
#define HPTCAN4551_RATE_30M_1M_80_6                 6, 3, 1, 1                  // 1Mbit @ 30MHz; 30 clocks/bit
#define HPTCAN4551_RATE_30M_2M_80_1                 1, 11, 3, 3                 // 2Mbit @ 30MHz; 15 clocks/bit
#define HPTCAN4551_RATE_30M_2M_80_3                 3, 3, 1, 1                  // 2Mbit @ 30MHz; 15 clocks/bit

// 250kbit @ 40MHz
#define HPTCAN4551_RATE_40M_250K_75_1               1, 119, 40, 40              // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_80_1               1, 127, 32, 32              // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_85_1               1, 135, 24, 24              // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_75_2               2, 59, 20, 20               // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_80_2               2, 63, 16, 16               // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_85_2               2, 67, 12, 12               // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_75_4               4, 29, 10, 10               // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_80_4               4, 31, 8, 8                 // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_85_4               4, 33, 6, 6                 // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_75_5               5, 23, 8, 8                 // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_75_8               8, 14, 5, 5                 // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_80_8               8, 15, 4, 4                 // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_85_8               8, 16, 3, 3                 // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_75_10              10, 11, 4, 4                // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_80_16              16, 7, 2, 2                 // 250kbit @ 40MHz; 160 clocks/bit
#define HPTCAN4551_RATE_40M_250K_75_20              20, 5, 2, 2                 // 250kbit @ 40MHz; 160 clocks/bit

// 500kbit @ 40MHz
#define HPTCAN4551_RATE_40M_500K_75_2               2, 29, 10, 10               // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_80_2               2, 31, 8, 8                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_75_4               4, 14, 5, 5                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_80_4               4, 15, 4, 4                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_85_4               4, 16, 3, 3                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_75_5               5, 11, 4, 4                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_80_8               8, 7, 2, 2                  // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_75_10              10, 5, 2, 2                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_80_16              16, 3, 1, 1                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_75_20              20, 2, 1, 1                 // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_75_1               1, 59, 20, 20               // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_80_1               1, 63, 16, 16               // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_85_1               1, 67, 12, 12               // 500kbit @ 40MHz; 80 clocks/bit
#define HPTCAN4551_RATE_40M_500K_85_2               2, 33, 6, 6                 // 500kbit @ 40MHz; 80 clocks/bit

// 1Mbit @ 40MHz
#define HPTCAN4551_RATE_40M_1M_75_1                 1, 29, 10, 10               // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_80_1                 1, 31, 8, 8                 // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_85_1                 1, 33, 6, 6                 // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_75_2                 2, 14, 5, 5                 // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_80_2                 2, 15, 4, 4                 // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_85_2                 2, 16, 3, 3                 // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_80_4                 4, 7, 2, 2                  // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_75_5                 5, 5, 2, 2                  // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_80_8                 8, 3, 1, 1                  // 1Mbit @ 40MHz; 40 clocks/bit
#define HPTCAN4551_RATE_40M_1M_75_10                10, 2, 1, 1                 // 1Mbit @ 40MHz; 40 clocks/bit

// 2-4Mbit @ 40MHz
#define HPTCAN4551_RATE_40M_2M_75_1                 1, 14, 5, 5                 // 2Mbit @ 40MHz; 20 clocks/bit
#define HPTCAN4551_RATE_40M_2M_80_1                 1, 15, 4, 4                 // 2Mbit @ 40MHz; 20 clocks/bit
#define HPTCAN4551_RATE_40M_2M_85_1                 1, 16, 3, 3                 // 2Mbit @ 40MHz; 20 clocks/bit
#define HPTCAN4551_RATE_40M_2M_80_2                 2, 7, 2, 2                  // 2Mbit @ 40MHz; 20 clocks/bit
#define HPTCAN4551_RATE_40M_2M_80_4                 4, 3, 1, 1                  // 2Mbit @ 40MHz; 20 clocks/bit
#define HPTCAN4551_RATE_40M_2M_75_5                 5, 2, 1, 1                  // 2Mbit @ 40MHz; 20 clocks/bit
#define HPTCAN4551_RATE_40M_4M_80_1                 1, 7, 2, 2                  // 4Mbit @ 40MHz; 10 clocks/bit
#define HPTCAN4551_RATE_40M_4M_80_2                 2, 3, 1, 1                  // 4Mbit @ 40MHz; 10 clocks/bit
#define HPTCAN4551_RATE_40M_8M_80_1                 1, 3, 1, 1                  // 8Mbit @ 40MHz; 5 clocks/bit

// 250kbit @ 60MHz
#define HPTCAN4551_RATE_60M_250K_75_2               2, 89, 30, 30               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_2               2, 95, 24, 24               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_85_2               2, 101, 18, 18              // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_3               3, 59, 20, 20               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_3               3, 63, 16, 16               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_85_3               3, 67, 12, 12               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_4               4, 44, 15, 15               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_4               4, 47, 12, 12               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_85_4               4, 50, 9, 9                 // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_5               5, 35, 12, 12               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_6               6, 29, 10, 10               // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_6               6, 31, 8, 8                 // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_85_6               6, 33, 6, 6                 // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_12              12, 14, 5, 5                // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_12              12, 15, 4, 4                // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_85_12              12, 16, 3, 3                // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_15              15, 11, 4, 4                // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_1               1, 179, 60, 60              // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_1               1, 191, 48, 48              // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_85_1               1, 203, 36, 36              // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_8               8, 23, 6, 6                 // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_10              10, 17, 6, 6                // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_80_24              24, 7, 2, 2                 // 250kbit @ 60MHz; 240 clocks/bit
#define HPTCAN4551_RATE_60M_250K_75_30              30, 5, 2, 2                 // 250kbit @ 60MHz; 240 clocks/bit

// 500kbit @ 60MHz
#define HPTCAN4551_RATE_60M_500K_75_3               3, 29, 10, 10               // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_3               3, 31, 8, 8                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_4               4, 23, 6, 6                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_75_5               5, 17, 6, 6                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_75_6               6, 14, 5, 5                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_6               6, 15, 4, 4                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_85_6               6, 16, 3, 3                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_8               8, 11, 3, 3                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_75_10              10, 8, 3, 3                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_12              12, 7, 2, 2                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_75_15              15, 5, 2, 2                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_24              24, 3, 1, 1                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_75_30              30, 2, 1, 1                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_75_2               2, 44, 15, 15               // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_2               2, 47, 12, 12               // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_85_2               2, 50, 9, 9                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_85_3               3, 33, 6, 6                 // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_75_1               1, 89, 30, 30               // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_80_1               1, 95, 24, 24               // 500kbit @ 60MHz; 120 clocks/bit
#define HPTCAN4551_RATE_60M_500K_85_1               1, 101, 18, 18              // 500kbit @ 60MHz; 120 clocks/bit

// 1Mbit @ 60MHz
#define HPTCAN4551_RATE_60M_1M_75_1                 1, 44, 15, 15               // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_80_1                 1, 47, 12, 12               // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_85_1                 1, 50, 9, 9                 // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_80_2                 2, 23, 6, 6                 // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_75_3                 3, 14, 5, 5                 // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_80_3                 3, 15, 4, 4                 // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_85_3                 3, 16, 3, 3                 // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_80_6                 6, 7, 2, 2                  // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_80_4                 4, 11, 3, 3                 // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_75_5                 5, 8, 3, 3                  // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_80_12                12, 3, 1, 1                 // 1Mbit @ 60MHz; 60 clocks/bit
#define HPTCAN4551_RATE_60M_1M_75_15                15, 2, 1, 1                 // 1Mbit @ 60MHz; 60 clocks/bit

// 2-4Mbit @ 60MHz
#define HPTCAN4551_RATE_60M_2M_80_1                 1, 23, 6, 6                 // 2Mbit @ 60MHz; 30 clocks/bit
#define HPTCAN4551_RATE_60M_2M_80_2                 2, 11, 3, 3                 // 2Mbit @ 60MHz; 30 clocks/bit
#define HPTCAN4551_RATE_60M_2M_80_3                 3, 7, 2, 2                  // 2Mbit @ 60MHz; 30 clocks/bit
#define HPTCAN4551_RATE_60M_2M_80_6                 6, 3, 1, 1                  // 2Mbit @ 60MHz; 30 clocks/bit
#define HPTCAN4551_RATE_60M_4M_80_1                 1, 11, 3, 3                 // 4Mbit @ 60MHz; 15 clocks/bit
#define HPTCAN4551_RATE_60M_4M_80_3                 3, 3, 1, 1                  // 4Mbit @ 60MHz; 15 clocks/bit

// 250kbit @ 80MHz
#define HPTCAN4551_RATE_80M_250K_75_2               2, 119, 40, 40              // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_80_2               2, 127, 32, 32              // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_85_2               2, 135, 24, 24              // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_4               4, 59, 20, 20               // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_80_4               4, 63, 16, 16               // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_85_4               4, 67, 12, 12               // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_5               5, 47, 16, 16               // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_8               8, 29, 10, 10               // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_80_8               8, 31, 8, 8                 // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_85_8               8, 33, 6, 6                 // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_10              10, 23, 8, 8                // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_16              16, 14, 5, 5                // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_80_16              16, 15, 4, 4                // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_85_16              16, 16, 3, 3                // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_20              20, 11, 4, 4                // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_1               1, 239, 80, 80              // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_80_1               1, 255, 64, 64              // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_80_32              32, 7, 2, 2                 // 250kbit @ 80MHz; 320 clocks/bit
#define HPTCAN4551_RATE_80M_250K_75_40              40, 5, 2, 2                 // 250kbit @ 80MHz; 320 clocks/bit

// 500kbit @ 80MHz
#define HPTCAN4551_RATE_80M_500K_75_4               4, 29, 10, 10               // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_80_4               4, 31, 8, 8                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_75_5               5, 23, 8, 8                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_75_8               8, 14, 5, 5                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_80_8               8, 15, 4, 4                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_85_8               8, 16, 3, 3                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_75_10              10, 11, 4, 4                // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_80_16              16, 7, 2, 2                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_75_20              20, 5, 2, 2                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_80_32              32, 3, 1, 1                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_75_40              40, 2, 1, 1                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_75_2               2, 59, 20, 20               // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_80_2               2, 63, 16, 16               // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_85_2               2, 67, 12, 12               // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_85_4               4, 33, 6, 6                 // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_75_1               1, 119, 40, 40              // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_80_1               1, 127, 32, 32              // 500kbit @ 80MHz; 160 clocks/bit
#define HPTCAN4551_RATE_80M_500K_85_1               1, 135, 24, 24              // 500kbit @ 80MHz; 160 clocks/bit

// 1Mbit @ 80MHz
#define HPTCAN4551_RATE_80M_1M_75_1                 1, 59, 20, 20               // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_80_1                 1, 63, 16, 16               // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_85_1                 1, 67, 12, 12               // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_75_2                 2, 29, 10, 10               // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_80_2                 2, 31, 8, 8                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_85_2                 2, 33, 6, 6                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_75_4                 4, 14, 5, 5                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_80_4                 4, 15, 4, 4                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_85_4                 4, 16, 3, 3                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_75_5                 5, 11, 4, 4                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_80_8                 8, 7, 2, 2                  // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_75_10                10, 5, 2, 2                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_80_16                16, 3, 1, 1                 // 1Mbit @ 80MHz; 80 clocks/bit
#define HPTCAN4551_RATE_80M_1M_75_20                20, 2, 1, 1                 // 1Mbit @ 80MHz; 80 clocks/bit

// 2-4Mbit @ 80MHz
#define HPTCAN4551_RATE_80M_2M_75_1                 1, 29, 10, 10               // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_80_1                 1, 31, 8, 8                 // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_75_2                 2, 14, 5, 5                 // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_80_2                 2, 15, 4, 4                 // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_85_2                 2, 16, 3, 3                 // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_80_4                 4, 7, 2, 2                  // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_75_5                 5, 5, 2, 2                  // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_80_8                 8, 3, 1, 1                  // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_2M_75_10                10, 2, 1, 1                 // 2Mbit @ 80MHz; 40 clocks/bit
#define HPTCAN4551_RATE_80M_4M_75_1                 1, 14, 5, 5                 // 4Mbit @ 80MHz; 20 clocks/bit
#define HPTCAN4551_RATE_80M_4M_80_1                 1, 15, 4, 4                 // 4Mbit @ 80MHz; 20 clocks/bit
#define HPTCAN4551_RATE_80M_4M_85_1                 1, 16, 3, 3                 // 4Mbit @ 80MHz; 20 clocks/bit
#define HPTCAN4551_RATE_80M_4M_80_2                 2, 7, 2, 2                  // 4Mbit @ 80MHz; 20 clocks/bit
#define HPTCAN4551_RATE_80M_4M_80_4                 4, 3, 1, 1                  // 4Mbit @ 80MHz; 20 clocks/bit
#define HPTCAN4551_RATE_80M_4M_75_5                 5, 2, 1, 1                  // 4Mbit @ 80MHz; 20 clocks/bit
#define HPTCAN4551_RATE_80M_8M_80_1                 1, 7, 2, 2                  // 8Mbit @ 80MHz; 10 clocks/bit
#define HPTCAN4551_RATE_80M_8M_80_2                 2, 3, 1, 1                  // 8Mbit @ 80MHz; 10 clocks/bit

#endif // CLASS_HPTCAN4551_RATES_H
