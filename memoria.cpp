#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <bitset>
#include <bits/stdc++.h> 
#include <deque>

#define N_BLOCOS_CACHE 64
#define TAMANHO_WORD 32
#define TAMANHO_OFFSET 4
#define TAMANHO_INDICE 6
#define TAMANHO_TAG 22

/*A memoria de dados nao foi, de fato, implementada, ja que nao ha necessidade
de apresentar os dados lidos. Os dados na cache tambem foram omitidos, ficando
representados apenas o indice, a tag e o bit de validade.
Leituras e escritas na cache e na memoria sao representadas por funcoes que simulam
esses processamentos.*/

/**
* -Descricao: struct que representa uma palavra da memoria cache
* -Entrada: N/A
* -Saida: N/A
*/
typedef struct Bloco{
    int tag;
    bool valido;
    bool sujo;
}Bloco;


/**
* -Descricao: converte numero decimal para binario
* -Entrada: enderecoDecimal
* -Saida: enderecoBinario
*/
std::bitset<TAMANHO_WORD> converteDecimalBinario(int enderecoDecimal){
    std::string aux;

    while (enderecoDecimal != 0){
        aux += (enderecoDecimal % 2 == 0 ? "0" : "1" );
        enderecoDecimal /= 2;
    }
    reverse(aux.begin(), aux.end());
    
    return std::bitset<TAMANHO_WORD>(aux);
}

/**
* -Descricao: converte numero binario de tamanho <tamanhoBinario> para decimal
* -Entrada: enderecoDecimal
* -Saida: enderecoBinario
*/
template<int tamanhoBinario>
int converteBinarioDecimal(std::bitset<tamanhoBinario> binario){
    int i, decimal, bin2;
    std::string bin; 
    
    for(i = binario.size() - 1; i>=0; i--){
        bin += binario[i] == 1 ? "1" : "0";
    }

    bin2 = stoi(bin);

    decimal = 0;
    for(i = 0; bin2 > 0; i++){
        decimal = decimal + pow(2, i) * (bin2 % 10);
        bin2 = bin2 / 10;
    }

    return decimal;
}

/**
* -Descricao: obtem uma porcao dos bits de enderecoBinario, delimitada pelas
*  posicoes max e min
* -Entrada: enderecoBinario, min, max
* -Saida: enderecoBinario[min:max]
*/
template<int tamanhoSub>
std::bitset<tamanhoSub> subBitset(std::bitset<TAMANHO_WORD> enderecoBinario, 
                                    int min, int max){
    int i;
    std::bitset<tamanhoSub> final;

    for(i=min; i<=max; i++){
        final[i-min] = enderecoBinario[i] == 1 ? 1 : 0;
    } 
    
    return final;
}

/**
* -Descricao: simula busca de um bloco dados na memoria e sua escrita na cache
* -Entrada: endereco
* -Saida: N/A
*/
void buscaBlocoDadosMemoria(std::bitset<TAMANHO_WORD> endereco){
    return;
}

/**
* -Descricao: simula escrita de um bloco de dados na memoria e remocao da cache
* -Entrada: endereco
* -Saida: N/A
*/
void escreveBlocoDadosMemoria(std::bitset<TAMANHO_WORD> endereco){
    return;
}

/**
* -Descricao: simula escrita do dado recebido na cache
* -Entrada: endereco, dado
* -Saida: N/A
*/
void escritaCache(std::bitset<TAMANHO_WORD> endereco, std::bitset<TAMANHO_WORD> dado){
    return;
}

/**
* -Descricao: simula leitura do dado na cache
* -Entrada: endereco
* -Saida: N/A
*/
void leituraCache(std::bitset<TAMANHO_WORD> endereco){
    return;
}

/**
* -Descricao: atende requisicoes de leitura e escrita, imprimindo resultados 
*  em arquivoSaida
* -Entrada: cache, enderecoDecimal, operacao, (refrencia) arquivoSaida 
* -Saida: true, se hit
          false, se miss
*/
bool atendeRequisicao(Bloco cache[], int enderecoDecimal, int operacao, 
                      std::bitset<TAMANHO_WORD> dado,
                      std::deque<std::string> &impressaoProcessamento){
    std::string aux;
    std::bitset<TAMANHO_WORD> enderecoBinario = converteDecimalBinario(enderecoDecimal);
    std::bitset<TAMANHO_INDICE> indiceBinario = 
    subBitset<TAMANHO_INDICE>(enderecoBinario, TAMANHO_OFFSET, TAMANHO_OFFSET + TAMANHO_INDICE - 1);
    int indiceDecimal = converteBinarioDecimal<TAMANHO_INDICE>(indiceBinario);
    std::bitset<TAMANHO_TAG> tagBinaria =  
    subBitset<TAMANHO_TAG>(enderecoBinario, TAMANHO_OFFSET + TAMANHO_INDICE, TAMANHO_WORD - 1);
    int tagDecimal = converteBinarioDecimal<TAMANHO_TAG>(tagBinaria);
        
    //leitura
    if(operacao == 0){
        //procura dentre as palavras no indice correspondente na cache
        if(!cache[indiceDecimal].valido){
            //miss de leitura

            //busca o bloco do dado na memoria e escreve na cache (simulacao)
            buscaBlocoDadosMemoria(enderecoBinario);
            cache[indiceDecimal].valido = true;
            cache[indiceDecimal].tag = tagDecimal;

            //leitura do dado trazido (simulacao)
            leituraCache(enderecoBinario);

            aux = std::to_string(enderecoDecimal) + " " + std::to_string(operacao)  + " M";
            impressaoProcessamento.push_back(aux);
            return false;
        } 

        else if(cache[indiceDecimal].tag == tagDecimal){
            //hit de leitura

            //leitura do dado (simulacao)
            leituraCache(enderecoBinario);

            aux = std::to_string(enderecoDecimal) + " " + std::to_string(operacao)  + " H";
            impressaoProcessamento.push_back(aux);
            return true;
        }

        else{
            //miss de leitura, substituicao necessaria

            //escreve o bloco de dados a ser sobrescrito na memoria, 
            //se algum dado estiver 'sujo'
            if(cache[indiceDecimal].sujo){
                escreveBlocoDadosMemoria(enderecoBinario);
                cache[indiceDecimal].sujo = false;
            }

            //busca o bloco do dado na memoria e sobrescreve na cache (simulacao)
            buscaBlocoDadosMemoria(enderecoBinario);
            cache[indiceDecimal].tag = tagDecimal;

            //leitura do dado trazido (simulacao)
            leituraCache(enderecoBinario);

            aux = std::to_string(enderecoDecimal) + " " + std::to_string(operacao)  + " M";
            impressaoProcessamento.push_back(aux);
            return false;
        }
        
    }

    //escrita
    else{
        if(!cache[indiceDecimal].valido){
            //miss de escrita

            //busca o bloco do dado na memoria e escreve na cache (simulacao)
            buscaBlocoDadosMemoria(enderecoBinario);
            cache[indiceDecimal].valido = true;
            cache[indiceDecimal].tag = tagDecimal;
            
            //escreve o dado recebido na cache (simulacao) e marca bloco como sujo
            escritaCache(enderecoBinario, dado);
            cache[indiceDecimal].sujo = true;

            aux = std::to_string(enderecoDecimal) + " " + std::to_string(operacao)  + " "
            + dado.to_string() + " W";
            impressaoProcessamento.push_back(aux);
            return false;
        }

        else if(cache[indiceDecimal].tag == tagDecimal){
            //hit de escrita

            //escreve o dado recebido na cache (simulacao)
            escritaCache(enderecoBinario, dado);
            cache[indiceDecimal].sujo = true;

            aux = std::to_string(enderecoDecimal) + " " + std::to_string(operacao)  + " "
            + dado.to_string() + " W";
            impressaoProcessamento.push_back(aux);
            return true;
        }

        else{
            //miss de escrita, substituicao necessaria
            
            //escreve o bloco de dados a ser sobrescrito na memoria, 
            //se algum dado estiver 'sujo'
            if(cache[indiceDecimal].sujo){
                escreveBlocoDadosMemoria(enderecoBinario);
                cache[indiceDecimal].sujo = false;
            }

            //busca o bloco do dado na memoria e escreve na cache (simulacao)
            buscaBlocoDadosMemoria(enderecoBinario);
            cache[indiceDecimal].tag = tagDecimal;

            //escreve o dado recebido na cache (simulacao) e marca bloco como sujo
            escritaCache(enderecoBinario, dado);
            cache[indiceDecimal].sujo = true;

            aux = std::to_string(enderecoDecimal) + " " + std::to_string(operacao)  + " "
            + dado.to_string() + " W";
            impressaoProcessamento.push_back(aux);
            return false;
        }
    }
    
}

/** 
* -Descricao: funcao principal, inciailiza cache e processa arquivo de entrada
* -Entrada: N/A
* -Saida: 0
*/
int main(){
    //variaveis auxiliares
    int enderecoDecimal, operacao, i;
    std::bitset<TAMANHO_WORD> dado;
    int hit = 0;
    int miss = 0;
    int leitura = 0;
    int escrita = 0;
    std::string buf, aux, aux2;
    std::ofstream arquivoSaida;
    std::deque<std::string> impressaoProcessamento;

    //incializacao memoria cache (vazia)
    Bloco cache[N_BLOCOS_CACHE];
    for(i=0; i<N_BLOCOS_CACHE; i++){
        cache[i].valido = false;
        cache[i].sujo = false;
    }

    //processamento das linhas do arquivo de entrada, lido da entrada padrao
    while(getline(std::cin, buf)){
        std::size_t pos = buf.find_first_of(" ");
        aux = buf;
        enderecoDecimal = stoi(buf.erase(pos));
        aux = aux.substr(pos+1);
        
        //se for uma escrita, le dado
        if(aux.size() > 32){
            std::size_t pos = aux.find_first_of(" ");
            aux2 = aux;
            operacao = stoi(aux.erase(pos));
            dado = std::bitset<TAMANHO_WORD>(aux2.substr(pos+1));
            escrita++;
        }

        //se for leitura
        else{
            operacao = stoi(aux);
            leitura++; 
        }

        bool result = atendeRequisicao(cache, enderecoDecimal, operacao, dado, impressaoProcessamento);
        if(result == true && operacao == 0){
            hit++;
        }
        else if(operacao == 0){
            miss++;
        }
        
    }
    
    //abertura do arquivo de saida
    arquivoSaida.open("result.txt");
    if(!arquivoSaida.is_open()){
        std::cout << std::endl << "Erro ao abrir o arquivo de saída." << std::endl;
        abort();
    }

    //fixando precisao de 3 casas decimais
    arquivoSaida << std::fixed << std::setprecision(3);

    //impressao das estatisticas
    arquivoSaida << "READS: " << leitura;
    arquivoSaida << std::endl << "WRITES: " << escrita;
    arquivoSaida << std::endl << "HITS: " << hit;
    arquivoSaida << std::endl << "MISSES: " << miss;
    arquivoSaida << std::endl << "HIT RATE: " << hit/float(leitura);
    arquivoSaida << std::endl << "MISS RATE: " << miss/float(leitura);
    arquivoSaida << std::endl << std::endl;

    //impressao das linhas do processamento
    for(i=0; i<int(impressaoProcessamento.size()); i++){
        arquivoSaida << impressaoProcessamento[i] << std::endl;
    }

    arquivoSaida.close();

    return 0;
}