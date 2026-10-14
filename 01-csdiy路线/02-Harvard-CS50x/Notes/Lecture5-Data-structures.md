## 1-数组基础操作

```c
#include <stdio.h>
#include <stdlib.h>

int find(int arr[], int size, int target){
    for (int i = 0; i < size; i++){
        if (arr[i] == target){
            return i;
        }
    }
    return -1;
}

void insert_at(int arr[], int *size, int pos, int value){
    for (int i = *size; i > pos; i--){
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
    (*size)++;
}

void delete_at(int arr[], int *size, int pos){
    for (int i = pos; i < *size - 1; i++){
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

void selection_sort(int arr[], int size){
    for (int i = 0; i < size - 1; i++){
        int min_idx = i;
        for (int j = i + 1; j < size; j++){
            if (arr[j] < arr[min_idx]){
                min_idx = j;
            }
        }
        int tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

void bubble_sort(int arr[], int size){
    for (int i = 0; i < size - 1; i++){
        int swapped = 0;
        for (int j = 0; j < size - 1 - i; j++){
            if (arr[j] > arr[j + 1]){
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped){
            break;
        }
    }
}

int binary_search(int arr[], int size, int target){
    int low = 0, high = size - 1;
    while (low <= high){
        int mid = low + (high - low) / 2;
        if (arr[mid] == target){
            return mid;
        }
        else if (arr[mid] < target){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}

// 扩容：返回新数组地址，调用者负责用返回值覆盖原指针
int *expand(int *old, int old_size, int new_size){
    int *bigger = malloc(sizeof(int) * new_size);
    if (bigger == NULL){
        return NULL;
    }
    for (int i = 0; i < old_size; i++){
        bigger[i] = old[i];
    }
    free(old);
    return bigger;
}
```

---

## 2-字符串工具

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void str_to_upper(char *s){
    for (int i = 0; s[i] != '\0'; i++){
        s[i] = toupper(s[i]);
    }
}

void str_to_lower(char *s){
    for (int i = 0; s[i] != '\0'; i++){
        s[i] = tolower(s[i]);
    }
}

void remove_newline(char *s){
    s[strcspn(s, "\n")] = '\0';
}

int count_substr(const char *s, const char *p){
    if (p[0] == '\0'){
        return 0;
    }
    int cnt = 0;
    int plen = strlen(p);
    const char *q = s;
    while ((q = strstr(q, p)) != NULL){
        cnt++;
        q += plen;
    }
    return cnt;
}

void split_demo(char *s){
    char *token = strtok(s, ",");
    while (token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
}
```

---

## 3-栈

```c
#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 50

typedef struct{
    int data[CAPACITY];
    int size;
} stack;

bool is_empty(stack *s){
    return s->size == 0;
}

bool is_full(stack *s){
    return s->size == CAPACITY;
}

void push(stack *s, int v){
    if (s->size < CAPACITY){
        s->data[s->size] = v;
        s->size++;
    }
}

int pop(stack *s){
    if (s->size == 0){
        return -1;
    }
    s->size--;
    return s->data[s->size];
}

int peek(stack *s){
    if (s->size == 0){
        return -1;
    }
    return s->data[s->size - 1];
}

int size_of_stack(stack *s){
    return s->size;
}

void clear_stack(stack *s){
    s->size = 0;
}
```

---

## 4-队列

```c
#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 50

typedef struct{
    int data[CAPACITY];
    int size;
} queue;

bool is_empty(queue *q){
    return q->size == 0;
}

bool is_full(queue *q){
    return q->size == CAPACITY;
}

void enqueue(queue *q, int v){
    if (q->size < CAPACITY){
        q->data[q->size] = v;
        q->size++;
    }
}

int dequeue(queue *q){
    if (q->size == 0){
        return -1;
    }
    int front = q->data[0];
    for (int i = 0; i < q->size - 1; i++){
        q->data[i] = q->data[i + 1];
    }
    q->size--;
    return front;
}

int front(queue *q){
    if (q->size == 0){
        return -1;
    }
    return q->data[0];
}

int back(queue *q){
    if (q->size == 0){
        return -1;
    }
    return q->data[q->size - 1];
}

void clear_queue(queue *q){
    q->size = 0;
}
```

---

## 5-循环队列

```c
#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 50

typedef struct{
    int data[CAPACITY];
    int head;
    int tail;
    int size;
} circular_queue;

void enqueue_cirq(circular_queue *q, int v){
    if (q->size < CAPACITY){
        q->data[q->tail] = v;
        q->tail = (q->tail + 1) % CAPACITY;
        q->size++;
    }
}

int dequeue_cirq(circular_queue *q){
    if (q->size == 0){
        return -1;
    }
    int v = q->data[q->head];
    q->head = (q->head + 1) % CAPACITY;
    q->size--;
    return v;
}
```

---

## 6-链表

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int number;
    struct node *next;
} node;

void push_front(node **head, int value){
    node *n = malloc(sizeof(node));
    if (n == NULL){
        return;
    }
    n->number = value;
    n->next = *head;
    *head = n;
}

void append(node **head, int value){
    node *n = malloc(sizeof(node));
    if (n == NULL){
        return;
    }
    n->number = value;
    n->next = NULL;
    if (*head == NULL){
        *head = n;
        return;
    }
    node *ptr = *head;
    while (ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = n;
}

void insert_sorted(node **head, int value){
    node *n = malloc(sizeof(node));
    if (n == NULL){
        return;
    }
    n->number = value;
    if (*head == NULL || (*head)->number >= value){
        n->next = *head;
        *head = n;
        return;
    }
    node *ptr = *head;
    while (ptr->next != NULL && ptr->next->number < value){
        ptr = ptr->next;
    }
    n->next = ptr->next;
    ptr->next = n;
}

int length(node *head){
    int count = 0;
    for (node *p = head; p != NULL; p = p->next){
        count++;
    }
    return count;
}

void delete_value(node **head, int value){
    node *ptr = *head;
    node *prev = NULL;
    while (ptr != NULL){
        if (ptr->number == value){
            if (prev == NULL){
                *head = ptr->next;
            }
            else{
                prev->next = ptr->next;
            }
            free(ptr);
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}

void delete_all(node **head, int value){
    node *ptr = *head;
    node *prev = NULL;
    while (ptr != NULL){
        if (ptr->number == value){
            node *next = ptr->next;
            if (prev == NULL){
                *head = next;
            }
            else{
                prev->next = next;
            }
            free(ptr);
            ptr = next;
        }
        else{
            prev = ptr;
            ptr = ptr->next;
        }
    }
}

node *reverse(node *head){
    node *prev = NULL;
    while (head != NULL){
        node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

node *merge_lists(node *a, node *b){
    if (a == NULL){
        return b;
    }
    if (b == NULL){
        return a;
    }
    node *ptr = a;
    while (ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = b;
    return a;
}

void free_list(node *head){
    while (head != NULL){
        node *next = head->next;
        free(head);
        head = next;
    }
}
```

---

## 7-二叉搜索树

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_node{
    int number;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

tree_node *insert(tree_node *root, int value){
    if (root == NULL){
        tree_node *n = malloc(sizeof(tree_node));
        if (n == NULL){
            return NULL;
        }
        n->number = value;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    if (value < root->number){
        root->left = insert(root->left, value);
    }
    else if (value > root->number){
        root->right = insert(root->right, value);
    }
    return root;
}

bool search(tree_node *root, int value){
    if (root == NULL){
        return false;
    }
    if (root->number == value){
        return true;
    }
    if (value < root->number){
        return search(root->left, value);
    }
    return search(root->right, value);
}

tree_node *find_min(tree_node *root){
    while (root != NULL && root->left != NULL){
        root = root->left;
    }
    return root;
}

tree_node *find_max(tree_node *root){
    while (root != NULL && root->right != NULL){
        root = root->right;
    }
    return root;
}

void inorder(tree_node *root){
    if (root == NULL){
        return;
    }
    inorder(root->left);
    printf("%d ", root->number);
    inorder(root->right);
}

void preorder(tree_node *root){
    if (root == NULL){
        return;
    }
    printf("%d ", root->number);
    preorder(root->left);
    preorder(root->right);
}

void postorder(tree_node *root){
    if (root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->number);
}

int height(tree_node *root){
    if (root == NULL){
        return 0;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

int count_nodes(tree_node *root){
    if (root == NULL){
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void free_tree(tree_node *root){
    if (root == NULL){
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

tree_node *delete_node(tree_node *root, int value){
    if (root == NULL){
        return NULL;
    }
    if (value < root->number){
        root->left = delete_node(root->left, value);
    }
    else if (value > root->number){
        root->right = delete_node(root->right, value);
    }
    else{
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        if (root->left == NULL){
            tree_node *tmp = root->right;
            free(root);
            return tmp;
        }
        if (root->right == NULL){
            tree_node *tmp = root->left;
            free(root);
            return tmp;
        }
        tree_node *succ = find_min(root->right);
        root->number = succ->number;
        root->right = delete_node(root->right, succ->number);
    }
    return root;
}
```

---

## 8-字典树 Trie

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define ALPHA 26

typedef struct trie_node{
    struct trie_node *children[ALPHA];
    bool is_word;
} trie_node;

trie_node *trie_new(){
    return calloc(1, sizeof(trie_node));
}

void trie_insert(trie_node *root, const char *word){
    trie_node *cur = root;
    for (int i = 0; word[i] != '\0'; i++){
        int idx = tolower(word[i]) - 'a';
        if (cur->children[idx] == NULL){
            cur->children[idx] = calloc(1, sizeof(trie_node));
        }
        cur = cur->children[idx];
    }
    cur->is_word = true;
}

bool trie_search(trie_node *root, const char *word){
    trie_node *cur = root;
    for (int i = 0; word[i] != '\0'; i++){
        int idx = tolower(word[i]) - 'a';
        if (cur->children[idx] == NULL){
            return false;
        }
        cur = cur->children[idx];
    }
    return cur->is_word;
}

bool trie_starts_with(trie_node *root, const char *prefix){
    trie_node *cur = root;
    for (int i = 0; prefix[i] != '\0'; i++){
        int idx = tolower(prefix[i]) - 'a';
        if (cur->children[idx] == NULL){
            return false;
        }
        cur = cur->children[idx];
    }
    return true;
}

void trie_free(trie_node *root){
    if (root == NULL){
        return;
    }
    for (int i = 0; i < ALPHA; i++){
        trie_free(root->children[i]);
    }
    free(root);
}
```

---

## 9-哈希表 固定桶数

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define N 26

typedef struct hash_node{
    char *name;
    char *number;
    struct hash_node *next;
} hash_node;

hash_node *table[N];
int total_count = 0;

unsigned int hash(const char *name){
    return toupper(name[0]) - 'A';
}

void hash_init(){
    for (int i = 0; i < N; i++){
        table[i] = NULL;
    }
    total_count = 0;
}

bool hash_insert(const char *name, const char *number){
    unsigned int idx = hash(name);
    for (hash_node *p = table[idx]; p != NULL; p = p->next){
        if (strcmp(p->name, name) == 0){
            return false;
        }
    }
    hash_node *n = malloc(sizeof(hash_node));
    if (n == NULL){
        return false;
    }
    n->name = malloc(strlen(name) + 1);
    n->number = malloc(strlen(number) + 1);
    if (n->name == NULL || n->number == NULL){
        free(n->name);
        free(n->number);
        free(n);
        return false;
    }
    strcpy(n->name, name);
    strcpy(n->number, number);
    n->next = table[idx];
    table[idx] = n;
    total_count++;
    return true;
}

char *hash_lookup(const char *name){
    unsigned int idx = hash(name);
    for (hash_node *p = table[idx]; p != NULL; p = p->next){
        if (strcmp(p->name, name) == 0){
            return p->number;
        }
    }
    return NULL;
}

bool hash_delete(const char *name){
    unsigned int idx = hash(name);
    hash_node *ptr = table[idx];
    hash_node *prev = NULL;
    while (ptr != NULL){
        if (strcmp(ptr->name, name) == 0){
            if (prev == NULL){
                table[idx] = ptr->next;
            }
            else{
                prev->next = ptr->next;
            }
            free(ptr->name);
            free(ptr->number);
            free(ptr);
            total_count--;
            return true;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return false;
}

void hash_unload(){
    for (int i = 0; i < N; i++){
        hash_node *ptr = table[i];
        while (ptr != NULL){
            hash_node *next = ptr->next;
            free(ptr->name);
            free(ptr->number);
            free(ptr);
            ptr = next;
        }
        table[i] = NULL;
    }
    total_count = 0;
}
```

---

## 10-哈希表 动态桶数 + rehash

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct hash_node{
    char *name;
    char *number;
    struct hash_node *next;
} hash_node;

int bucket_count = 26;
hash_node **table;
int total_count = 0;

unsigned int hash_general(const char *name, int buckets){
    unsigned int h = 0;
    for (int i = 0; name[i] != '\0'; i++){
        h = h * 31 + (unsigned char)name[i];
    }
    return h % buckets;
}

void hash_init(){
    table = calloc(bucket_count, sizeof(hash_node *));
    total_count = 0;
}

void rehash(int new_bucket_count){
    hash_node **new_table = calloc(new_bucket_count, sizeof(hash_node *));
    if (new_table == NULL){
        return;
    }
    for (int i = 0; i < bucket_count; i++){
        hash_node *ptr = table[i];
        while (ptr != NULL){
            hash_node *next = ptr->next;
            unsigned int new_idx = hash_general(ptr->name, new_bucket_count);
            ptr->next = new_table[new_idx];
            new_table[new_idx] = ptr;
            ptr = next;
        }
    }
    free(table);
    table = new_table;
    bucket_count = new_bucket_count;
}

bool hash_insert(const char *name, const char *number){
    unsigned int idx = hash_general(name, bucket_count);
    for (hash_node *p = table[idx]; p != NULL; p = p->next){
        if (strcmp(p->name, name) == 0){
            return false;
        }
    }
    hash_node *n = malloc(sizeof(hash_node));
    if (n == NULL){
        return false;
    }
    n->name = malloc(strlen(name) + 1);
    n->number = malloc(strlen(number) + 1);
    if (n->name == NULL || n->number == NULL){
        free(n->name);
        free(n->number);
        free(n);
        return false;
    }
    strcpy(n->name, name);
    strcpy(n->number, number);
    n->next = table[idx];
    table[idx] = n;
    total_count++;
    if ((double)total_count / bucket_count > 0.75){
        rehash(bucket_count * 2);
    }
    return true;
}

char *hash_lookup(const char *name){
    unsigned int idx = hash_general(name, bucket_count);
    for (hash_node *p = table[idx]; p != NULL; p = p->next){
        if (strcmp(p->name, name) == 0){
            return p->number;
        }
    }
    return NULL;
}

bool hash_delete(const char *name){
    unsigned int idx = hash_general(name, bucket_count);
    hash_node *ptr = table[idx];
    hash_node *prev = NULL;
    while (ptr != NULL){
        if (strcmp(ptr->name, name) == 0){
            if (prev == NULL){
                table[idx] = ptr->next;
            }
            else{
                prev->next = ptr->next;
            }
            free(ptr->name);
            free(ptr->number);
            free(ptr);
            total_count--;
            return true;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return false;
}

void hash_unload(){
    for (int i = 0; i < bucket_count; i++){
        hash_node *ptr = table[i];
        while (ptr != NULL){
            hash_node *next = ptr->next;
            free(ptr->name);
            free(ptr->number);
            free(ptr);
            ptr = next;
        }
        table[i] = NULL;
    }
    free(table);
    table = NULL;
    total_count = 0;
    bucket_count = 26;
}
```

---

## 11-哈希表字典

```c
void dict_put(const char *key, const char *value){
    hash_insert(key, value);
}

char *dict_get(const char *key){
    return hash_lookup(key);
}

bool dict_contains(const char *key){
    return hash_lookup(key) != NULL;
}

void dict_remove(const char *key){
    hash_delete(key);
}

int dict_size(){
    return total_count;
}

void dict_unload(){
    hash_unload();
}
```