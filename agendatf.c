#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;
typedef struct{
    int minuto;
    int hora;
}Hora_inicio;
typedef struct{
    int minuto;
    int hora;
}Hora_fim;
typedef struct{
    Data data;
    Hora_inicio inicio;
    Hora_fim fim;
    char descricao[50];
    char local[20];
}Evento;

void le_evento (FILE *f, int x,int n);
void mostra_evento(FILE *f, int x);
void mostra_data(FILE *f, int x);
void prox_eventos(FILE *f,int x);
void remover_eventos(FILE *f,int x);

int main(){
    int parada=1;
    FILE *f = fopen("agenda.bin","ab+");
    if(f == NULL){
        printf("Erro na abertura do arquivo de entrada!");
        return 1;
    }
    int registros=0;
    fseek (f, 0, SEEK_END);
    registros = ftell(f); // indica o numero de registros salvos
    if (registros>0){
        registros = registros/sizeof(Evento);  
    }
    printf("Agenda de Eventos iniciada.\n");
    while(parada==1){
    printf("\nVoce tem %d eventos registrados\n",registros);
    printf("\nInforme o servico desejado:\n");
    printf("1 - Cadastrar um novo evento.\n");
    printf("2 - Mostrar todos os eventos.\n");
    printf("3 - Eventos da data.\n");
    printf("4 - Proximos eventos.\n");
    printf("5 - Remover evento.\n");
    printf("6 - Encerrar o programa.\n");
    printf("\n");
    int opcao;
    scanf("%d",&opcao);
    switch(opcao){
        case 1 :
        printf("\nVoce escolheu a opcao Cadastrar um novo evento!\n");
        printf("Quantos eventos deseja adicionar?\n");
        int n;
        scanf("%d",&n); 
        registros = registros + n;   
        le_evento(f,registros,n);        
        printf("\n");
        break;
        case 2 :
        printf("\nVoce escolheu a opcao Mostrar todos os eventos!\n");
        if(registros==0){
            printf("\nNao ha eventos salvos na agenda!\n");
        }else{
            mostra_evento(f,registros);
        }        
        break;
        case 3 :
        printf("\nVoce escolheu a opcao Eventos da data!\n");
        if(registros==0){
            printf("\nNao ha eventos salvos na agenda!\n");
        }else{
            mostra_data(f,registros);
        }
        break;
        case 4 :
        printf("\nVoce escolheu a opcao Proximos eventos!\n");
        if(registros==0){
            printf("\nNao ha eventos salvos na agenda!\n");
        }else{
            prox_eventos(f,registros);
        }
        break;
        case 5 :
        printf("\nVoce escolheu a opcao Remover evento!\n");
        if(registros==0){
            printf("\nNao ha eventos salvos na agenda!\n");
        }else{
            remover_eventos(f,registros);
            fseek (f, 0, SEEK_END);
            registros = ftell(f); // para recalcular quantidade de eventos
            if (registros>0){
                registros = registros/sizeof(Evento);
            }
        }
        break;
        case 6 :
        printf("\nPrograma finalizado!\n");
        parada=0;
        break;
    }
    }
    fclose(f);
    return 0;
}
void le_evento (FILE *f,int x, int n){
    Evento a;
    Evento *b;
    b = malloc(sizeof(Evento)*x);
    int j=0;
    fseek(f,0,SEEK_SET);
    if(x!=1){
    for(j=0;j<x-n;j++){
        fread(&b[j],sizeof(Evento),1,f);
    }
    }  
    char espaco[10];
    j=x-n;
    while(n!=0){
    if(x==0){
        printf("\nDigite um novo Evento:\n");
        printf("\nDigite uma data\n");
        printf("Digite o dia: ");
        scanf("%d",&a.data.dia);
        printf("Digite o mes: ");
        scanf("%d",&a.data.mes);
        printf("Digite o ano: ");
        scanf("%d",&a.data.ano);
        printf("Digite o horario inicial\n");
        printf("Digite a hora: ");
        scanf("%d",&a.inicio.hora);
        printf("Digite o minuto: ");
        scanf("%d",&a.inicio.minuto);
        printf("Digite o horario final\n");
        printf("Digite a hora: ");
        scanf("%d",&a.fim.hora);
        printf("Digite o minuto: ");
        scanf("%d",&a.fim.minuto);
        gets(espaco);
        printf("Digite uma descricao: ");
        gets(a.descricao);
        printf("Digite o local: ");
        gets(a.local);
        fseek(f, 0, SEEK_END);
        fwrite(&a, sizeof(Evento), 1, f);
        n--;
        b[j] = a;
        j++;
    }else{
        printf("\nDigite um novo Evento:\n");
        printf("\nDigite uma data\n");
        printf("Digite o dia: ");
        scanf("%d",&a.data.dia);
        printf("Digite o mes: ");
        scanf("%d",&a.data.mes);
        printf("Digite o ano: ");
        scanf("%d",&a.data.ano);
        printf("Digite o horario inicial\n");
        printf("Digite a hora: ");
        scanf("%d",&a.inicio.hora);
        printf("Digite o minuto: ");
        scanf("%d",&a.inicio.minuto);
        printf("Digite o horario final\n");
        printf("Digite a hora: ");
        scanf("%d",&a.fim.hora);
        printf("Digite o minuto: ");
        scanf("%d",&a.fim.minuto);
        gets(espaco);
        printf("Digite uma descricao: ");
        gets(a.descricao);
        printf("Digite o local: ");
        gets(a.local);
        int k=0;
        int aux=0;
        for(k=0;k<x-n;k++){
            if(a.data.dia == b[k].data.dia && a.data.mes == b[k].data.mes && a.data.ano == b[k].data.ano && a.inicio.hora == b[k].inicio.hora && a.inicio.minuto == b[k].inicio.minuto){
                aux++;
                break;
            }
        }
        if(aux == 0){
            fseek(f, 0, SEEK_END);
            fwrite(&a, sizeof(Evento), 1, f);
            n--;
            b[j] = a;
            j++;
        }else{
            printf("\nDado invalido, digite novamente.\n");
        }
    }      
    }
    free(b);   
}
void mostra_evento(FILE *f, int x){
    Evento a;
    int j;
    fseek(f,0,SEEK_SET);
    for(j=0;j<x;j++){
        printf("#%d",(j+1));
        fread(&a,sizeof(a),1,f);
        printf("\nData: %d/%d/%d\n",a.data.dia,a.data.mes,a.data.ano);
        printf("Horario inicial: %dh:%dmin\n",a.inicio.hora,a.inicio.minuto);
        printf("Horario final: %dh:%dmin\n",a.fim.hora,a.fim.minuto);
        printf("Descricao: %s\n",a.descricao);
        printf("Local: %s\n",a.local);
    }
}
void mostra_data(FILE *f, int x){
    Evento a;
    int j,cont=0;
    int dia, mes, ano;
    printf("\nDigite dia, mes e ano para checagem: \n");
    printf("Dia: ");
    scanf("%d",&dia);
    printf("Mes: ");
    scanf("%d",&mes);
    printf("Ano: ");
    scanf("%d",&ano);
    fseek(f,0,SEEK_SET);
    for(j=0;j<x;j++){
        fread(&a,sizeof(a),1,f);
        if((ano==a.data.ano) && (mes==a.data.mes) && (dia==a.data.dia)){
            cont++;
            printf("#%d",cont);
            printf("\nData: %d/%d/%d\n",a.data.dia,a.data.mes,a.data.ano);
            printf("Horario inicial: %dh:%dmin\n",a.inicio.hora,a.inicio.minuto);
            printf("Horario final: %dh:%dmin\n",a.fim.hora,a.fim.minuto);
            printf("Descricao: %s\n",a.descricao);
            printf("Local: %s\n",a.local);
        } 
    }
    if(cont==0){
        printf("\nNao ha nenhum evento marcado nesse dia.\n");
    }
}
void prox_eventos(FILE *f, int x){
    Evento a;
    int j,posicao=-1;
    int dia, mes, ano;
    printf("\nDigite a data atual: \n");
    printf("Dia: ");
    scanf("%d",&dia);
    printf("Mes: ");
    scanf("%d",&mes);
    printf("Ano: ");
    scanf("%d",&ano);
    fseek(f,0,SEEK_SET);
    for(j=0;j<x;j++){
        fread(&a,sizeof(a),1,f);
        if((ano==a.data.ano) && (mes==a.data.mes) && (dia==a.data.dia)){
            posicao=j;
            break;
        }else if((ano==a.data.ano)&&(mes==a.data.mes)&&(dia<a.data.dia)){
            posicao=j;
            break;
        }else if((ano==a.data.ano) && (mes<a.data.mes)){
            posicao=j;
            break;
        }else if(ano<a.data.ano){
            posicao=j;
            break;
        }
    }
    int cont=0;
    if(x-posicao<5){ // x e o numero de registros
        printf("\n%d eventos foram encontrados\n",(x-posicao));
        fseek(f,posicao*sizeof(Evento),SEEK_SET);
        for(j=posicao;j<x;j++){
            fread(&a,sizeof(a),1,f);
            cont++;
            printf("#%d",cont);
            printf("\nData: %d/%d/%d\n",a.data.dia,a.data.mes,a.data.ano);
            printf("Horario inicial: %dh:%dmin\n",a.inicio.hora,a.inicio.minuto);
            printf("Horario final: %dh:%dmin\n",a.fim.hora,a.fim.minuto);
            printf("Descricao: %s\n",a.descricao);
            printf("Local: %s\n",a.local);
        }
    }else if(posicao==-1){
        printf("\nNao ha eventos marcados apos essa data.\n");
    }else{
        printf("\n5 eventos foram encontrados\n");
        fseek(f,posicao*sizeof(Evento),SEEK_SET);
        for(j=posicao;j<posicao+5;j++){
            fread(&a,sizeof(a),1,f);
            cont++;
            printf("#%d",cont);
            printf("\nData: %d/%d/%d\n",a.data.dia,a.data.mes,a.data.ano);
            printf("Horario inicial: %dh:%dmin\n",a.inicio.hora,a.inicio.minuto);
            printf("Horario final: %dh:%dmin\n",a.fim.hora,a.fim.minuto);
            printf("Descricao: %s\n",a.descricao);
            printf("Local: %s\n",a.local);

        }
    }
}
void remover_eventos(FILE *f,int x){
    Evento *a;
    a=malloc(sizeof(Evento)*x);
    int j;
    fseek(f,0,SEEK_SET);
    for(j=0;j<x;j++){
        fread(&a[j],sizeof(Evento),1,f);
    }
    int dia,mes,ano,hora,minuto,pos=-1;
    printf("\nDigite uma data e horario inicial de um evento a ser removido.");
    printf("\nDia: ");
    scanf("%d",&dia);
    printf("Mes: ");
    scanf("%d",&mes);
    printf("Ano: ");
    scanf("%d",&ano);
    printf("Hora: ");
    scanf("%d",&hora);
    printf("Minuto: ");
    scanf("%d",&minuto);
    for(j=0;j<x;j++){
        if((ano==a[j].data.ano) && (mes==a[j].data.mes) && (dia==a[j].data.dia) && (hora==a[j].inicio.hora) && (minuto==a[j].inicio.minuto)){
            pos=j;
            break;
        }
    }
    if(pos!=-1){
    fclose(f);
    FILE *g = fopen("agenda.bin", "wb+");
    fseek(g,0,SEEK_SET);
    for(j=0;j<x;j++){
        if(j==pos){
            continue;
        }else{
            fwrite(&a[j], sizeof(Evento), 1, g);
        }
    }
    printf("\nEvento removido com sucesso!\n");
    fclose(f);
    FILE *f = fopen("agenda.bin","ab+");
    }else{
        printf("\nEvento a ser removido nao encontrado.\n");
    }
    free(a);    
}
