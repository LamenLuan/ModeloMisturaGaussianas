#include "Gaussiana.hpp"

const float Gaussiana::M_CONSTANTE_APRENDIZAGEM = 2.5;

// Construtores/Destrutores:
Gaussiana::Gaussiana(float t_media, float t_peso)
    : m_media(t_media), m_peso(t_peso)
{
}

Gaussiana::~Gaussiana()
{
}

// Metodos:
float Gaussiana::funcaoDensidadeProbabilidade(int t_valorPixel)
{
    // Dividindo a formula em duas partes por ser extensa.
    float parte1 = 0, parte2 = 0, diferenca = t_valorPixel - m_media;

    parte1 = 1 / (sqrt(2 * M_PI) * m_desvioPadrao);

    parte2 = exp(-0.5 * pow(diferenca, 2) * (1 / m_desvioPadrao));

    return parte1 * parte2;
}

float Gaussiana::funcaoRho()
{
    float rho = funcaoDensidadeProbabilidade(m_media) *
        M_CONSTANTE_APRENDIZAGEM;
    return rho;
}

void Gaussiana::atualizaPeso(bool t_match)
{
    m_peso = m_peso + M_CONSTANTE_APRENDIZAGEM * ( (int) t_match - m_peso);
}

void Gaussiana::atualizaMedia(int t_valorPixel)
{
    m_media = ((1 - funcaoRho()) * m_media) + (funcaoRho() * t_valorPixel);
}

void Gaussiana::atualizaDesvioPadrao(int t_valorPixel)
{
    float diferenca = t_valorPixel - m_media;

    m_desvioPadrao = ((1 - funcaoRho()) * m_desvioPadrao) +
        (funcaoRho() * diferenca * diferenca);
}

// Getters:
float Gaussiana::getMedia() const { return m_media; }
float Gaussiana::getDesvioPadrao() const { return m_desvioPadrao; }
float Gaussiana::getPeso() const { return m_peso; }

// Setters:
void Gaussiana::setMedia(float t_media)
{
    m_media = t_media;
}
void Gaussiana::setDesvioPadrao(float t_desvioPadrao)
{
    m_desvioPadrao = t_desvioPadrao;
}
void Gaussiana::setPeso(float t_peso)
{
    m_peso = t_peso;
}