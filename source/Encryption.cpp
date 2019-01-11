#include <Encryption.hpp>

void FormatText(std::string& text);

__uint32_t Get32bits(std::string& text);

void CropText(std::string& text);

void EncryptionAlgorithm(__uint32_t& firstBlock, __uint32_t& secondBlock, const __uint32_t key);

std::string IntToHexStr(const __uint32_t value);

std::string Encryption(std::string& text, const __uint32_t key)
{
    std::string source = text;
    FormatText(source);
    std::string cryptoText;
    while (!source.empty())
    {
        __uint32_t firstBlock = Get32bits(source);
        CropText(source);
        __uint32_t secondBlock = Get32bits(source);
        CropText(source);
        for (size_t round = 0; round < N; round++)
        {
            EncryptionAlgorithm(firstBlock, secondBlock, key);
            EncryptionAlgorithm(secondBlock, firstBlock, key);
        }
        cryptoText += IntToHexStr(firstBlock);
        cryptoText += IntToHexStr(secondBlock);
    }
    return cryptoText;
}

void FormatText(std::string& text)
{
    if (text.size()%(BLOCK_SIZE/8) != 0)
    {
        size_t numOfNeededSymbols = text.size()%(BLOCK_SIZE/8);
        for (size_t len = 0; len <= numOfNeededSymbols; len++)
        {
            text[text.size() + len] = 0;
        }
    }
}

__uint32_t Get32bits(std::string& text) {
    __uint32_t bits = 0x00000000;
    for (size_t symbol = 0; symbol < BLOCK_SIZE/8; symbol++)
    {
        bits |= text[symbol];
        bits = CircleRotation(bits, 8*sizeof(char));
    }
    return bits;
}

void CropText(std::string& text)
{
    std::string croped;
    for (size_t i = BLOCK_SIZE/8; i < text.size(); i++)
    {
        croped += text[i];
    }
    text = croped;
}

void EncryptionAlgorithm(__uint32_t& firstBlock, __uint32_t& secondBlock, const __uint32_t key)
{
    firstBlock = XOR(firstBlock, key);
    secondBlock = CircleRotation(secondBlock, ROTATION_INDEX);
    secondBlock = ModAdditation(firstBlock, secondBlock, MODULE);
}

std::string IntToHexStr(const __uint32_t value)
{
    std::stringstream stream;
    stream << std::hex << value;
    std::string str = stream.str();
    return str;
}
