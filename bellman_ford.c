#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#define MAX 100
typedef struct item{
    int v1,v2,wt;
}node;
node x[MAX];
int nov, noe;
int dist[MAX], pred[MAX];
int w[MAX][MAX];

void bellman_ford(int src) {
    for(int i=0; i<nov; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;
    for (int i = 0; i < nov-1; i++) {
        for (int j = 0; j < noe; j++) {
            int u = x[j].v1;
            int v = x[j].v2;
            int cost = x[j].wt;
            if (dist[v] > dist[u]+cost) {
                dist[v] = dist[u]+cost;
                pred[v] = u;
            }
        }
    }
    for(int j=0; j<noe; j++) {
        int u = x[j].v1;
        int v = x[j].v2;
        int cost = x[j].wt;
        if (dist[v] > dist[u]+cost) {
            printf("Graph contain negative weight cycle");
            break;
        }
    }
    for(int i=0; i<nov; i++) {
        printf("(%d, %d)\n",dist[i], pred[i]);
    }
}
// no need
// void mstprint(int src){
//     printf("mstprint\n");
//     for(int i=0; i<nov; i++) {
//         if(i != src) {
//             printf("Edges(%d-%d)->%d\n",pred[i], i, dist[i]);
//         }
//     }
// }
void adjacentprint(int src, int des)  {
    int p[10], x, k=0;
    p[k] = des;
    x = des;
    while(x != src) {
        p[++k] = pred[x];
        x = pred[x];
        printf("%c\n",x+65);
    }
    //  for(int i=k-1; i>=0; i--) {
    for(int i=k; i>=0; i--) {
        printf("%c->",p[i]+65);
    }
    printf("\n");
}
void print_ip() {
    FILE *fp;
    fp = fopen("ip_bellman_ford.txt","r");
    if(fp == NULL) {
        printf("File is empty");
    }
    fscanf(fp, "%d",&nov);
    for(int i=0; i<nov; i++) {
        printf("The adjacent of the vertix %c is : ",i+65);
        for(int j=0; j<nov; j++) {
            fscanf(fp, "%d",&w[i][j]);
            if(w[i][j] != 0) {
                printf("%c, ",j+65);
            }
        }
        printf("\n");
    }
    printf("Adjacency Matrix:\n");
    for(int i=0; i<nov; i++) {
        for(int j=0; j<nov; j++) {
            printf("%3d",w[i][j]);
        }
        printf("\n");
    }
    fclose(fp);
}
void file() {
    FILE *fp;
    fp = fopen("ip_bellman_ford.txt","r");
    if(fp == NULL) {
        printf("File is empty");
    }
    fscanf(fp, "%d",&nov);
    int edgeIndex = 0;
    for (int i=0; i<nov; i++) {
        for (int j=0; j<nov; j++) {
            int weight;
            fscanf(fp, "%d", &weight);
            // data
            if (weight != 0) {
                x[edgeIndex].v1 = i;
                x[edgeIndex].v2 = j;
                x[edgeIndex].wt = weight;
                edgeIndex++;
            }
        }
    }
    noe = edgeIndex;
    printf("Vertices : %d\n",nov);
    printf("Edges : %d\n",noe);
    fclose(fp);
}
int main() {
    print_ip();
    file();
    int src;
    printf("Enter the starting vertex : ");
    scanf("%d",&src);
    bellman_ford(src);
    for(int i=1; i<nov; i++) {
        printf("From %c to %c :\n",src+65,i+65);
        adjacentprint(src, i);
        printf("\n");
    }
    // mstprint(src);

    return 0;
}