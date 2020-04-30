#include <stdio.h>
struct edg
{
    int a;
    int b;
    int w;
};

struct subs
{
    int n;
    int p;
};


void swap(struct edg* A, struct edg* B)
{
    struct edg t;
     t.w = A->w;
     A->w = B->w;
     B->w = t.w;
     t.a = A->a;
     A->a = B->a;
     B->a = t.a;
     t.b = A->b;
     A->b = B->b;
     B->b = t.b;
}
int partition (struct edg arr[], int low, int high)
{
    struct edg pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].w < pivot.w)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(struct edg arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }

}

int find(struct subs verts[],int x)
{
    if(verts[x].p < 0)
    {
        printf("find-if\n");
        return x;
    }
    else
    {
        return find(verts,verts[x].p);
    }
}

int unionop(struct subs verts[],int a, int b)
{
    int aset = find(verts, a);
    int bset = find(verts, b);
    if(aset != bset)
    {
        printf("\nUnion");
        verts[aset].p = bset;
    }

}

int iscycle( struct edg result[], int counte, int v)
{
    printf("iscycle1 \t");
    struct subs verts[counte];
    int j =0;

    for(int i =0; i<v;i++)
    {
        verts[i].n = i;
        verts[i].p = -1;
    }
    if(counte<3)
    {
        return 0;
    }
    else
    {
        while(j<=counte)
        {
            printf("\nj->%d",j);
            //printf("iscycle2 \ta-%d   b-%d",result[j].a,result[j].b);
            if(find(verts,result[j].a) != find(verts,result[j].b))
            {
                printf("iscycle2 \ta-%d   b-%d",result[j].a,result[j].b);
                unionop(verts,result[j].a,result[j].b);
            }
            else if(find(verts,result[j].a) == find(verts,result[j].b))
            {
                printf("\n1\t");
                return 1;
            }
            j++;

        }
        return 0;
    }

}

int kruskal(struct edg inp[], struct edg result[],int v)
{
    int countv = 2;
    int counte = 2;
    while (counte<v)
    {
        printf("krusk1    %d",counte);
        result[counte].a = inp[countv].a;
        result[counte].b = inp[countv].b;
        result[counte].w = inp[countv].w;
        if(iscycle(result,counte,v) == 1)
        {
            result[counte].a = 9999;
            result[counte].b = 9999;
            result[counte].w = 9999;
            counte--;
        }
        printf("\tifcheck\t");
        countv++;
        counte++;
    }

}


int main()
{
    int e;
    int v;
    printf("Enter no. of vertices: ");
    scanf("%d",&v);
    printf("\nEnter no. of edges: ");
    scanf("%d",&e);
    struct edg inp[e];
    inp[0].a = 0;
    inp[0].b = 1;
    inp[0].w = 10;

    inp[1].a = 0;
    inp[1].b = 2;
    inp[1].w = 6;

    inp[2].a = 0;
    inp[2].b = 3;
    inp[2].w = 5;

    inp[3].a = 1;
    inp[3].b = 3;
    inp[3].w = 15;

    inp[4].a = 2;
    inp[4].b = 3;
    inp[4].w = 4;
    quickSort(inp,0,e-1);
    struct edg result[v-1];
    result[0].a = inp[0].a;
    result[0].b = inp[0].b;
    result[0].w = inp[0].w;
    result[1].a = inp[1].a;
    result[1].b = inp[1].b;
    result[1].w = inp[1].w;
    for(int i = 2;i<v-1;i++)
    {
        result[i].a = i;
        result[i].b = -1;
        result[i].w = 9999;
    }
    for(int k=0;k<e;k++)
    {
    printf("%d    ",inp[k].w);
    }
    printf("\n");
    kruskal(inp,result,v);
    printf("kruskdone");
    for(int k = 0; k<v-1;k++)
    {
        printf("%d to %d wt-> %d \n",result[k].a,result[k].b,result[k].w);
    }

}
