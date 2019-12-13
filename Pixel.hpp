#include "Gaussiana.hpp"

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

class Pixel
{
private:
public:
    // Quantidade de gaussianas usadas na mistura.
    static const int M_QUANTIDADE_DISTRIBUICOES;

    Gaussiana *m_mistura = new Gaussiana[M_QUANTIDADE_DISTRIBUICOES];

// Construtores/Destrutores:
    Pixel(int t_valorPixel = 0);
    virtual ~Pixel();

// Metodos:
    float probabilidadeDoPixel(int t_valorPixel) const;
    short buscaMaiorPeso() const;
    void renormalizaGaussianas();
    void leNovoPixel(int t_valorPixel);
    short buscaMenorPeso() const;
    float pixelMaisProvavel();
    
// Getters:

// Setters:

};

#endif