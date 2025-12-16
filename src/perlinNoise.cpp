#include <iostream>
#include <random>
#include "perlinNoise.h"


// Credits:
// https://www.youtube.com/watch?v=6-0UaeJBumA
// https://github.com/OneLoneCoder/Javidx9/blob/master/ConsoleGameEngine/SmallerProjects/OneLoneCoder_PerlinNoise.cpp

void PerlinNoise::PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float *fOutput) {
    // Used 1D Perlin Noise
    for (int x = 0; x < nCount; x++)
    {
        float fNoise = 0.0f;
        float fScaleAcc = 0.0f;
        float fScale = 1.0f;

        for (int o = 0; o < nOctaves; o++)
        {
            int nPitch = nCount >> o;
            if (nPitch <= 1) break;
            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % nCount;

            float fBlend = (float)(x - nSample1) / (float)nPitch;
            float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];

            fScaleAcc += fScale;
            fNoise += fSample * fScale;
            fScale /= 2.0f;
        }

        // Scale to seed range
        fOutput[x] = fNoise / fScaleAcc;
    }
}

void PerlinNoise::PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float *fOutput) {
		// Used 1D Perlin Noise
		for (int x = 0; x < nWidth; x++) {
			for (int y = 0; y < nHeight; y++) {				
				float fNoise = 0.0f;
				float fScaleAcc = 0.0f;
				float fScale = 1.0f;

				for (int o = 0; o < nOctaves; o++) {
					int nPitch = nWidth >> o;
					int nSampleX1 = (x / nPitch) * nPitch;
					int nSampleY1 = (y / nPitch) * nPitch;
					
					int nSampleX2 = (nSampleX1 + nPitch) % nWidth;					
					int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

					float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
					float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

					float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
					float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

					fScaleAcc += fScale;
					fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
					fScale = fScale / 2.0f;
				}

				// Scale to seed range
				fOutput[y * nWidth + x] = fNoise / fScaleAcc;
			}
	}
};