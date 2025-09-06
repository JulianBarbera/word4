#include "word4.h"

int main(int argc, char **argv) {
  Entry *entries;
  int count = parse("data.jsonl", &entries);
  Extrema extremes = extremas(entries, count);
  if (argc > 1 && upper(argv[1])) {
    if (!contains(entries, count, argv[1])) {
      return 1;
    }
  }
  value(entries, &extremes, count);
  sort(entries, 0, count - 1);
  uint32_t neg = 0;
  uint32_t pos = 0;
  uint32_t anti[5];
  uint32_t conf[5];
  while (1) {
    printf("Try %s\n", entries[0].word);
    knock(entries, count, 0);
    printf("Greys\n");
    neg |= hashed_input();
    printf("Yellow\n");
    pos |= hashed5(anti);
    printf("Green\n");
    hashed5(conf);
    if (!pare(entries, count, pos, neg, conf, anti)) {
      exit(1);
    };
  }
  return 1;
}
