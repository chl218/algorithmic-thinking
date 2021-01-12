#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      int j = i + offset;
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

void identify_identical(int snowflakes[][6], int n) {
   int i, j;
   for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
         if (are_identical(snowflakes[i], snowflakes[j])) {
            printf("Twin snowfakes found.\n");
            return;
         }
      }
   }
   printf("No two intergs are alike.\n");
}

#define SIZE 100000

int main(void) {

   static int snowflakes[SIZE][6];

   int n;
   scanf("%d", &n);

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < 6; j++) {
         scanf("%d", &snowflakes[i][j]);
      }
   }

   identify_identical(snowflakes, n);

   return 0;
}