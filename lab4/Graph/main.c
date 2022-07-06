#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
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
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
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
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param path 储存路径的数组
 * @param g 图
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
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    int i, j, visited[max_dis] ; //i和j为循环参数，数组visited记录节点是否被访问
    //visited数组初始化
    for( i = 0 ; i < g.N ; i++ )
        visited[i] = 0 ;
    //深度优先遍历
    DFS(g, 0, visited) ;
    //深度优先遍历后如果存在未被访问的节点，则图不连通，否则连通
    for( j = 0 ; j < g.N ; j++ )
    {
        if( visited[j] != 1 )
            return 0 ;
    }
    return 1 ;
}

/**
 * 深度优先遍历
 * @param g 图
 * @param v 图的起点
 * @param visited[] 记录节点是否被访问的数组
 */
void DFS(Graph g, int v, int visited[]){
    int w ;
    visited[v] = 1 ;
    //从第一个邻接点开始，对其递归使用深度优先遍历，直到所有邻接点都被访问为止
    for( w = FirstNeighbor(g, v); w >= 0 ; w = NextNeighbor(g, v, w))
    {
        if( visited[w] != 1 )
            DFS(g, w, visited) ;
    }
}

/**
 * 找到节点的第一个邻接点
 * @param g 图
 * @param v 节点
 * @return 找到则返回第一个邻接点的序号，否则返回-1
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
 * 找到节点的当前邻接点的下一个邻接点
 * @param g 图
 * @param v 节点
 * @param w 节点的当前邻接点
 * @return 找到则返回邻接点的序号，否则返回-1
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
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    int counter, v, w ;
    for( v = 0 ; v < g.N ; v++ )
    {
        counter = 0 ;
        for( w = 0 ; w < g.N ; w++ )
        {
            //权值小于max_dis则计数器加一
            if( g.matrix[v][w] != max_dis )
                counter++ ;
        }
        node_degree[v] = counter - 1 ; //写入数组
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    int v, w, i, j, k, m, counter, degree, node[g.N][g.N] ;
    double cluster, p, n ;
    cluster = 0 ;
    //对每一个节点v
    for( v = 0 ; v < g.N ; v++ )
    {
        counter = 0 ;
        //除v以外的节点w
        for( w = 0 ; w < g.N ; w++ )
        {
            if( g.matrix[v][w] > 0 && g.matrix[v][w] != max_dis )
            {
                node[v][counter] = w ;
                counter++ ;
            }
        }
        //计算出节点v的度
        degree = counter ;
        //n记录节点v的邻接点之间边的条数
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
        //计算聚类系数
        p = degree * ( degree - 1 ) / 2 ;
        if( p != 0 )
            cluster += n/p ;
    }
    return cluster/g.N ;
}

/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //初始化
    //S为最短路径的结果集，初始时只有源节点
    //D记录源点到图中各个节点的最短路径的值
    int i, j, k, w, e, S[g.N], D[g.N], p[max_dis], path1[max_dis] ;
    for( i = 0 ; i < g.N ; i++ )
    {
        S[i] = 0 ; //1表示在路径中，0表示不在路径中
        D[i] = g.matrix[start][i] ; //初始时等于邻接矩阵源点所在行对应的值
        p[i] = D[i] < max_dis ? start : -1 ; //初始化路径数组
    }
    //源点加入路径
    S[start] = 1 ;
    D[start] = 0 ;
    //求最短路径并加入S集
    for( i = 1 ; i < g.N ; i++ )
    {
        int min = max_dis ;
        int temp ;
        //找到D中最小值对应的节点
        for( w = 0 ; w < g.N ; w++ )
        {
            if( S[w] == 0 && D[w] < min )
            {
                temp = w ;
                min = D[w] ;
            }
        }
        //加入路径
        S[temp] = 1 ;
        //更新从源点出发至其余点的最短路径
        for( w = 0 ; w < g.N ; w++ )
        {
            if( S[w] == 0 && D[temp] + g.matrix[temp][w] < D[w] )
            {
                D[w] = D[temp] + g.matrix[temp][w] ;
                p[w] = temp ; //修改w的前继为temp
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
 * 计算图的直径和半径，提示: Floyd算法
 * @param g 图
 * @param diameter 指向直径变量的指针
 * @param radius 指向半径变量的指针
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    int max, matrix1[g.N][g.N], Ecc[g.N] ; //数组matrix1复制g.matrix,数组Ecc记录各节点的离心率
    int i, j, k ; //循环参数
    //数组复制
    for( i = 0 ; i < g.N ; i++ )
    {
        for( j = 0 ; j < g.N ; j++ )
        {
            matrix1[i][j] = g.matrix[i][j] ;
        }
    }
    //Floyd核心算法
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
    //计算各节点离心率，记录在数组Ecc中
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
    //比较各节点的离心率，最大值赋给diameter，最小值赋给radius
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
