
#include <iostream>
#include <cstdlib>

#define system_clear system("cls")
#define system_pause system("Pause")

/**
 * 	Engenharia Informatica - L
 *  Disciplina: Informatica 2
 *  Nome do Projeto: Sistema de Cadastramento
 *  Dev's Name: Eloide Simao Novela
 *  Data: 2023/07/19
 *
 *  Dicricao: Este e um sistema de castramento, ele usa dois algoritmos,
 *  um de ordenacao, e um de busca. O sistema ordena ou atualiza os dados
 *  usando o algoritmo de ordenacao por insercao, e a busca/pesquisa e feita
 *  pelo algoritmo de busca binario. O algoritmo de busca nao e interativo
 *  mas sim, e recursivo.
 *  O Sistema tem a tambem a funcionalidade de remover elementos do seu banco
 *  de dados(arrays), este algoritmo funciona da seguinte maneira: o usuario
 *  seleciona um elemento(indece ou a posicao) para a remocao entao esse elemento
 *  e deslocado para a ultima posicao da lista e é feichado o campo de visao do
 *  utilizador.
 *
 *  O algoritmo de pesquisa pode pesquisar atraves de tres(3) chaves: nome, idade e id.
 */

using namespace std;

typedef struct Pessoa {
    string nome;
    short int idade;
    short int id;
} Pessoa;

void add(struct Pessoa *, int, int &);
void show(struct Pessoa *, int, int);
void update(struct Pessoa *, int);
bool b_search(struct Pessoa *, int, int, string, short int, short int, int &);
void remove(struct Pessoa *, int &, int);

const int size = 100; // espaco maximo do banco de dados(array).

int aux_size = 0;
Pessoa arr[size];

int main( ) {

    int main_input = 0;
    cout << "Menu Principal\n"
         << "1. Adicionar\n"
         << "2. Mostrar\n"
         << "3. Buscar\n"
         << "4. Remover\n"
         << "0. Sair\n"
         << "\nEntrada: ";
    cin >> main_input;

    system_clear;

    switch ((main_input)) {
    case 1: {
        add(arr, size, aux_size);
        update(arr, aux_size);
        main();
        break;
    } case 2: {
        show(arr, aux_size, -1);
        system_pause;
        system_clear;
        main();
        break;
    } case 3: {
        string name;
        int index = -1, input = -1, id = -1;
        update(arr, aux_size);
        cout << "Tipo de Busca\n"
             << "1. Buscar pelo nome\n"
             << "2. Buscar pelo id\n"
             << "\nEntrada: ";
        cin >> input;
        system_clear;
        
        switch (input) {
        case 2: {
            cout << "Insira o id: ";
            cin >> id;
            system_clear;
            
            break;
        } case 1: {
        	
            cout << "Insira o nome: ";
            cin >> name;
            system_clear;
            
            break;

        } default:
            cout << "Erro: Entrada Invalida\nO Sistema vai te redirecionar para o Menu Inicial\n";
            system_pause;
            system_clear;
            main();
        }

        if (b_search(arr, aux_size, 0, name, -1, id, index)) {

            cout << "Encontrado" << endl;
            show(arr, aux_size, index);
            system_pause;
            system_clear;
            main();

        } else {
            cout << "Nao encontrado" << endl;
            system_pause;
            system_clear;
            main();
        }
        break;
    } case 4: {
        int id = -1, index = -1;
        show(arr,aux_size, -1);

        if ((aux_size > 0)) {

            cout << "Insira o Id\n"
                 << "Entrada: ";
            cin >> id;

            if (b_search(arr, aux_size, 0, "", -1, id, index)) {

                remove(arr, aux_size, index);
                cout << "Removido..." << endl;

            } else {

                cout << "Erro: Item nao encontrado\nO sistema vai te redirecionar para a Menu inicial!" << endl;
            }
        }
        system_pause;
        system_clear;
        main();
        break;
    } case 0:
        exit(0);
        break;
    default:
        cout << "Erro: Entrada Invalida!" << endl;
        system_pause;
        system_clear;
        main();
        break;
    }
}

void add(struct Pessoa arr[], int size, int & saved) {
    int aux_size = 0;

    cout << "Quantas pessoas deseja cadastrar?\n"
         << "Entrada: ";
    cin >> aux_size;
    system_clear;

    for (int i = saved ; i < aux_size + saved ; i++) {

        cout << "Insira o nome: ";
        cin >> arr[i].nome;
        cout << "Insira a idade: ";
        cin >> arr[i].idade;
        arr[i].id = i + 1;

        system_clear;
    }

    cout << "Termindo...";
    system_clear;
    saved += aux_size;
}

void show(struct Pessoa arr[], int aux_size, int index) {
    string tab;

    if ((aux_size > 0) || (index >= 0)) {

        cout << "Id\tNome\t\tIdade" << endl;
    } else {

        cout << "Lista Vazia" << endl;
    }

    if (index < 0) {
        for (int i = 0 ; i < aux_size ; i++) {
            if (arr[i].nome.length() >= 8) {

                tab = "\t";

            } else {

                tab = "\t\t";

            }
            cout << arr[i].id << "\t" << arr[i].nome << tab << arr[i].idade << endl;
        }
    } else {
        if (arr[index].nome.length() >= 8) {

            tab = "\t";

        } else {

            tab = "\t\t";

        }
        cout << arr[index].id << "\t" << arr[index].nome << tab << arr[index].idade << endl;
    }
}

void update(struct Pessoa arr[], int size) {

    string aux_str;
    int len = 1, aux_idade = 0, aux_id = -1;

    for (int i = 0 ; i < size ; i++) {

        for (int j = 0 ; j < (int) arr[i].nome.size() ; j++) {

            if ((int) arr[i].nome[j] >= 65 && (int) arr[i].nome[j] <= 90) {

                arr[i].nome[j] = (char) ((int) arr[i].nome[j] + 32);

            }
        }
    }

    for (int j = 0 ; j < size ; j++) {

        arr[j].nome[0] = (char) ((int) arr[j].nome[0] - 32);

    }

    for (int j = 0 ; j < size - 1 ; j++) {

        for (int i = 1 + j ; i > 0 ; i--) {

            for (int l = 0 ; l < len ; l++) {

                if ((int) arr[i].nome[l] < (int) arr[i-1].nome[l]) {
                    aux_str = arr[i].nome;
                    aux_idade = arr[i].idade;
                    aux_id = arr[i].id;

                    arr[i].nome = arr[i-1].nome;
                    arr[i].idade = arr[i-1].idade;
                    arr[i].id = arr[i-1].id;

                    arr[i-1].nome = aux_str;
                    arr[i-1].idade = aux_idade;
                    arr[i-1].id = aux_id;

                } else if ((int) arr[i].nome[l] == (int) arr[i-1].nome[l]) {

                    len++;
                }
            }
            len = 1;
        }
    }
}

bool b_search(struct Pessoa arr[], int end, int begin, string name, short int age, short id, int & index) {

    int middle = 0, len = 1;

    if (begin <= end) {

        middle = (end + begin) / 2;

        for (int l = 0 ; l < len ; l++) {

            if ((arr[middle].nome == name) || (arr[middle].idade == age) || (arr[middle].id == id)) {

                index = middle;
                return true;

            } else if ((int) name[l] > (int) arr[middle].nome[l]) {

                return b_search(arr, end, middle + 1, name, age, id, index);

            } else if ((int) name[l] < (int) arr[middle].nome[l]) {

                return b_search(arr, middle - 1, begin, name, age, id, index);

            } else if ((int) name[l] == (int) arr[middle].nome[l]) {

                len++;
            }
        }
    }

    return false;
}

void remove(struct Pessoa arr[], int & size, int index) {

    string aux_str;
    int aux_idade = 0, aux_id = -1;

    if (((index >= 0) && (index < size))) {

        for (int j = index ; j < size - 1; j++) {
            aux_str = arr[j].nome;
            aux_idade = arr[j].idade;
            aux_id = arr[j].id;

            arr[j].nome = arr[j+1].nome;
            arr[j].idade = arr[j+1].idade;
            arr[j].id = arr[j+1].id;

            arr[j+1].nome = aux_str;
            arr[j+1].idade = aux_idade;
            arr[j+1].id = aux_id;
        }

    } else {

        return;
    }
    size--;
}
