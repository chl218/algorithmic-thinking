#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(int size) {

   char *str = malloc(size);
   if (str == NULL) {
      fprintf(stderr, "malloc failed\n");
      exit(1);
   }

   int ch;
   int len = 0;
   while ((ch = getchar()) != EOF && (ch != '\n')) {
      str[len++] = ch;

      if (len == size) {
         size = size * 2;
         str = realloc(str, size);
         if (str == NULL) {
            fprintf(stderr, "reloc failed\n");
            exit(1);
         }
      }
   }

   str[len] = '\0';
   return str;
}


#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

unsigned long oaat(char *key, unsigned long len, unsigned long bits) {
   unsigned long hash = 0;
   for (unsigned long i = 0; i < len; i++) {
      hash += key[i];
      hash += (hash << 10);
      hash += (hash >> 6);
   }

   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);

   return hash & hashmask(bits);
}


#define NUM_BITS 17

typedef struct word_node {
   char **word;
   struct word_node *next;
} word_node;

int in_hash_table(word_node *hash_table[], char *find, unsigned find_len) {
   unsigned word_hash = oaat(find, find_len, NUM_BITS);
   word_node *ptr = hash_table[word_hash];
   while (ptr) {
      if ((strlen(*(ptr->word)) == find_len) && (strncmp(*(ptr->word), find, find_len) == 0)) {
         return 1;
      }
      ptr = ptr->next;
   }
   return 0;
}


void identify_compound_words(char *words[], word_node *hash_table[], int total_words) {
   for (int i = 0; i < total_words; i++) {
      unsigned len = strlen(words[i]);
      for (int j = 1; j < len; j++) {
         if (in_hash_table(hash_table, words[i], j) && in_hash_table(hash_table, &words[i][j], len - j)) {
            printf("%s\n", words[i]);
            break;
         }
      }
   }
}


#define WORLD_LENGTH 16

int main() {
   static char *words[1 << WORLD_LENGTH] = {NULL};
   static word_node *hash_table[1 << NUM_BITS] = {NULL};

   int total = 0;
   char *word = read_line(WORLD_LENGTH);

   while (*word) {

      words[total] = word;
      word_node *ptr = malloc(sizeof(word_node));
      if (ptr == NULL) {
         fprintf(stderr, "malloc failed\n");
         exit(1);
      }
      unsigned len = strlen(word);
      unsigned word_hash = oaat(word, len, NUM_BITS);

      ptr->word = &words[total];
      ptr->next = hash_table[word_hash];
      hash_table[word_hash] = ptr;

      word = read_line(WORLD_LENGTH);
      total++;
   }

   identify_compound_words(words, hash_table, total);

   return 0;
}