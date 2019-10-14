#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include "Gaussiana.hpp"

class Pixel
{
private:

public:
    // Quantidade de gaussianas usadas na mistura.
    enum M_QUANTIDADE_DISTRIBUICOES {M_QUANTIDADE_DISTRIBUICOES = 3};
    
    Gaussiana* m_mistura[M_QUANTIDADE_DISTRIBUICOES];
    // Construtores/Destrutores:
    Pixel(int t_valorPixel = 0);
    virtual ~Pixel();
    // Metodos:
    float probabilidadeDoPixel(int t_valorPixel = 0);
    void leNovoPixel(int t_valorPixel);
    void renormalizaGaussiana(void);
    // Getters:

    // Setters:

};

#endif