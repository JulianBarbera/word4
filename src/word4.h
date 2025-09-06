#ifndef WORDLE_H
#define WORDLE_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_BUFFER_SIZE 256
#define MAX_ITERATIONS 100000

typedef struct Entry {
  char word[6];
  float score;
  int frequency;
  float reward;
} Entry;

typedef struct Extrema {
  float minScore;
  float maxScore;
  int minFreq;
  int maxFreq;
} Extrema;

// calculatons.c
uint32_t hash_single(char c);
uint32_t hash(char *word, int count);
uint32_t hash_word(char *word);
float reward(Entry *data, Extrema *extremes);
int num_vowels(char *word);

// data.c
Extrema extremas(Entry *data, int count);
void swap(Entry *a, Entry *b);
void sort(Entry *data, int low, int high);
int pare(Entry *data, int count, uint32_t pos, uint32_t neg, uint32_t *conf,
         uint32_t *anti);
void value(Entry *data, Extrema *extremes, int count);
int contains(Entry *data, int count, char *word);
int knock(Entry *data, int count, int pos);

// io.c
int parse(char *filename, Entry **entries);
int print_word(char *word, char *secret);
int upper(char *word);
uint32_t hashed_input();
uint32_t hashed5(uint32_t *five);

#endif
