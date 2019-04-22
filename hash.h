
struct hashNode
{
    char countryName[20];
    int numOfCities ;
    double totalTourist ;
    int status; //0 empty 1 used 2 deleted
};

typedef struct hashNode* hashptr;
hashptr *table;
int tableSize;
void deleteInTable()
{
    char country[51];
    printf("Enter The Country You Want To Delete : \n");
    getchar();
    gets(country);
    if (deleteFromHashTable(country,tableSize)!=-1)
        printf("Deleted Successfully!\n");
    else
        printf("Country Is NOT In Hash Table.\n");
}
void searchInTable()
{
    char country[51];
    printf("Enter The Country You Are Looking For : \n");
    getchar();
    gets(country);
    int i = searchInHash(country,&tableSize);
    if (i == -1)
        printf("Country Not Found!\n");
    else
        printf("Country : %s , Index In Hashtable = %d , # Of Cities : %d , # Of Tourists : %.1f .\n",table[i]->countryName,i,table[i]->numOfCities,table[i]->totalTourist);

}

void fillTreeInTable(AVL T)
{
    if (T!=NULL)
    {
        fillTreeInTable(T->left);
        insertInHashTable(T->countryName,countCities(T->cities),T->numOfTourists);
        fillTreeInTable(T->right);
    }
}

void insertInHashTable (char hash_name[],int hash_cities,double hash_tor)
{
    int quadIndex =  QuadraticIndex(hash(hash_name));
    strcpy(table[quadIndex]->countryName,hash_name);
    table[quadIndex]->numOfCities = hash_cities;
    table[quadIndex]->totalTourist = hash_tor ;
    table[quadIndex]->status = 1;
    int numOfEntries = countEntries();
    if ( numOfEntries > tableSize/2 )
        Rehash();
}


void createHashTable (AVL T)
{
    if (countNodes(T)>0)
    {
        tableSize = firstPrimeAfter2x(countNodes(T));
        table =  (hashptr) malloc ( (tableSize) * sizeof(struct hashNode) );
        int i;
        for (i=0; i<tableSize; i++)
        {
            table[i]= (hashptr)malloc(sizeof(struct hashNode));
            table[i]-> status =0;
        }
        fillTreeInTable(T);
        printf("Table Created Successfully!\n");
    }

}


int isPrime (int x)
{
    int i;
    for (i=2 ; i<= x/2 ; i++)
    {
        if (x%i == 0)
            return 0;
    }
    return 1;
}
// This function returns the first prime after a specific number.
int firstPrimeAfter2x (int x)
{
    int i;
    for (i=2*x ; ; i++)
    {
        if (isPrime(i)==1)
            return i;
    }
}

//This function returns the next empty index based on Quadratic Hashing.
int QuadraticIndex ( int index )
{
    if (table[index%tableSize]->status==0)
        return index;
    int i=1;
    int nextIndex = (index + i*i)%tableSize;
    while (table[nextIndex]->status ==1)
    {
        i++;
        nextIndex = (index + i*i)%tableSize;
    }
    return nextIndex;
}
//This Function is used when the user wants to add a country to the hash table
void insertToTable()
{
    char country[51];
    int numOfCities;
    float numOfTourists;
    printf("Enter The Name Of The Country You Want To Add : \n");
    getchar();
    gets(country);
    printf("Enter The Number Of Cities In %s:\n",country);
    scanf("%d",&numOfCities);
    printf("Enter The Number Of Tourists In %s:\n",country);
    scanf("%f",&numOfTourists);
    insertInHashTable(country,numOfCities,numOfTourists);
    printf("Country %s Added Successfully.\n",country);

}

int countEntries()
{
    int i,num=0;
    for (i=0; i<tableSize; i++)
        if (table[i]->status==1)
            num++;
    return num;
}

void printHashTable ( )
{

    printf("-------------------------------------------------------------------------------------------------\n");
    printf("\t%-15s%-15s%-25s%s\n", "INDEX", "Country","Number of Cities","Total Tourists");
    printf("-------------------------------------------------------------------------------------------------\n");
    int i;
    for (i=0 ; i<tableSize ; i++)
    {
        printf("\t %-14d", i);
        if (table[i]->status == 2)
            printf("*DELETED\n");

        else if (table[i]->status ==0)
            printf("*EMPTY\n");

        else
        {
            printf("%-20s%-20d%.1f\n",table[i]->countryName, table[i]->numOfCities, table[i]->totalTourist);
        }
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
}


void Rehash ( )
{
    printf("entered rehash\n");
    if (tableSize != 0)
    {
        int i;
        int numOfEntries=0;
        int temp =tableSize;
        hashptr* newTable = (hashptr) malloc ( sizeof (hashptr) *(temp));
        for (i=0; i<temp; i++)
        {
            newTable[i]= malloc(sizeof(struct hashNode));
            if (table[i]->status ==1)
            {
                numOfEntries++;
                strcpy(newTable[i]->countryName,table[i]->countryName);
                newTable[i]->numOfCities=table[i]->numOfCities;
                newTable[i]->totalTourist=table[i]->totalTourist;
                newTable[i]->status= 1;
            }
            else
                newTable[i]->status = 0;
            free(table[i]);
        }
        if (numOfEntries>0)
        {
            tableSize = firstPrimeAfter2x(numOfEntries);
            table =  malloc ( sizeof (hashptr) *(tableSize));
            int i;
            for (i=0; i<tableSize; i++)
            {
                table[i]= (hashptr)malloc(sizeof(struct hashNode));
                table[i]->status=0;
            }
        }
        for (i=0 ; i<temp ; i++)
        {
            if (newTable[i]->status == 1)
            {
                insertInHashTable(newTable[i]->countryName,newTable[i]->numOfCities,newTable[i]->totalTourist);
                free(newTable[i]);
            }
        }
    }
}


//This function searches for a specific word in the hash table.
int searchInHash (char word [])
{
    int index = hash(word);
    int i=0;
    int newIndex= (index + i*i)%tableSize;
    while (table[newIndex]->countryName != NULL && strcasecmp(word, table[newIndex]->countryName)!= 0 )
    {
        i++;
        newIndex= (index + i*i)%tableSize;
        if (table[newIndex]->status==0)
            return -1;
    }
    if (table[newIndex]->countryName != NULL && table[newIndex]->status ==1 )
        return newIndex;
    else
        return -1;
}


// This function deletes a specific word from the hash table.
int deleteFromHashTable (char word[])
{
    int target = searchInHash( word);
    if (target != -1 )
        table[target]->status =2;

    return target;
}





void printHashTableInFile ()
{

    FILE*out=fopen("finalOutput.txt","w");

    fprintf(out,"-------------------------------------------------------------------------------------------------\n");
    fprintf(out,"\t%-15s%-15s%-15s\t%s\n", "INDEX", "Country","Number of Cities","Total Tourists");
    fprintf(out, "-------------------------------------------------------------------------------------------------\n");
    int i;
    for (i=0 ; i<tableSize ; i++)
    {
        fprintf(out, "\t %-14d", i);
        if (table[i]->status ==2)
            fprintf(out, "*DELETED\n");

        else if (table[i]->status == 0 )
            fprintf(out, "*EMPTY\n");

        else
        {
            fprintf(out, "%-15s%-15d%.1f",table[i]->countryName, table[i]->numOfCities, table[i]->totalTourist);
        }

        fprintf(out,"\n");
    }

    fprintf(out, "-----------------------------------------------------------------------------------------------------\n");

    fclose(out);
    printf("Data Written To File Successfully.\n");
}

//This function returns hash value for a String.
int hash (char*s)
{
    long hashValue =0;
    while (*s!= '\0')
        hashValue = (hashValue << 5)+ *(s++);
    return abs(hashValue%tableSize);
}

int getTableSize()
{
    return tableSize;
}

