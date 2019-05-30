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
        else
            Quadro[i] = 1;
        cout << Quadro[i] << " "; 

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
    }//fim do switch/case
   // MeioDeComunicacao(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora
