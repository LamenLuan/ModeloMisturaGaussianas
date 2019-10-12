#ifndef GAUSSIANA_HPP_
#define GAUSSIANA_HPP_

#include <cmath>

class Gaussiana
{
private:
    float m_media{0.0};
    float m_desvioPadrao{0.5};
    float m_peso{0};

public:
    // Constante de aprendizagem usada na atualização
    // dos valores da Gaussiana.
    static const float CONSTANTE_APRENDIZAGEM;

    // Construtores/Destrutores:
    Gaussiana(float t_media = 0, float t_peso = 0);
    virtual ~Gaussiana();

    // Metodos:
    float funcaoDensidadeProbabilidade(int t_valorPixel);
    float funcaoRho();
    void atualizaPeso(bool t_match);
    void atualizaMedia(int t_valorPixel);
    void atualizaDesvioPadrao(int t_valorPixel);

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
