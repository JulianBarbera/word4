#include "word4.h"

int main(int argc, char **argv) {
  Entry *entries;
  int count = parse("data.jsonl", &entries);
  Extrema extremes = extremas(entries, count);

  value(entries, &extremes, count);
  sort(entries, 0, count - 1);
  int opMode = USER;
  char *secret;

  uint32_t neg = 0;
  uint32_t pos = 0;
  uint32_t anti[5] = {0};
  uint32_t conf[5] = {0};

  if (argc > 1) {
    secret = argv[1];
    if (!upper(secret) || !contains(entries, count, secret)) {
      printf("%s is not a valid word.\n", secret);
      exit(2);
    }
    opMode = AGENT;
  }

  uint i = 0;
  int guess_pos;
  if (opMode) {

    do {
      guess_pos = first_valid(entries, count);
      char *guess = entries[guess_pos].word;
      if (!print_word(guess, secret)) {
        exit(5);
      }
      if (!strcmp(guess, secret)) {
        exit(1);
      }
      for (int j = 0; j < 5; j++) {
        if (guess[j] == secret[j]) {
          conf[j] = hash_single(secret[j]);
        } else if (hash_single(guess[j]) & hash_word(secret)) {
          pos |= hash_single(guess[j]);
          anti[j] |= hash_single(guess[j]);
        } else {
          neg |= hash_single(guess[j]);
        }
      }
      if (!pare(entries, count, pos, neg, conf, anti)) {
        printf("No possible words remain.\n");
        exit(2);
      };
      i++;
    } while (knock(entries, count, guess_pos) >= 0);

  } else {
    while (i < 16) {
      guess_pos = first_valid(entries, count);
      char *guess = entries[guess_pos].word;
      printf("Try %s\n", guess);
      knock(entries, count, guess_pos);
      printf("Greys\n");
      neg |= hashed_input();
      printf("\033[0;%i;%imYellow\033[0m\n12345\n", BLACK - 10, YELLOW);
      pos |= hashed5(anti);
      printf("\033[0;%i;%imGreen\033[0m\n12345\n", BLACK - 10, GREEN);
      hashed5(conf);
      if (!pare(entries, count, pos, neg, conf, anti)) {
        printf("No possible words remain.\n");
        exit(1);
      };
      i++;
    }
  }

  return 4;
}
