#include <stdio.h>
#include <unistd.h>

// Print Window
void printWindow(int w[], int window_size)
{
  printf("Window Contains : ");
  for (int i = 0; i < window_size; i++)
    printf("%d ", w[i]);
  printf("\n");
}

int main()
{
  int tf; // Total Frames
  printf("Enter total frames to send : ");
  scanf("%d", &tf);

  int window_size; // Window Size
  printf("Enter the window size : ");
  scanf("%d", &window_size);
  int w[window_size]; // Window
  int n = 1;
  for (int i = 0; i < window_size; i++)
  {
    printf("Sending frame %d\n", n);
    w[i] = n;
    n++;
  }

  printWindow(w, window_size);

  while (n - window_size <= tf)
  {
    int r;
    printf("Enter acknowledgment for frame %d (ACK:1, NACK:0) : ", w[0]);
    scanf("%d", &r);
    if (r)
    {
      printf("\n");
      for (int i = 0; i < window_size - 1; i++)
        w[i] = w[i + 1];
      if (n <= tf)
      {
        printf("Sending frame %d\n", n);
        w[window_size - 1] = n;
        n++;
      }
      else
      {
        w[window_size - 1] = 0;
        n++;
      }
      printWindow(w, window_size);
    }
    else
    {
      printf("\nWaiting for %d seconds\n", 1);
      sleep(1);
      for (int i = 0; i < window_size; i++)
        printf("Sending frame %d\n", w[i]);
      printWindow(w, window_size);
    }
  }
  return 0;
}

// Enter total frames to send : 7
// Enter the window size : 3
// Sending frame 1
// Sending frame 2
// Sending frame 3
// Window Contains : 1 2 3
// Enter acknowledgment for frame 1 (ACK:1, NACK:0) : 1

// Sending frame 4
// Window Contains : 2 3 4
// Enter acknowledgment for frame 2 (ACK:1, NACK:0) : 1

// Sending frame 5
// Window Contains : 3 4 5
// Enter acknowledgment for frame 3 (ACK:1, NACK:0) : 0

// Waiting for 1 seconds
// Sending frame 3
// Sending frame 4
// Sending frame 5
// Window Contains : 3 4 5
// Enter acknowledgment for frame 3 (ACK:1, NACK:0) : 1

// Sending frame 6
// Window Contains : 4 5 6
// Enter acknowledgment for frame 4 (ACK:1, NACK:0) : 1

// Sending frame 7
// Window Contains : 5 6 7
// Enter acknowledgment for frame 5 (ACK:1, NACK:0) : 0

// Waiting for 1 seconds
// Sending frame 5
// Sending frame 6
// Sending frame 7
// Window Contains : 5 6 7
// Enter acknowledgment for frame 5 (ACK:1, NACK:0) : 1

// Window Contains : 6 7 0
// Enter acknowledgment for frame 6 (ACK:1, NACK:0) : 1

// Window Contains : 7 0 0
// Enter acknowledgment for frame 7 (ACK:1, NACK:0) : 1

// Window Contains : 0 0 0
