#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include "Gaussiana.hpp"

class Pixel
{
private:
    // Quantidade de gaussianas usadas na mistura.
public:
    enum M_QUANTIDADE_DISTRIBUICOES {M_QUANTIDADE_DISTRIBUICOES = 3};
    Gaussiana* m_mistura[M_QUANTIDADE_DISTRIBUICOES];
    
    // Construtores/Destrutores:
    Pixel(int valorDoPixel = 0);
    virtual ~Pixel();
    // Metodos:
    float probabilidadeDoPixel(int valorDoPixel = 0);
    // Getters:

    // Setters:

};

#endif