#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

struct Carta {
    std::string nome;
    int ataque;
    int defesa;
    int velocidade;
};

void exibirCarta(const Carta& carta) {
    std::cout << "Nome: " << carta.nome << "\n";
    std::cout << "1 - Ataque: " << carta.ataque << "\n";
    std::cout << "2 - Defesa: " << carta.defesa << "\n";
    std::cout << "3 - Velocidade: " << carta.velocidade << "\n";
}

int escolherAtributo(bool jogadorHumano) {
    if (jogadorHumano) {
        int escolha;
        std::cout << "Escolha o atributo para comparar [1-Ataque, 2-Defesa, 3-Velocidade]: ";
        std::cin >> escolha;
        return escolha;
    } else {
        // Computador escolhe aleatoriamente
        int escolha = rand() % 3 + 1;
        std::cout << "Computador escolheu o atributo: " << escolha << "\n";
        return escolha;
    }
}

int obterValorAtributo(const Carta& carta, int atributo) {
    switch (atributo) {
        case 1: return carta.ataque;
        case 2: return carta.defesa;
        case 3: return carta.velocidade;
        default: return 0;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<Carta> baralho = {
        {"Dragao", 90, 80, 70},
        {"Tigre", 75, 60, 85},
        {"Leão", 80, 70, 65},
        {"Cobra", 60, 50, 90},
        {"Urso", 85, 90, 55},
        {"Lobo", 70, 60, 80}
    };

    // Embaralhar baralho
    std::random_shuffle(baralho.begin(), baralho.end());

    // Dividir baralho entre jogador e computador
    std::vector<Carta> jogadorDeck(baralho.begin(), baralho.begin() + baralho.size() / 2);
    std::vector<Carta> computadorDeck(baralho.begin() + baralho.size() / 2, baralho.end());

    int pontosJogador = 0, pontosComputador = 0;
    bool vezDoJogador = true;

    while (!jogadorDeck.empty() && !computadorDeck.empty()) {
        std::cout << "\n--- Nova Rodada ---\n";
        Carta cartaJogador = jogadorDeck.front();
        Carta cartaComputador = computadorDeck.front();

        std::cout << "Sua carta:\n";
        exibirCarta(cartaJogador);

        std::cout << "\nCarta do adversário:\n";
        exibirCarta(cartaComputador);

        int atributo = escolherAtributo(vezDoJogador);
        int valorJogador = obterValorAtributo(cartaJogador, atributo);
        int valorComputador = obterValorAtributo(cartaComputador, atributo);

        std::cout << "Você (" << valorJogador << ") x Adversário (" << valorComputador << ")\n";

        if (valorJogador > valorComputador) {
            std::cout << "Você venceu a rodada!\n";
            pontosJogador++;
        } else if (valorJogador < valorComputador) {
            std::cout << "Você perdeu a rodada!\n";
            pontosComputador++;
        } else {
            std::cout << "Empate!\n";
        }

        // Remover cartas usadas
        jogadorDeck.erase(jogadorDeck.begin());
        computadorDeck.erase(computadorDeck.begin());

        // Alternar vez
        vezDoJogador = !vezDoJogador;
        std::cout << "Pontuação: Você " << pontosJogador << " x " << pontosComputador << " Computador\n";
    }

    std::cout << "\n--- Fim de jogo ---\n";
    if (pontosJogador > pontosComputador) {
        std::cout << "Parabéns! Você venceu o jogo!\n";
    } else if (pontosJogador < pontosComputador) {
        std::cout << "Que pena! O computador venceu o jogo!\n";
    } else {
        std::cout << "O jogo terminou empatado!\n";
    }

    return 0;
}