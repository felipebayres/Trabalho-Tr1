#include "funcoes.hpp"
// Tamanho da string
int TamanhoMensagem = 0;
// Tamanho da string em bits
int tamanho = 0,tamanho2 = 0;
void AplicacaoTransmissora(void){
    
    std::string mensagem;
    cout << "Digite uma mensagem:";
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
    tamanho2 = tamanho;
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
    int tipoDeCodificacao = 0;
    int* fluxoBrutoDeBits = new int[tamanho2];
    switch (tipoDeCodificacao) {
        case 0 : //codificao binaria 
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            cout << "Codificacao binaria do quadro:";
            for(int i = 0;i < tamanho2; i++)
                cout << fluxoBrutoDeBits[i];
            cout << "\n";
            break;
        case 1 : //codificacao manchester
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            cout << "Codificacao Manchester do quadro:";
            for(int i = 0;i < tamanho2*2; i++)
                cout << fluxoBrutoDeBits[i];
            cout << "\n";
            break;
        case 2 : //codificacao manchester diferencial
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
            cout << "Codificacao ManchesterDiferencial do quadro:";
            for(int i = 0;i < tamanho2*2; i++)
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
        FluxoBrutoDeBitsPontoA = new int[tamanho2*2];
        FluxoBrutoDeBitsPontoB = new int[tamanho2*2];
        //Transferencia de Bits
        for(int i = 0; i < (tamanho2*2);i++){
            FluxoBrutoDeBitsPontoA[i] = FluxoBrutoDeBits[i];
            //Probabilidade de dar certo
            if ((rand()%100) >= PorcentagemDeErros )
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
        FluxoBrutoDeBitsPontoA = new int[tamanho2];
        FluxoBrutoDeBitsPontoB = new int[tamanho2];
        //Transferencia de Bits
        for(int i = 0; i < tamanho2;i++){
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
	int tipoDeDecodificacao = 0; //alterar de acordo o teste
	int *fluxoBrutoDeBits = new int[tamanho2]; //trabalhando sempre com bits!
	cout <<"Quadro que a CamadaFisicaReceptora recebe:";
    for(int i = 0 ; i < tamanho2 ; i++)
        cout << quadro[i];
    cout << "\n";
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
    for(int i = 0;i < tamanho2; i++)
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
    int *msg_decodificada = (int *) malloc (tamanho2 * 2 * sizeof (int)); // Vetor decodificado tem metade do tamanho do vetor codificado
    for (int i =0 ; i<tamanho2; i++)
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
	int *vet_decodificado = (int *) malloc (tamanho2* sizeof (int)); //vetor codificado tem o dobro do tamanho do quadro
	int i=0,j=0,primeira_vez=0;
	for (j=0; j<(tamanho2*2);){
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
	int *vet_codificado = (int *) malloc (2*tamanho2 * sizeof (int)); // vetor codificado tem o dobro do tamanho do quadro
	int i=0,j=0;

	for (i=0; i<tamanho2*2; i++)
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
	int *vet_codificado = (int *) malloc (2*tamanho2* sizeof (int)); //vetor codificado tem o dobro do tamanho do quadro
	int i=0,j=0,primeira_vez=0;
	for (i=0; i<tamanho2; i++){
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
    
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    //chama proxima camada
    //CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora (Implementada)

void CamadaEnlaceDadosTransmissoraControleDeErro (int* quadro) {
    int tipoDeControleDeErro = 2; //alterar de acordo com o teste
    int* quadrotemporario;
    switch (tipoDeControleDeErro) {
        case 0 : //bit de paridade par
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            CamadaFisicaTransmissora(quadro);
            break;
        case 1 : //bit de paridade impar
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            CamadaFisicaTransmissora(quadro);
            break;
        case 2 : //CRC
            quadrotemporario = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            CamadaFisicaTransmissora(quadrotemporario);
            break;
        case 3 : //codigo de Hamming
            CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
            break;
    }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro


void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (int* quadro){
    int contador_bit1 = 0 , i;
	int bit_paridade = 2; // valor simbolico
	for (i=0 ; i< tamanho; i++) // for que conta a quantidade de bits 1 presentes no quadro
    {
		if(quadro[i] == 1)
			contador_bit1++;
	}

	int *vet_paridade = (int *) malloc ( (tamanho + 1) * sizeof (int)); // quadro codificado com o bit de paridade, ou seja, tamanho = tamanho do quadro + 1 

	if( contador_bit1 % 2 == 0) // é par a quantidade de bits 1?
		bit_paridade = 0;	
	else // se for impar
		bit_paridade = 1;
	
    vet_paridade = quadro; // faz a cópia
    vet_paridade[tamanho] = bit_paridade; // acrescenta o bit de paridade no final
	quadro = vet_paridade;
    cout << "Quadro com o bit de paridade par:";
    for (i = 0; i <= tamanho; i++)
       cout << (quadro[i]) ;
    cout << "\n";
    tamanho = tamanho + 1;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (int* quadro){
    int  i;	
	int bit_paridade=2 , valor_quadro =0 , expoente =0 , base = 2;
   
	for(i = tamanho -1; i>= 0; i--){      
        valor_quadro += quadro[i] *  ( pow(base,expoente) );
        expoente++;
    }
    // if e else que avalia apenas se é par ou impar
    if(valor_quadro % 2 == 0) // valor decimal do quadro é par? coloca 0
        bit_paridade = 1;
    else // se não ,o valor do quadro é impar, logo coloque 1
        bit_paridade = 0;
	
    int *vet_paridade_impar = (int *) malloc ( (tamanho + 1) * sizeof (int)); // quadro codificado com o bit de paridade, ou seja, tamanho = tamanho do quadro + 1 

	vet_paridade_impar = quadro;
   	vet_paridade_impar[tamanho] = bit_paridade; // coloca no bit mais a direita o bit de paridade

   	quadro = vet_paridade_impar; // quadro agora tem o bit de paridade
    cout << "Quadro formado com o bit de paridade impar:";
   	for (i = 0; i <= tamanho; i++)
        cout << quadro[i];
   cout << "\n";
   tamanho = tamanho + 1;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (int* quadro){
    int TamanhoHamming;
    
    //Calcula o tamanho do codigo de hamming
    for (int i = 0; ;++i)
    {
        if (pow(2, i) >= (tamanho + i + 1)){
            TamanhoHamming = tamanho + i;
            break;
         }
    }

    int QuadroHamming[TamanhoHamming];
    int k = TamanhoHamming - tamanho;
    
    //Inicializar o vetor com valores diferentes de 1 e 0
    for (int i = 0; i < TamanhoHamming ; i++)
        QuadroHamming[i] = 2;
    
    
    // Essa parte coloca cada bit do quadro no lugar correto do novo quadro. Mas sem calcular os coeficientes
    for (int position = 0, expoente = 0,i = 0; i < tamanho; ++position){
        if (pow (2, expoente) == (position + 1))
        {
            ++expoente;
            continue;
        }
        QuadroHamming[position] = quadro[i];
        i++;
    }
    
    /*
    cout << endl;
    cout << "QuadroHamming sem os coeficientes:";
    for (int i = 0 ; i < TamanhoHamming ; i++)
        cout << QuadroHamming[i];
    */
   
    // Calcula os coeficientes do quadro 
    bitset<10> bits;
    for (int expoente = 0; expoente < k; ++expoente)
    {
        int PosicaoCoeficiente = 0;
        int ContagemDe1 = 0;
        for (size_t c = 1; c <= TamanhoHamming; ++c)
        {
                bits = c;
                if (bits.test(expoente)) // expoente from 0 to 3
                {
                    if (QuadroHamming[c - 1] == 2)
                        PosicaoCoeficiente = c - 1;
                    else if (QuadroHamming[c - 1] == 0)
                        ++ContagemDe1;
                }
        }   
        if (ContagemDe1 % 2 != 0)
            QuadroHamming[PosicaoCoeficiente] = 1;
        else
            QuadroHamming[PosicaoCoeficiente] = 0;
    }
    cout << "QuadroHamming : ";
    for (int i = 0 ; i < TamanhoHamming ; i++){
        cout << QuadroHamming[i];
        quadro[i] = QuadroHamming[i];
    }
    tamanho = TamanhoHamming;
    cout << "\n";    
}  //implementacao do algoritmo
   //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming
int* CamadaEnlaceDadosTransmissoraControleDeErroCRC (int* quadro){
     //implementacao do algoritmo
    //usar polinomio CRC-32(IEEE 802)
    int *polinomiocrc = new int[33];
    int *restoenvio = new int[32];
    polinomiocrc[0] = 1; polinomiocrc[6] = 1; polinomiocrc[9] = 1;
    polinomiocrc[10] = 1;
    polinomiocrc[16] = 1; polinomiocrc[20] = 1; polinomiocrc[21] = 1;
    polinomiocrc[22] = 1;
    polinomiocrc[24] = 1; polinomiocrc[25] = 1; polinomiocrc[27] = 1;
    polinomiocrc[28] = 1;
    polinomiocrc[30] = 1; polinomiocrc[31] = 1; polinomiocrc[32] = 1;

    int *vetorenvioCRC = new int[tamanho+32];
    for( int i=0; i<tamanho; i++)
        vetorenvioCRC[i] = quadro[i];
    // print do vetor com os 32 bits zero adicionados
    cout << "Quadro recebido e adicionados os 32 0's para a operacao CRC: ";
    for (int i=0; i<tamanho+32; i++)
        cout << vetorenvioCRC[i];
    cout <<"\n";
    // fim print

    // o CRC utiliza a operacao OU(exclusivo) para realizar a divisao, assim:
    for(int i=0; i<33; i++) {
        for(int j=0; j<33; j++) {
            if ( vetorenvioCRC[j+i] == polinomiocrc[j] ) // se os bits forem 11 ou 00
                vetorenvioCRC[j+i] = 0;
            else
                //  caso onde os bits sao 10 ou 01
                vetorenvioCRC[j+i] = 1;
        }
    }
    // separa os 32 bits que devem ser adicionados a mensagem enviada
    for (int i=0; i<32; i++)
        restoenvio[i] = vetorenvioCRC[tamanho+i];

    // adiciona a mensagem aos novos 32 bits
    for( int i=0; i<tamanho; i++)
        vetorenvioCRC[i] = quadro[i];
    for (int i=0; i<32; i++)
        vetorenvioCRC[tamanho+i] = restoenvio[i];

    //
    cout<< "Mensagem após a codificacao crc: ";
    for (int i=0; i<tamanho+32; i++)
        cout << vetorenvioCRC[i];
    cout <<"\n";
    // *****************
    // falta retornar o quadro
    tamanho2 = tamanho2 + 32;
    return vetorenvioCRC;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC



// Parte da recepcao 



void CamadaEnlaceDadosReceptora (int* quadro) {
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    //chama proxima camada
    CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

void CamadaEnlaceDadosReceptoraEnquadramento (int* quadro) {
    //algum codigo aqui
}//fim do metodo CamadaEnlaceDadosReceptoraEnquadramento
void CamadaEnlaceDadosReceptoraControleDeErro (int* quadro) {
    int tipoDeControleDeErro = 2; //alterar de acordo com o teste
    switch (tipoDeControleDeErro) {
        case 0 : //bit de paridade par
           CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
            break;
        case 1 : //bit de paridade impar
            CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(quadro);
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
    // camada receptora retira o bit de paridade do quadro
    int ocorreu_erro = 0 , contador_bit1=0 , i;
    int *vet_decodificado = (int *) malloc ( tamanho * sizeof (int)); // quadro decodificado SEM o bit de paridade, ou seja, tamanho = tamanho do quadro
    for (i =0; i< tamanho; i++){
        vet_decodificado[i] = quadro[i];
   		if(quadro[i] == 1)
   			contador_bit1++;
    }
   
   
   // Primeiro comparacao, analise se o bit de paridade for =0 e a quantidades de bits 1 é impar, se for, ocorreu erro
   //Segunda comparacao, verifica se o bit de paridade é 1 e se a quantidades de bits 1 é par, se for, houve erro tambem
   //Lembrando que esse metodo, não é possível detectar qual o bit que ocorreu o erro
   if( ( quadro[tamanho] == 0 && (contador_bit1 % 2 != 0) )  || ( quadro[tamanho] == 1 && (contador_bit1 % 2 == 0) ) )
   {
   		ocorreu_erro=1;
   		cout << "Ocorreu erro pelo metodo Paridade PAR!\n";
   }

   quadro = vet_decodificado; // quadro original, sem o bit de paridade

   for (i = 0; i < tamanho; i++)
      cout << quadro[i];
   cout << "\n";
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar (int * quadro) {
    // quadro representa o quadro codificado com paridade [tamanho +1]
    int ocorreu_erro = 0, valor_quadro = 0 ,base = 2 , expoente = 0 , i;
      
    int *vet_decodificado = (int *) malloc ( tamanho * sizeof (int)); // quadro decodificado SEM o bit de paridade, ou seja, tamanho = tamanho do quadro
    for(i = tamanho -1; i>= 0; i--){      
        valor_quadro += quadro[i] *  ( pow(base,expoente) );
        expoente++;
    }
   for (i =0; i< tamanho; i++)
        vet_decodificado[i] = quadro[i];

   
    // vet_paridade_impar[tamanho+1] = 0;
    // Primeiro comparacao, analise se o bit de paridade for =0 e valor decimal do quadro é impar, se for, ocorreu erro
    //Segunda comparacao, verifica se o bit de paridade é 1 e se a valor decial do quadro é par, se for, houve erro tambem
    //Lembrando que esse metodo, não é possível detectar qual o bit que ocorreu o erro
   if( ( quadro[tamanho] == 0 && (valor_quadro % 2 != 0) )  || ( quadro[tamanho] == 1 && (valor_quadro % 2 == 0) ) ){
   		ocorreu_erro=1;
   		cout << "Ocorreu erro pelo metodo Paridade IMPAR!\n";
   }
   quadro = vet_decodificado;

   for (i = 0; i < tamanho; i++)
        cout << quadro[i];
   cout << "\n";

}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar
void CamadaEnlaceDadosReceptoraControleDeErroCRC (int * quadro) {
   //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
    //usar polinomio CRC-32(IEEE 802)
    int *polinomiocrc = new int[33];
    int *restoenvio = new int[32];
    polinomiocrc[0] = 1; polinomiocrc[6] = 1; polinomiocrc[9] = 1;
    polinomiocrc[10] = 1;
    polinomiocrc[16] = 1; polinomiocrc[20] = 1; polinomiocrc[21] = 1;
    polinomiocrc[22] = 1;
    polinomiocrc[24] = 1; polinomiocrc[25] = 1; polinomiocrc[27] = 1;
    polinomiocrc[28] = 1;
    polinomiocrc[30] = 1; polinomiocrc[31] = 1; polinomiocrc[32] = 1;
    int *vetorenvioCRC = new int[tamanho+32];
    for( int i=0; i<tamanho; i++)
        vetorenvioCRC[i] = quadro[i];
    // o CRC utiliza a operacao OU(exclusivo) para realizar a divisao, assim:
    for(int i=0; i<33; i++) {
        for(int j=0; j<33; j++) {
            if ( quadro[j+i] == polinomiocrc[j] ) // se os bits forem 11 ou 00
                quadro[j+i] = 0;
            else
                //  caso onde os bits sao 10 ou 01
                quadro[j+i] = 1;
        }
    }
    // verificar se houve erro, caso uma das 32 posicoes finais do vetor nao seja 0, houve erro
    for(int j = 0; j<32; j++) {
        if ( quadro[tamanho+j] != 0 ) {
            cout << "Erro detectado na transmissao da mensagem!\n";
            break;
        }
    }
    cout << "Quadro apos a divisao pelo polinomio do CRC: ";
    for (int i=0; i<tamanho+32; i++)
        cout << quadro[i];
    cout <<"\n";
    for( int i=0; i<tamanho; i++)
        quadro[i] = vetorenvioCRC[i];
    return;
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (int * quadro) {
    bitset<10> output (0);
    bitset<10> bits (0);
    size_t hammingcodesize = tamanho;
    int i, TamanhoQuadroOriginal;
    // Calcular o tamanho do quadro original
    
    for (i = 0; pow(2, i) < hammingcodesize; ++i)
        ;
    TamanhoQuadroOriginal = tamanho - i;
    
    size_t k = tamanho - TamanhoQuadroOriginal;
    bool Erro = false;
    for (size_t c = 0; c < k; ++c)
    {
        int countof1s = 0;
        for (size_t index = 1; index <= tamanho; ++index)
        {
            bits = index;
            if (bits.test(c))
            {
                if (quadro[index - 1] == 1)
                    ++countof1s;
            }
        }
        if (countof1s % 2 != 0)
        {
            Erro = true;
        }
    }
    if (Erro)
        cout << "Houve um erro no codigo de Hamming\n";
    int expoente = 0,j=0;
    
    cout << "Quadro da camada de enlace:";
    for (int i = 1;i <= tamanho ; i++){
        if(i == pow(2,expoente)){
            expoente++;
        }
        else{
            quadro[j] = quadro[i-1];
            cout << quadro[j];
            j++;
        }
    }
    cout << "\n";
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming