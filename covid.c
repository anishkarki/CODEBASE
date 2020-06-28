#include <stdio.h>
#include <time.h>
#include <string.h>

#define FILE_NAME "covid.bin"



typedef struct
{
    char country[20];
    unsigned int active;
    unsigned int recovered;
    unsigned int deaths;
} s_countryinfo;

int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;

    len = strlen(name);

    for(index=0;index<len;++index)
    {
        if (!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName=0;
            break;
        }
    }
    return validName;
}

void addCovidDatabase()
{
    s_countryinfo addCovidINFODatabase = {0};
    printf("\nADD new COUNTRY's INFO:");
    printf("\nEnter Details Below:");
    printf("\nCountry name = ");
    scanf("%s",&addCovidINFODatabase.country);
    printf("Checking for the existing same country...\n");
    deleteCountry(addCovidINFODatabase.country);
    printf("\nActive Cases = ");
    scanf("%u",&addCovidINFODatabase.active);
    printf("Death cases = ");
    scanf("%u",&addCovidINFODatabase.deaths);
    printf("Recovered = ");
    scanf("%u",&addCovidINFODatabase.recovered);
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if (fp == NULL)
    {
        printf("\nFile is not opened.");
        exit(1);
    }
    fwrite(&addCovidINFODatabase,sizeof(addCovidINFODatabase),1,fp);
    fclose(fp);
}

void viewinfo()
{
    int found = 0;
    char countryname[20] = {};
    s_countryinfo addCovidINFODatabase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countData = 1;
    printf("\nDetails:");
    fp =fopen(FILE_NAME,"rb");
    if (fp==NULL)
    {
        printf("\nNo database");
        exit(0);
    }
    while (fread(&addCovidINFODatabase,sizeof(addCovidINFODatabase),1,fp))
    {
        printf("\n==========================================");
        printf("\n Country Name = %s",addCovidINFODatabase.country);
        printf("\n Active = %u",addCovidINFODatabase.active);
        printf("\n recovered = %u",addCovidINFODatabase.recovered);
        printf("\n Death = %u",addCovidINFODatabase.deaths);
        printf("\n==========================================");
        found = 1;
        ++countData;
    }
    fclose(fp);
    if (!found)
    {
        printf("\nNo datafound!");
    }
    printf("\nPress any key!");
    fflush(stdin);
    getchar();
}

void searchCases()
{
    int uchoice;
    char cinp[1];
    char inputsname[3] = {0,0,0};
    int choiceinp;
    int found = 0;
    char country[20] = {};
    s_countryinfo addCovidINFODatabase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countData = 1;
    printf("\nDetails:");
    fp =fopen(FILE_NAME,"rb");
    if (fp==NULL)
    {
        printf("\nNo database");
        exit(0);
    }
    printf("\nSearch COVID DATA!");
    printf("\nEnter the Country's Name to search:");
    scanf("%s",&country);
    printf("\nDo you want all the data?[Y/n]");
    scanf("%s",&cinp);
    if (!strcmp(cinp, "Y"))
    {
        inputsname[0] = 1;
        inputsname[1] = 1;
        inputsname[2] = 1;
    }
    else{
        printf("\n1. Active Cases");
        printf("\n2. Recovered Cases");
        printf("\n3. Deaths");
        printf("\n4. Active and Recovered");
        printf("\n5. Active and Deaths");
        printf("\n6. Recovered and Deaths");
        printf("\nEnter your choice=>");
        scanf("%d",&uchoice);
        switch(uchoice)
        {
        case 1:
            inputsname[0] = 1;
            break;
        case 2:
            inputsname[1] = 1;
            break;
        case 3:
            inputsname[2] = 1;
            break;
        case 4:
            inputsname[0] = 1;
            inputsname[1] = 1;
            break;
        case 5:
            inputsname[0] = 1;
            inputsname[2] = 1;
            break;
        case 6:
            inputsname[1] = 1;
            inputsname[2] = 1;
            break;
        }
    }
    while (fread(&addCovidINFODatabase,sizeof(addCovidINFODatabase),1,fp))
    {
        if (!strcmp(addCovidINFODatabase.country,country))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n=====================================================");
        printf("\nCountry Name = %s",addCovidINFODatabase.country);
        if (*inputsname == 1)
        {
        printf("\nActive = %u",addCovidINFODatabase.active);
        }
        if (*(inputsname+1) == 1)
        {
        printf("\nRecovered = %u",addCovidINFODatabase.recovered);
        }
        if (*(inputsname+2) == 1)
        {
        printf("\nDeaths = %u",addCovidINFODatabase.deaths);
        }
        printf("\n=======================================================");

    }
    else
    {
        printf("\n\t No record for %s",country);
    }
    fclose(fp);
    printf("\n Press any key to go to main menu....");
    getchar();
}
void deleteCountry(char country[20])
{
    int found = 0;
    int countryDelete = 0;
    char countryname[20] = {0};
    s_countryinfo addCovidINFODatabase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    printf("\nDeleting the country info!");

    fp = fopen(FILE_NAME,"rb");
    if (fp == NULL)
    {
        printf("\nFile not found.");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if (tmpFp == NULL)
    {
        fclose(fp);
        printf("\nFile is not opened");
        exit(1);
    }
    printf("\nThe country updated:%s",country);
    while(fread(&addCovidINFODatabase,sizeof(addCovidINFODatabase),1,fp))
    {
        if (!strcmp(addCovidINFODatabase.country,country))
        {
            found = 1;
        }
        else
        {
            fwrite(&addCovidINFODatabase,sizeof(addCovidINFODatabase),1,tmpFp);
        }
    }
    (found)? printf("\nRecord deleted successfully...."):printf("\nRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}

void menu()
{
    char countryname[20];
    int choice = 0;
    do
    {
        printf("\n1. Add data");
        printf("\n2. Search data");
        printf("\n3. View data");
        printf("\n4. Delete Record");
        printf("\n0. Exit");
        printf("\nEnter choice=>");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addCovidDatabase();
            break;
        case 2:
            searchCases();
            break;
        case 3:
            viewinfo();
            break;
        case 4:

            printf("\nEnter the name of country:");
            scanf("%s",&countryname);
            deleteCountry(countryname);
            break;
        case 0:
            printf("\nEXITING");
            break;
        default:
            printf("\nInvalid choice");

        }
    }
    while(choice != 0);
}
int isFileExists(const char *path)
{
    FILE *fp = fopen(path,"rb");
    int status = 0;
    if (fp!=NULL)
    {
        status = 1;
        fclose(fp);
    }
    return status;
}

void init()
{
    FILE *fp = NULL;
    int status = 0;
    status = isFileExists(FILE_NAME);

    if (!status)
    {
        //create a binary file
        fp = fopen(FILE_NAME,"wb");
        if (fp!=NULL)
        {

            fclose(fp);
        }
    }
    menu();
}
int main()
{
    init();
    return 0;
}
