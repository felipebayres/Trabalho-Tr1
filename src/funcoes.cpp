#include "funcoes.hpp"
int TamanhoMensagem = 0;
int tamanho = 0;
void AplicacaoTransmissora(void){
    
    std::string mensagem;
    cout << "Digite uma mensagem:" << endl;
    std::getline(std::cin, mensagem);
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
    
    tamanho = MensagemBinaria.length();
    int Quadro[tamanho];
    
    for (int i = 0 ; i < MensagemBinaria.length(); i++) {
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
    int* fluxoBrutoDeBits = new int[tamanho];
    switch (tipoDeCodificacao) {
        case 0 : //codificao binaria 
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1 : //codificacao manchester
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2 : //codificacao manchester diferencial
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
            break;
    }
    MeioDeComunicacao(fluxoBrutoDeBits);
}
void MeioDeComunicacao(int* FluxoBrutoDeBits){
    int* FluxoBrutoDeBitsPontoA = new int[tamanho];
    int* FluxoBrutoDeBitsPontoB = new int[tamanho];
    
    //Transferencia de Bits
    for(int i = 0; i < tamanho;i++){
        FluxoBrutoDeBitsPontoA[i] = FluxoBrutoDeBits[i];
        FluxoBrutoDeBitsPontoB[i] = FluxoBrutoDeBitsPontoA[i];
    }
    CamadaFisicaReceptora(FluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora (int*  quadro) {
	int tipoDeDecodificacao = 0; //alterar de acordo o teste
	int *fluxoBrutoDeBits = new int[tamanho]; //trabalhando sempre com bits!
	switch (tipoDeDecodificacao) 
	{
		case 0 : //codificao binaria
		fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);    
        break;
		
      case 1 : //codificacao manchester
		//fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
		break;
		
      case 2 : //codificacao manchester diferencial
		//fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadro);
		break;

	}//fim do switch/case
	//chama proxima camada
	CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

void CamadaDeAplicacaoReceptora(int *quadro){ 
   int quantidade = tamanho; // pega tamanho do vetor 
   //printf("quantidade %d\n",quantidade );
   int i =0;
   int aux,j=0;
   int bytes = 7;
 
 	int *vetor_decodificado = (int *) malloc (quantidade * sizeof(int)) ; // aloca a quantidade de elementos(base decimal) do vetor
    //Para converter de binario para decimal, basta decimal = bit7 * 2ˆ7 + bit6 * 2ˆ6 +... + bit0 * 2ˆ0
   int base = 2,expoente = 0;
   for(i = 0; i<quantidade/8; i++)
   {
      expoente = 0;
      for (aux = bytes; aux >= 8*j ; aux--) // aux começa em bytes = 7, pois a conversao começa do bit menos significativo pro mais significativo.
      {
         vetor_decodificado[i] += quadro[aux] * pow(base,expoente); // conversao do binario para decimal
         expoente++;
      }
      j++;
      bytes += 8;
      
   }
   
   for (aux = 0; aux < quantidade; aux++) // for que serve apenas pra garantir que o valor armazenado seja o valor correto , usando o casting
      vetor_decodificado[aux] = uint8_t(vetor_decodificado[aux]);
    
    std::stringstream ss;
    for(int i = 0; i < quantidade; i++){
    ss << (char) vetor_decodificado[i];
    }
    std::string mensagem = ss.str();
    AplicacaoReceptora(mensagem);
    }//fim do metodoCamadaDeAplicacaoReceptora








void AplicacaoReceptora(string mensagem) {
    cout << "Mensagem recebida: ";
    cout <<mensagem ;
    cout << endl;
}//fim do metodoAplicacaoReceptora


int * CamadaFisicaReceptoraCodificacaoBinaria (int *quadro ) {
  return quadro;
}

int * CamadaFisicaTransmissoraCodificacaoBinaria(int *quadro){
    /*Como a entrada ja esta condizente com a codificação binaria 
    *é retornado exatamente a mesma coisa*/
    return quadro;

}

