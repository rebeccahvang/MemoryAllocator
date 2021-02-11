// Hana Lee 40847074
// Rebecca Huang 42285382

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHAR 80
#define HEAP_SIZE 127

uint8_t heap[HEAP_SIZE];


int free_block(int size){
    int current_ind = 0;
    int free_addr = 0;
    int split_addr = 0;

    // gives us size (including header + footer) and address of header
    while (current_ind < HEAP_SIZE) {
        uint8_t current_binary = heap[current_ind];
        
        // check if block is free
        if ((int) (current_binary & 1) == 0){
            int current_size = current_binary >> 1;
            if (current_size >= size) {
                return current_ind;
            }
        }        
    }

    // gives us size (including header + footer) and address of header
    // while (current_addr < HEAP_SIZE){
    //     // if current block is equals size
    //     if (heap[current_addr] == size && heap[current_addr + 1] == 0) {
    //         malloc(size, current_addr);
    //         return current_addr;
    //     }
    //     // if current block equals size but is allocated, skip over
    //     else if (heap[current_addr] == size && heap[current_addr + 1] == 1) {
    //         current_addr += heap[current_addr];
    //     }
    //     // if current block too small, just skip over
    //     else if (heap[current_addr] < size) {
    //         current_addr += heap[current_addr];
    //     }
    //     // if current block too big and not allocation, split and malloc
    //     else if (heap[current_addr] > size && heap[current_addr + 1] == 0) {
    //         split_addr = current_addr;
    //         current_addr += heap[split_addr];
    //     }
    // }
    // // if only option is to split
    // if (split_addr != 0) {
    //     return split(size, split_addr);
    // }
    return -1;
}

int split(int size, int addr){
    int total_size = heap[addr];
    // call malloc to set new header/footer
    malloc(size, addr);

    // relabel header/footer of remaining blocks
    heap[addr + size + 1] = total_size - size;
    heap[addr + total_size] = total_size - size;
}

// change header + footer, set payload equal to 1
int malloc(int size, int addr){
    int i;
    heap[addr] = size;
    heap[addr + size] = size;

    for (i = addr + 1; i < addr + size; i++) {
        heap[i] = 1;
    }
    return 0;
}

// get address of payload, free the blocks
int free_memory(int addr) {
    int size = heap[addr - 1];
    int i;

    // reset the entry indexes, leaving the header and footer
    for (i = addr; i < addr + size; i++) {
        heap[i] = 0;
    }

    // check forward coalescence
    if (heap[addr + size] == 0) {
        int next_header = addr + size - 1;
        int next_size = heap[next_header];
        // update header and footer to new size
        heap[addr - 1] = next_size + heap[addr - 1];
        heap[addr + size + next_size - 1] = next_header + next_size;
        heap[next_header] = 0;
    }

    // check backward coalescence
    if (heap[addr - 3] == 0){
        int prev_footer = addr - 2;
        int prev_size = heap[prev_footer];
        int prev_header = prev_footer - prev_size + 1;

        // reset previous header and current footer to new size 
        heap[prev_header] = prev_size + size;
        heap[addr + size - 1] = prev_size + size;

        // set things in between back to zero
        heap[addr - 1] = 0;
        heap[prev_footer] = 0;
    }

    return 0;
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
