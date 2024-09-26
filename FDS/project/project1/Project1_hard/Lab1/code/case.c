int *new_matrix(int N)
{
    int *matrix = malloc(N * N * sizeof(int)); /*Get memory to store matrix*/
    srand(time(NULL));                         /*Set time seed so that the matrix is created randomly*/
    for (int i = 0; i < N * N; i++)
    {
        matrix[i] = rand() % 20 - 9; /*Get a matrix with number between -9 to 10*/
    }                                /*Certainly you can change 20 and 9*/
    /*Finally return a new matrix*/
    return matrix;
}