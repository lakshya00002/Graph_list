#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20

typedef struct Node {
    int vertex;
    struct Node* next; 
} Node;

typedef struct {
    int num_vertices;
    Node **adj_list; 
} GraphList;

typedef struct {
    int items[MAXSIZE];
    int rear;
    int front; 
} Queue;

Queue *create_queue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int is_empty(Queue* queue) {
    return ((queue->front == -1) && (queue->rear == -1)) || (queue->front > queue->rear);
}

int is_full(Queue* queue) {
    return queue->rear == MAXSIZE - 1;
}

void enqueue(Queue* queue, int element) {
    if(is_full(queue)) {
        printf("Cannot enqueue. Queue is full");
    }
    else {
        queue->items[++queue->rear] = element;
        if(queue->front == -1) 
            queue->front = 0;
    }
}

void dequeue(Queue* queue) {
    if(is_empty(queue)) {
        printf("Cannot dequeue. Queue is empty");
    }
    else {
        for (int i = queue->front; i < queue->rear; i++) {
            queue->items[i] = queue->items[i + 1];
        }
        queue->rear--;

        if(queue->front > queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        }
    }
}

void destroy(Queue* queue) {
    free(queue);
}

GraphList* create_graph_list(int vertices) {
    GraphList* graph = malloc(sizeof(GraphList));
    graph->num_vertices = vertices;
    graph->adj_list = malloc(sizeof(Node*) * vertices);

    for(int i = 0; i < graph->num_vertices; i++) {
        graph->adj_list[i] = NULL;
    }

    return graph;
}

int add_edge_list(GraphList* graph, int src, int dest) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adj_list[src];
    graph->adj_list[src] = newNode;

    newNode = malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adj_list[dest];
    graph->adj_list[dest] = newNode;

    return 0;
}

int bfs_iterative(GraphList *graph, int start_vertex) {
    int curr_vertex;
    int visited[graph->num_vertices];
    for(int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }
    Queue *queue = create_queue();
    enqueue(queue, start_vertex);
    while(!is_empty(queue)) {
        curr_vertex = queue->items[queue->front];
        dequeue(queue);
        if(!visited[curr_vertex]) {
            visited[curr_vertex] = 1;
            printf("Visited %d \n", curr_vertex);
        }
        Node* temp = graph->adj_list[curr_vertex];
        while(temp != NULL) {
             int adj_vertex = temp->vertex;
             if(!visited[adj_vertex]) {
                enqueue(queue, adj_vertex);
             }
             temp = temp->next;
        }
    }
    destroy(queue);
    return 0; 
}

int main() {
    GraphList *graph = create_graph_list(5);
    add_edge_list(graph, 0, 1);
    add_edge_list(graph, 0, 2);
    add_edge_list(graph, 0, 3);
    add_edge_list(graph, 3, 4);
    add_edge_list(graph, 1, 2);
    bfs_iterative(graph, 0);

    return 0;
}


