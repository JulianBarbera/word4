// calculations.c
#include "word4.h"

float reward(Entry *data, Extrema *extremes) {
  float score = 1 - ((data->score - extremes->minScore) /
                     (extremes->maxScore - extremes->minScore));
  float frequency =
      (log10(data->frequency) - log10(extremes->minFreq)) /
      (float)(log10(extremes->maxFreq) - log10(extremes->minFreq));

  // printf("word: %s, score: %f, freq: %f\n", data->word, score, frequency);
  int numVowels = num_vowels(data->word);
  float reward = score * frequency * numVowels * numVowels;
  return reward;
}

int num_vowels(char *word) {
  uint32_t vowels = 1065233U & hash_word(word);
  int count = 0;
  while (vowels) {
    vowels &= vowels - 1;
    count++;
  }
  return count;
}

uint32_t hash_single(char c) {
  if (c >= 'A' && c <= 'Z') {
    return 1U << (c - 'A');
  }
  if (c >= 'a' && c <= 'z') {
    return 1U << (c - 'A' - 32);
  }
  return 0;
}

uint32_t hash(char *word, int count) {
  uint32_t hashed = 0;
  for (int i = 0; i < count; i++) {
    if (word[i] == 0) {
      break;
    }
    hashed |= hash_single(word[i]);
  }
  return hashed;
}

uint32_t hash_word(char *word) { return hash(word, 5); }
