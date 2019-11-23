#include <cmath>
#include <iostream>

#ifndef GAUSSIANA_HPP_
#define GAUSSIANA_HPP_

class Gaussiana
{
private:
    float m_media{0.0};
    float m_desvioPadrao{0.5};
    float m_peso{0};

public:

    // Constante de aprendizagem usada na atualizacao
    // dos valores da Gaussiana.
    static const float M_CONSTANTE_APRENDIZAGEM;

// Construtores/Destrutores:
    Gaussiana(float t_media = 0, float t_peso = 1);
    virtual ~Gaussiana();

// Metodos:
    float funcaoDensidadeProbabilidade(int t_valorPixel);
    float funcaoRho(int t_valorPixel);
    void atualizaPeso(bool t_match);
    void atualizaMedia(int t_valorPixel);
    void atualizaDesvioPadrao(int t_valorPixel);
    bool verificaMatch(int t_valorPixel) const;

// Getters:
    float getMedia() const;
    float getDesvioPadrao() const;
    float getPeso() const;

// Setters:
    void setMedia(float t_media);
    void setDesvioPadrao(float t_desvioPadrao);
    void setPeso(float t_peso);
};

#endif
