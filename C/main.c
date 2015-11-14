#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    unsigned  i = 1;
    unsigned  j = 0;
    char * token;
    int parse_int;

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
                switch (i) //Different cases
                    {
                        case 1 :
                            hooker[hooker_cnt].id  = atoi(token);
                            i++;
                            printf("Item loaded %d\n",hooker[hooker_cnt].id);
                            break;
                        case 2 :
                            strncpy(hooker[hooker_cnt].name, token, sizeof(hooker[hooker_cnt].name)-1 );
                            hooker[hooker_cnt].name[sizeof(hooker[hooker_cnt].name)-1] = '\0';
                            i++;
                            printf("Item loaded %s\n",hooker[hooker_cnt].name);
                            break;
                        case 3 :
                            hooker[hooker_cnt].age  = atoi(token);
                            i++;
                            printf("Item loaded %d\n", hooker[hooker_cnt].age);
                            break;
                        case 4 :
                            hooker[hooker_cnt].status  = atoi(token);
                            i++;
                            printf("Item loaded %d\n", hooker[hooker_cnt].status);
                            break;
                        case 5 :
                            hooker[hooker_cnt].skill  = atoi(token);
                            i++;
                            printf("Item loaded %d\n", hooker[hooker_cnt].skill);
                            break;
                        case 6 :
                            hooker[hooker_cnt].price  = atoi(token);
                            i++;
                            printf("Item loaded %d\n", hooker[hooker_cnt].price);
                            break;
                        case 7 :
                            printf("All data have been loaded.\n");
                            i=1;
                            system("pause\n");
                            break;
                    }

            token = strtok(NULL, ";" );
            parse_int = !parse_int;
                }
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
