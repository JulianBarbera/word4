// data.c
#include "word4.h"
#include <stdint.h>

Extrema extremas(Entry *data, int count) {
  int curr = 0;
  Extrema extremes = {5, 0, UINT16_MAX, 0};

  for (; curr < count; curr++) {
    if (data[curr].score < extremes.minScore && data[curr].score) {
      extremes.minScore = data[curr].score;
    } else if (data[curr].score > extremes.maxScore && data[curr].score) {
      extremes.maxScore = data[curr].score;
    }
    if (data[curr].frequency < extremes.minFreq && data[curr].frequency) {
      extremes.minFreq = data[curr].frequency;
    } else if (data[curr].frequency > extremes.maxFreq &&
               data[curr].frequency) {
      extremes.maxFreq = data[curr].frequency;
    }
  }

  return extremes;
}

void swap(Entry *a, Entry *b) {
  Entry t = *a;
  *a = *b;
  *b = t;
}

int partition(Entry entries[], int low, int high) {

  Entry pivot = entries[high];

  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (entries[j].reward > pivot.reward) {
      i++;
      swap(&entries[i], &entries[j]);
    }
  }

  swap(&entries[i + 1], &entries[high]);
  return i + 1;
}

void sort(Entry *data, int low, int high) {
  if (low < high) {

    int pivot = partition(data, low, high);

    sort(data, low, pivot - 1);
    sort(data, pivot + 1, high);
  }
}

void value(Entry *data, Extrema *extremes, int count) {
  for (int i = 0; i < count; i++) {
    data[i].reward = reward(&data[i], extremes);
  }
}

int contains(Entry *data, int count, char *word) {
  for (int i = 0; i < count; i++) {
    if (strcmp(data[i].word, word) == 0) {
      return 1;
    }
  }
  return 0;
}

int pare(Entry *data, int count, uint32_t pos, uint32_t neg, uint32_t *conf,
         uint32_t *anti) {
  for (int i = 0; i < count; i++) {
    uint32_t hashed = hash_word(data[i].word);

    if ((hashed & neg) != 0 || ((hashed & pos) != pos)) {
      data[i] = (Entry){};
      continue;
    }

    int valid = 1;
    for (int j = 0; j < 5; j++) {
      if (conf[j] != 0 && (conf[j] & hash_single(data[i].word[j])) == 0) {
        valid = 0;
        break;
      }

      if (anti[j] != 0 && (anti[j] & hash_single(data[i].word[j])) != 0) {
        valid = 1;
        break;
      }
    }

    if (!valid) {
      data[i] = (Entry){};
    }
  }
  sort(data, 0, count - 1);
  return data[0].word[0] != '\0';
}

int knock(Entry *data, int count, int pos) {
  if (data[pos].word[0] != 0) {
    data[pos] = (Entry){};
    sort(data, 0, count - 1);
    return 1;
  }
  return 0;
}
