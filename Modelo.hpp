#include <iostream>
#include <list>
#include "Pixel.hpp"
#include "opencv2/opencv.hpp"

#ifndef __MODELO_H
#define __MODELO_H

class Modelo
{
private:
    cv::VideoCapture m_entrada;
    std::list<Pixel*> m_frames_modelo;

public:

    // Recebe o caminho completo, junto com nome e extensão do video de entrada.
    //
    // Exemplos:
    //      new Modelo("teste.mts");
    //      Modelo mod2("../Videos/entrada.mp4");
    Modelo(std::string caminho_entrada);
    virtual ~Modelo();

    // Usada internamente em executa() por questoes de reaproveitamento de 
    // código. Cria um video de saida utilizando um cv::VideoWriter, recebendo 
    // seu nome, sua extensao e por padrão ".avi".
    //
    // Exemplo:
    //      abre_saida(saida1, diretorio, "saida");
    //      abre_saida(saida2, "../Videos/" "saida2");
    void abre_saida(cv::VideoWriter &saida, std::string caminho,
    std::string nome);

    // Instancia uma quantidade de objetos Pixel referente ao produto entre a 
    // altura do video recebido de entrada pela sua largura, sao armazenadas na
    // std::list m_frames_modelo.
    // Para a criação da lista, e lido um frame da entrada.
    void inicia_gaussianas();

    // Faz as operações para gerar os frames (um de cada a cada chamada do 
    // metodo) das duas saidas do modelo. Recebe cv::Mat do frame a ser 
    // processado e os objetos cv::VideoWriter das respectivas saidas.
    void gera_frames_saida(cv::Mat &frame, cv::VideoWriter &saida1,
        cv::VideoWriter &saida2);

    // Alimenta as gaussinas do modelo com o frame recebido de parametro para 
    // atualizar seus valores.
    void le_novo_pixel(cv::Mat &frame);

    // Controla a repeticao que le um novo frame da entrada, gera os frames de 
    // saida a partir do modelo e atualiza o modelo com estes novos dados.
    // Recebe como parametro o diretorio onde serao criados os dois videos de 
    // saida, "saida1.avi" e "saida2.avi".
    //
    // Exemplo:
    //      modelo1.executa("../UTFPR/ModeloGaussianas/");
    void executa(std::string diretorio);
};

#endif