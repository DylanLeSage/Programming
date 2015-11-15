#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum
{
    HOOKER_ID = 0,
    HOOKER_NAME = 1,
    HOOKER_AGE = 2,
    HOOKER_STAT = 3,
    HOOKER_SKILL = 4,
    HOOKER_PRICE = 5,
    HOOKER_ATT_COUNT
} hparse_e;
/*
- Unikatni ID
- Jmeno zamestnance
- Vek
- Zdravotni stav    (hodnoty 0 - 10) -> 0  = "It's better to fuck a dead donkey.
- Sexualni zdatnost (hodnoty 0 - 10) -> 10  = Porn Star, Anal Princess, Blowjob Queen, etc.
- Cena za full service
*/
struct Hooker
{
        int id;
        char name[256];
        int age;
        int status;
        int skill;
        int price;
};

typedef struct Hooker hooker_t;

hooker_t hooker[15];


/*
  strtok, fopen, fwrite, fclose

 */

int main()
{
    const char * file_name = "hooker_15.csv";
    FILE *fd = NULL;
    char line[1024];

    unsigned  hooker_cnt = 0; /// counter of filled structures
    hparse_e  i = HOOKER_ID;
    unsigned  j = 0;
    char * token;

    /*** BEGIN Hooker open file */
    fd = fopen(file_name, "r");

    if(fd == NULL)
    {
        perror("Error fopen ");
    }
    else
    {
        printf("Your file : %s have been succesfully loaded.\n\n",file_name);
        system("pause\n");
    }
    /*** END of Hooker open file */

    /*** BEGIN Hooker process file */

    while ( fgets( line, sizeof(line), fd) != NULL) //|| hooker_cnt < (sizeof(hooker) / sizeof(hooker_t)))
    {
        token = strtok( line, ";" );

            while ( token != NULL)
            {
                #define HPARSE_HELPER_INT(X) \
                                    X(HOOKER_ID,    id)\
                                    X(HOOKER_AGE,   age)\
                                    X(HOOKER_STAT,  status)\
                                    X(HOOKER_SKILL, skill)\
                                    X(HOOKER_PRICE, price)

                #define HPARSE_HELPER_STRING(X) \
                                    X(HOOKER_NAME, name)
                switch(i)
                {

                #define X(enum, att) \
                    case enum: \
                        hooker[hooker_cnt].att  = atoi(token); \
                        printf("Item loaded %d\n",hooker[hooker_cnt].att);\
                        break;
                HPARSE_HELPER_INT(X)
                #undef X

                #define X(enum, att) \
                    case enum: \
                            strncpy(hooker[hooker_cnt].att, token, sizeof(hooker[hooker_cnt].att)-1 );\
                            hooker[hooker_cnt].att[sizeof(hooker[hooker_cnt].att)-1] = '\0';\
                            printf("Item loaded %s\n",hooker[hooker_cnt].att);\
                            break;
                HPARSE_HELPER_STRING(X)
                #undef X

                default:
                    printf("Unknown parse state!!\n");
                }

                i = (i + 1) % HOOKER_ATT_COUNT;
                token = strtok(NULL, ";" );
       }

    for( j = 0; j < hooker_cnt; j++)
    {
        printf("Structure no ( %d ) :\n Name -> %s\n    Age -> %d   Health status -> %d   Skills -> %d\nPrice - %d\n\n", hooker[i].id, hooker[i].name, hooker[i].age, hooker[i].status, hooker[i].skill, hooker[i].price);
    }


    while(!feof(fd))
    {
        /// fd is not NULL
        line[0] = 0;
        fgets(line, sizeof(line)-1, fd);
        line[sizeof(line)-1] = '\0';
        printf("%s", line);
    }

    /*** END of Hooker process file */

    /// close Hooker file
    fclose(fd);

    return 0;
}
