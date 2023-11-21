#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
	char name[100];
	int age;
}; 

void printStudent(Student s){
	printf("%d - %s, %d years old\n", &s, s.name, s.age);
}

int main()
{
	/*
	Pointer & Array
	Struct
	*/
	
//	Student[]= {isi}, {}, {isi}, {isi}, {isi};
//	Student*[]= NULL, NULL, *{isi}, NULL;
	
	char names[][100]= {"Ghoran", "Delvin", "Daniel"};
	int ages[]= {20, 30, 15};
	
	Student *students[3];
	for(int i=0; i<3; i++)
	{
		students[i]= (Student*)malloc(sizeof(Student));
		strcpy(students[i]->name, names[i]);
		students[i]->age= ages[i];
	}
	
	free(students[0]);
	students[0]=NULL;
	
	for(int i=0; i<3; i++)
	{
		if(students[i]!=NULL)
		{
			printf("Index %d: %s, %d years old\n", i, students[i]->name, students[i]->age);
		}
		else
		{
			printf("index %d: NULL\n", i);
		}
	}
	
//	Student *sp1 = NULL;
	Student *sp1 = (Student*)malloc(sizeof(Student)); //langkah langkah alocate memori ke pointer
	strcpy(sp1 -> name, "Budi");
	sp1 -> age = 10;
	printf("%s, %d years old\n", sp1->name, sp1->age);
	free(sp1);//cuma bisa free struct yang ada pointernya
	sp1 = NULL; //null pointer access, menggunakan sesuatu yang tidak ada
	printf("%s, %d years old\n", sp1->name, sp1->age);
	
//	Student s1;
//	strcpy(s1.name, "Budi");
//	s1.age = 10;
//	printStudent(s1);
	
//	Student[]= {isi}, {}, {isi}, {isi};
//	
//	char names[][100]= {"Ghoran", "Delvin", "Daniel"};
//	int ages[]= {20, 30, 15};
//	
//	Student students[3];
//	for(int i=0; i<3; i++)
//	{
//		strcpy(students[i].name, names[i]);
//		students[i].age= ages[i];
//	}
	
//	Student s= students[1];
//	students[3]= s;
//	strcpy(students[1].name, "Delvin Anderson");

//	Student *komti = &students[1];
//	strcpy((*komti).name, "Delvin Anderson");
//	strcpy(komti -> name, "Delvin Anderson");
//	
//	for(int i=0; i<4; i++)
//	{
//		printf("%d - %s, %d years old\n", &students[i], students[i].name, students[i].age);
//	//	printStudent(students[i]);
//	}
//	
//	printf("Komti %s %d\n", komti -> name, komti -> age);
//	
//	int scores[] = {100, 98, 95, 90};
//	//			   1000 1004 1008 1012
//	
////	printf("%d\n", scores[3]);
//
//	int size= sizeof(scores) / sizeof(scores[0]);
//	
//	for(int i=0; i<size; i++)
//	{
//		printf("Index %d. %d - %d\n", i, &scores[i], scores[i]);
//	}
//	
//	char names[][100]= {"Ghoran", "Delvin", "Daniel"};
	//[untuk stringnya][untuk characternya]
	
//	int a = 5; //address, 4
//	int *b = &a; //pointer menunjuak address
//	*b = 20;
//	int **c = &b;
//	
//	printf("address of a: %d\n", &a);
//	printf("value of a: %d\n", a);
//	printf("\n");
//	printf("address of b: %d\n", &b);
//	printf("value of b: %d\n", b);
//	printf("value of *b: %d\n", *b);
//	printf("\n");
//	printf("address of c: %d\n", &c);
//	printf("value of c: %d\n", c);
//	printf("value of *c: %d\n", *c);
//	printf("value of **c: %d\n", **c);
	
	return 0; 
}