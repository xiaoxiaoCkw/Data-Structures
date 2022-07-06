#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N�Ƕ�������E�Ǳ���
    int **matrix;//�����ڽӾ���
    vextype *vertex;//�洢�ڵ������
} Graph;


Graph createGraph(int n);
int isConnected(Graph g);
void DFS(Graph g, int v, int visited[]);
int FirstNeighbor(Graph g, int v);
int NextNeighbor(Graph g, int v, int w);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);

/**
 * ����һ���ڵ���Ϊn��ͼ
 * @param n �ڵ����
 * @return �������ͼ
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}

/**
 * ���ݾ���d��·������path���·���������Ͳ���Ҫ·���Ľڵ���Ҳ����ȷ���·��
 * @param d ·������
 * @param path ����·��������
 * @param g ͼ
 */
void printPath(int d, int *path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s ", g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[path[k]]);
}

/**
 * �ж�ͼ�Ƿ���ͨ
 * @param g ͼ
 * @return ��ͨ����1�����򷵻�0
 */
int isConnected(Graph g) {
    int i, j, visited[max_dis] ; //i��jΪѭ������������visited��¼�ڵ��Ƿ񱻷���
    //visited�����ʼ��
    for( i = 0 ; i < g.N ; i++ )
        visited[i] = 0 ;
    //������ȱ���
    DFS(g, 0, visited) ;
    //������ȱ������������δ�����ʵĽڵ㣬��ͼ����ͨ��������ͨ
    for( j = 0 ; j < g.N ; j++ )
    {
        if( visited[j] != 1 )
            return 0 ;
    }
    return 1 ;
}

/**
 * ������ȱ���
 * @param g ͼ
 * @param v ͼ�����
 * @param visited[] ��¼�ڵ��Ƿ񱻷��ʵ�����
 */
void DFS(Graph g, int v, int visited[]){
    int w ;
    visited[v] = 1 ;
    //�ӵ�һ���ڽӵ㿪ʼ������ݹ�ʹ��������ȱ�����ֱ�������ڽӵ㶼������Ϊֹ
    for( w = FirstNeighbor(g, v); w >= 0 ; w = NextNeighbor(g, v, w))
    {
        if( visited[w] != 1 )
            DFS(g, w, visited) ;
    }
}

/**
 * �ҵ��ڵ�ĵ�һ���ڽӵ�
 * @param g ͼ
 * @param v �ڵ�
 * @return �ҵ��򷵻ص�һ���ڽӵ����ţ����򷵻�-1
 */
int FirstNeighbor(Graph g, int v){
    int i ;
    for( i = 0 ; i < g.N ; i++ )
    {
        if( g.matrix[v][i] != max_dis )
            return i ;
    }
    return -1 ;
}

/**
 * �ҵ��ڵ�ĵ�ǰ�ڽӵ����һ���ڽӵ�
 * @param g ͼ
 * @param v �ڵ�
 * @param w �ڵ�ĵ�ǰ�ڽӵ�
 * @return �ҵ��򷵻��ڽӵ����ţ����򷵻�-1
 */
int NextNeighbor(Graph g, int v, int w){
    int i ;
    for( i = w + 1 ; i < g.N ; i++ )
    {
        if( g.matrix[v][i] != max_dis )
            return i ;
    }
    return -1 ;
}

/**
 * ����ÿ����Ķ�
 * @param g ͼ
 * @param node_degree ��ÿ����Ķ�д�����������
 */
void nodeDegree(Graph g, int *node_degree) {
    int counter, v, w ;
    for( v = 0 ; v < g.N ; v++ )
    {
        counter = 0 ;
        for( w = 0 ; w < g.N ; w++ )
        {
            //ȨֵС��max_dis���������һ
            if( g.matrix[v][w] != max_dis )
                counter++ ;
        }
        node_degree[v] = counter - 1 ; //д������
    }
}

/**
 * ����ͼ�ľ���ϵ��
 * @param g ͼ
 * @return ���ؾ���ϵ��
 */
double clusteringCoefficient(Graph g) {
    int v, w, i, j, k, m, counter, degree, node[g.N][g.N] ;
    double cluster, p, n ;
    cluster = 0 ;
    //��ÿһ���ڵ�v
    for( v = 0 ; v < g.N ; v++ )
    {
        counter = 0 ;
        //��v����Ľڵ�w
        for( w = 0 ; w < g.N ; w++ )
        {
            if( g.matrix[v][w] > 0 && g.matrix[v][w] != max_dis )
            {
                node[v][counter] = w ;
                counter++ ;
            }
        }
        //������ڵ�v�Ķ�
        degree = counter ;
        //n��¼�ڵ�v���ڽӵ�֮��ߵ�����
        n = 0 ;
        for( i = 0 ; i < degree ; i++ )
        {
            k = node[v][i] ;
            for( j = i + 1 ; j < degree ; j++ )
            {
                m = node[v][j] ;
                if( g.matrix[k][m] < max_dis )
                    n++ ;
            }

        }
        //�������ϵ��
        p = degree * ( degree - 1 ) / 2 ;
        if( p != 0 )
            cluster += n/p ;
    }
    return cluster/g.N ;
}

/**
 * ʹ��dijkstra�㷨���㵥Դ���·��
 * @param g ͼ
 * @param start ���
 * @param end �յ�
 * @param path ��start��end��·��, [start,...,end]
 * @return ·������
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //��ʼ��
    //SΪ���·���Ľ��������ʼʱֻ��Դ�ڵ�
    //D��¼Դ�㵽ͼ�и����ڵ�����·����ֵ
    int i, j, k, w, e, S[g.N], D[g.N], p[max_dis], path1[max_dis] ;
    for( i = 0 ; i < g.N ; i++ )
    {
        S[i] = 0 ; //1��ʾ��·���У�0��ʾ����·����
        D[i] = g.matrix[start][i] ; //��ʼʱ�����ڽӾ���Դ�������ж�Ӧ��ֵ
        p[i] = D[i] < max_dis ? start : -1 ; //��ʼ��·������
    }
    //Դ�����·��
    S[start] = 1 ;
    D[start] = 0 ;
    //�����·��������S��
    for( i = 1 ; i < g.N ; i++ )
    {
        int min = max_dis ;
        int temp ;
        //�ҵ�D����Сֵ��Ӧ�Ľڵ�
        for( w = 0 ; w < g.N ; w++ )
        {
            if( S[w] == 0 && D[w] < min )
            {
                temp = w ;
                min = D[w] ;
            }
        }
        //����·��
        S[temp] = 1 ;
        //���´�Դ����������������·��
        for( w = 0 ; w < g.N ; w++ )
        {
            if( S[w] == 0 && D[temp] + g.matrix[temp][w] < D[w] )
            {
                D[w] = D[temp] + g.matrix[temp][w] ;
                p[w] = temp ; //�޸�w��ǰ��Ϊtemp
            }
        }
    }
    path1[0] = end ;
    e = end ;
    i = 1 ;
    while( e != start )
    {
        path1[i] = p[e] ;
        e = p[e] ;
        i++ ;
    }
    k = i - 1 ;
    for( j = 0 ; j <= i ; j++ )
    {
        path[j] = path1[k] ;
        k-- ;
    }
    return D[end] ;
}

/**
 * ����ͼ��ֱ���Ͱ뾶����ʾ: Floyd�㷨
 * @param g ͼ
 * @param diameter ָ��ֱ��������ָ��
 * @param radius ָ��뾶������ָ��
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    int max, matrix1[g.N][g.N], Ecc[g.N] ; //����matrix1����g.matrix,����Ecc��¼���ڵ��������
    int i, j, k ; //ѭ������
    //���鸴��
    for( i = 0 ; i < g.N ; i++ )
    {
        for( j = 0 ; j < g.N ; j++ )
        {
            matrix1[i][j] = g.matrix[i][j] ;
        }
    }
    //Floyd�����㷨
    for( k = 0 ; k < g.N ; k++ )
    {
        for( i = 0 ; i < g.N ; i++ )
        {
            for( j = 0 ; j < g.N ; j++ )
            {
                if( matrix1[i][j] > matrix1[i][k] + matrix1[k][j] )
                    matrix1[i][j] = matrix1[i][k] + matrix1[k][j] ;
            }
        }
    }
    //������ڵ������ʣ���¼������Ecc��
    for( i = 0 ; i < g.N ; i++ )
    {
        max = 0 ;
        for( j = 0 ; j < g.N ; j++ )
        {
            if( matrix1[i][j] > max )
                max = matrix1[i][j] ;
        }
        Ecc[i] = max ;
    }
    //�Ƚϸ��ڵ�������ʣ����ֵ����diameter����Сֵ����radius
    *diameter = 0 ;
    *radius = max_dis ;
    for( i = 0 ; i < g.N ; i++ )
    {
        if( Ecc[i] > *diameter )
            *diameter = Ecc[i] ;
        if( Ecc[i] < *radius )
            *radius = Ecc[i] ;
    }

}



int main() {
    int node_num;
    int edge_num;
    int ca = 1;
    int i;
    if (freopen("stu.in", "r", stdin) == NULL) {
        printf("There is an error in reading file stu.in");
    }
    while (scanf("%d %d\n", &node_num, &edge_num) != EOF) {
        printf("\ncase %d:\n", ca++);
        int start_idx, end_idx, weight;
        Graph g = createGraph(node_num);
        for( i = 0; i < node_num; i++) {
            sprintf(g.vertex[i], "%d", i);
        }
        for ( i = 0; i < edge_num; i++) {
            scanf("%d %d %d\n", &start_idx, &end_idx, &weight);
            g.matrix[start_idx][end_idx] = weight;
            g.matrix[end_idx][start_idx] = weight;
        }

        printf("connected: %d\n", isConnected(g));

        int *degree = (int *)malloc(sizeof(int) * g.N);
        nodeDegree(g, degree);
        printf("degree distribution:\n");
        for( i=0; i<g.N; i++)
        {
            printf("node%s:%d,", g.vertex[i], degree[i]);
        }
        printf("\n");
        free(degree);

        double c = clusteringCoefficient(g);
        printf("clustering coefficient:%f\n", c);

        if(isConnected(g))
        {
            int *short_path = (int *)malloc(sizeof(int) * g.N);
            int dis = dijkstra(g, 1, 3, short_path);
            printf("the shortest path between 1 and 3: %d\n", dis);
            printPath(dis, short_path, g);
            free(short_path);

            int diameter, radius;
            computeEcc(g, &diameter, &radius);
            printf("diameter:%d\n", diameter);
            printf("radius:%d\n", radius);
        }
    }

    return 0;
}
