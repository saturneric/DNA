//
//  main.c
//  DNA
//
//  Created by Eric on 15-9-12.
//  Copyright (c) 2015年 Bakantu Eric. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DNA_MAX 6
#define EARTH_MAX 1000000
#define CREATIVE_LIFE 5
#define DNA_DIFF 3
#define COPY_NUM 4
#define DIFF_NUM 10

int const best_dna[DNA_MAX] = {1,0,1,0,1,1};
int diff_dna = 100;
int enviroment_num = 0;

struct creative {
    int dna[DNA_MAX];
    int copy_n;
    int life;
    int diff_n;
} creative;

int add_creative(struct creative *a_creative[], int father_dna[DNA_MAX], int mother_dna[DNA_MAX]);
void creative_copy(struct creative *cc_creative[], int no);
void kill_creative(struct creative *k_creative[]);
int dna_done(struct creative *d_creative[]);
void dna_ability(struct creative *db_creative);

int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    struct creative *creatives[EARTH_MAX];
    int father[6] = {0,1,0,1,0,1}, mother[6] = {1,1,1,0,1,1};
    for (int i = 0; i < EARTH_MAX; i++) creatives[i] = NULL;
    
    
    {
    add_creative(creatives,father,mother);
    add_creative(creatives,mother,father);
    add_creative(creatives,mother,father);
    add_creative(creatives,mother,father);
    add_creative(creatives,mother,father);
    add_creative(creatives,mother,father);
    }
    
    
    int count = 0, ifdone = 0;
    while (!(ifdone = dna_done(creatives))){
        count = 0;
        for (int i = 0; i < EARTH_MAX; i++){
            if (creatives[i] != NULL){
                creative_copy(creatives, i);
                count++;
            }
        }
        kill_creative(creatives);
        printf("COUNT: %d\n",count);
        if (count == 0){
            add_creative(creatives,father,mother);
            add_creative(creatives,mother,father);
            add_creative(creatives,mother,father);
            add_creative(creatives,mother,father);
            add_creative(creatives,mother,father);
            add_creative(creatives,mother,father);
        }
    }
    return 0;
}

int dna_done (struct creative *d_creative[]){
    int done = 0,s_done = 0;
    for (int i = 0; i < EARTH_MAX; i++){
        for (int j = 0; j < DNA_MAX; j++){
            if (d_creative[i] != NULL){
                if (d_creative[i]->dna[j] != best_dna[j]) s_done = 0;
            }
            else{
                s_done = 0;
                continue;
            }
        }
        if (s_done == 1){
            done = i;
            break;
        }
        s_done = 1;
    }
    return done;
}

int add_creative(struct creative *a_creative[], int father_dna[DNA_MAX], int mother_dna[DNA_MAX]){
    int a_done = 0;
    srand((unsigned)time(NULL));
    for (int i = 0;i < EARTH_MAX; i++){
        if (a_creative[i] == NULL){
            a_done = 1;
            a_creative[i] = malloc(sizeof(struct creative));
            a_creative[i]->life = 0;
            int dna_cut = rand()%DNA_MAX, dna_fm = rand()%2;
            for (int j = 0; j < dna_cut; j++){
                if (dna_fm) a_creative[i]->dna[j] = father_dna[j];
                else a_creative[i]->dna[j] = mother_dna[j];
            }
            for (int j = dna_cut; j < DNA_MAX; j++){
                if(!dna_fm)a_creative[i]->dna[j] = father_dna[j];
                else a_creative[i]->dna[j] = mother_dna[j];
            }
            dna_ability(a_creative[i]);
            if ((rand()%(a_creative[i]->diff_n)) == (rand()%DNA_MAX)){
                a_creative[i]->dna[rand()%DNA_MAX] = rand()%2;
            }
            break;
        }
    }
    return a_done;
}

void dna_ability(struct creative *db_creative){
    int envir_same = 0,envir_diff = 0;
    for (int i = 0; i < DNA_MAX-DNA_DIFF; i++){
        if ((db_creative->dna[i]) == best_dna[i]) envir_same++;
    }
    db_creative->copy_n = COPY_NUM-envir_same;
    
    for (int i = DNA_MAX-DNA_DIFF; i < DNA_MAX; i++){
        if((db_creative->dna[i]) == best_dna[i]) envir_diff++;
    }
    db_creative->diff_n = DIFF_NUM-envir_diff;
}

void creative_copy(struct creative *cc_creative[],int no){
    srand((unsigned)time(NULL));
    if ((rand()%(cc_creative[no]->copy_n)) == 0){
        int count = 0,ifnot = 0;
        if (no != 0)
        while ((cc_creative[no+(++count)] != NULL) && ((no+count) < EARTH_MAX)){
            ifnot = 1;
            add_creative(cc_creative,cc_creative[no]->dna,cc_creative[no+count]->dna);
            break;
        }
        count = 0;
        while ((ifnot == 0) && (cc_creative[no-(++count)] != NULL) && ((no-count) >= 0)){
            ifnot = 1;
            add_creative(cc_creative,cc_creative[no]->dna,cc_creative[no-count]->dna);
            break;
        }
    }
}

void kill_creative(struct creative *k_creative[]){
    for (int i = 0; i < EARTH_MAX; i++){
        if (k_creative[i] != NULL){
            if (k_creative[i]->life == CREATIVE_LIFE){
                free(k_creative[i]);
                k_creative[i] = NULL;
            }
            else (k_creative[i]->life)++;
        }
    }
}
