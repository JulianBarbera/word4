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
  uint32_t anti[5];
  uint32_t conf[5];

  if (argc > 1) {
    secret = argv[1];
    if (!upper(secret) || !contains(entries, count, secret)) {
      printf("%s is not a valid word.\n", secret);
      return 2;
    }
    opMode = AGENT;
  }

  uint i = 0;
  if (opMode) {
    do {
      if (!print_word(entries[0].word, secret)) {
        return 5;
      }
      if (!strcmp(entries[0].word, secret)) {
        return 1;
      }
      i++;
    } while (knock(entries, count, 0));
  } else {
    while (i < 16) {
      printf("Try %s\n", entries[0].word);
      knock(entries, count, 0);
      printf("Greys\n");
      neg |= hashed_input();
      printf("\033[0;%i;%imYellow\033[0m\n12345\n", BLACK - 10, YELLOW);
      pos |= hashed5(anti);
      printf("\033[0;%i;%imGreen\033[0m\n12345\n", BLACK - 10, GREEN);
      hashed5(conf);
      if (!pare(entries, count, pos, neg, conf, anti)) {
        printf("No possible words remain.\n");
        // exit(1);
      };
      i++;
    }
  }

  return 1;
}
