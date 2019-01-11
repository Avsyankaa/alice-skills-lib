// Copyright 2019 SemenAndreev
#include <modules.hpp>

void MOD(__int64_t& value, const __uint32_t module);

__uint32_t XOR(const __uint32_t block, const __uint32_t key)
{
    return block ^ key;
}

__uint32_t CircleRotation(const __uint32_t block, const unsigned char rotationIndex)
{
    __uint32_t rightHalf = block >> (BLOCK_SIZE - rotationIndex);
    __uint32_t leftHalf = block << rotationIndex;
    return rightHalf | leftHalf;
}

__uint32_t ModAdditation(const __uint32_t firstBlock, const __uint32_t secondBlock, const __uint32_t module)
{
    __int64_t summ = firstBlock;
    summ += secondBlock;
    MOD(summ, module);
    return summ;
}

__uint32_t ModSubtruction(const __uint32_t unknownBlock, const __uint32_t knownBlock, const __uint32_t module)
{
    __int64_t sub = unknownBlock;
    sub -= knownBlock;
    MOD(sub, module);
    return sub;
}

void MOD(__int64_t& value, const __uint32_t module)
{
    while (value > module)
    {
        value -= module;
    }
    while (value < 0)
    {
        value += module;
    }
}
