#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

typedef struct {
    char character;
    char code[MAX_CHAR];
} HuffmanCode;

Node* nodes[MAX_CHAR];
int freq[MAX_CHAR];
int size = 0;
HuffmanCode huffmanCodes[MAX_CHAR];
int huffmanCodeCount = 0;

Node* createNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

void addFrequency(char character, int frequency) {
    freq[(unsigned char)character] = frequency;
}

Node* extractMin() {
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (nodes[i]->frequency < nodes[minIndex]->frequency) {
            minIndex = i;
        }
    }
    Node* minNode = nodes[minIndex];
    nodes[minIndex] = nodes[--size];
    return minNode;
}

void insertNode(Node* node) {
    nodes[size++] = node;
}

void buildHuffmanTree() {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            nodes[size++] = createNode((char)i, freq[i]);
        }
    }
    while (size > 1) {
        Node* left = extractMin();
        Node* right = extractMin();
        Node* combined = createNode('\0', left->frequency + right->frequency);
        combined->left = left;
        combined->right = right;
        insertNode(combined);
    }
}

void generateCodes(Node* root, char* code, int length) {
    if (root->left == NULL && root->right == NULL) {
        huffmanCodes[huffmanCodeCount].character = root->character;
        strncpy(huffmanCodes[huffmanCodeCount].code, code, length);
        huffmanCodes[huffmanCodeCount].code[length] = '\0';
        huffmanCodeCount++;
        return;
    }
    if (root->left != NULL) {
        code[length] = '0';
        generateCodes(root->left, code, length + 1);
    }
    if (root->right != NULL) {
        code[length] = '1';
        generateCodes(root->right, code, length + 1);
    }
}

void calculateHuffmanCodes() {
    buildHuffmanTree();
    char code[MAX_CHAR];
    huffmanCodeCount = 0;
    generateCodes(nodes[0], code, 0);
}

void printHuffmanCodes() {
    for (int i = 0; i < huffmanCodeCount; i++) {
        printf("%c com frequencia %d codificado como %s\n",
               huffmanCodes[i].character,
               freq[(unsigned char)huffmanCodes[i].character],
               huffmanCodes[i].code);
    }
}

char* encode(char* str) {
    static char encodedStr[MAX_CHAR * 8];
    encodedStr[0] = '\0';
    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < huffmanCodeCount; j++) {
            if (huffmanCodes[j].character == str[i]) {
                strcat(encodedStr, huffmanCodes[j].code);
                break;
            }
        }
    }
    return encodedStr;
}

char* decode(char* bits) {
    static char decodedStr[MAX_CHAR];
    Node* currentNode = nodes[0];
    int index = 0;
    for (int i = 0; bits[i]; i++) {
        if (bits[i] == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
        if (currentNode->left == NULL && currentNode->right == NULL) {
            decodedStr[index++] = currentNode->character;
            currentNode = nodes[0];
        }
    }
    decodedStr[index] = '\0';
    return decodedStr;
}

void clear() {
    for (int i = 0; i < MAX_CHAR; i++) {
        freq[i] = 0;
    }
    size = 0;
}

void compactationRates(char* str) {
    int originalBits = strlen(str) * 8;
    int huffmanBits = strlen(encode(str));
    printf("%s %d.%02d%% %d.%02d%%\n",
           encode(str),
           (huffmanBits * 100) / originalBits,
           (huffmanBits * 1000 / originalBits) % 10,
           (huffmanBits * 100) / (strlen(encode(str)) * 8),
           (huffmanBits * 1000 / (strlen(encode(str)) * 8)) % 10);
}

int main(int argc, char *argv[]) {
    char command[10];
    char character;
    int frequency;
    char str[MAX_CHAR];
    char bits[MAX_CHAR];

    while (1) {
        printf("->");
        scanf("%s", command);
        
        if (strcmp(command, "add") == 0) {
            scanf(" %c %d", &character, &frequency);
            addFrequency(character, frequency);
        } else if (strcmp(command, "calc") == 0) {
            calculateHuffmanCodes();
        } else if (strcmp(command, "print") == 0) {
            printHuffmanCodes();
        } else if (strcmp(command, "cod") == 0) {
            scanf("%s", str);
            printf("%s\n", encode(str));
            compactationRates(str);
        } else if (strcmp(command, "dec") == 0) {
            scanf("%s", bits);
            printf("%s\n", decode(bits));
        } else if (strcmp(command, "clear") == 0) {
            clear();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Comando não reconhecido.\n");
        }
    }

    return 0;
}
