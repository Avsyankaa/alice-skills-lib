// Copyright 2019 SemenAndreev
#include <decryption.hpp>

__uint32_t Get32bitsFromHexText(std::string& text);

void CropHexText(std::string& text);

void DecryptionAlgorithm(__uint32_t& firstBlock, __uint32_t& secondBlock, const __uint32_t key);

std::string IntToString(__uint32_t value);

void FormatString(std::string& string);

std::string Decryption(std::string& cryptoText, const __uint32_t key)
{
    std::string openText;
    while (!cryptoText.empty())
    {
        __uint32_t firstBlock = Get32bitsFromHexText(cryptoText);
        CropHexText(cryptoText);
        __uint32_t secondBlock = Get32bitsFromHexText(cryptoText);
        CropHexText(cryptoText);
        for (size_t round = 0; round < N; round++) // TODO: CHANGE IT
        {
            DecryptionAlgorithm(firstBlock, secondBlock, key);
            DecryptionAlgorithm(secondBlock, firstBlock, key);
        }
        openText += IntToString(firstBlock);
        openText += IntToString(secondBlock);
    }
    FormatString(openText);
    return openText;
}

__uint32_t Get32bitsFromHexText(std::string& text)
{
    std::stringstream stream;
    for (size_t i = 0; i < 2*BLOCK_SIZE/8; i++)
    {
        stream << std::hex << text[i];
    }
    __uint32_t binaryBlock;
    stream >> binaryBlock;
    return binaryBlock;
}

void CropHexText(std::string& text)
{
    std::string croped;
    for (size_t i = 2*BLOCK_SIZE/8; i < text.size(); i++)
    {
        croped += text[i];
    }
    text = croped;
}

void DecryptionAlgorithm(__uint32_t& firstBlock, __uint32_t& secondBlock, const __uint32_t key)
{
    firstBlock = ModSubtruction(firstBlock, secondBlock, MODULE);
    firstBlock = CircleRotation(firstBlock, BLOCK_SIZE - ROTATION_INDEX);
    secondBlock = XOR(secondBlock, key);
}

std::string IntToString(__uint32_t value)
{
    std::string str;
    for (size_t symbol = 0; symbol < BLOCK_SIZE/8; symbol++)
    {
        char ch = 0x00;
        ch |= value;
        value = CircleRotation(value, 8*sizeof(char));
        str += ch;
    }
    return str;
}

void FormatString(std::string& str)
{
    std::string formated;
    size_t i = 0;
    while (str[i])
    {
        formated += str[i];
        i++;
    }
    str = formated;
}
