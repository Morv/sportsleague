/*Written by: Bryan, Morvan, Ricky, Connor, Ian (Group 4)
10/27/2013
Purpose:Exam 3 Sports League
~!Ninjas vs. Pirates is serious underground business!~
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define pause system ("pause")
#define cls system ("cls")
#define TSIZE 12
#define flush fflush(stdin)

typedef struct{
	int hTeam;
	int aTeam;
	int hScore;
	int aScore;
} GAME;//end of the GAME struct

typedef struct{
	char teamName [40];  
	double wins;
	double losses;
	double pct;
	int pointsScored;
	int pointsAgainst;
} TEAM; // end of Team struct

//prototypes
void displayStandings(TEAM team[TSIZE]);
int displayMainMenu();
void displayTeams(TEAM team[]);
void inputData(TEAM team[TSIZE]);
void saveSeasonStandings(TEAM team[], int z);
void readSeasonInfo (TEAM team[]);
void resetSeasonStandings(TEAM team[]);
void sortPCT (TEAM team[]);
char switchPCT (TEAM team[], int i);
void menuDesign (char menuArray[][80]);
int verifyChoice(int userChoice, int maxChoice);

main (){
	int i = 0, choice = 0, z = TSIZE;

	char activeTeams [12][15]= {"Pirates", "Raiders", "Thieves", "Mongrel", "Seahags", "Wenches", "Ninjas", 
		"Hitmen", "Shadows", "Shades", "Ronin", "Rogues"};
	TEAM team[TSIZE]= {0};//create an array of structs as the data type TEAM
	
	for (i=0; i<TSIZE; i++){
		strcpy(team[i].teamName, activeTeams[i]);//strcpy to move a string to a char pointer
	}
	
	system("mode 80, 35"); //width and height locked at max 80x35, scrolling disabled ("mode COLS = 80") works with scrolling enabled
	
	readSeasonInfo(team); //opens binary file
	do{
		switch(choice = displayMainMenu())
		{
		case 1:
			inputData(team); //input game
			break;
		case 2:
			sortPCT(team);			//sorts teams by PCT
			displayStandings(team);
			break;
		case 3:
			resetSeasonStandings(team); //sets all numbers to zero
			break;
		case 4:
			saveSeasonStandings(team, z);
			printf("NINJA VANISH!\n");
			break;
		}//end switch
	}while(choice != 4); //end do-while

	pause;
}

int displayMainMenu(){
	int result = 0, i =0, j =0;
	char menuArray[4][80] = {'/0'};

	for (j=0; j<3; j++)
	{
		for (i=0; i<35; i++)
		{
			menuArray[j][i]= 205;
		}//end inside for loop
	}//end outside for loop

	menuArray[0][0]= 201;
	menuArray[0][35]= 187;
	menuArray[1][0]=204;
	menuArray[1][35]=185;
	menuArray[2][0]= 200;
	menuArray[2][35]=188;
	menuArray[3][0]=186;

	cls;
	printf("\t\t\t  NINJAS VS PIRATES COMBAT LEAGUE!\n\n");
	printf("\t\t\t%s\n", menuArray[0]);
	printf("\t\t\t%c             MAIN MENU            %c\n", menuArray[3][0], menuArray[3][0]);
	printf("\t\t\t%s\n", menuArray[1]);
	printf("\t\t\t%c1) Enter the result of a game     %c\n", menuArray[3][0], menuArray[3][0]);
	printf("\t\t\t%c2) Display the league standings   %c\n", menuArray[3][0], menuArray[3][0]);
	printf("\t\t\t%c3) Restart the entire season      %c\n", menuArray[3][0], menuArray[3][0]);
	printf("\t\t\t%c4) Quit the program               %c\n", menuArray[3][0], menuArray[3][0]);
	printf("\t\t\t%s\n", menuArray[2]);
	printf("Enter a choice (1-4): ");
	scanf("%i", &result);
	flush;
	result = verifyChoice(result, 4);
	cls;
	
	return result;
}//end main menu
void displayStandings(TEAM team[TSIZE]){
	int i = 0, j=0;
	char menuArray[4][80] = {'/0'};
	FILE *fp2;
	fp2 = fopen("LeaqueStandings.txt", "w");
	if (fp2 == NULL){
		printf("Failed to open text file!\n");
		pause;
		exit(-1);
	}
	else 
		//printf("Text File created!\n");
		//pause;
	
							//menu design
	for (j=0; j<3; j++)
	{
		for (i=0; i<80; i++)
		{
			menuArray[j][i]= 205;
		}//end inside for loop
	}//end outside for loop

	menuArray[0][0] = 201;
	menuArray[0][79]= 187;
	menuArray[1][0] = 204;
	menuArray[1][79]= 185;
	menuArray[2][0] = 200;
	menuArray[2][79]= 188;
	menuArray[3][0] = 186;
	menuArray[3][1] = 196;
	menuArray[3][2] = 199;
	menuArray[3][3] = 182;
							//end menu design
		
	cls;
	for (i=0; i< 80; i++)
	{
	printf("%c", menuArray[0][i]); //%s is not working in this function.  it prints out every row of the array.
	}//end for loop
	
	printf("%c               ************LEAGUE STANDINGS***********\t\t\t       %c%c\t\t\t\t\t\t\t\t\t       %c",
			menuArray[3][0], menuArray[3][0], menuArray[3][0], menuArray[3][0]);
	printf("%cTeam Name\tWins\tLosses\tPoints Scored\t Points Against\t\tPCT    %c", menuArray[3][0], menuArray[3][0]);
	
	for (i=0; i< 80; i++)
	{
	printf("%c", menuArray[1][i]);
	}//end for loop

	fprintf(fp2, "                 ************LEAGUE STANDINGS***********\n\n");
	fprintf(fp2, "Team Name\tWins\tLosses\tPoints Scored\t Points Against\t\tPCT\n");
	fprintf(fp2, "_____________________________________________________________________________\n\n");

	for (i=0; i<TSIZE; i++){
		printf("%c%s      \t  %.0lf      %.0lf    \t      %i     \t       %i\t       %.3lf   %c", menuArray[3][0], team[i].teamName, team[i].wins, 
			team[i].losses, team[i].pointsScored, team[i].pointsAgainst, team[i].pct, menuArray[3][0]);
		
		printf("%c", menuArray[3][2]);
		for (j=1; j<79; j++)
		{
			printf("%c", menuArray[3][1]);
		}//end inner for loop (lines separating teams)
		printf("%c", menuArray[3][3]);

		fprintf(fp2, "%s        \t  %.0lf      %.0lf    \t      %i     \t       %i\t       %.3lf\n", team[i].teamName, team[i].wins, 
			team[i].losses, team[i].pointsScored, team[i].pointsAgainst, team[i].pct );
	}//end for loop to print stats

	for (i=0; i< 80; i++)
	{
	printf("%c", menuArray[2][i]);
	}//end for loop

	fclose(fp2);
	pause;
}//end displayStandings

void displayTeams(TEAM team[]){
	int i = 0, j =0;
	char menuArray[4][15] = {'/0'};

								//menu design
	for (j=0; j<3; j++)
	{
		for (i=0; i<15; i++)
		{
			menuArray[j][i]= 205;
		}//end inside for loop
	}//end outside for loop

	menuArray[0][0] = 201;
	menuArray[0][14]= 187;
	menuArray[1][0] = 204;
	menuArray[1][14]= 185;
	menuArray[2][0] = 200;
	menuArray[2][14]= 188;
	menuArray[3][0] = 186;
	menuArray[3][1] = 196;
	menuArray[3][2] = 199;
	menuArray[3][3] = 182;
	menuArray[3][4] = 179;
							//end menu design
	printf("\t\t\t");
	for (i=0; i<15; i++)
	{
		printf("%c", menuArray[0][i]);
	}//end for loop
	
	printf("\n");
	printf("\t\t\t%c    TEAMS    %c\n",menuArray[3][0],menuArray[3][0]);
	printf("\t\t\t");

	for (i=0; i<15; i++)
	{
		printf("%c", menuArray[1][i]);
	}//end for loop
	printf("\n");

	for (i=0; i<TSIZE; i++){
		if (i > 8)
		{
			switch(strlen(team[i].teamName))
			{
			case 5:
				printf("\t\t\t%c %i%c %s   %c\n",menuArray[3][0], i+1, menuArray[3][4] , team[i].teamName, menuArray[3][0]);
				break;
			case 6: 
				printf("\t\t\t%c %i%c %s  %c\n",menuArray[3][0], i+1, menuArray[3][4] , team[i].teamName, menuArray[3][0]);
				break;				
			default:
				printf("\t\t\t%c %i%c %s %c\n",menuArray[3][0], i+1, menuArray[3][4] , team[i].teamName, menuArray[3][0]);
			break;
			}//end switch

		}else{
			switch(strlen(team[i].teamName))
			{
				case 6:
					printf("\t\t\t%c %i %c %s  %c\n",menuArray[3][0], i+1, menuArray[3][4] , team[i].teamName, menuArray[3][0]);
					break;
				default:
					printf("\t\t\t%c %i %c %s %c\n",menuArray[3][0], i+1, menuArray[3][4] , team[i].teamName, menuArray[3][0]);
					break;
			}//end switch
		}//end if-else
	}//end for loop
	printf("\t\t\t");
	for (i=0; i< 15; i++)
	{
		printf("%c", menuArray[2][i]);
	}//end for loop
	printf("\n");
}//end displayTeams

void inputData (TEAM team[TSIZE]){
	int homeTeam = 0, homeTeamScore = 0, awayTeam = 0, awayTeamScore = 0;
	int i = 0;

	do{
		displayTeams(team);
		printf("Enter Home Team number: ");
		scanf("%i", &homeTeam);
		flush;
		homeTeam = verifyChoice(homeTeam, 12);

		printf("Enter Home Team Score: ");
		scanf("%i", &homeTeamScore);
		flush;

		while (homeTeamScore < 0) //error check for negative scores
		{
			printf("Enter a positive number for the team's score: ");
			scanf("%i", &homeTeamScore);
			flush;
		}//end while
			
		printf("Enter Away Team number: ");
		scanf("%i", &awayTeam);
		awayTeam = verifyChoice(awayTeam, 12);
		flush;

		while (homeTeam == awayTeam)
		{
			printf("Ninjas nor Pirates will fight themselves!\n");
			printf("Enter Away Team number: ");
			scanf("%i", &awayTeam);
			awayTeam = verifyChoice(awayTeam, 12);
			flush;
		}//end while

		printf("Enter Away Team Score: ");
		scanf("%i", &awayTeamScore);
		flush;
		while (awayTeamScore < 0)
		{
			printf("Enter a positive number for the team's score: ");
			scanf("%i", &awayTeamScore);
			flush;
		}//end while

		while(homeTeamScore == awayTeamScore)
		{
			cls;
			printf("Ninjas and Pirates always fight till death, somebody's gotta win!\n");
			printf("Please check score and enter again!\n");
			printf("Enter score for %s: ", team[homeTeam-1].teamName);
			scanf("%i", &homeTeamScore);
			printf("Enter score for %s: ", team[awayTeam-1].teamName);
			scanf("%i", &awayTeamScore);
			pause;
		}//end while

	}while(homeTeam == awayTeam || homeTeam < 1 || homeTeam > 12 || awayTeam < 1 || awayTeam > 12); //END BIG WHILE

	if (homeTeamScore > awayTeamScore)
	{
		team[homeTeam-1].wins = team[homeTeam-1].wins + 1;
		team[awayTeam-1].losses = team[awayTeam-1].losses + 1;
	}//end if

	if (homeTeamScore < awayTeamScore)
	{
		team[awayTeam-1].wins = team[awayTeam-1].wins + 1;
		team[homeTeam-1].losses = team[homeTeam-1].losses +1;
	}//end if
	cls;

	team[homeTeam-1].pointsScored += homeTeamScore;//all this outside of loops so it happens regardless of win/lose status
	team[homeTeam-1].pointsAgainst += awayTeamScore;
	team[awayTeam-1].pointsScored += awayTeamScore;
	team[awayTeam-1].pointsAgainst += homeTeamScore;
	team[homeTeam-1].pct = ( (team[homeTeam-1].wins) / (team[homeTeam-1].wins + team[homeTeam-1].losses) );
	team[awayTeam-1].pct = ( (team[awayTeam-1].wins) / (team[awayTeam-1].wins + team[awayTeam-1].losses) );

}//end input game (enter result of a game)

void readSeasonInfo (TEAM team[], int z){

	FILE * fp1;
	fp1 = fopen("standings.bin", "ab");
	if (fp1 == NULL){
		printf("Failed to open binary file!\n");
		pause;
		exit(-1);
	}
	else 
		//printf("Binary File created!\n"); 
	fclose (fp1);
		//pause;
	fp1 = fopen("standings.bin", "rb");
	fread(&z, sizeof (int), 1, fp1);
	fread(team, sizeof(TEAM), TSIZE, fp1);
	fclose(fp1);

}//end readSeasonInfo
void resetSeasonStandings(TEAM team[]){
	int i=0;

	for (i=0; i<TSIZE; i++){
		team[i].pointsScored = 0;
		team[i].pointsAgainst= 0;
		team[i].pct = 0.0;
		team[i].wins = 0;
		team[i].losses = 0;
	}//end for loop

	saveSeasonStandings(team, TSIZE);
	printf("Standings have been reset!\n");
	pause;
}// end resetSeasonStandings

void saveSeasonStandings(TEAM team[], int z){

	FILE *fp1;
	fp1 = fopen ("standings.bin", "wb");
	fwrite(&z, sizeof(int),1,fp1);
	fwrite (team, sizeof(TEAM), z, fp1);
	fclose(fp1);


}//end saveSeasonStandings.

void sortPCT (TEAM team[]){
	int i=0;
	char switchMade = 'N';
	int bottom = TSIZE - 1;

	do {
		switchMade = 'N';
		for (i=0; i < bottom; i++)
		{
			if (team[i].pct < team[i+1].pct){
				switchMade = switchPCT(team, i);
			}//end if
		}//end for
		bottom--;

	}while (switchMade == 'Y'); //end do-while

	return;
}//end function sortPCT

char switchPCT (TEAM team[], int i){
	TEAM tempTeam = {0};

	tempTeam = team[i];

	team[i] = team[i+1];
	team[i+1] = tempTeam;

	return 'Y';
}//end function switchPCT

int verifyChoice(int userChoice, int maxChoice)
{
        int result = userChoice;
        while (result > maxChoice || result < 1) //0 is set to be the lowest choice option.
        {
                printf("\nEnter a number between 1 and %i: ", maxChoice);
                scanf_s("%i", &result);
                flush;
        }//end if statement

        return result;
}//end verifyChoice range
