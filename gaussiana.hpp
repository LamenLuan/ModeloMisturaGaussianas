#ifndef GAUSS_H
#define GAUSS_H

#include <cmath>
/** documentação
 *
 */
#define constanteAprendizagem 2.0
#define dimensionalidade 100

class GaussianaAdaptativa
{
private:
	const int dimensionalidade=100;
    float m_media{0.0};
    float m_desvioPadrao{0.5};
    float m_peso{0};
public:
    //Construtores/Destrutores:
    GaussianaAdaptativa(float t_media=0.0, float t_peso=0);
    ~GaussianaAdaptativa();

    //Getters:
    float getMedia();
    float getDesvioPadrao();
    float getPeso();

    //Setters:
    void setMedia(float t_media);
    void setDesvioPadrao(float t_desvioPadrao);
    void setPeso(float t_peso);

    //Metodos:
    float funcaoDensidadeProbabilidade(int t_valorPixel);
    float funcaoRho();
    void atualizaPeso(bool t_match);
    void atualizaMedia(int t_valorPixel);
    void atualizaDesvioPadrao(int t_valorPixel);
};

inline float GaussianaAdaptativa::funcaoDensidadeProbabilidade(
		int t_valorPixel) {
}

#endif
