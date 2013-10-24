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
void displayTeams(char activeTeams[][15]);
void inputData(char activeTeams[][15], TEAM team[TSIZE]);

main (){
	int i = 0, choice = 0;

	char activeTeams [12][15]= {"Pirates", "Raiders", "Theives", "Mongrel", "Seahags", "Wenches", "Ninjas", 
		"Hitmen", "Shadows", "Shades", "Ronin", "Rogues"};

	TEAM team[TSIZE] = {0};//create AND **INITIALIZE** array of team

	for (i=0; i<TSIZE; i++){
		strcpy(team[i].teamName, activeTeams[i]);//strcpy to move a string to a char pointer
	}

	do{
		switch(choice = displayMainMenu())
		{
		case 1:
			inputData(activeTeams, team);
			break;
		case 2:
			displayStandings(team);
			break;
		case 3:
			break;
		case 4:
			printf("NINJA VANISH!\n");
			break;
		}//end switch
	}while(choice != 4);

	pause;
}

int displayMainMenu(){
	int result = 0, i =0, j =0;
	char chararray[4][50] = {'/0'};

		for (j=0; j<3; j++)
		{
		for (i=0; i<35; i++)
		{
		chararray[j][i]= 205;
		}//end inside for loop
		}//end outside for loop

		chararray[0][0]= 201;
		chararray[0][35]= 187;
		chararray[1][0]=204;
		chararray[1][35]=185;
		chararray[2][0]= 200;
		chararray[2][35]=188;
		chararray[3][0]=186;

	printf("NINJAS VS PIRATES COMBAT LEAGUE!\n\n");
	printf("%s\n", chararray[0]);
	printf("%c             MAIN MENU            %c\n", chararray[3][0], chararray[3][0]);
	printf("%s\n", chararray[1]);
	printf("%c1) Enter the result of a game     %c\n", chararray[3][0], chararray[3][0]);
	printf("%c2) Display the league standings   %c\n", chararray[3][0], chararray[3][0]);
	printf("%c3) Restart the entire season      %c\n", chararray[3][0], chararray[3][0]);
	printf("%c4) Quit the program               %c\n", chararray[3][0], chararray[3][0]);
	printf("%s\n", chararray[2]);
	printf("Enter a choice (1-4): ");
	scanf("%i", &result);
	flush;

	while (result < 1 || result > 4)
	{
		printf("Enter a number 1-4: ");
		scanf("%i", &result);
		flush;
	}//error check
	cls;
	return result;
}//end main menu
void displayStandings(TEAM team[TSIZE]){
	int i = 0;
	cls;
	printf("                 ************LEAGUE STANDINGS***********\n\n");
	printf("Team Name\tWins\tLosses\tPoints Scored\t Points Against\t\tPCT\n");
	printf("_____________________________________________________________________________\n\n");

	for (i=0; i<TSIZE; i++){
		printf("%s        \t  %.0lf      %.0lf    \t      %i     \t       %i\t       %.3lf\n", team[i].teamName, team[i].wins, 
			team[i].losses, team[i].pointsScored, team[i].pointsAgainst, team[i].pct );
	}//end for loop to print stats
	pause;
}//end displayStandings

void displayTeams(char activeTeams[][15]){

	int i = 0;

	for (i=0; i<12; i++){
		printf("%i: %s\n",i , activeTeams[i]);
	}//end for loop

}//end displayTeams

void inputData (char activeTeams[][15], TEAM team[TSIZE]){
	int homeTeam = 0, homeTeamScore = 0, awayTeam = 0, awayTeamScore = 0, noTieFlag = 0;
	int i = 0;

	do{
		do{
			noTieFlag = 0;
			displayTeams(activeTeams);
			printf("Enter Home Team: ");
			scanf("%i", &homeTeam);
			printf("Enter Home Team Score: ");
			scanf("%i", &homeTeamScore);

			printf("Enter Away Team: ");
			scanf("%i", &awayTeam);
			printf("Enter Away Team Score: ");
			scanf("%i", &awayTeamScore);
			if(homeTeam == awayTeam){
				cls;
				printf("Ninjas nor Pirates will fight themselves!\n");
			printf("Please check teams again and reenter information.\n");
			pause;
			cls;
			}
			if (homeTeam > 11 || awayTeam > 11){
				cls;
			printf("That team of combatants doesn't exist!\n");
			printf("Check team name again!\n");
			pause;
			cls;
			}
		}while(homeTeam == awayTeam || homeTeam > 11 || awayTeam > 11);
		if (( homeTeamScore > awayTeamScore) && (homeTeamScore != awayTeamScore))
		{
			team[homeTeam].wins = team[homeTeam].wins + 1;
			team[awayTeam].losses = team[awayTeam].losses + 1;
		}

		if (( homeTeamScore < awayTeamScore) && (homeTeamScore != awayTeamScore))
		{
			team[awayTeam].wins = team[awayTeam].wins + 1;
			team[homeTeam].losses = team[homeTeam].losses +1;
		}

		if(homeTeamScore == awayTeamScore && (homeTeam != awayTeam))
		{
			cls;
			printf("Ninjas and Pirates always fight till death, somebody's gotta win!\n");
			printf("Please check score and enter again!\n");
			pause;
			noTieFlag = 1;
		}//end else if
		cls;
	} while(noTieFlag == 1);//end do-while that prevents erroroneous entering of scores/ties

	team[homeTeam].pointsScored += homeTeamScore;//all this outside of loops so it happens regardless of win/lose status
	team[homeTeam].pointsAgainst += awayTeamScore;
	team[awayTeam].pointsScored += awayTeamScore;
	team[awayTeam].pointsAgainst += homeTeamScore;
	team[homeTeam].pct = ( (team[homeTeam].wins) / (team[homeTeam].wins + team[homeTeam].losses) );
	team[awayTeam].pct = ( (team[awayTeam].wins) / (team[awayTeam].wins + team[awayTeam].losses) );

}//end input game (enter result of a game)







/*
//Function Headers/Protoypes
int displayMenu();
void addEmployee (EMPLOYEE[], int *empNum);
void printEmployeeReport (EMPLOYEE[], int empNum);
void printAllEmployeesReport (EMPLOYEE[], int empNum); 
void printpayRollInfoPayrollTotal(EMPLOYEE[], int empNum);
int readpayRollInfoData(EMPLOYEE payRollInfo[]);
void savepayRollInfoData(EMPLOYEE payRollInfo[], int empNum);

main(){
int empNum = 0, choice = 0;
DATE payDate;

EMPLOYEE payRollInfo[CSIZE];//create an array of structs as the data type EMPLOYEE

empNum = readpayRollInfoData(payRollInfo);//had to assign empNum the value from the file via pass by value in readpayRollInfoData function, cuz pass by reference wasn't working like I believe it should.

do{
choice = displayMenu();//incorporates getting user choice and error checking the choice.
switch(choice){
case 1:
addEmployee(payRollInfo, &empNum);
break;
case 2:
printEmployeeReport(payRollInfo, empNum);
break;
case 3:
printAllEmployeesReport(payRollInfo, empNum);
break;
case 4:
printpayRollInfoPayrollTotal(payRollInfo, empNum);
break;
case 5:
savepayRollInfoData(payRollInfo, empNum);//the current EMPLOYEE payRollInfo array is written into the file. Using "wb", it destroys the old data and rewrites a totally new file/data set.
break;
}//end switch	
}while(choice != 5);
pause;
}//end Main

void addEmployee (EMPLOYEE payRollInfo[], int *empNum){//int*empNum points to empNum by position in the call.
char tempFirstName[40] = "";// not sure struct variables need be initialized.
char tempLastName[40] = "";
int day = 0, month = 0, year = 0;
DATE payDateTemp;
payRollInfo[*empNum].regularPay = 0.0;
payRollInfo[*empNum].overTimePay = 0.0;
payRollInfo[*empNum].hourlyRate = 0.0;
payRollInfo[*empNum].hoursWorked = 0;

printf("Enter First Name of Employee:\n");
scanf("%s", &tempFirstName);
flush;
printf("Enter Last Name of Employee:\n");
scanf("%s", &tempLastName);
flush;
do{//error check for valid month
printf("Enter the Pay Month (MM):\n");//could error check valid date ranges if int struct DATE was used
scanf("%i", &month);
flush;
if(month <1 || month > 12)
printf("Please enter a valid month, 1-12!\n");
}while(month <1 || month > 12);

do{//error check for valid day
printf("Enter the Pay Day (DD):\n");
scanf("%i", &day);
flush;
if (day < 1 || day > 31)
printf("Please enter a valid day, 1-31!\n");
}while(day < 1 || day > 31);

do{//error check for valid year
printf("Enter the Pay Year (YYYY):\n");
scanf("%i", &year);
flush;
if (year != 2013)
printf("The current valid year is 2013!\n");
}while (year != 2013);

payDateTemp.month = month;
payDateTemp.day = day;
payDateTemp.year = year;
strcpy(payRollInfo[*empNum].firstName, tempFirstName);//strcpy to move a string to a char pointer
strcpy(payRollInfo[*empNum].lastName, tempLastName);

payRollInfo[*empNum].payDate = payDateTemp;
printf("Enter hourly pay rate for %s %s: \n", payRollInfo[*empNum].firstName, payRollInfo[*empNum].lastName);
scanf("%lf", &payRollInfo[*empNum].hourlyRate);
printf("Enter hours worked for %s %s: \n", payRollInfo[*empNum].firstName,payRollInfo[*empNum].lastName);
scanf("%lf", &payRollInfo[*empNum].hoursWorked);

if (payRollInfo[*empNum].hoursWorked > PAYHOURS){
payRollInfo[*empNum].regularPay = PAYHOURS * payRollInfo[*empNum].hourlyRate;
payRollInfo[*empNum].overTimePay = (payRollInfo[*empNum].hoursWorked - PAYHOURS) * payRollInfo[*empNum].hourlyRate * 1.5;
payRollInfo[*empNum].grossPay = payRollInfo[*empNum].regularPay + payRollInfo[*empNum].overTimePay;
}else {
payRollInfo[*empNum].regularPay = payRollInfo[*empNum].hourlyRate * payRollInfo[*empNum].hoursWorked;
payRollInfo[*empNum].overTimePay = 0;
payRollInfo[*empNum].grossPay = payRollInfo[*empNum].regularPay;
}//end if else for calculating employee pay.

(*empNum)++;//dereference with paranthesis first.

}//end addEmployee

int displayMenu(){
int result = 0;

do{
cls;
printf("Welcome to Optimus Programming Payroll Plus\n");
printf("   1.Enter employee payroll information\n");
printf("   2.Display payroll for an employee on a pay date\n");
printf("   3.Display payroll for all employees on a pay date\n");
printf("   4.Display total payroll for the company\n");
printf("   5.SAVE AND EXIT Payroll by Optimus Programming\n");
printf("Please make a valid selection:");
scanf("%i", &result);
flush;

if (result <1 || result > 5){
cls;
printf("Please make a valid selection!\n");
pause;
}// end if

}while (result < 1 || result > 5);//end do while. Error check for invalid menu selectio.
cls;

return result;

}//end displayMenu

void printAllEmployeesReport (EMPLOYEE payRollInfo[], int empNum){
int i = 0, dateNullFlag = 0;//dateNullFlag for signaling that no records exist for a date entered by user.
SEARCHDATE x;//temp struct for comparison of dates for search engine

if(empNum == 0)//error checking for no employee records
printf("There are no reports to print.\n\n");
else if (empNum != 0)// user inputs for search date
printf("Reports for all Employees:\n\n");
printf("Enter Pay Roll month\n");
scanf("%i", &x.month);
flush;
printf("Enter Pay Roll Day\n");
scanf("%i", &x.day);
flush;
printf("Enter Pay Roll Year\n");
scanf("%i", &x.year);
flush;
cls;
for(i = 0; i < empNum; i++)
if (payRollInfo[i].payDate.month == x.month && payRollInfo[i].payDate.day == x.day && payRollInfo[i].payDate.year == x.year){
printf("Employee Report\n\n");
printf("Name: %s %s \n", payRollInfo[i].firstName, payRollInfo[i].lastName );
printf("Pay Date: %i/%i/%i\n", payRollInfo[i].payDate.month,payRollInfo[i].payDate.day,payRollInfo[i].payDate.year);
printf("Hourly Rate: $%.2lf \n", payRollInfo[i].hourlyRate);
printf("Hours Worked: %.1lf \n", payRollInfo[i].hoursWorked);
printf("Regular Pay: $%.2lf \n", payRollInfo[i].regularPay);
printf("Over Time Pay: $%.2lf \n", payRollInfo[i].overTimePay);
printf("Gross Pay: $%.2lf\n", payRollInfo[i].grossPay);
dateNullFlag = 1;
}//end if

if (dateNullFlag == 0)//this flag tells user if date entered has NO records. If even one matched, the flag is changed to 1 inside the if/for loop
printf("No records exist for that date.\n");
pause;

}//end printpayRollInfoReport

void printpayRollInfoPayrollTotal(EMPLOYEE payRollInfo[], int empNum){
int i = 0;
double totalHours = 0, totalRegPay = 0, totalOT = 0, totalGross = 0;
SEARCHDATE x; //temp struct for search date.


printf("Enter Pay Roll month\n");
scanf("%i", &x.month);
flush;
printf("Enter Pay Roll Day\n");
scanf("%i", &x.day);
flush;
printf("Enter Pay Roll Year\n");
scanf("%i", &x.year);
flush;
cls;
for(i = 0; i < empNum; i++){
if (payRollInfo[i].payDate.month == x.month && payRollInfo[i].payDate.day == x.day && payRollInfo[i].payDate.year == x.year){
totalHours += payRollInfo[i].hoursWorked;
totalRegPay += payRollInfo[i].regularPay;
totalOT += payRollInfo[i].overTimePay;
totalGross += payRollInfo[i].grossPay;
}//end if
}//end for loop
printf("Pay roll totals for following date are:\n\n");
printf("Pay Date: %i/%i/%i\n", x.month, x.day, x.year);
printf("Total man hours worked: %.1lf\n", totalHours);
printf("Total for Reg Pay: $%.2lf\n", totalRegPay);
printf("Total for OT Pay: $%.2lf\n", totalOT);
printf("Total for Gross Pay: $%.2lf\n", totalGross);
pause;

}//end printpayRollInfoPayrollTotal

void printEmployeeReport (EMPLOYEE payRollInfo[], int empNum){
int i = 0, reportNum = 0;
SEARCHDATE x;//temp struct for comparison of dates for search engine
cls;
if(empNum == 0)
printf("There are no reports to print.\n\n");
else {
for (i = 0; i < empNum; i++){
printf("%i:%s %s\n", i, payRollInfo[i].firstName, payRollInfo[i].lastName);
}//end for

printf("Please choose an employee report to print:\n");
scanf("%i", &reportNum);//pick which employee
flush;
printf("Enter Pay Roll Month\n");//next few variables are for the date to print
scanf("%i", &x.month);
flush;
printf("Enter Pay Roll Day\n");
scanf("%i", &x.day);
flush;
printf("Enter Pay Roll Year\n");
scanf("%i", &x.year);
flush;
cls;
if(reportNum < empNum && reportNum >= 0){//will prevent user from printing a screen of garbage if they choose an array element that has nothing in it.
cls;
if (payRollInfo[reportNum].payDate.month == x.month && payRollInfo[reportNum].payDate.day == x.day && payRollInfo[reportNum].payDate.year == x.year){
printf("Employee Report\n\n");
printf("Name: %s %s \n", payRollInfo[reportNum].firstName, payRollInfo[reportNum].lastName );
printf("Pay Date: %i/%i/%i\n", payRollInfo[reportNum].payDate.month,payRollInfo[reportNum].payDate.day,payRollInfo[reportNum].payDate.year);
printf("Hourly Rate: $%.2lf \n", payRollInfo[reportNum].hourlyRate);
printf("Hours Worked: %.1lf \n", payRollInfo[reportNum].hoursWorked);
printf("Regular Pay: $%.2lf \n", payRollInfo[reportNum].regularPay);
printf("Over Time Pay: $%.2lf \n", payRollInfo[reportNum].overTimePay);
printf("Gross Pay: $%.2lf\n", payRollInfo[reportNum].grossPay);
}//end inner if
else if (payRollInfo[reportNum].payDate.month != x.month || payRollInfo[reportNum].payDate.day != x.day || payRollInfo[reportNum].payDate.year != x.year)
printf("No pay roll records match that date.\n");
}//end outer if
else 
printf("Invalid employee number!\n");//keeps peeps from trying to print an empoyee that doesn't exist.

}//end else error check for no employee records

pause;
}//end printEmployeeReport

void savepayRollInfoData(EMPLOYEE payRollInfo[], int empNum){

FILE* fp1;

fp1 = fopen ("payRollInfo.bin", "wb");//using "wb" here is acceptable because we want it to destroy all the data and just rewrite everything from the array that is current during current session. 
fwrite(&empNum, sizeof(int), 1, fp1);
fwrite(payRollInfo, sizeof(EMPLOYEE), empNum, fp1);//writes EMPLOYEE customer array of structs to the bin file.
fclose (fp1);
}//end savepayRollInfoData

int readpayRollInfoData(EMPLOYEE payRollInfo[]){
int num = 0;
FILE *fp1;

fp1 = fopen ("payRollInfo.bin", "ab+");//opening file with "ab+" preserves the data in it, and allows it to be written into the array for this program session.
if(fp1 == NULL){                   //As is, with no path, it is created in the project folder of Visual Studios
printf("Failed to create file!\n");
exit(-1);//close program if file isn't created.
}
else 
printf("File created successfully!\n");
fclose(fp1);

fp1 = fopen("payRollInfo.bin", "ab+");
fread(&num, sizeof(int), 1, fp1);
fread (payRollInfo, sizeof(EMPLOYEE), num, fp1);//i had to make this num variable because for some reason I couldn't get it to assign *empNum 
fclose (fp1);
return num;//returns the number of employess at the function call, which will facilitate in loading the correct empNum when the program is opened after a file is created.

}//end readpayRollInfoData
*/
