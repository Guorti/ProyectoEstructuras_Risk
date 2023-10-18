#ifndef HUFFMAN_DATA_HXX
#define HUFFMAN_DATA_HXX

#include "HuffmanData.h"

HuffmanData::HuffmanData() = default;

HuffmanData::HuffmanData(char symbol, int frecuencia)
{
    this->symbol = symbol;
    this->frecuencia = frecuencia;
}

HuffmanData::HuffmanData(int frecuencia)
{
    this->symbol = '\0';
    this->frecuencia = frecuencia;
}

HuffmanData::~HuffmanData()
{
}

char HuffmanData::getSymbol() const
{
    return symbol;
}

void HuffmanData::setSymbol(char symbol)
{
    this->symbol = symbol;
}

int HuffmanData::getFrecuencia() const
{
    return frecuencia;
}

void HuffmanData::setFrecuencia(int frecuencia)
{
    this->frecuencia = frecuencia;
}

bool HuffmanData::operator<(HuffmanData const &otherHuffmanData) const
{
    return frecuencia < otherHuffmanData.frecuencia || (frecuencia == otherHuffmanData.frecuencia && symbol < otherHuffmanData.symbol);
}

bool HuffmanData::operator>(HuffmanData const &otherHuffmanData) const
{
    return frecuencia > otherHuffmanData.frecuencia || (frecuencia == otherHuffmanData.frecuencia && symbol > otherHuffmanData.symbol);
}


bool HuffmanData::operator==(HuffmanData const &otherHuffmanData) const
{
    return frecuencia == otherHuffmanData.frecuencia;
}

bool HuffmanData::operator!=(HuffmanData const &otherHuffmanData) const
{
    return !(otherHuffmanData == *this);
}

#endif