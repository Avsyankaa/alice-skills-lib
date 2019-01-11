// Copyright 2019 SemenAndreev
#ifndef MODULES_HPP
#define MODULES_HPP

#include <cmath>

#define ROTATION_INDEX 17
#define BLOCK_SIZE 32
#define MODULE static_cast<__uint32_t>(pow(2, BLOCK_SIZE) - 1)
#define N 32

__uint32_t XOR(const __uint32_t block, const __uint32_t key);
__uint32_t CircleRotation(const __uint32_t block, const unsigned char rotationIndex);
__uint32_t ModAdditation(const __uint32_t firstBlock, const __uint32_t secondBlock, const __uint32_t module);
__uint32_t ModSubtruction(const __uint32_t unknownBlock, const __uint32_t knownBlock, const __uint32_t module);

#endif // MODULES_HPP
