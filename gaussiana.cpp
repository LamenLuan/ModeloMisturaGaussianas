#include "gaussiana.hpp"

//Construtores/Destrutores:
GaussianaAdaptativa::GaussianaAdaptativa(float t_media, float t_peso)
: m_media(t_media), m_peso(t_peso)
{

}

GaussianaAdaptativa::~GaussianaAdaptativa()
{

}

//Getters:
float GaussianaAdaptativa::getMedia() {return m_media; }
float GaussianaAdaptativa::getDesvioPadrao() {return m_desvioPadrao; }
float GaussianaAdaptativa::getPeso() {return m_peso; }

//Setters:
void GaussianaAdaptativa::setMedia(float t_media)
{ 
    m_media = t_media;
}
void GaussianaAdaptativa::setDesvioPadrao(float t_desvioPadrao)
{ 
    m_desvioPadrao = t_desvioPadrao;
}
void GaussianaAdaptativa::setPeso(float t_peso)
{
    m_peso = t_peso;
}

//Metodos:
float GaussianaAdaptativa::funcaoDensidadeProbabilidade(int t_valorPixel)
{
    //Dividindo a formula em duas partes por ser extensa.
    float parte1 = 0, parte2 = 0, diferenca = t_valorPixel - m_media;

    parte1 = 1 / ( pow( (2 * M_PI),
    ( GaussianaAdaptativa::dimensionalidade/ 2) ) * pow(fabs(m_desvioPadrao), 0.5) );

    parte2 = exp(-0.5 * diferenca * (1 / m_desvioPadrao) * diferenca);
    return parte1 * parte2;
}

float GaussianaAdaptativa::funcaoRho()
{
    float rho = funcaoDensidadeProbabilidade(m_media) * constanteAprendizagem;
    return rho;
}

void GaussianaAdaptativa::atualizaPeso(bool t_match)
{
    m_peso = ( (1 - constanteAprendizagem) * m_peso) +
    (constanteAprendizagem * (int) t_match);
}

void GaussianaAdaptativa::atualizaMedia(int t_valorPixel)
{
    m_media = ( (1 - funcaoRho() ) * m_media) + (funcaoRho() * t_valorPixel);
}

void GaussianaAdaptativa::atualizaDesvioPadrao(int t_valorPixel)
{
    float diferenca = t_valorPixel - m_media;

    m_desvioPadrao = ( (1 - funcaoRho() ) * m_desvioPadrao) +
    (funcaoRho() * diferenca * diferenca);
}
