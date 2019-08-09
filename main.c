#include<stdio.h>
#include<stdlib.h>

typedef struct  _hockeyPlayer
{
    char Name[100];
    char Team[100];
    int numGoals[100];
    int totalGoals;
    float avgGoals;

} hockeyPlayer;

int globalGoalsTotal =0;
float globalGoalsAvg =0;
int numGames = 0;
int size = 0;
int playerIndex = 0 ;
int goalIndex = 0 ;

const char DetermineRating(int Value)
{
    int Range = 0 ;
    if(Value < 5)
    {
        Range = 0 ;
    } else if (Value < 10)
    {
        Range = 1 ;
    } else if (Value < 15)
    {
        Range = 2 ;
    } else
    {
        Range = 3 ;
    }

    switch (Range)
    {
        case 0:
            return 'D';
            break;
        case 1:
            return 'C';
            break;
        case 2:
            return 'B';
            break;
        case 3:
            return 'A';
            break;
    }
}

int main()
{
    int i;
    char* instruction = 'n'; //Continue adding players if yes is selected, if no is selected continue

    //  Player array structure pointer created, with no memory allocation yet
    hockeyPlayer* arr_hockeyPlayer = (hockeyPlayer*) malloc(0 * sizeof(hockeyPlayer));
    printf("<<<<<  MORNE's HOCKEY GAME IN C >>>>>> \n");
    printf("<<<<<       201573396           >>>>>> \n\n");
    printf("Do you want to add a player? y/n ");
    scanf("%s",&instruction);

    while(instruction == 'y')
    {
        size++; //Keep track of the amount of players, started with 1 as char instruction must be yes to enter this loop
        arr_hockeyPlayer = realloc(arr_hockeyPlayer, size); //Allocate memory to amount of players at this stage

        printf("\nEnter details of player %d\n\n", size); //Format specified is %d for integer

        printf("Enter Player name: ");
        playerIndex = size-1;
        scanf("%s",(*(arr_hockeyPlayer + playerIndex)).Name); //Assign player name, Format specified is %s for string

        printf("Enter Team name: ");
        scanf("%s",(*(arr_hockeyPlayer + playerIndex)).Team); //Assign team name

        printf("Enter Goals, enter '-1' when done: \n");
        int numgoals = 0;
        int *input = 0;
        scanf("%d",&input); //Read value into input

        while (input != -1)
        {
            numgoals++;
            goalIndex = numgoals-1 ;
            *(((*(arr_hockeyPlayer + playerIndex)).numGoals)+ goalIndex) = input; //Go to player at playerindex, and add input to the goalindex of that player, fixed array of 100
            scanf("%d",&input); //Continue to request input until receiving '-1'
        }

        numGames = numgoals;

        printf("Do you want to add another player? y/n ");
        scanf("%s",&instruction);
        free(input);
    }

    for(i = 0; i < size; i++ )
    {
        int t;
        (*(arr_hockeyPlayer + i)).totalGoals = 0; //Index starts at 0
        for (t=0; t<numGames; t++)
        {
          (*(arr_hockeyPlayer + i)).totalGoals += *(((*(arr_hockeyPlayer+i)).numGoals) + t); //Sum and iterate all the goals of each game
        }
        (*(arr_hockeyPlayer + i)).avgGoals = 1.0*((*(arr_hockeyPlayer+ i )).totalGoals)/numGames;
        globalGoalsTotal += (*(arr_hockeyPlayer + i)).avgGoals; //Sum up the global aberage
    }
    globalGoalsAvg = (globalGoalsTotal*1.0)/size;
    int countFlag = 0;

    printf("\n");
    printf("Name\tTeam\ttotalGoals\tAve Num Goals\tGoals\t\tRating\n");

    for(i = 0; i < size; i++ )
    {
        if ((*(arr_hockeyPlayer + i)).avgGoals >= globalGoalsAvg)
        {
            countFlag++; //Player is flagged when players average goals is more than the global average
            printf("%s%s\t%s\t%d\t\t%0.2f\t\t","F:", (*(arr_hockeyPlayer+i)).Name,(*(arr_hockeyPlayer+i)).Team,(*(arr_hockeyPlayer+i)).totalGoals,(*(arr_hockeyPlayer+i)).avgGoals);
        }else
            printf("%s\t%s\t%d\t\t%0.2f\t\t",(*(arr_hockeyPlayer+i)).Name,(*(arr_hockeyPlayer+i)).Team,(*(arr_hockeyPlayer+i)).totalGoals,(*(arr_hockeyPlayer+i)).avgGoals);
        int t;
        for (t=0;t<numGames;t++)
        {
            printf("%d;",*(((*(arr_hockeyPlayer+i)).numGoals)+t));
        }
        //printf("\t%s;", DetermineRating( (*(arr_hockeyPlayer+i)).totalGoals ) ) ;

        printf("\n\n");
    }
    printf("%s%d%s%0.2f;","Num Flagged: ",countFlag," is greater or equal than overall average of ", globalGoalsAvg);

     printf("\n _________________________________________________________\n");
     printf("|                                                         |\n");
     printf("|                       Best Player                       |\n");
     printf("|                      Undetermined                       |\n");
     printf("|                                                         |\n");
     printf("|_________________________________________________________|\n");

    free(instruction);
    free(arr_hockeyPlayer);

    return 0;
}
