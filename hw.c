// Hana Lee 40847074
// Rebecca Huang 42285382

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHAR 80
#define HEAP_SIZE 127

int heap[HEAP_SIZE] = {0};


int free_block(int size){
    int current_addr = 0;
    int free_addr = 0;
    int split_addr = 0;
    
    while (current_addr < HEAP_SIZE){
        // if current block is equals size
        if (heap[current_addr] == size && heap[current_addr + 1] == 0) {
            malloc(size, current_addr);
            return current_addr;
        }
        // if current block equals size but is allocated, skip over
        else if (heap[current_addr] == size && heap[current_addr + 1] == 1) {
            current_addr += heap[current_addr];
        }
        // if current block too small, just skip over
        else if (heap[current_addr] < size) {
            current_addr += heap[current_addr];
        }
        // if current block too big and not allocation, split and malloc
        else if (heap[current_addr] > size) {
            split_addr = current_addr;
        }
    }
    if (current_addr == 0) {
        return split(size, split_addr);
    }
    return -1;
}

int split(int size, int addr){
    
}

int malloc(int size, int addr){
    int i;
    heap[addr] = size;
    heap[addr + size - 1] = size;

    for (i = addr + 1; i < addr + size; i++) {
        heap[i] = 1;
    }
}

int free_memory(int addr) {
    int size = heap[addr] + 2;
    int i;

    for (i = addr + 1; i < addr + size; i++) {
        heap[i] = 0;
    }
    return 1;
}


int main(int argc, char* argv[]) {
    while (!NULL) {
        // parse through input
        char line[MAX_CHAR];
        char* args[13];

        fputs(">", stdout);
        fgets(line, sizeof(line), stdin);

        int arg_count = 0;
        char* token = strtok(line, " \n");
        while (token != NULL){
            args[arg_count] = token;
            token = strtok(NULL, " \n");
            arg_count++;
        }
        args[arg_count] = NULL;


        if (strcmp(args[0], "quit") == 0){
            break;
        }

        else if (strcmp(args[0], "malloc") == 0) {
            int addr = free_block(atoi(args[1]) + 2);
            if (addr != -1) {
                printf("%d", addr + 1);
            }
        }

        else if (strcmp(args[0], "free") == 0) {
            int addr = atoi(args[1]);
            free_memory(addr);
        }

        else if (strcmp(args[0], "blocklist") == 0) {
           
        }

        else if (strcmp(args[0], "writemem") == 0) {
            int addr = atoi(args[1]);
            char * text = args[2];
        }

        else if (strcmp(args[0], "printmem") == 0) {
            int addr = atoi(args[1]);
            int num_chars_to_print = args[2];
        }     
    }
    return 0;
}