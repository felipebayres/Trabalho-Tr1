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
#include <math.h>

using namespace std;
//Funcoes implementadas
void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string);
void CamadaFisicaTransmissora(uint8_t *);

uint8_t* CamadaFisicaTransmissoraCodificacaoBinaria (uint8_t*);

void CamadaFisicaReceptora (int*);
int* CamadaFisicaReceptoraCodificacaoBinaria (int *); 

// ----------------------------------------------------

void MeioDeComunicacao(int*);


int* CamadaFisicaTransmissoraCodificacaoManchester (int*);
int* CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int*);


int* CamadaFisicaReceptoraCodificacaoManchester (int*);
int* CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int*);

void CamadaDeAplicacaoReceptora (int*);
void AplicacaoReceptora (string);


#endif
