#include "Gaussiana.hpp"

const float Gaussiana::M_CONSTANTE_APRENDIZAGEM = 0.2;

// Construtores/Destrutores:
Gaussiana::Gaussiana(float t_media, float t_peso)
    : m_media(t_media), m_peso(t_peso)
{
}

Gaussiana::~Gaussiana()
{
}

// Metodos:

// VALOR DA PARTE 1 ESTA PASSANDO DE 5, UMA FDP PODE CHEGAR EM UM VALOR MAIOR 
// QUE UM? 
float Gaussiana::funcaoDensidadeProbabilidade(int t_valorPixel)
{
    // Dividindo a formula em duas partes por ser extensa.
    float parte1 = 0, parte2 = 0, diferenca = t_valorPixel - m_media;

    parte1 = 1 / (sqrt(2 * M_PI) * m_desvioPadrao);
    parte2 = exp(-0.5 * diferenca * diferenca * (1 / m_desvioPadrao));
    if (parte1 * parte2 >= 1)
    {
        std::cout << "SFOIDOIASFJIOS" << "\n";
    }
    return parte1 * parte2;
}
// A FUNCAO RHO ESTA DANDO VALORES MAIORES QUE 1, O QUE RESULTA EM VALORES 
// NEGATIVOS NA ATUALIZACAO DO DESVIO PADRAO POR CONTA DA FDP.
float Gaussiana::funcaoRho()
{
    float rho = funcaoDensidadeProbabilidade(m_media) *
                M_CONSTANTE_APRENDIZAGEM;
    return rho;
}

void Gaussiana::atualizaPeso(bool t_match)
{
    //Estudar para saber se realmente poderemos usar a formula comentada em
    //qualquer caso.
    //m_peso = m_peso + M_CONSTANTE_APRENDIZAGEM * ( (int) t_match - m_peso);
    m_peso =
        (1 - M_CONSTANTE_APRENDIZAGEM) * m_peso + M_CONSTANTE_APRENDIZAGEM *
                                                      t_match;
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

// O valor 2.5 define o intervalo de media que dita a ocorrencia (ou nao) do
// match.
bool Gaussiana::verificaMatch(int t_valorPixel)
{
    float desvioNecessario = m_desvioPadrao * 2.5;
    return t_valorPixel <= (m_media + desvioNecessario) &&
           t_valorPixel >= (m_media - desvioNecessario);
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