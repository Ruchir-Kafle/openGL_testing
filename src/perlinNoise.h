#pragma once

class PerlinNoise {
    public:
        static void PerlinNoise1D(int nCount, float *fSeed, int octaves, float *fOutput);
        static void PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float *fOutput);
};