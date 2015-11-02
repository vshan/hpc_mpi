#include "mpi.h"
#include <stdio.h>
#define MASTER 0

void main() {
  int token, size, taskid;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

  if (taskid == MASTER) {
    MPI_Recv(&token, 1, MPI_INT, taskid - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Task %d: Token %d received from task %d\n", taskid, token, taskid-1);
  } else {
    token = 50;
  }
  
  MPI_Send(&token, 1, MPI_INT, (taskid + 1)%size, 0, MPI_COMM_WORLD);

  if (taskid == MASTER) {
    MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Task %d: Token %d received from task %d\n", taskid, token, size-1);
  }

  MPI_Finalize();
}