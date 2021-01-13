#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000

typedef struct snowflake_node {
   int snowflake[6];
   struct snowflake_node *next;
} snowflake_node;

int identical_right(int snowflake1[], int snowflake2[], int offset) {
   for (int i = 0; i < 6; i++) {
      if (snowflake1[i] != snowflake2[(i + offset) % 6]) {
         return 0;
      }
   }
   return 1;
}

int identical_left(int snowflake1[], int snowflake2[], int offset) {
   for (int i = 0; i < 6; i++) {
      int j = offset - i;
      if (j < 0) {
         j += 6;
      }
      if (snowflake1[i] != snowflake2[j]) {
         return 0;
      }
   }
   return 1;
}

int are_identical(int snowflake1[], int snowflake2[]) {
   for (int i = 0; i < 6; i++) {
      if (identical_right(snowflake1, snowflake2, i)) {
         return 1;
      }
      if (identical_left(snowflake1, snowflake2, i)) {
         return 1;
      }
   }

   return 0;
}

void identify_identical(snowflake_node *snowflakes[]) {

   for (int i = 0; i < SIZE; i++) {
      snowflake_node *node1 = snowflakes[i];
      while (node1 != NULL) {
         snowflake_node *node2 = node1->next;
         while (node2 != NULL) {
            if (are_identical(node1->snowflake, node2->snowflake)) {
               printf("Twin snowfakes found.\n");
               return;
            }
            node2 = node2->next;
         }
         node1 = node1->next;
      }
   }

   printf("No two snowflakes are alike.\n");
}

int hash(int snowflake[]) {
   return (snowflake[0] + snowflake[1] + snowflake[2] +
           snowflake[3] + snowflake[4] + snowflake[5]) % SIZE;
}

int main(void) {

   static snowflake_node *snowflakes[SIZE] = {NULL};

   int n;
   scanf("%d", &n);

   for (int i = 0; i < n; i++) {
      snowflake_node *ptr = malloc(sizeof(snowflake_node));
      if (ptr == NULL) {
         fprintf(stderr, "malloc failed\n");
         exit(1);
      }

      for (int j = 0; j < 6; j++) {
         scanf("%d", &ptr->snowflake[j]);
      }

      int index = hash(ptr->snowflake);
      ptr->next = snowflakes[index];
      snowflakes[index] = ptr;
   }

   identify_identical(snowflakes);

   for (int i = 0; i < SIZE; i++) {
      snowflake_node *ptr = snowflakes[i];
      while (ptr != NULL) {
         snowflake_node *tmp = ptr;
         ptr = ptr->next;
         free(tmp);
      }
   }

   return 0;
}