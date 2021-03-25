//PROGRAMA HECHO POR:
//ROSADO DOMÍNGUEZ LUIS FERNANDO
//GARDUÑO BALDAZO CRISTIAN
//CERVERA SOTO SARA NOEMI
//GRUPO: 2452
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int menu();
void Sistema1();
void SubMenu(float *x, float *y, int *i);
void InversaDos(float inv[][2], float a[][2]);
void Sistema2();
void SubMenu2(float *x, float *y, float *z, int *i);
void Sistema3();
void InversaTres(float inv[][3], float a[][3]);
void Sistema4();
int main()
{
	int op_menu, respuesta;
	do{
		op_menu = menu();
		system("cls");
		switch(op_menu){
			case 1: Sistema1();
					break;
			case 2: Sistema2();
					break;
			case 3: Sistema3();
					break;
			case 4: Sistema4();
					break;
			case 5: 
					exit(1);
					break;
		}
		do{
			printf("\nDesea realizar otra operacion?: [1] Si, [2] No");
			fflush(stdin);
			printf("\nOpcion: ");
			scanf("%d", &respuesta);
		} while(respuesta<1 || respuesta >2);
	} while(respuesta == 1);
}

int menu(){
	int opcion;
	system("cls");
	printf("\t-METODO DE NEWTON RAPHSON-");
	printf("\nSeleccione el sistema a resolver:");
	printf("\n[1] 1. f1(x, y) = x2 + xy - 10 = 0 \n    2. f2(x, y) = y + 3xy2 - 50 = 0\n");
	printf("\n[2] 1. f1(x, y) = x2 + y2 - 9 = 0 \n    2. f2(x, y) = -ex - 2y - 3 = 0\n");
	printf("\n[3] 1. f1(x, y, z) = 2x2 - 4x + y2 + 3z2 + 6z + 2 = 0 \n    2. f2(x, y, z) = x2 + y2 - 2y + 2z2 - 5 = 0 \n    3. f3(x, y, z) = 3x2 - 12x + y2 - 3z2 + 8 = 0\n");
	printf("\n[4] 1. f1(x, y, z) = x2 - 4x + y2 = 0 \n    2. f2(x, y, z) = x2 - x - 12y + 1 = 0 \n    3. f3(x, y, z) = 3x2 - 12x + y2 - 3z2 + 8 = 0  \n");
	printf("\n[5] Salir");
	printf("\nOpcion (Digite el numero): ");
	scanf("%d", &opcion);
	// Recupera opcion el main
	return opcion;
}

void Sistema1()
{
	float x=0, y=0;
	float sol1=0, sol2=0, error=0;
	int i, j=0, k=0, ite=0;
	printf("\t-SISTEMA 1-\n");
	printf("1. f1(x, y) = x2 + xy - 10 = 0 \n2. f2(x, y) = y + 3xy2 - 50 = 0\n");
	SubMenu(&x, &y, &i);
	
	float p[1][1]={0};
	float a[2][2]={0}; //jacobiana
	float F[1][1]={0}; //F(X)
	float inv[2][2]={0}; //inversa jacobiana
	float mult[1][1]={0};
	p[0][0]=x;
	p[0][1]=y;
	
	printf("\n-------------------------------------------------------\n");
	for(ite=0; ite<=i; ite++)
	{
		printf("\tITERACION # %d\n", ite);
		printf("-------------------------------------------------------\n");
		
		printf("\n(x, y)\n[%-3f]\n[%-3f]\n", p[0][0], p[0][1]);
		a[0][0]=(2*p[0][0])+p[0][1];
		a[0][1]=p[0][0];
		a[1][0]=3*(pow(p[0][1],2));
		a[1][1]=1+(3*p[0][0])*(2*p[0][1]);
		
		printf("\nJacobiana\n");
		for(j=0; j<2; j++)
		{
			for(k=0; k<2; k++)
			{
				printf("[%-3f]", a[j][k]);
			}
			putchar('\n');
		}
		
		F[0][0]=(pow(p[0][0],2))+(p[0][0]*p[0][1])-10;
		F[0][1]=p[0][1]+(3*p[0][0]*(pow(p[0][1],2)))-50;
		printf("\nF(X)\n");
		printf("[%-3f]\n[%-3f]\n", F[0][0], F[0][1]);
			
		InversaDos(inv, a);
		mult[0][0]=(inv[0][0]*F[0][0])+(inv[0][1]*F[0][1]);
		mult[0][1]=(inv[1][0]*F[0][0])+(inv[1][1]*F[0][1]);
		printf("\nProducto de Jacobiana Inversa con F(X)\n[%-3f]\n[%-3f]\n", mult[0][0],mult[0][1]);
		x=p[0][0];
		y=p[0][1];
		p[0][0]=x-mult[0][0];
		p[0][1]=y-mult[0][1];
		
		printf("\nError Absoluto\n");
		if(F[0][0]<0 && F[0][1]<0)
		{
			if(-1*F[0][0] > -1*F[0][1])
			{
				printf("[%-3f]\n", F[0][0]);
				error=F[0][0];
			}
			else
				{
					printf("[%-3f]\n", -1*F[0][1]);
					error=F[0][1];
				}
		}
		else
			if(F[0][0]>F[0][1])
			{
				printf("[%-3f]\n", -1*F[0][0]);
				error=F[0][0];
			}
			else
				{
					printf("[%-3f]\n", -1*F[0][1]);
					error=F[0][1];
				}
		if(error<0.0001)
		{
			sol1=p[0][0];
			sol2=p[0][1];
		}
		printf("\n-------------------------------------------------------\n");
	}
	
	printf("\nSOLUCION ES: X = %-3f  Y = %-3f\nError Abs: %-3f\n", sol1, sol2, error);
}

void SubMenu(float *x, float *y, int *i)
{
	printf("\nIngrese los puntos iniciales\n");
	printf("(SE RECOMIENDA REVISAR SU GRAFICA Y DE AHI TOMAR UN PUNTO INICIAL)\n");
	printf("Punto X: ");
		scanf("%f", x);
	printf("Punto Y: ");
		scanf("%f", y);
	printf("Ingrese el numero de iteraciones: ");
	scanf("%d", i);
}

void InversaDos(float inv[][2], float a[][2])
{
	int i=0, j=0;
	float det, aux=0;
	det = (a[0][0]*a[1][1])-(a[1][0]*a[0][1]);
	aux=a[0][0];
	
	a[0][0]=a[1][1];
	a[0][1]=-1*a[0][1];
	a[1][0]=-1*a[1][0];
	a[1][1]=aux;
	
	//printf("\n\nMatriz cambiada:\n");
	//for(i=0; i<2; i++)
	//{
	//	for(j=0; j<2; j++)
	//	{
	//		printf("[%-3f]", a[i][j]);
	//	}
	//	putchar('\n');
	//}
	
	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			inv[i][j]=(1/det)*a[i][j];
		}
	}
	
	printf("\nMatriz Inversa:\n");
	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			printf("[%-3f]", inv[i][j]);
		}
		putchar('\n');
	}
}

void Sistema2()
{
	float x=0, y=0;
	float sol1=0, sol2=0, error=0;
	int i, j=0, k=0, ite=0;
	printf("\t-SISTEMA 2-\n");
	printf("\n1. f1(x, y) = x2 + y2 - 9 = 0 \n2. f2(x, y) = -ex - 2y - 3 = 0\n");
	SubMenu(&x, &y, &i);
	
	float p[1][1]={0};
	float a[2][2]={0}; //jacobiana
	float F[1][1]={0}; //F(X)
	float inv[2][2]={0}; //inversa jacobiana
	float mult[1][1]={0};
	p[0][0]=x;
	p[0][1]=y;
	
	printf("\n-------------------------------------------------------\n");
	for(ite=0; ite<=i; ite++)
	{
		printf("\tITERACION # %d\n", ite);
		printf("-------------------------------------------------------\n");
		
		printf("\n(x, y)\n[%-3f]\n[%-3f]\n", p[0][0], p[0][1]);
		a[0][0]=2*p[0][0];
		a[0][1]=2*p[0][1];
		a[1][0]=-1*(exp(p[0][0]));
		a[1][1]=-2;
		
		printf("\nJacobiana\n");
		for(j=0; j<2; j++)
		{
			for(k=0; k<2; k++)
			{
				printf("[%-3f]", a[j][k]);
			}
			putchar('\n');
		}
		
		F[0][0]=(pow(p[0][0],2))+(pow(p[0][1],2))-9;
		F[0][1]=(-1*exp(p[0][0]))-(2*p[0][1])-3;
		printf("\nF(X)\n");
		printf("[%-3f]\n[%-3f]\n", F[0][0], F[0][1]);
		
		InversaDos(inv, a);
		mult[0][0]=(inv[0][0]*F[0][0])+(inv[0][1]*F[0][1]);
		mult[0][1]=(inv[1][0]*F[0][0])+(inv[1][1]*F[0][1]);
		
		printf("\nProducto de Jacobiana Inversa con F(X)\n[%-3f]\n[%-3f]\n", mult[0][0],mult[0][1]);
		x=p[0][0];
		y=p[0][1];
		p[0][0]=x-mult[0][0];
		p[0][1]=y-mult[0][1];
		
	printf("\nError Absoluto\n");
		if(F[0][0]<0 && F[0][1]<0)
		{
			if(-1*F[0][0] > -1*F[0][1])
			{
				printf("[%-3f]\n", F[0][0]);
				error=F[0][0];
			}
			else
				{
					printf("[%-3f]\n", -1*F[0][1]);
					error=F[0][1];
				}
		}
		else
			if(F[0][0]>F[0][1])
			{
				printf("[%-3f]\n", -1*F[0][0]);
				error=F[0][0];
			}
			else
				{
					printf("[%-3f]\n", -1*F[0][1]);
					error=F[0][1];
				}
		if(error<0.0001)
		{
			sol1=p[0][0];
			sol2=p[0][1];
		}
		printf("\n-------------------------------------------------------\n");
	}
	printf("\nSOLUCION ES: X = %-3f  Y = %-3f\nError Abs: %-3f\n", sol1, sol2, error);
}

void Sistema3()
{
	float x=0, y=0, z=0;
	
	int i, j=0, k=0, ite=0;
	float sol1=0, sol2=0, sol3=0, error=0;
	printf("\t-SISTEMA 3-\n");
	printf("1. f1(x, y, z) = 2x2 - 4x + y2 + 3z2 + 6z + 2 = 0 \n2. f2(x, y, z) = x2 + y2 - 2y + 2z2 - 5 = 0 \n3. f3(x, y, z) = 3x2 - 12x + y2 - 3z2 + 8 = 0\n");
	SubMenu2(&x, &y, &z, &i);
	float p[3]={0};
	float a[3][3]={0}; //jacobiana
	float F[3]={0}; //F(X)
	float inv[3][3]={0}; //inversa jacobiana
	float mult[3]={0};
	p[0]=x;
	p[1]=y;
	p[2]=z;
	
	
	printf("\n-------------------------------------------------------\n");
	for(ite=0; ite<=i; ite++)
	{
		printf("\tITERACION # %d\n", ite);
		printf("-------------------------------------------------------\n");
		printf("\n(x, y)\n[%-3f]\n[%-3f]\n[%-3f]\n", p[0], p[1], p[2]);
		
		a[0][0]=(4*p[0])-4;
		a[0][1]=2*p[1];
		a[0][2]=(6*p[2])+6;
		a[1][0]=2*p[0];
		a[1][1]=(2*p[1])-2;
		a[1][2]=4*p[2];
		a[2][0]=(6*p[0])-12;
		a[2][1]=2*p[1];
		a[2][2]=-6*p[2];
		printf("\nJacobiana\n");
		for(j=0; j<3; j++)
		{
			for(k=0; k<3; k++)
			{
				printf("[%-3f]", a[j][k]);
			}
			putchar('\n');
		}
	
		F[0]=(2*pow(p[0],2))-(4*p[0])+(pow(p[1],2))+(3*pow(p[2],2))+(6*p[2])+2;
		F[1]=(pow(p[0],2))+(pow(p[1],2))-(2*p[1])+(2*pow(p[2],2))-5;
		F[2]=(3*pow(p[0],2))-(12*p[0])+pow(p[1],2)-(3*pow(p[2],2))+8;
		printf("\nF(X)\n");
		printf("[%-3f]\n[%-3f]\n[%-3f]\n", F[0], F[1], F[2]);
		
		InversaTres(inv, a);
		mult[0]=(inv[0][0]*F[0])+(inv[0][1]*F[1])+(inv[0][2]*F[2]);
		mult[1]=(inv[1][0]*F[0])+(inv[1][1]*F[1])+(inv[1][2]*F[2]);
		mult[2]=(inv[2][0]*F[0])+(inv[2][1]*F[1])+(inv[2][2]*F[2]);
		
		printf("\nProducto de Jacobiana Inversa con F(X)\n[%-3f]\n[%-3f]\n[%-3f]\n", mult[0],mult[1], mult[2]);
		x=p[0];
		y=p[1];
		z=p[2];
		p[0]=x-mult[0];
		p[1]=y-mult[1];
		p[2]=z-mult[2];
		
		printf("\nError Absoluto\n");
		if(F[0]>F[1] && F[0]>F[2])
		{
			printf("[%-3f]\n", abs(F[0]));
			error=F[0];
		}
		else
			if(F[1]>F[0] && F[1]>F[2])
			{
				printf("[%-3f]\n", abs(F[1]));
				error=F[1];
			}
			else
				if(F[2]>F[0] && F[2]>F[1])
				{
					printf("[%-3f]\n", abs(F[2]));
					error=F[2];
				}
		if(error<0.0001)
		{
			sol1=p[0];
			sol2=p[1];
			sol3=p[2];
		}
		printf("\n-------------------------------------------------------\n");
	}
	printf("\nSOLUCION ES: X = %-3f  Y = %-3f  Z = %-3f\nError Abs: %-3f\n", sol1, sol2, sol3, error);
}

void SubMenu2(float *x, float *y, float *z, int *i)
{
	printf("\nIngrese los puntos iniciales\n");
	printf("(SE RECOMIENDA REVISAR SU GRAFICA Y DE AHI TOMAR UN PUNTO INICIAL)\n");
	printf("Punto X: ");
		scanf("%f", x);
	printf("Punto Y: ");
		scanf("%f", y);
	printf("Punto Z: ");
		scanf("%f", z);
	printf("Ingrese el numero de iteraciones: ");
	scanf("%d", i);
}

void InversaTres(float inv[][3], float a[][3])
{
	int i=0, j=0;
	float det, aux=0;
	float adj[3][3]={0}; //adjunta
	float t[3][3]={0}; //traspuesta
	det = ((a[0][0]*a[1][1]*a[2][2])+(a[1][0]*a[2][1]*a[0][2])+(a[2][0]*a[0][1]*a[1][2]))-((a[0][2]*a[1][1]*a[2][0])+(a[1][2]*a[2][1]*a[0][0])+(a[2][2]*a[0][1]*a[1][0]));
	printf("\nDet |A| = %-3f", det);
	
	adj[0][0]=(a[1][1]*a[2][2])-(a[2][1]*a[1][2]);
	adj[0][1]=-1*((a[1][0]*a[2][2])-(a[2][0]*a[1][2]));
	adj[0][2]=(a[1][0]*a[2][1])-(a[2][0]*a[1][1]);
	
	adj[1][0]=-1*((a[0][1]*a[2][2])-(a[2][1]*a[0][2]));
	adj[1][1]=(a[0][0]*a[2][2])-(a[2][0]*a[0][2]);
	adj[1][2]=-1*((a[0][0]*a[2][1])-(a[2][0]*a[0][1]));
	
	adj[2][0]=(a[0][1]*a[1][2])-(a[1][1]*a[0][2]);
	adj[2][1]=-1*((a[0][0]*a[1][2])-(a[1][0]*a[0][2]));
	adj[2][2]=(a[0][0]*a[1][1])-(a[1][0]*a[0][1]);
	
	printf("\nAdjunta de A:\n");
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("[%-3f]", adj[i][j]);
		}
		putchar('\n');
	}
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			t[j][i]=adj[i][j];
		}
	}
	
	printf("\nTraspuesta de Adj:\n");
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("[%-3f]", t[i][j]);
		}
		putchar('\n');
	}
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			inv[i][j]=(1/det)*t[i][j];
		}
	}
	
	printf("\nMatriz Inversa:\n");
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("[%-3f]", inv[i][j]);
		}
		putchar('\n');
	}
}

void Sistema4()
{
	float x=0, y=0, z=0;
	int i, j=0, k=0, ite=0;
	float sol1=0, sol2=0, sol3=0, error=0;
	printf("\t-SISTEMA 4-\n");
	printf("1. f1(x, y, z) = x2 - 4x + y2 = 0 \n2. f2(x, y, z) = x2 - x - 12y + 1 = 0 \n3. f3(x, y, z) = 3x2 - 12x + y2 - 3z2 + 8 = 0  \n");
	SubMenu2(&x, &y, &z, &i);
	float p[3]={0};
	float a[3][3]={0}; //jacobiana
	float F[3]={0}; //F(X)
	float inv[3][3]={0}; //inversa jacobiana
	float mult[3]={0};
	p[0]=x;
	p[1]=y;
	p[2]=z;
	
	printf("\n-------------------------------------------------------\n");
	for(ite=0; ite<=i; ite++)
	{
		printf("\tITERACION # %d\n", ite);
		printf("-------------------------------------------------------\n");
		printf("\n(x, y)\n[%-3f]\n[%-3f]\n[%-3f]\n", p[0], p[1], p[2]);
		
		a[0][0]=(2*p[0])-4;
		a[0][1]=2*p[1];
		a[0][2]=0;
		a[1][0]=(2*p[0])-1;
		a[1][1]=-12;
		a[1][2]=0;
		a[2][0]=(6*p[0])-12;
		a[2][1]=2*p[1];
		a[2][2]=-6*p[2];
		printf("\nJacobiana\n");
		for(j=0; j<3; j++)
		{
			for(k=0; k<3; k++)
			{
				printf("[%-3f]", a[j][k]);
			}
			putchar('\n');
		}
	
		F[0]=(pow(p[0],2))-(4*p[0])+(pow(p[1],2));
		F[1]=(pow(p[0],2))-p[0]-(12*p[1])+1;
		F[2]=(3*pow(p[0],2))-(12*p[0])+pow(p[1],2)-(3*pow(p[2],2))+8;
		printf("\nF(X)\n");
		printf("[%-3f]\n[%-3f]\n[%-3f]\n", F[0], F[1], F[2]);
		
		InversaTres(inv, a);
		mult[0]=(inv[0][0]*F[0])+(inv[0][1]*F[1])+(inv[0][2]*F[2]);
		mult[1]=(inv[1][0]*F[0])+(inv[1][1]*F[1])+(inv[1][2]*F[2]);
		mult[2]=(inv[2][0]*F[0])+(inv[2][1]*F[1])+(inv[2][2]*F[2]);
		
		printf("\nProducto de Jacobiana Inversa con F(X)\n[%-3f]\n[%-3f]\n[%-3f]\n", mult[0],mult[1], mult[2]);
		x=p[0];
		y=p[1];
		z=p[2];
		p[0]=x-mult[0];
		p[1]=y-mult[1];
		p[2]=z-mult[2];
		
		printf("\nError Absoluto\n");
		if(F[0]>F[1] && F[0]>F[2])
		{
			printf("[%-3f]\n", abs(F[0]));
			error=F[0];
		}
		else
			if(F[1]>F[0] && F[1]>F[2])
			{
				printf("[%-3f]\n", abs(F[1]));
				error=F[1];
			}
			else
				if(F[2]>F[0] && F[2]>F[1])
				{
					printf("[%-3f]\n", abs(F[2]));
					error=F[2];
				}
				
		if(error<0.0001)
		{
			sol1=p[0];
			sol2=p[1];
			sol3=p[2];
		}
		printf("\n-------------------------------------------------------\n");
	}
	printf("\nSOLUCION ES: X = %-3f  Y = %-3f  Z = %-3f\nError Abs: %-3f\n", sol1, sol2, sol3, error);
}
