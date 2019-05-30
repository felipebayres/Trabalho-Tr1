#ifndef FUNCOES_HPP_
#define FUNCOES_HPP_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <bitset>
#include <stdint.h>
#include <vector>
using namespace std;

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string);
void CamadaFisicaTransmissora(int*);
void MeioDeComunicacao(int*);

int* CamadaFisicaTransmissoraCodificacaoBinaria (int*);
int* CamadaFisicaTransmissoraCodificacaoManchester (int*);
int* CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int*);

void CamadaFisicaReceptora (int);
int CamadaFisicaReceptoraCodificacaoBinaria (int); 
int CamadaFisicaReceptoraCodificacaoManchester (int);
int CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int);

void CamadaDeAplicacaoReceptora (int);
void AplicacaoReceptora (string );


#endif