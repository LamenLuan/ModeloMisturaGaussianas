#include "Pixel.hpp"

Pixel::Pixel(int t_valorPixel)
{
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
        m_mistura[i] = new Gaussiana(t_valorPixel, (float) 1 / 
            M_QUANTIDADE_DISTRIBUICOES);
}

Pixel::~Pixel()
{
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
        delete m_mistura[i];
}

// Probabilidade total do pixel vai ser a soma da funcao densidade
// probabilidade de cada gaussiana da mistura multiplicado por seu peso 
// especifico.
float Pixel::probabilidadeDoPixel(int t_valorPixel)
{
    float probabilidade = 0;
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
        probabilidade += 
            m_mistura[i]->funcaoDensidadeProbabilidade(t_valorPixel) *
            m_mistura[i]->getPeso();
    return probabilidade;
}

void Pixel::leNovoPixel(int t_valorPixel)
{
    bool matche = false;
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
    {
        if(m_mistura[i]->verificaMatch(t_valorPixel))
        {
            m_mistura[i]->atualizaMedia(t_valorPixel);
            m_mistura[i]->atualizaDesvioPadrao(t_valorPixel);
            matche = true;
            break;
        }
    }
    // Os parametro de DesvioPadrão e Peso foram atualizados com base nos 
    // proprios valores do pixel.
    if(!matche)
    {
        m_mistura[M_QUANTIDADE_DISTRIBUICOES - 1]->setMedia(t_valorPixel);
        m_mistura[M_QUANTIDADE_DISTRIBUICOES - 1]->setDesvioPadrao
            (m_mistura[M_QUANTIDADE_DISTRIBUICOES-1]->getDesvioPadrao()*10);
        m_mistura[M_QUANTIDADE_DISTRIBUICOES - 1]->setPeso
            (m_mistura[M_QUANTIDADE_DISTRIBUICOES - 1]->getPeso()/10);
    }
}

void Pixel::renormalizaGaussiana(void)
{
    // O valor SomatorioPesos(max) está baseado na soma de todos os pesos.
    // O valor min será sempre zero.
    float SomatorioPesos = 0;
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)
        SomatorioPesos += m_mistura[i]->getPeso();
    
    for (size_t i = 0; i < M_QUANTIDADE_DISTRIBUICOES; i++)        
        m_mistura[i]->setPeso(m_mistura[i]->getPeso()/SomatorioPesos);
}