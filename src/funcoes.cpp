#include "funcoes.hpp"
int TamanhoMensagem = 0;
void AplicacaoTransmissora(void){
    
    std::string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;
    //chama a proxima camada
    CamadaDeAplicacaoTransmissora(mensagem);
}
void CamadaDeAplicacaoTransmissora (string mensagem) {
    TamanhoMensagem = mensagem.length();
    string MensagemBinaria = "";
    //Transforma a mensagem escrita em letras em binario
    for (char& _char : mensagem) {
        MensagemBinaria +=bitset<8>(_char).to_string();
    }
    
    int tamanho = MensagemBinaria.length();
    int Quadro[tamanho];
    
    for (int i = 0 ; i < MensagemBinaria.length(); ++i) {
        Quadro[i] = MensagemBinaria[i];
        
        // ASCII para 0
        if(Quadro[i] == 48)
            Quadro[i] = 0;
        //ASCII para 1
        if(Quadro[i] ==49)
            Quadro[i] = 1;
    }
        CamadaFisicaTransmissora(Quadro);
}

void CamadaFisicaTransmissora(int* quadro){
    int tipoDeCodificacao = 0;
    int* fluxoBrutoDeBits;
    switch (tipoDeCodificacao) {
        case 0 : //codificao binaria 
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1 : //codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2 : //codificacao manchester diferencial
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
            break;
    }
   // MeioDeComunicacao(fluxoBrutoDeBits);
}
void MeioDeComunicacao(int* FluxoBrutoDeBits){
    int* FluxoBrutoDeBitsPontoA;
    int* FluxoBrutoDeBitsPontoB;
    
    //Transferencia de Bits
    for(int i = 0; i < TamanhoMensagem*8;i++){
        FluxoBrutoDeBitsPontoA[i] = FluxoBrutoDeBits[i];
        FluxoBrutoDeBitsPontoB[i] = FluxoBrutoDeBitsPontoB[i];
    }
    CamadaFisicaReceptora(FluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora (int*  quadro) {
	int tipoDeDecodificacao = 0; //alterar de acordo o teste
	int *fluxoBrutoDeBits ; //trabalhando sempre com bits!
	switch (tipoDeDecodificacao) 
	{
		case 0 : //codificao binaria
		fluxoBrutoDeBits = (int *) CamadaFisicaReceptoraCodificacaoBinaria(quadro);    
        break;
		
      case 1 : //codificacao manchester
		//fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
		break;
		
      case 2 : //codificacao manchester diferencial
		//fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadro);
		break;

	}//fim do switch/case
	//chama proxima camada
	//CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

int * CamadaFisicaReceptoraCodificacaoBinaria (int *quadro ) 
{
  



}





int * CamadaFisicaTransmissoraCodificacaoBinaria(int *quadro){
    /*Como a entrada ja esta condizente com a codificação binaria 
    *é retornado exatamente a mesma coisa*/
    return quadro;

}

