#pragma once

#include <cmath>
#include "RTWeekend.h"
#include "Vec3.h"

struct Perlin {

private:
    static const int pointCount = 256;
    static const int mask = pointCount - 1;

    Vec3* randomVectors;
    int* permX;
    int* permY;
    int* permZ;

public:
    Perlin() {
        randomVectors = new Vec3[pointCount];
        for (size_t i = 0; i < pointCount; i++) {
            Vec3 v = Vec3::Random(-1.0f, 1.0f);
            v.Normalize();
            randomVectors[i] = v;
        }

        permX = PerlinGeneratePerm();
        permY = PerlinGeneratePerm();
        permZ = PerlinGeneratePerm();
    }

    ~Perlin() {
        delete[] randomVectors;
        delete[] permX;
        delete[] permY;
        delete[] permZ;
    }

    float Noise(const Vec3& p) const {
        float u = p.X - std::floorf(p.X);
        float v = p.Y - std::floorf(p.Y);
        float w = p.Z - std::floorf(p.Z);

        int i = static_cast<int>(std::floorf(p.X));
        int j = static_cast<int>(std::floorf(p.Y));
        int k = static_cast<int>(std::floorf(p.Z));

        Vec3 c[2][2][2]{ };

        for (int di = 0; di < 2; di++) {
            for (int dj = 0; dj < 2; dj++) {
                for (int dk = 0; dk < 2; dk++) {
                    c[di][dj][dk] = randomVectors[
                        permX[(i + di) & mask] ^
                        permY[(j + dj) & mask] ^
                        permZ[(k + dk) & mask]
                    ];
                }
            }
        }

        return TrilinearInterp(c, u, v, w);
    }

    float Turbulence(const Vec3& p, int depth = 7) const {
        float acc = 0.0f;
        Vec3 pTemp = p;
        float weight = 1.0f;

        for (int i = 0; i < depth; i++) {
            acc += Noise(pTemp) * weight;
            weight *= 0.5f;
            pTemp *= 2.0f;
        }

        return std::fabsf(acc);
    }

private:
    static int* PerlinGeneratePerm() {
        int* p = new int[pointCount];
        for (int i = 0; i < pointCount; i++) {
            p[i] = i;
        }

        Permute(p, pointCount);

        return p;
    }

    static void Permute(int* p, int n) {
        for (int i = n - 1; i > 0; i--) {
            int target = RandomInt(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }

    static float TrilinearInterp(Vec3 c[2][2][2], float u, float v, float w) {
        float uu = u * u * (3 - 2 * u);
        float vv = v * v * (3 - 2 * v);
        float ww = w * w * (3 - 2 * w);

        float acc = 0.0f;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    Vec3 weightVec(u - i, v - j, w - k);
                    acc += (i * uu + (1 - i) * (1 - uu))
                         * (j * vv + (1 - j) * (1 - vv))
                         * (k * ww + (1 - k) * (1 - ww))
                         * Vec3::Dot(c[i][j][k], weightVec);

                }
            }
        }

        return acc;
    }
};