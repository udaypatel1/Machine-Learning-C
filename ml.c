/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>


// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);
void freeMatrix(double** mat, int rows);

// main method starts here
int main(int argc, char** argv){
    
    FILE* fp = fopen(argv[1],"r");

    if(fp == NULL){
        printf("error\n");
        return 0;
    }

    int attributes;
    int dataRows;

    fscanf(fp, "%d", &attributes);
    fscanf(fp, "%d", &dataRows);

    /*printf("attributes: %d\tdataRows: %d\n", attributes, dataRows);*/

    /* make matrices for attributes and for 1 column matrix of house prices Y */

    
    double** trainData = malloc(dataRows * sizeof(double*));
    for(int i = 0; i < dataRows; i++){
        trainData[i] = malloc((attributes+1) * sizeof(double));
    }

    for(int i = 0; i < dataRows; i++){
        for(int j = 0; j < attributes+1; j++){
            trainData[i][j] = 0;
        }
    }

    for(int i = 0; i < dataRows; i++){
        trainData[i][0] = 1.000000;
    }

    double** finalHousePrices = malloc(dataRows * sizeof(double*));
    for(int i = 0; i < dataRows; i++){
        finalHousePrices[i] = malloc(1 * sizeof(double));
    }

    for(int i = 0; i < dataRows; i++){
        finalHousePrices[i][0] = 0;
    }
    

    /* parse the incoming doubles from train txt and populate the two matrices above */
    int match;

    int curCol = 0;
    int yRow = 0;
    int xRow = 0;
    int xCol = 1;
    
    while((match = fgetc(fp)) != EOF){

        
        if(xRow == dataRows){
            break;
        }
        
        curCol++;

        


        /*printf("col: %d xRow: %d xCol: %d\t", curCol,xRow,xCol);*/

        double val;

        fscanf(fp, "%lf", &val);

        /*printf("VAL: %f", val);*/

        if(curCol > (attributes)){
            /*printf(" - hit - ");*/
            finalHousePrices[yRow][0] = val;
            yRow++;
            xRow++;
            xCol = 1;
            curCol = 0;
            /*printf("\n");*/

        }
        else{
            /*printf(" - added - ");*/
            /*printf("inserting %f at [%d][%d]\n", val,xRow,xCol);*/
            trainData[xRow][xCol] = val;
            xCol++;
            
            
        }
        
    }

    fclose(fp);

    /*
    int i = 0;
    
    while(i < dataRows){
        printf("y[%d][0]: %f\n", i, finalHousePrices[i][0]);
        i++;
    }
    printf("\n");
    for(int i = 0; i < dataRows; i++){
        for(int j = 0; j < attributes+1; j++){
            printf("trainData[%d][%d]: %lf ", i,j,trainData[i][j]);
        }
        printf("\n");
    }
    */

    
    /*
    double** matT = transposeMatrix(trainData, dataRows, attributes+1);
    double** matX = multiplyMatrix(trainData, matT, dataRows, attributes+1, attributes+1, dataRows);
    double** matI = inverseMatrix(matX,dataRows);
    */
    /*
    for(int i = 0; i < dataRows; i++){
        for(int j = 0; j < dataRows; j++){
            printf("matX[%d][%d]: %lf\n", i,j,matX[i][j]);
        }
        printf("\n");
    }
    */
    /*printf("trainData[1][2]: %f\tTransposed[2][1]: %f\n", trainData[1][2], matT[2][1]); */

    
    
    
    /*
    for(int i = 0; i < dataRows; i++){
        for(int j = 0; j < dataRows; j++){
            printf("matInv[%d][%d]: %lf\n", i,j,matI[i][j]);
        }
        printf("\n");
    }
    */







    double** trainDataTranspose = transposeMatrix(trainData, dataRows, attributes+1);
    /*printf("passed 1\n");*/
    /*
    printf("XTRANS\n");
    for(int i = 0; i < attributes+1; i++){
        for(int j = 0; j < dataRows; j++){
            printf("Xtrans[%d][%d]: %lf\n",i,j,trainDataTranspose[i][j]);
        }
        printf("\n");
    }
    */
    double** trainDataMultWithTranspose = multiplyMatrix(trainDataTranspose, trainData, attributes+1, dataRows, dataRows, attributes+1);
    /*printf("passed 2\n");*/
    /*
    printf("Xtrans x X\n");
    for(int i = 0; i < attributes+1; i++){
        for(int j = 0; j < attributes+1; j++){
            printf("XtransTIMESx[%d][%d]: %lf\n",i,j,trainDataMultWithTranspose[i][j]);
        }
        printf("\n");
    }
    */
    
    double** wholeInverse = inverseMatrix(trainDataMultWithTranspose, attributes+1);
    /*printf("passed 3\n");*/
    
    
    double** invMultTrainDataTranspose = multiplyMatrix(wholeInverse, trainDataTranspose, attributes+1, attributes+1, attributes+1, dataRows);
    /*printf("passed 4\n");*/
    
    
    double** W = multiplyMatrix(invMultTrainDataTranspose, finalHousePrices, attributes+1, dataRows, dataRows, 1);
    /*printf("passed 5\n");*/
    /*
    freeMatrix(finalHousePrices, dataRows);
    freeMatrix(invMultTrainDataTranspose, attributes+1);
    freeMatrix(wholeInverse, attributes+1);
    freeMatrix(trainDataMultWithTranspose, attributes+1);
    freeMatrix(trainData, dataRows);
    freeMatrix(trainDataTranspose, attributes+1); 
    */
    

    /*
    for(int i = 0; i < attributes+1; i++){
        free(invMultTrainDataTranspose[i]);
    }
    free(invMultTrainDataTranspose);

    for(int i = 0; i < dataRows; i++){
        free(finalHousePrices[i]);
    }
    free(finalHousePrices);
    */
    /*
    for(int i = 0; i < attributes+1; i++){
        printf("W[%d][0]: %lf\n", i, W[i][0]);
    }
    printf("\n");
    */
    /* W is of size attributes+1 x 1 */

    



    FILE* fp2 = fopen(argv[2], "r");

    if(fp2 == NULL){
        printf("error\n");
        return 0;
    }

    int textRows;
    fscanf(fp2,"%d",&textRows);

    double** Xprime = malloc(textRows * sizeof(double*));
    for(int i = 0; i < textRows; i++){
        Xprime[i] = malloc((attributes+1) * sizeof(double));
    }

    for(int i = 0; i < textRows; i++){
        for(int j = 0; j < attributes+1; j++){
            Xprime[i][j] = 0;
        }
    }

    for(int i = 0; i < textRows; i++){
        Xprime[i][0] = 1.00000;
    }

    int match2;
    int xPrimeRow = 0;
    int xPrimeCol = 1;
    int curColPrime = 0;
    while((match2 = fgetc(fp2)) != EOF){

        if(xPrimeRow == textRows){
            break;
        }
        

        curColPrime++;

        double val2;
        fscanf(fp2, "%lf", &val2);

        /*printf("curCol: %d | attributes: %d | xPrimeRow: %d | xPrimeCol: %d | Val: %lf\n", curColPrime, attributes, xPrimeRow, xPrimeCol, val2);*/

        if(xPrimeCol == attributes){

            Xprime[xPrimeRow][xPrimeCol] = val2;
            xPrimeRow++;
            xPrimeCol = 1;
            curColPrime = 0;
        }

        else{

            Xprime[xPrimeRow][xPrimeCol] = val2;
            xPrimeCol++;
        }

    }

    fclose(fp2);
    /*
    for(int i = 0; i < textRows; i++){
        for(int j = 0; j < attributes; j++){
            printf("Xprime[%d][%d]: %lf\n", i,j,Xprime[i][j]);
        }
        printf("\n");
    }
    */

    double** Yprime = multiplyMatrix(Xprime, W, textRows, attributes+1, attributes+1, 1);
    
    
    
    for(int i = 0; i < textRows; i++){
        printf("%0.0lf\n", Yprime[i][0]);
    }

    freeMatrix(Yprime, textRows);
    freeMatrix(finalHousePrices, dataRows);
    freeMatrix(invMultTrainDataTranspose, attributes+1);
    freeMatrix(wholeInverse, attributes+1);
    freeMatrix(trainDataMultWithTranspose, attributes+1);
    freeMatrix(trainData, dataRows);
    freeMatrix(trainDataTranspose, attributes+1); 
    freeMatrix(Xprime, textRows);
    freeMatrix(W, attributes+1);
    
	return 0;
}

void freeMatrix(double** mat, int rows){
    for(int i = 0; i < rows; i++){
        free(mat[i]);
    }
    free(mat);
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*)); 
    
    // your code goes here

    if(c1 != r2){
        return 0;
    }

    for(int i = 0; i < r1; i++){
        result[i] = malloc(c2 * sizeof(double)); /* r1 by c2 matrix */
    }

    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c2; j++){
            result[i][j] = 0;
        }
    }

    
    for(int i = 0; i < r1; i++){ /*rows of matA */
        for(int j = 0; j < c2; j++){ /* cols of matB */
            for(int common = 0; common < c1; common++){
                
                result[i][j] += matA[i][common] * matB[common][j];
                
                /*printf("%lf\t%lf\t%lf\n", result[i][j], matA[i][common], matB[common][j]);*/
            }

        }

        
    }
    
    
    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
  
	double** matTran=malloc(col*sizeof(double*)); 
    
    // your code goes here
    
    for(int i = 0; i < col; i++){

        matTran[i] = malloc(row * sizeof(double));
    }

    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            matTran[i][j] = 0;
        }
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matTran[j][i] = mat[i][j];
        }
    }
    

    
    
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension)
{

    /* initialize the identity matrix n x n */

    double** matI=malloc(dimension*sizeof(double*)); 
    for(int i = 0; i < dimension; i++){
        matI[i] = malloc(dimension * sizeof(double));
    }

    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            matI[i][j] = 0;
        }
    }

    for(int i = 0; i < dimension; i++){
        matI[i][i] = 1.000000;
    }


    for(int p = 0; p < dimension; p++){
        double f = matA[p][p];

        /*printf("f is %lf\n", f);*/
         
        /* divide Mrowp and Nrowp by f */
        for(int r = 0; r < dimension; r++){
            
            /*printf("matA[%d][%d] = %lf - f = %lf | %lf / %lf = %lf", p,r,matA[p][r], f, matA[p][r], f, temp);*/
            matA[p][r] = matA[p][r] / f;
            matI[p][r] = matI[p][r] / f;

            
        }

        

        for(int i = (p+1); i < dimension; i++){

            f = matA[i][p];
            
            /* subtract Mrowp*f from Mrowi and subtract Nrowp*f from Nrowi */
            for(int r = 0; r < dimension; r++){
                
                /*printf("matA[%d][%d] = %lf - f = %lf | %lf - (%lf * %lf) = %lf", i,r,matA[i][r], f, matA[i][r], matA[p][r],f, temp);*/
                matA[i][r] = matA[i][r] - (matA[p][r] * f);
                /*printf("matA[%d][%d] = %lf - f = %lf | %lf - (%lf * %lf) = %lf", i,r,matI[i][r], f, matI[i][r], matI[p][r],f, temp);*/
                matI[i][r] = matI[i][r] - (matI[p][r] * f);
            }
        }

    }

    /* part 2 */

    for(int p = dimension-1; p >= 0; p--){

        for(int i = (p-1); i >= 0; i--){

            double f = matA[i][p];

            /* subtract Mrowp*f from Mrowi and subtract Nrowp*f from Nrowi */
            for(int r = 0; r < dimension; r++){
                matA[i][r] = matA[i][r] - (matA[p][r] * f);
                matI[i][r] = matI[i][r] - (matI[p][r] * f);
            }
        }
    }

    return matI;
}


