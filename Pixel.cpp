#include "Pixel.hpp"

Pixel::Pixel(int valorDoPixel)
{
    for (size_t i = 0; i < QUANTIDADE_DISTRIBUICOES; i++)
        m_mistura[i] = new Gaussiana(valorDoPixel, (float) 1 / 
            QUANTIDADE_DISTRIBUICOES);
}

Pixel::~Pixel()
{
    for (size_t i = 0; i < QUANTIDADE_DISTRIBUICOES; i++)
        delete m_mistura[i];
}

float Pixel::probabilidadeDoPixel(int valorDoPixel)
{
    float probabilidade = 0;
    for (size_t i = 0; i < QUANTIDADE_DISTRIBUICOES; i++)
        probabilidade += 
            m_mistura[i]->funcaoDensidadeProbabilidade(valorDoPixel) *
            m_mistura[i]->getPeso();
    return probabilidade;
}