#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario {
    char nome[50];
    char senha[20];
    char tipo_cliente[10];
    char email[50];
    int telefone;
    struct usuario *prox;
    struct usuario *ant;
} Usuario;

typedef struct lista_usuario {
    Usuario *inicio;
    Usuario *fim;
} ListaUsuario;

void cadastrar_usuario_inicio(ListaUsuario *lista, const char *nome, const char *senha, const char *tipo_cliente, const char *email, const int telefone) {
    Usuario *novo_usuario = (Usuario *)malloc(sizeof(Usuario));

    if (novo_usuario == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(novo_usuario->nome, nome, sizeof(novo_usuario->nome) - 1);
    novo_usuario->nome[sizeof(novo_usuario->nome) - 1] = '\0';
    strncpy(novo_usuario->senha, senha, sizeof(novo_usuario->senha) - 1);
    novo_usuario->senha[sizeof(novo_usuario->senha) - 1] = '\0';
    strncpy(novo_usuario->tipo_cliente, tipo_cliente, sizeof(novo_usuario->tipo_cliente) - 1);
    novo_usuario->tipo_cliente[sizeof(novo_usuario->tipo_cliente) - 1] = '\0';
    strncpy(novo_usuario->email, email, sizeof(novo_usuario->email) - 1);
    novo_usuario->email[sizeof(novo_usuario->email) - 1] = '\0';
    novo_usuario->telefone = telefone;  // Atribuindo o telefone

    novo_usuario->prox = lista->inicio;
    novo_usuario->ant = NULL;

    if (lista->inicio != NULL) {
        lista->inicio->ant = novo_usuario;
    } else {
        lista->fim = novo_usuario;
    }
    lista->inicio = novo_usuario;
}

void cadastrar_usuario_fim(ListaUsuario *lista, const char *nome, const char *senha, const char *tipo_cliente, const char *email, const int telefone) {
    Usuario *novo_usuario = (Usuario *)malloc(sizeof(Usuario));

    if (novo_usuario == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(novo_usuario->nome, nome, sizeof(novo_usuario->nome) - 1);
    novo_usuario->nome[sizeof(novo_usuario->nome) - 1] = '\0';
    strncpy(novo_usuario->senha, senha, sizeof(novo_usuario->senha) - 1);
    novo_usuario->senha[sizeof(novo_usuario->senha) - 1] = '\0';
    strncpy(novo_usuario->tipo_cliente, tipo_cliente, sizeof(novo_usuario->tipo_cliente) - 1);
    novo_usuario->tipo_cliente[sizeof(novo_usuario->tipo_cliente) - 1] = '\0';
    strncpy(novo_usuario->email, email, sizeof(novo_usuario->email) - 1);
    novo_usuario->email[sizeof(novo_usuario->email) - 1] = '\0';
    novo_usuario->telefone = telefone;  // Atribuindo o telefone

    novo_usuario->prox = NULL;
    novo_usuario->ant = lista->fim;

    if (lista->fim != NULL) {
        lista->fim->prox = novo_usuario;
    } else {
        lista->inicio = novo_usuario;
    }
    lista->fim = novo_usuario;
}

void cadastrar_usuario_meio(ListaUsuario *lista, const char *nome, const char *senha, const char *tipo_cliente, const char *email, const int telefone, const char *nome_referencia) {
    Usuario *atual = lista->inicio;

    while (atual != NULL && strcmp(atual->nome, nome_referencia) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Usuário de referência não encontrado.\n");
        return;
    }

    Usuario *novo_usuario = (Usuario *)malloc(sizeof(Usuario));
    if (novo_usuario == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(novo_usuario->nome, nome, sizeof(novo_usuario->nome) - 1);
    novo_usuario->nome[sizeof(novo_usuario->nome) - 1] = '\0';
    strncpy(novo_usuario->senha, senha, sizeof(novo_usuario->senha) - 1);
    novo_usuario->senha[sizeof(novo_usuario->senha) - 1] = '\0';
    strncpy(novo_usuario->tipo_cliente, tipo_cliente, sizeof(novo_usuario->tipo_cliente) - 1);
    novo_usuario->tipo_cliente[sizeof(novo_usuario->tipo_cliente) - 1] = '\0';
    strncpy(novo_usuario->email, email, sizeof(novo_usuario->email) - 1);
    novo_usuario->email[sizeof(novo_usuario->email) - 1] = '\0';
    novo_usuario->telefone = telefone;

    novo_usuario->prox = atual->prox;
    novo_usuario->ant = atual;

    if (atual->prox != NULL) {
        atual->prox->ant = novo_usuario;
    } else {
        lista->fim = novo_usuario;
    }
    atual->prox = novo_usuario;

    printf("Usuário cadastrado no meio, após %s.\n", nome_referencia);
}

void listar_usuarios(const ListaUsuario *lista) {
    Usuario *atual = lista->inicio;

    printf("Usuários cadastrados (início ao fim):\n");
    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("Senha: %s\n", atual->senha);
        printf("Tipo de cliente: %s\n", atual->tipo_cliente);
        printf("E-mail: %s\n", atual->email);
        printf("Telefone: %d\n", atual->telefone);
        printf("---------------\n");
        atual = atual->prox;
    }
}

void excluir_usuario(ListaUsuario *lista, const char *nome) {
    Usuario *atual = lista->inicio;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Usuário não encontrado.\n");
        return;
    }

    if (atual->ant != NULL) {
        atual->ant->prox = atual->prox;
    } else {
        lista->inicio = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->ant = atual->ant;
    } else {
        lista->fim = atual->ant;
    }

    free(atual);
    printf("Usuário %s excluído.\n", nome);
}

void liberar_lista(ListaUsuario *lista) {
    Usuario *atual = lista->inicio;
    while (atual != NULL) {
        Usuario *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}

void exibir_menu() {
    printf("\nMenu de opções:\n");
    printf("1 - Cadastrar usuário no início\n");
    printf("2 - Cadastrar usuário no fim\n");
    printf("3 - Cadastrar usuário no meio\n");
    printf("4 - Listar usuários\n");
    printf("5 - Excluir usuário\n");
    printf("6 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    ListaUsuario lista;
    lista.inicio = NULL;
    lista.fim = NULL;

    int opcao, telefone;
    char nome[50], senha[20], tipo_cliente[10], email[50], nome_referencia[50];

    do {
        exibir_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:  // Cadastrar no início
                printf("Digite o nome do usuário: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite a senha do usuário: ");
                fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = '\0';

                printf("Digite o tipo de cliente (vendedor/comprador): ");
                fgets(tipo_cliente, sizeof(tipo_cliente), stdin);
                tipo_cliente[strcspn(tipo_cliente, "\n")] = '\0';

                printf("Digite o e-mail do usuário: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Digite o telefone do usuário: ");
                scanf("%d", &telefone);  // Lendo o telefone como inteiro
                cadastrar_usuario_inicio(&lista, nome, senha, tipo_cliente, email, telefone);
                break;

            case 2:  // Cadastrar no fim
                printf("Digite o nome do usuário: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite a senha do usuário: ");
                fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = '\0';

                printf("Digite o tipo de cliente (vendedor/comprador): ");
                fgets(tipo_cliente, sizeof(tipo_cliente), stdin);
                tipo_cliente[strcspn(tipo_cliente, "\n")] = '\0';

                printf("Digite o e-mail do usuário: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Digite o telefone do usuário: ");
                scanf("%d", &telefone);  // Lendo o telefone como inteiro
                cadastrar_usuario_fim(&lista, nome, senha, tipo_cliente, email, telefone);
                break;

            case 3:  // Cadastrar no meio
                printf("Digite o nome do usuário: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite a senha do usuário: ");
                fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = '\0';

                printf("Digite o tipo de cliente (vendedor/comprador): ");
                fgets(tipo_cliente, sizeof(tipo_cliente), stdin);
                tipo_cliente[strcspn(tipo_cliente, "\n")] = '\0';

                printf("Digite o e-mail do usuário: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';

                printf("Digite o telefone do usuário: ");
                scanf("%d", &telefone);  // Lendo o telefone como inteiro

                printf("Digite o nome do usuário de referência: ");
                fgets(nome_referencia, sizeof(nome_referencia), stdin);
                nome_referencia[strcspn(nome_referencia, "\n")] = '\0';

                cadastrar_usuario_meio(&lista, nome, senha, tipo_cliente, email, telefone, nome_referencia);
                break;

            case 4:
                listar_usuarios(&lista);
                break;

            case 5:
                printf("Digite o nome do usuário a ser excluído: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                excluir_usuario(&lista, nome);
                break;

            case 6:
                liberar_lista(&lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 6);

    return 0;
}
