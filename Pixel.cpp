#include "Pixel.hpp"

const int Pixel::M_QUANTIDADE_DISTRIBUICOES = 3;

// Construtores/Destrutores:
Pixel::Pixel(int t_valorPixel)
{
    for (size_t i = 0; i < Pixel::M_QUANTIDADE_DISTRIBUICOES; i++)
    {
        (m_mistura + i)->setMedia(t_valorPixel);
        (m_mistura + i)->setPeso((float)1 / Pixel::M_QUANTIDADE_DISTRIBUICOES);
    }
}

Pixel::~Pixel()
{
    delete[] m_mistura;
}

// Metodos:

// Probabilidade total do pixel vai ser a soma da funcao densidade
// probabilidade de cada gaussiana da mistura multiplicado por seu peso
// especifico.
float Pixel::probabilidadeDoPixel(int t_valorPixel) const
{
    float probabilidade = 0;
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
        probabilidade +=
            (m_mistura + i)->funcaoDensidadeProbabilidade(t_valorPixel) *
            (m_mistura + i)->getPeso();
    return probabilidade;
}

float Pixel::pixelMaisProvavel()
{
    return m_mistura[buscaMaiorPeso() ].getMedia();
}

void Pixel::renormalizaGaussianas()
{
    // O valor SomatorioPesos esta baseado na soma de todos os pesos, e o
    // valor minimo sera sempre zero.
    float SomatorioPesos = 0;
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
        SomatorioPesos += (m_mistura + i)->getPeso();

    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
        (m_mistura + i)->setPeso((m_mistura + i)->getPeso() / SomatorioPesos);
}

void Pixel::leNovoPixel(int t_valorPixel)
{
    bool match = false;
    short indiceMenor;
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
    {
        if ((m_mistura + i)->verificaMatch(t_valorPixel))
        {
            (m_mistura + i)->atualizaMedia(t_valorPixel);
            (m_mistura + i)->atualizaDesvioPadrao(t_valorPixel);
            (m_mistura + i)->atualizaPeso(true);
            match = true;
        }
        else
            (m_mistura + i)->atualizaPeso(false);
    }
    if (!match)
    {
        indiceMenor = buscaMenorPeso();
        (m_mistura + indiceMenor)->setMedia(t_valorPixel);
        (m_mistura + indiceMenor)->setDesvioPadrao(3);
        (m_mistura + indiceMenor)->setPeso(0.01);
    }
    renormalizaGaussianas();
}
 
short Pixel::buscaMenorPeso() const
{
    short indiceMenor = 0;
    for (size_t i = 1; i < M_QUANTIDADE_DISTRIBUICOES; i++)
    {
        if ((m_mistura + indiceMenor)->getPeso() > (m_mistura + i)->getPeso())
            indiceMenor = i;
    }
    return indiceMenor;
}

short Pixel::buscaMaiorPeso() const
{
    short indiceMenor = 0;
    for (size_t i = 1; i < M_QUANTIDADE_DISTRIBUICOES; i++)
    {
        if ((m_mistura + indiceMenor)->getPeso() < (m_mistura + i)->getPeso())
            indiceMenor = i;
    }
    return indiceMenor;
}
