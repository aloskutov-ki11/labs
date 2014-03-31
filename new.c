#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <inttypes.h>



int getSizeOfNumberInFile(char *FileName, char *signA);
void resetMass(unsigned char *M,  unsigned long int sizeM);
void printMass(unsigned char *M, unsigned long int sizeA);
void reverseMass(unsigned char *M, unsigned long int sizeA);

int MoreOrLess(unsigned char *A,unsigned long int sizeA, unsigned char *B, unsigned long int sizeB);
int MoreOrLessFromLeft(unsigned char *A,unsigned long int sizeA, unsigned char *B, unsigned long int sizeB);//слева от числа берем цифры и сравниваем - это для деления в столбик

int unsetLeaderNULLS(unsigned char *M,unsigned long int sizeM); //в инвертированном массиве лидирующие нули убираем


void readNumber(char *FileName, unsigned char *M, unsigned long int sizeA);
void summ(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC);

void difference(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC);

void imul(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC);

void division(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC, unsigned char *O, unsigned long int sizeO);


int main(int argc, char **argv){

//входные параметры
char *FileNameA = argv[1];
char *operation = argv[2];
char *FileNameB = argv[3];
char *FileNameC = argv[4];


	
	//для первого числа
	unsigned char *A;
	unsigned long int sizeA;
	char signA = '+';
	
	//для второго числа
	unsigned char *B;
	unsigned long int sizeB;
	char signB = '+';
	
	//для результата
	unsigned char *C;
	unsigned long int sizeC;
	char signC;
	
	//если остаток нужно будет считать
	unsigned char *O;
	unsigned long int sizeO;
	
	
	//получим размер первого файла
	sizeA = getSizeOfNumberInFile(FileNameA, &signA);

	unsigned long int size = sizeA/2;
	if(size*2 == sizeA)
		sizeA = sizeA/2;
	else
		sizeA = sizeA/2+1;

	
	//сброс в ноль
	A = (unsigned char*)malloc(sizeA);
	resetMass(A, sizeA);
	
	//чтение в массив А
	readNumber(FileNameA, A, sizeA);
	
	//получим размер второго файла
	sizeB = getSizeOfNumberInFile(FileNameB, &signB);

	size = sizeB/2;
	if(size*2 == sizeB)
		sizeB = sizeB/2;
	else
		sizeB = sizeB/2+1;

	
	//сброс в ноль
	B = (unsigned char*)malloc(sizeB);
	resetMass(B, sizeB);
	
	//чтение в массив B
	readNumber(FileNameB, B, sizeB);
///////////////////////////////////////////////////////////////////////////////////////////
/////////////    вычисление
///////////////////////////////////////////////////////////////////////////////////////////	
	
	if(!strcmp(operation, "+"))
	{
		if(sizeA >= sizeB)
			sizeC = sizeA + 1;
			
		if(sizeB > sizeA)
			sizeC = sizeB + 1;
		
		
		C = (unsigned char*)malloc(sizeC);
		resetMass(C, sizeC);
		summ(A, sizeA, B, sizeB, C, sizeC);
			
		sizeC = unsetLeaderNULLS(C, sizeC);
		
		reverseMass(A, sizeA);
		reverseMass(B, sizeB);
		reverseMass(C, sizeC);
	
		printf("\n");
		printMass(A, sizeA);
		printf("+ ");
		printMass(B, sizeB);
		printf(" = ");
	
		printMass(C, sizeC);
		printf("\n");
		
		
	}
	
	if(!strcmp(operation, "-"))
	{
		int k = 3;

		sizeC = sizeA;
		
		k = MoreOrLess(A, sizeA, B, sizeB);
		
		//printf("less or more: %d\n\n", k);
		switch(k){
			case 1: case 3:
				sizeC = sizeA;
				C = (unsigned char*)malloc(sizeC);
				resetMass(C, sizeC);
				difference(A, sizeA, B, sizeB, C, sizeC);
			break;
			case 2:
				sizeC = sizeB;
				C = (unsigned char*)malloc(sizeC);
				resetMass(C, sizeC);
				difference(B, sizeB, A, sizeA,  C, sizeC);
			break;
		}
		sizeC = unsetLeaderNULLS(C, sizeC);
		
		reverseMass(A, sizeA);
		reverseMass(B, sizeB);
		reverseMass(C, sizeC);
	
		printf("\n");
		printMass(A, sizeA);
		printf("- ");
		printMass(B, sizeB);
		printf(" = ");
	
		printMass(C, sizeC);
		
			
	
	}
	
	if(!strcmp(operation, "*"))
	{
		sizeC = sizeA + sizeB + 1;
		C = (unsigned char*)malloc(sizeC);
		resetMass(C, sizeC);
		imul(A, sizeA, B, sizeB,  C, sizeC);
		
		reverseMass(A, sizeA);
		reverseMass(B, sizeB);
		reverseMass(C, sizeC);
	
		printf("\n");
		printMass(A, sizeA);
		printf("* ");
		printMass(B, sizeB);
		printf(" = ");
	
		printMass(C, sizeC);
		
	}
	
	if(!strcmp(operation, "/") || !strcmp(operation, "%"))
	{
		sizeC = sizeA;
		sizeO = sizeB;
		
		if(sizeB > sizeA)
		{
			sizeC = sizeB;
			sizeO = sizeA;
		}
		
		C = (unsigned char*)malloc(sizeC);
		O = (unsigned char*)malloc(sizeO);
		resetMass(C, sizeC);
		resetMass(O, sizeO);
		division(A, sizeA, B, sizeB,  C, sizeC,  O, sizeO);
		
		sizeC = unsetLeaderNULLS(C, sizeC);
		sizeO = unsetLeaderNULLS(O, sizeO);
		
		reverseMass(A, sizeA);
		reverseMass(B, sizeB);
		reverseMass(O, sizeO);
	
		if(!strcmp(operation, "/"))
		{
			printf("\n");
		printMass(A, sizeA);
			printf("/ ");
			printMass(B, sizeB);
			printf(" = ");
	
			printMass(C, sizeC);
			printf("\n");
		}
		else
		{
			printf("\n");
			printMass(A, sizeA);
			printf(" mod ");
			printMass(B, sizeB);
			printf(" = ");
	
			printMass(O, sizeO);
			printf("\n");
		}
	}
	
	if(!strcmp(operation, "^"))
	{
		printf("hello\n");
		
	}
	
	



	return 0;
	
	
}
//***************************************************************************************//

void division(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC, unsigned char *O, unsigned long int sizeO){

	
	unsigned char *Atmp = (unsigned char *)malloc(sizeA);
	unsigned long int sizeAtmp = sizeA;
	resetMass(Atmp, sizeAtmp);
	
	unsigned char *R = (unsigned char *)malloc(1);
	resetMass(R, 1);
	
	
	unsigned char *upL = (unsigned char *)malloc(sizeB+1);
	unsigned long int sizeUpL = sizeB+1;
	resetMass(upL, sizeUpL);
	
	unsigned char *dwnL = (unsigned char *)malloc(sizeB+1);
	unsigned long int sizeDwnL = sizeB+2;
	resetMass(dwnL, sizeDwnL);
	
	
	
	unsigned char *resL = (unsigned char *)malloc(sizeB+1);
	unsigned long int sizeResL = sizeB+1;
	resetMass(resL, sizeResL);
	
	unsigned long int indexC = 0;
	
	
	int i;
	for(i = 0; i < sizeA; ++i)
		Atmp[i] = A[i];
		
	int k;
	
	int exit = 1;
	while(exit != 2)
	{
		//работаем с верхним левым массивом
		k = MoreOrLessFromLeft(Atmp, sizeAtmp, B, sizeB);
		if(k != 2)
		{
			sizeUpL = sizeB;
		}
		else
		{
			sizeUpL = sizeB + 1;
		}
		//printf("k=%d\n\n",k);
		
		for(i = 1; i <= sizeUpL; ++i)
			upL[sizeUpL - i] = Atmp[sizeAtmp - i];
		
	
		R[0] = 1;
		k = 2;
		
		//подбираем очередное число частного
		while( k == 2 )
		{
			resetMass(dwnL, sizeDwnL);
			sizeDwnL = sizeB + 2;
			imul(R, 1, B, sizeB, dwnL, sizeDwnL);
			
			sizeDwnL = unsetLeaderNULLS(dwnL, sizeDwnL);
			++R[0];
			if(sizeDwnL == 0)
				break;
			//printf("R[i] = %d\n", R[sizeR]);
			k = MoreOrLess(dwnL, sizeDwnL, upL, sizeUpL);
			
		}
		
		if(R[0] == 2)
			R[0] = R[0] - 1;
		else
			R[0] = R[0] - 2;
			
		//printf("\nR[sizeR] = %d\n", R[0]);
		
		C[indexC] = R[0];
		
		resetMass(dwnL, sizeDwnL);
		imul(R, 1, B, sizeB, dwnL, sizeDwnL);

		/*printf("\nupLeft ");
		printMass(upL, sizeUpL);
		
		printf("\n\ndwnL ");
		printMass(dwnL, sizeDwnL);*/


		difference(upL, sizeUpL, dwnL, sizeDwnL, resL, sizeResL);
		
		/*printf("\nresL ");
		printMass(resL, sizeResL);*/
		sizeResL = sizeUpL;
		
		
		//делаем новый tmpA
		for(i = 0; i <= sizeResL; ++i)
			Atmp[sizeAtmp - i] = resL[sizeResL - i];
			
			
		sizeAtmp = unsetLeaderNULLS(Atmp, sizeAtmp);
		
		/*printf("\nAtmp ");
		printMass(Atmp, sizeAtmp);
		printf("\n\n--------------------\n");*/
		
		
		++indexC;
		exit = MoreOrLess(Atmp, sizeAtmp, B, sizeB);
		
		if(sizeAtmp == 0)
			exit = 2;
	
	}

		/*printf("\nостаток: ");
		printMass(resL, sizeResL);
		printf("\n\n--------------------\n");*/
	
	for(i = 0; i < sizeResL; ++i)	
		O[i] = resL[i];


}
int unsetLeaderNULLS(unsigned char *M,unsigned long int sizeM){

	int i = 1;
	
	while( (M[sizeM - i] == 0) && (sizeM != 0) )
	{
		--sizeM;
	}
	
	return sizeM;
}


int MoreOrLessFromLeft(unsigned char *A,unsigned long int sizeA, unsigned char *B, unsigned long int sizeB){
	int k = 3;
	int i;
	for(i = 1; i <= sizeB; ++i)
	{
		if(A[sizeA - i] > B[sizeB - i])
		{
			k = 1;
			break;
		}
		if(B[sizeB - i] > A[sizeA - i])
		{
			k = 2;
			break;
		}
	}
	
	return k;
}


void imul(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC){

	unsigned long int i,j;
	
	unsigned long long tmp;
	
	for (i = 0; i < sizeA; i++)
	{
    	for (j = 0; j < sizeB; j++)
    	{
       	 	tmp = A[i] * B[j];
 			//printf("\n*** %llu\n", tmp);
 			C[i + j + 1] +=  tmp / 100;
				C[i + j] += tmp % 100;
		}
		
		unsigned long int k;
		for (k = 0; k < sizeC; k++)
		{
			C[k + 1] +=  C[k] / 100;
			C[k] = C[k] % 100;
		}
			
	}	


}

void difference(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC){

	int i;
	unsigned long int tmp;
	unsigned long int tmp2 = 1;
	
	unsigned char *A1 = (unsigned char *)malloc(sizeA);
	for(i = 0; i < sizeA; ++i)
	{
		A1[i] = A[i];
	}
	
	int zayom = 0;
	for(i = 0; i < sizeC; ++i)
	{
		if(zayom)
		{
			if(A1[i] > 0)
			{
				--A1[i];
				zayom=0;
				
			}
			
		}
		if(i < sizeB)
		{
			if(A1[i] >= B[i])
			{
				zayom = 0;
				C[i] = A1[i] - B[i];
			}	
			else
			{
				zayom = 0;
				C[i] = 100+A1[i] - B[i];
				++zayom;
			}
		}
		else
		{
			while( (A1[i] > 0) && zayom)
			{
				--A1[i];
				zayom=0;
				
			}
			if( (A1[i] == 0) && zayom)
			{
				A1[i] = 99;
				++zayom;
			}
			C[i] = A1[i];
		}
		
	}

}

void summ(unsigned char *A, unsigned long int sizeA, unsigned char *B, unsigned long int sizeB, unsigned char *C, unsigned long int sizeC){

	int i;
	unsigned long int tmp;
	for(i = 0; i < sizeC; ++i)
	{
		tmp = A[i] + B[i];
	
		C[i] += tmp % 100;
		C[i+1] += tmp/100;
	}

}
int MoreOrLess(unsigned char *A,unsigned long int sizeA, unsigned char *B, unsigned long int sizeB){

		int k = 3;
		unsigned long int lenght;
		
		lenght = sizeA;
		if(sizeA > sizeB)
		{
			k = 1;  //первое число больше второго
			lenght = sizeA;
		}
		else
		{
			if(sizeB > sizeA)
			{
				lenght = sizeB;
				k = 2;
			}
			else
			{
				unsigned long int ix;
				for (ix = lenght-1; ix >= 0; --ix)
				{
					if(A[ix] > B[ix])
					{
						k = 1;
						break;
					}
					if(B[ix] > A[ix])
					{
						k = 2;
						break;
					}
				}
			}
			
		}
		
		return k;

}


void reverseMass(unsigned char *M, unsigned long int sizeA){

	int i = 0;
	unsigned long int tmp;
	

		for (i = 0; i < sizeA/2; ++i)
		{
			tmp = M[i];
		
				M[i] = M[sizeA-1-i];
				M[sizeA-1-i] = tmp;
		}

	
}
void readNumber(char *FileName, unsigned char *M, unsigned long int sizeA){
	
	FILE *fp; 
	fp = fopen(FileName, "r");
	
	struct stat st;
	stat(FileName, &st);
	unsigned long int size = st.st_size - 2;
	
	
	
	char ch;
	int c = 0;
	int tmp = 0;
	int subTmp = 0;
	
	
	int i = 0; int j = 1;
	while(i < sizeA)
	{
		
		
		while( (c < 2) && (size != -1) )
		{
			fseek(fp,size,SEEK_SET);
			ch = getc(fp);
			
			if(ch >= '0' && ch <= '9')
			{
				subTmp = tmp;
				tmp = ch - '0';
				tmp = tmp*j + subTmp;
				j *= 10;
			}
			
			--size;
			++c;
		}
		
		M[i] = tmp;
		tmp = 0;
		j = 1;
		++i;
		c = 0;
	}

	fclose(fp);
}


void printMass(unsigned char *M, unsigned long int sizeA){
	
	int k = sizeA;
	int i;
	
	for(i = 0; i < k; ++i)
		printf("%d ", M[i]);
		
}
void resetMass(unsigned char *M,  unsigned long int sizeM){
	
	int i;
	
	for(i = 0; i < sizeM; ++i)
		M[i] = 0;
}
int getSizeOfNumberInFile(char *FileName, char *signA){

	//читаем размер и вместо знака числа записываем 0
	struct stat st;
	stat(FileName, &st);
	unsigned long int size = st.st_size;
	
	
	FILE *fp; 
	fp = fopen(FileName, "r+");
		
		char ch = getc(fp);
		if( (ch < '0') || (ch > '9') )
		{
			*signA = ch;
			size = size - 1;
			fseek(fp,0,SEEK_SET);
			fputs("0", fp);
		}
	fclose(fp);	
	
	
	return size-1;
}
