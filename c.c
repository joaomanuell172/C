#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Verifica o sistema operacional para usar o comando correto de limpar tela
void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

struct Jogador {
    char nome[20];
    int escolha;
    int vivo; 
};

int main() {
    srand(time(NULL));

    struct Jogador j1, j2;
    int balas = 1;
    int max_balas = 5;
    int rodada = 1;

    // Configuração inicial
    limpar_tela();
    printf("=== JOGO DE PEDRA, PAPEL E TIRO ===\n\n");
    
    printf("Digite o nome do Jogador 1: ");
    scanf("%s", j1.nome);
    j1.vivo = 1;

    printf("Digite o nome do Jogador 2: ");
    scanf("%s", j2.nome);
    j2.vivo = 1;

    while(rodada <= 5) {
        // --- TURNO JOGADOR 1 ---
        limpar_tela();
        printf("=== Rodada %d ===\n", rodada);
        printf("ATENCAO: %s deve olhar para longe agora!\n", j2.nome);
        printf("-------------------------------------------------\n");
        printf("%s, e sua vez.\n", j1.nome);
        printf("1=Pedra  2=Papel  3=Tesoura\n");
        printf("Escolha (1-3): ");
        scanf("%d", &j1.escolha);

        // --- TURNO JOGADOR 2 ---
        limpar_tela();
        printf("=== Rodada %d ===\n", rodada);
        printf("ATENCAO: %s deve olhar para longe agora!\n", j1.nome);
        printf("-------------------------------------------------\n");
        printf("%s, e sua vez.\n", j2.nome);
        printf("1=Pedra  2=Papel  3=Tesoura\n");
        printf("Escolha (1-3): ");
        scanf("%d", &j2.escolha);

        // Limpa a tela antes de mostrar o resultado para suspense
        limpar_tela();
        printf("=== RESULTADO DA RODADA %d ===\n\n", rodada);
        printf("%s escolheu: %d\n", j1.nome, j1.escolha);
        printf("%s escolheu: %d\n\n", j2.nome, j2.escolha);

        // Lógica de validação J1
        if(j1.escolha < 1 || j1.escolha > 3) {
            printf("%s nao jogou corretamente e perdeu a vez!\n", j1.nome);
            int disparo = rand() % max_balas;
            if(disparo < balas) {
                printf("BANG! %s atirou e acertou %s! %s morreu.\n", j2.nome, j1.nome, j1.nome);
                j1.vivo = 0;
                break;
            } else {
                printf("CLICK! %s atirou, mas nao tinha bala!\n", j2.nome);
                int opc;
                printf("%s, deseja aumentar a dificuldade? (0=nao, 1=sim): ", j2.nome);
                scanf("%d", &opc);
                if(opc == 1 && balas < max_balas) {
                    balas++;
                    printf("Dificuldade aumentada! Agora o revolver tem %d balas.\n", balas);
                }
            }
            rodada++;
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar(); // Pausa para leitura
            continue;
        }

        // Lógica de validação J2
        if(j2.escolha < 1 || j2.escolha > 3) {
            printf("%s nao jogou corretamente e perdeu a vez!\n", j2.nome);
            int disparo = rand() % max_balas;
            if(disparo < balas) {
                printf("BANG! %s atirou e acertou %s! %s morreu.\n", j1.nome, j2.nome, j2.nome);
                j2.vivo = 0;
                break;
            } else {
                printf("CLICK! %s atirou, mas nao tinha bala!\n", j1.nome);
                int opc;
                printf("%s, deseja aumentar a dificuldade? (0=nao, 1=sim): ", j1.nome);
                scanf("%d", &opc);
                if(opc == 1 && balas < max_balas) {
                    balas++;
                    printf("Dificuldade aumentada! Agora o revolver tem %d balas.\n", balas);
                }
            }
            rodada++;
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar();
            continue;
        }

        // Lógica do Vencedor
        int vencedor = 0; 
        if(j1.escolha != j2.escolha) {
            if((j1.escolha==1 && j2.escolha==3) ||
               (j1.escolha==2 && j2.escolha==1) ||
               (j1.escolha==3 && j2.escolha==2))
                vencedor = 1;
            else
                vencedor = 2;
        }

        // Resolução do Tiro
        if(vencedor == 0) {
            printf("Empate! Ninguem dispara.\n");
        } else {
            struct Jogador *ganhador = (vencedor == 1) ? &j1 : &j2;
            struct Jogador *perdedor = (vencedor == 1) ? &j2 : &j1;

            printf("%s venceu a rodada e aponta a arma!\n", ganhador->nome);
            int disparo = rand() % max_balas;
            
            // Suspense...
            // Sleep(1000); // Pode usar se estiver no Windows para dar drama

            if(disparo < balas) {
                printf("\nBANG!!!\n");
                printf("%s atirou e acertou %s! %s morreu.\n", ganhador->nome, perdedor->nome, perdedor->nome);
                perdedor->vivo = 0;
                break;
            } else {
                printf("\nCLICK... (Sem bala)\n");
                printf("%s sobreviveu.\n", perdedor->nome);
                
                int opc;
                printf("%s, deseja colocar mais uma bala no tambor? (0=nao, 1=sim): ", ganhador->nome);
                scanf("%d", &opc);
                if(opc == 1 && balas < max_balas) {
                    balas++;
                    printf("Dificuldade aumentada! Tambor tem %d balas.\n", balas);
                } else if(opc == 1) {
                    printf("O tambor ja esta cheio!\n");
                }
            }
        }

        printf("\nPressione ENTER para a proxima rodada...");
        getchar(); getchar(); // Hack simples para pausar no C
        rodada++;
    }

    printf("\n=== Fim do Jogo ===\n");
    if(j1.vivo && j2.vivo) printf("Fim das 5 rodadas! Ambos sobreviveram.\n");
    else if(j1.vivo) printf("VITORIA DE %s!\n", j1.nome);
    else if(j2.vivo) printf("VITORIA DE %s!\n", j2.nome);
    else printf("Ambos foram eliminados!\n");

    return 0;
}
