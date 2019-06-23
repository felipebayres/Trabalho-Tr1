#ifndef FUNCOES_HPP_
#define FUNCOES_HPP_
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <bitset>
#include <stdint.h>
#include <vector>
#include <math.h>
using namespace std;

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string);
void CamadaFisicaTransmissora(int*);

int* CamadaFisicaTransmissoraCodificacaoBinaria (int*);

void CamadaFisicaReceptora (int*);
int* CamadaFisicaReceptoraCodificacaoBinaria (int*); 
void MeioDeComunicacao(int*,int);


int* CamadaFisicaTransmissoraCodificacaoManchester (int*);
int* CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int*);


int* CamadaFisicaReceptoraCodificacaoManchester (int*);
int* CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int*);

void CamadaDeAplicacaoReceptora (int*);
void AplicacaoReceptora (string);

//Trabalho 2 
// Camada transmissao
void CamadaEnlaceDadosTransmissora(int*); // Implementada
void CamadaEnlaceDadosTransmissoraEnquadramento(int*);
void CamadaEnlaceDadosTransmissoraControleDeErro(int*); // Implementada
void CamadaEnlaceDadosTransmissoraControleDeFluxo(int*);

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int*);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int*);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int*);
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(int*); // Implementada

//Camada receptora
void CamadaEnlaceDadosReceptora(int*); //Implementada
void CamadaEnlaceDadosReceptoraEnquadramento (int*);
void CamadaEnlaceDadosReceptoraControleDeErro(int*); //Implementada
void CamadaEnlaceDadosReceptoraControleDeFluxo (int*);

void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(int*);
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(int*);
void CamadaEnlaceDadosReceptoraControleDeErroCRC(int*);
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(int*);

#endif