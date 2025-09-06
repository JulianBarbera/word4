// io.c
#include "word4.h"
#include <stdint.h>

int parse(char *filename, Entry **entries) {
  FILE *fdata;

  fdata = fopen(filename, "r");
  if (fdata == NULL) {
    printf("Unable to open file.");
    return 0;
  }

  char buffer[MAX_BUFFER_SIZE];
  char word[6];
  float score;
  int frequency;
  float reward;
  int i = 0, errors = 0, iterations = 0, count = 0;

  while (fgets(buffer, sizeof(buffer), fdata) != NULL) {
    if (sscanf(buffer,
               "{\"word\": \"%5[^\"]\", \"score\": %f, \"frequency\": %d, "
               "\"reward\": %f}",
               word, &score, &frequency, &reward) == 4) {
      count++;
    } else {
      errors++;
      printf("Invalid read! %i\n", errors);
    }
  }

  if (count == 0) {
    fclose(fdata);
    return 0;
  }

  Entry *data = malloc(count * sizeof(Entry));
  if (data == NULL) {
    printf("Memory allocation failed");
    fclose(fdata);
    return 0;
  }

  rewind(fdata);

  while (fgets(buffer, sizeof(buffer), fdata) != NULL &&
         iterations++ < MAX_ITERATIONS) {
    if (sscanf(buffer,
               "{\"word\": \"%5[^\"]\", \"score\": %f, \"frequency\": %i, "
               "\"reward\": %f}",
               word, &score, &frequency, &reward) == 4) {
      strcpy(data[i].word, word);
      data[i].score = score;
      data[i].frequency = frequency;
      data[i].reward = reward;
      i++;
    }
  }
  fclose(fdata);
  *entries = data;
  return count;
}

int print_word(char *word, char *secret) {
  int BLACK = 40;
  int YELLOW = 43;
  int GREEN = 42;
  int WHITE = 47;
  int bgcolor = WHITE;
  int fgcolor = BLACK;
  uint32_t secretHash = hash_word(secret);
  for (int i = 0; i < 5; i++) {
    bgcolor = WHITE;
    if (word[i] == secret[i]) {
      bgcolor = GREEN;
    } else if (hash_single(word[i]) & secretHash) {
      bgcolor = YELLOW;
    }
    printf("\033[0;%i;%im%c\033[0m", fgcolor - 10, bgcolor, word[i]);
  }
  printf("\n");
  return 1;
}

int upper(char *word) {
  for (int i = 0; i < 5; i++) {
    if (word[i] >= 'a' && word[i] <= 'z') {
      word[i] -= 32;
    } else if (word[i] < 'A' || word[i] > 'Z')
      return 0;
  }
  return 1;
}

uint32_t hashed_input() {
  char buffer[MAX_BUFFER_SIZE];
  if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
    return 0;
  }
  buffer[strcspn(buffer, "\n")] = 0;
  return hash(buffer, MAX_BUFFER_SIZE);
}

uint32_t hashed5(uint32_t *five) {
  for (int i = 0; i < 5; i++) {
    five[i] = 0;
  }
  char buffer[MAX_BUFFER_SIZE];
  if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
    return 0;
  }
  buffer[strcspn(buffer, "\n")] = 0;

  for (int i = 0; i < 5; i++) {
    if (buffer[i] != 0) {
      five[i] = hash_single(buffer[i]);
    }
  }
  return hash(buffer, MAX_BUFFER_SIZE);
}
