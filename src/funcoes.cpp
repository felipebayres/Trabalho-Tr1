#include "funcoes.hpp"

void AplicacaoTransmissora(void){
    
    std::string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;
    //chama a proxima camada
    CamadaDeAplicacaoTransmissora(mensagem);
}
void CamadaDeAplicacaoTransmissora (string mensagem) {
    
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
        CamadaFisicaTransmissora(Quadro);
    }
}

void CamadaFisicaTransmissora(int* quadro){
    int tipoDeCodificacao = 0;
    int* fluxoBrutoDeBits; 
    switch (tipoDeCodificacao) {
        case 0 : //codificao binaria 
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1 : //codificacao manchester
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2 : //codificacao manchester diferencial
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
            break;
    }
   // MeioDeComunicacao(fluxoBrutoDeBits);
}

void CamadaFisicaReceptora (int*  quadro) 
{
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

int * CamadaFisicaTransmissoraCodificacaoBinaria(int *quadro){
    /*Como a entrada ja esta condizente com a codificação binaria 
    *é retornado exatamente a mesma coisa*/
    return quadro;

}

int * CamadaFisicaReceptoraCodificacaoBinaria (int *quadro ) 
{
	 
   int quantidade = sizeof(quadro)/sizeof(int); // pega tamanho do vetor 
   //printf("quantidade %d\n",quantidade );
   int i =0;
   int aux,j=0;
   int bytes = 7;
 
 	int *vetor_decodificado = (int *) malloc (quantidade * sizeof(int)) ; // aloca a quantidade de elementos(base decimal) do vetor

    //Para converter de binario para decimal, basta decimal = bit7 * 2ˆ7 + bit6 * 2ˆ6 +... + bit0 * 2ˆ0
   int base = 2,expoente = 0;
   for(i = 0; i<quantidade; i++)
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
      vetor_decodificado[aux] = uint16_t(vetor_decodificado[aux]);

   
   return vetor_decodificado;
}