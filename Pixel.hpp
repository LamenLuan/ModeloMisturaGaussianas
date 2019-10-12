#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include "Gaussiana.hpp"

class Pixel
{
private:
    // Quantidade de gaussianas usadas na mistura.
    enum QUANTIDADE_DISTRIBUICOES {QUANTIDADE_DISTRIBUICOES = 3};
    Gaussiana* m_mistura[QUANTIDADE_DISTRIBUICOES];

public:
    // Construtores/Destrutores:
    Pixel(int valorDoPixel = 0);
    virtual ~Pixel();
    // Metodos:
    float probabilidadeDoPixel(int valorDoPixel = 0);
    // Getters:

    // Setters:

};

#endif