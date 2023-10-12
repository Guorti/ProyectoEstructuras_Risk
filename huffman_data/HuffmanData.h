#ifndef HUFFMAN_DATA_H
#define HUFFMAN_DATA_H

using namespace std;

class HuffmanData
{
private:
    char symbol;
    int frecuencia;

public:
    /* Constructor and Destructor */
    HuffmanData();
    HuffmanData(char symbol, int frecuencia);
    HuffmanData(int frecuencia);
    ~HuffmanData();

    /* Getters and Setters */
    char getSymbol() const;
    void setSymbol(char symbol);

    int getFrecuencia() const;
    void setFrecuencia(int frecuencia);

    /* Operators */

    bool operator<(HuffmanData const &otherHuffmanData) const;

    bool operator>(HuffmanData const &otherHuffmanData) const;

    bool operator==(HuffmanData const &otherHuffmanData) const;

    bool operator!=(HuffmanData const &otherHuffmanData) const;

};
#include "HuffmanData.hxx"
#endif