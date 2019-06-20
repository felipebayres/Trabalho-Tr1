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
    cout << "Quadro formado pela CamadaDeAplicaçãoTransmissora:";
    for (int i = 0 ; i < MensagemBinaria.length(); i++) {
        Quadro[i] = MensagemBinaria[i];
        cout<<MensagemBinaria[i];
        // ASCII para 0
        if(Quadro[i] == 48)
            Quadro[i] = 0;
        //ASCII para 1
        if(Quadro[i] ==49)
            Quadro[i] = 1;
    }
    printf("\n");
    CamadaEnlaceDadosTransmissora(Quadro);
}

void CamadaFisicaTransmissora(int* quadro){
    int tipoDeCodificacao = 2;
    int* fluxoBrutoDeBits = new int[tamanho];
    switch (tipoDeCodificacao) {
        case 0 : //codificao binaria 
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            cout << "Codificacao binaria do quadro:";
            for(int i = 0;i < tamanho; i++)
                cout << fluxoBrutoDeBits[i];
            cout << "\n";
            break;
        case 1 : //codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            cout << "Codificacao Manchester do quadro:";
            for(int i = 0;i < tamanho*2; i++)
                cout << fluxoBrutoDeBits[i];
            cout << "\n";
            break;
        case 2 : //codificacao manchester diferencial
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
            cout << "Codificacao ManchesterDiferencial do quadro:";
            for(int i = 0;i < tamanho*2; i++)
                cout << fluxoBrutoDeBits[i];
            cout << "\n";
            break;
    }
    MeioDeComunicacao(fluxoBrutoDeBits,tipoDeCodificacao);
}
void MeioDeComunicacao(int* FluxoBrutoDeBits,int tipoDeCodificacao){
    int* FluxoBrutoDeBitsPontoA;
    int* FluxoBrutoDeBitsPontoB;
    int erro, PorcentagemDeErros;
    PorcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%
    
    if(tipoDeCodificacao==1 || tipoDeCodificacao==2){
        FluxoBrutoDeBitsPontoA = new int[tamanho*2];
        FluxoBrutoDeBitsPontoB = new int[tamanho*2];
        //Transferencia de Bits
        for(int i = 0; i < (tamanho*2);i++){
            FluxoBrutoDeBitsPontoA[i] = FluxoBrutoDeBits[i];
            //Probabilidade de dar certo
            if ((rand()%100) > PorcentagemDeErros )
                FluxoBrutoDeBitsPontoB[i] = FluxoBrutoDeBitsPontoA[i];
                
            //Probabilidade de dar errado
            else{
                if ( FluxoBrutoDeBitsPontoA[i] == 1)
                    FluxoBrutoDeBitsPontoB[i] = 0;
                else if ( FluxoBrutoDeBitsPontoA[i] == 0)
                    FluxoBrutoDeBitsPontoB[i] = 1;
            }  
        }
    }
    else{
        FluxoBrutoDeBitsPontoA = new int[tamanho];
        FluxoBrutoDeBitsPontoB = new int[tamanho];
        //Transferencia de Bits
        for(int i = 0; i < tamanho;i++){
            FluxoBrutoDeBitsPontoA[i] = FluxoBrutoDeBits[i];
            if ((rand()%100) > PorcentagemDeErros )
                FluxoBrutoDeBitsPontoB[i] = FluxoBrutoDeBitsPontoA[i];
                //Probabilidade de dar certo
            else{
                if ( FluxoBrutoDeBitsPontoA[i] == 1)
                    FluxoBrutoDeBitsPontoB[i] = 0;
                else if ( FluxoBrutoDeBitsPontoA[i] == 0)
                    FluxoBrutoDeBitsPontoB[i] = 1;
            }  
        }
    }
    CamadaFisicaReceptora(FluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora (int*  quadro) {
	int tipoDeDecodificacao = 2; //alterar de acordo o teste
	int *fluxoBrutoDeBits = new int[tamanho]; //trabalhando sempre com bits!
	switch (tipoDeDecodificacao) {
		case 0 : //codificao binaria
		fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);    
        break;
		
      case 1 : //codificacao manchester
		fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
		break;
		
      case 2 : //codificacao manchester diferencial
		fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchesterDiferencial(quadro);
		break;

	}//fim do switch/case
	cout << "FluxoDeBits depois da decodificação:";
    for(int i = 0;i < tamanho; i++)
        cout << fluxoBrutoDeBits[i];
    cout << "\n";
    //chama proxima camada
	CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

void CamadaDeAplicacaoReceptora(int *quadro){ 
   int quantidade = tamanho; // pega tamanho do vetor 
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
int * CamadaFisicaReceptoraCodificacaoManchester(int *quadro){
    // Decodificação  manchester 
    int Clock0=0,Clock1 = 1;
    int j=0;
    int *msg_decodificada = (int *) malloc (tamanho * 2 * sizeof (int)); // Vetor decodificado tem metade do tamanho do vetor codificado
    for (int i =0 ; i<tamanho; i++)
    {
    	if ( quadro[j] == Clock0 && quadro[j+1] ==Clock1) // se for "01" na codificao manchester significa que o BIT = 0, usa os valores do clock para sincronizar
    		msg_decodificada[i] = 0;

    	else if (quadro[j] == Clock1 && quadro[j+1] ==Clock0)// se for "10" na codificao manchester significa que o BIT = 1
    		msg_decodificada[i] = 1;

    	j+=2;
    }
    return msg_decodificada;
}
int * CamadaFisicaReceptoraCodificacaoManchesterDiferencial(int *quadro){
    //int Clock = 1; // considerando clock = 01
	int *vet_decodificado = (int *) malloc (tamanho* sizeof (int)); //vetor codificado tem o dobro do tamanho do quadro
	int i=0,j=0,primeira_vez=0;
	for (j=0; j<(tamanho*2);){
        if(primeira_vez==0){
            if (quadro[j]==0){ // clock começa como 01
			    vet_decodificado[i] = 1;
		    }
		    else if (quadro[j]==1){ // clock começa como 01
			    vet_decodificado[i] = 0;	
		    }
        }else if(primeira_vez==1){
            if (quadro[j-1]==quadro[j]){ // se o bit é 0 inverte
			    vet_decodificado[i] = 1;
		    }
		    else if (quadro[j-1]!=quadro[j]){ //se o bit é 1 não inverte
			    vet_decodificado[i] = 0;
		    }
        }
		j+=2;
        i+=1;
        primeira_vez=1;	
	}
    //printf("Mensagem recebida:");
	return vet_decodificado;
}
int * CamadaFisicaTransmissoraCodificacaoBinaria(int *quadro){
    /*Como a entrada ja esta condizente com a codificação binaria 
    *é retornado exatamente a mesma coisa*/
    return quadro;

}
int * CamadaFisicaTransmissoraCodificacaoManchester(int *quadro){
   int Clock0=0,Clock1 = 1; // considerando clocks = 01
	int *vet_codificado = (int *) malloc (2*tamanho * sizeof (int)); // vetor codificado tem o dobro do tamanho do quadro
	int i=0,j=0;

	for (i=0; i<tamanho*2; i++)
	{
		if ( ( Clock0 ^ quadro[i] ) == 0  &&  (Clock1 ^ quadro[i] ) == 1 ) // xor == 0 && xor == 1? codifica manchester como "01"
		{
			vet_codificado[j] =  0; 
			vet_codificado[j+1] =  1;
		}
		else if (   (Clock0 ^ quadro[i] ) == 1   &&   (Clock1 ^ quadro[i] ) == 0  )  // xor == 1 && xor == 0??  significa que é bit = 1  no quadro,logo vira "10" no Manchester por conta do clock
		{
			vet_codificado[j] = 1;
			vet_codificado[j+1] = 0;	
		}
		j+=2;	
	}
	return vet_codificado;
}
int * CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int *quadro){
    //int Clock = 1; // considerando clock = 01
	int *vet_codificado = (int *) malloc (2*tamanho* sizeof (int)); //vetor codificado tem o dobro do tamanho do quadro
	int i=0,j=0,primeira_vez=0;
	for (i=0; i<tamanho; i++){
        if(primeira_vez==0){
            if (quadro[i]==0){ // clock começa como 01
			    vet_codificado[j] = 1; 
			    vet_codificado[j+1] = 0;
		    }
		    else if (quadro[i]==1){ // clock começa como 01
			    vet_codificado[j] = 0;
			    vet_codificado[j+1] = 1;	
		    }
        }else if(primeira_vez==1){
            if (quadro[i]==0){ // se o bit é 0 inverte
			    vet_codificado[j] = !(vet_codificado[j-1]); 
			    vet_codificado[j+1] =  !(vet_codificado[j]);
		    }
		    else if (quadro[i]==1){ //se o bit é 1 não inverte
			    vet_codificado[j] = vet_codificado[j-1];
			    vet_codificado[j+1] = !(vet_codificado[j]);	
		    }
        }
		j+=2;
        primeira_vez=1;	
	}
	return vet_codificado;
}



//Trabalho 2

void CamadaEnlaceDadosTransmissora (int* quadro) {
    
    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    CamadaEnlaceDadosTransmissoraControleDeFluxo(quadro);
    //chama proxima camada
    CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora (Implementada)

void CamadaEnlaceDadosTransmissoraControleDeErro (int* quadro) {
    int tipoDeControleDeErro = 0; //alterar de acordo com o teste
    switch (tipoDeControleDeErro) {
        case 0 : //bit de paridade par
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1 : //bit de paridade impar
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2 : //CRC
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
        case 3 : //codigo de Hamming
            CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
            break;
    }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (int* quadro){
    //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (int* quadro){
    //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (int* quadro){
    //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming

void CamadaEnlaceDadosTransmissoraControleDeErroCRC (int* quadro){
    //implementacao do algoritmo
    //usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC



// Parte da recepcao 



void CamadaEnlaceDadosReceptora (int* quadro) {
    CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    CamadaEnlaceDadosReceptoraControleDeFluxo(quadro);
    //chama proxima camada
    CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

void CamadaEnlaceDadosReceptoraEnquadramento (int* quadro) {
    //algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento
void CamadaEnlaceDadosReceptoraControleDeErro (int* quadro) {
    int tipoDeControleDeErro = 0; //alterar de acordo com o teste
    switch (tipoDeControleDeErro) {
        case 0 : //bit de paridade par
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
            break;
        case 1 : //bit de paridade impar
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2 : //CRC
            CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
            break;
        case 3 : //codigo de hamming
            CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
            break;
    }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErro
void CamadaEnlaceDadosReceptoraControleDeFluxo (int* quadro) {
    //algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeFluxo

void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (int * quadro) {
    //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar (int * quadro) {
    //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar
void CamadaEnlaceDadosReceptoraControleDeErroCRC (int * quadro) {
    //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
    //usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (int * quadro) {
    //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming