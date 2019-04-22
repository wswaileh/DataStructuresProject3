typedef struct City* city;

struct City{
    char cityName[51];
    int rank;
    float numOfTourists;
    city next;
};

typedef struct City* cititesLIST;



city findLast(city);
void addLast(city ,char *,int ,float);



void addLast(city a,char *name,int rank,float tourists)
{

    //creating the new node
    city newNode = (city) malloc(sizeof(struct City));
    newNode -> next = NULL;
    strcpy(newNode->cityName,name);
    newNode->rank = rank;
    newNode->numOfTourists = tourists;

    city last = findLast(a);
    last -> next = newNode;

}
city findLast(city a)
{
    city temp=a;
    while (  temp->next != NULL )
        temp = temp->next;
    return temp;
}

void printList(city a)
{
    if (a == NULL)
        printf("Empty List!\n");
    else
    {
        city temp=a->next;
        while (temp != NULL){
            printf("City : %s , Rank = %d , Tourists Number = %.2f\n",temp->cityName,temp->rank,temp->numOfTourists);
            temp = temp->next;
        }

    }

}

int isCityInList(city a,char *cityName)
{
    city temp = a->next;
    while (temp!=NULL)
    {
        if (strcmp(temp->cityName,cityName)==0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int countCities(city A)
{
    city temp = A->next;
    int counter = 0;
    while (temp!=NULL)
    {
        counter++;
        temp = temp->next;
    }
    return counter;
}
