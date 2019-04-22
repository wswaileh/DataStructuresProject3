#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "avl.h"
#include "hash.h"

AVL readFromFile(AVL);
AVL insertCountryMenu(AVL);
AVL addCityMenu(AVL );


int main()
{
    int choice;
    AVL T=NULL;

    showMenu();
    scanf("%d",&choice);
    while (choice != 3)
    {

        if (choice == 1)
        {
            showTreeMenu();
            scanf("%d",&choice);
            while (choice != 8)
            {
                switch (choice)
                {
                case 1 :
                    T = readFromFile(T);
                    break;
                case 2:
                    T = insertCountryMenu(T);
                    break;
                case 3 :
                    deleteCountryMenu(T);
                    break;
                case 4 :
                    inOrder(T);
                    printf("\n");
                    break;
                case 5 :
                    T = addCityMenu(T);
                    break;
                case 6 :
                    printf("The Height Of The Tree Is %d\n",height(T));
                    break;
                case 7 :
                    searchCountry(T);
                    break;
                case 8:
                    break;
                }
                showTreeMenu();
                scanf("%d",&choice);
            }
        }

        else
        {
            showTableMenu();
            scanf("%d",&choice);
            while (choice != 9)
            {
                switch(choice)
                {
                case 1:
                    createHashTable(T);
                    break;
                case 2:
                    printHashTable();
                    break;
                case 3:
                    printf("Table Size = %d.\n",getTableSize());
                    break;
                case 4:
                    printf("((hashValue << 5)+ *(s++))%tableSize.\n");
                    break;
                case 5:
                    insertToTable();
                    break;
                case 6:
                    searchInTable();
                    break;
                case 7:
                    deleteInTable();
                    break;
                case 8:
                    printHashTableInFile();
                case 9:
                    break;
                case 10:
                    printf("%d\n",countEntries());
                    break;
                }
                showTableMenu();
                scanf("%d",&choice);
            }
        }
        showMenu();
        scanf("%d",&choice);
    }

    return 0;

}


void showMenu()
{
    printf(" _______________________________________________________\n");
    printf("| Enter The Number Of Operation You Want To Do Please : |\n");
    printf("|     1.Show Tree Menu.                                 |\n");
    printf("|     2.Show Table Menu.                                |\n");
    printf("|     3.Exit.                                           |\n");
    printf("|_______________________________________________________|\n");
    printf("# Of Operation : ");
}
void showTreeMenu()
{
    printf(" _______________________________________________________\n");
    printf("| Enter The Number Of Operation You Want To Do Please : |\n");
    printf("|     1.Read From File.                                 |\n");
    printf("|     2.Insert Country.                                 |\n");
    printf("|     3.Delete Country.                                 |\n");
    printf("|     4.Print Tree inorder.                             |\n");
    printf("|     5.Add A City To A Country.                        |\n");
    printf("|     6.Print Tree Height.                              |\n");
    printf("|     7.Search For A Country.                           |\n");
    printf("|     8.Back                                            |\n");
    printf("|_______________________________________________________|\n");
    printf("# Of Operation : ");
}

void showTableMenu()
{
    printf(" _______________________________________________________\n");
    printf("| Enter The Number Of Operation You Want To Do Please : |\n");
    printf("|     1.Create Table.                                   |\n");
    printf("|     2.Print Hash Table.                               |\n");
    printf("|     3.Print Table Size.                               |\n");
    printf("|     4.Print Out Used Hash Function.                   |\n");
    printf("|     5.Insert New Record To Hash Table.                |\n");
    printf("|     6.Search For A Specific Record.                   |\n");
    printf("|     7.Delete A Specific Record.                       |\n");
    printf("|     8.Save Hash Table To File.                        |\n");
    printf("|     9.Back                                            |\n");
    printf("|_______________________________________________________|\n");
    printf("# Of Operation : ");
}


void searchCountry(AVL T)
{
    char name[51];
    printf("Enter The name of the country: \n");
    scanf("%s",name);
    AVL temp = findCountryInTree(T,name);
    if (!isCountryInTree(T,name))
        printf("Country Not Found!\n");
    else
    {
        printf("Country was Found , Total Tourists = %.2f , The Cities Are : \n",findCountryInTree(T,name)->numOfTourists);
        printList(findCountryInTree(T,name)->cities);
    }
}
AVL addCityMenu(AVL T1)
{
    AVL T = T1;
    char country[51],name[51];
    int rank;
    float numOfTourists;
    printf("Enter The Country Name :\n");
    getchar();
    gets(country);
    printf("Enter The City Name:\n");
    gets(name);
    printf("enter The Rank And Number Of Tourists Seperated by space:\n");
    scanf("%d %f",&rank,&numOfTourists);

    if (isCountryInTree(T,country))
    {
        if (isCityInList(findCountryInTree(T,country)->cities,name))
            printf("City Already Added!\n");
        else
        {
            addLast(findCountryInTree(T,country)->cities,name,rank,numOfTourists);
            printf("City %s Was Added Successfully!\n",name);
        }

    }
    else
    {
        printf("Country Is Not Found In Tree ! Do You Want To Add It ? 1 for yes 0 for no:\n");
        int choice;
        scanf("%d",&choice);
        if (!choice)
            printf("Country And City Weren't Added.\n");
        else
        {
            T=insert(T,country);
            addLast(findCountryInTree(T,country)->cities,name,rank,numOfTourists);
        }
    }
    return T;
}

AVL insertCountryMenu(AVL T)
{
    AVL T1=T;
    char name[51];
    printf("Enter The Name Of The Country You Want To Insert : \n");
    getchar();
    gets(name);
    if (!isCountryInTree(T1,name))
    {
        T1=insert(T1,name);
        findCountryInTree(T1,name)->numOfTourists=0;
        printf("Country Inserted Successfully!\n");
    }
    else
        printf("Country Is Already In tree !\n");
    return T1;
}

void deleteCountryMenu(AVL T)
{

    if (T==NULL)
        printf("Tree Is Empty!\n");
    else
    {
        char countryName[51];
        int choice;
        printf("Enter The Name Of The Country You Want To Delete : \n");
        getchar();
        gets(countryName);
        printf("Warning! The Following Cities In %s Will Be Deleted!\n",countryName);
        printList(findCountryInTree(T,countryName)->cities);
        printf("Are You Sure You Want To Delete %s ? if yes enter 1 , if not enter 0 please : \n",countryName);
        scanf("%d",&choice);
        if (choice)
        {
            deleteNode(T,countryName);
            printf("Country Deleted Successfully.\n");
        }
        else
            printf("The Country Is Not Deleted.\n");
    }
}

AVL readFromFile(AVL T1)
{
    AVL T = T1;
    FILE *in = fopen("cities.txt","r");
    char line[101],*token,*country;

    while (fgets(line,101,in))
    {
        char tokens[4][30];
        token = strtok(line,"*");
        int i=0;
        while (token!=NULL)
        {
            strcpy(tokens[i++],token);
            token = strtok(NULL,"\n*");
        }

        if (isCountryInTree(T,tokens[2]))
        {
            addLast(  findCountryInTree(T,tokens[2])->cities,tokens[1],atoi(tokens[0]),atof(tokens[3]));
            findCountryInTree(T,tokens[2])->numOfTourists += atof(tokens[3]);
        }

        else
        {
            T = insert(T,tokens[2]);
            findCountryInTree(T,tokens[2])->cities = (city) malloc(sizeof(struct City));
            findCountryInTree(T,tokens[2])->cities->next = NULL;
            addLast(  findCountryInTree(T,tokens[2])->cities,tokens[1],atoi(tokens[0]),atof(tokens[3]));
            findCountryInTree(T,tokens[2])->numOfTourists = atof(tokens[3]);

        }

    }
    printf("File Read Successfully!\n");
    return T;
}


