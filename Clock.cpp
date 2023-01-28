#include <ctime>
#include <windows.h>
#include <cmath>
#include <conio.h>
#include <iostream>

struct TimerCycle {

	double sec = 0; int min = 0; int hour = 0; double seccompare = 0; clock_t timer = NULL; 
	double cycletimer = NULL;
	
	void NoBp() //Stopwatch script
	{   
		timer = clock();
		while (GetAsyncKeyState(0x70) == 0)
		{
			if (GetAsyncKeyState(0x71) != 0) { // Condition for the pause function. I'm just adding how much time has elapsed during the pause to the timer variable in order to keep "clock()-timer" interval same value
				clock_t timer1 = clock(); 
				system("cls");  
				Sleep(500); 
				printf("\n Paused at %dhr %dmin %.0fsec", hour, min, sec); 
				while (GetAsyncKeyState(0x71) == 0); 
				Sleep(500); 
				system("cls"); 
				timer += clock() - timer1; 
			}
			cycletimer = (double)(clock() - timer) / CLOCKS_PER_SEC; //Finding how much time has elapsed
			sec = cycletimer - abs(cycletimer - (int)cycletimer); //Converting time to seconds by separating the fractional part
			if (sec > seccompare) { 
				system("cls"); 
				printf("\n  %dhr %dmin %.0fsec elapsed", hour, min, sec); 
			} //Checking, if a second has passed
			if (sec == 60.0) { 
				cycletimer = 0;  
				timer = clock(); 
				min++; 
				system("cls"); 
			} // If 60 seconds passed - restoring the cycle, increasing the minutes
			if (min % 60 == 0 && min != 0) { cycletimer = 0; min = 0; timer = clock(); hour++; system("cls"); } // If 60 minutes past then icreasing count of the hours;
			seccompare = sec;
		}
	}
	int Bp(int sb, int mb, int hb) //Timer script
	{
		timer = clock();
		while (GetAsyncKeyState(0x70) == 0)
		{
			if (GetAsyncKeyState(0x71) != 0) { 
				clock_t timer1 = clock();
				system("cls");
				Sleep(500);
				printf("\n Paused at %dhr %dmin %.0fsec", hour, min, sec);
				while (GetAsyncKeyState(0x71) == 0);
				Sleep(500);
				system("cls");
				timer += clock() - timer1;
			}
			if ((int)sec == sb && min == mb && hour == hb) return 0; // Checking timer conditions
			cycletimer = (double)(clock() - timer) / CLOCKS_PER_SEC;
			sec = cycletimer - abs(cycletimer - (int)cycletimer);
			if (sec > seccompare) {
				system("cls"); 
				printf("\n  %dhr %dmin %.0fsec elapsed", hour, min, sec); 
			}
			if (sec == 60.0) {
				cycletimer = 0;  
				timer = clock(); 
				min++; system("cls"); 
			}
			if (min % 60 == 0 && min != 0) { 
				cycletimer = 0; 
				min = 0; 
				timer = clock();
				hour++; 
				system("cls"); 
			}
			seccompare = sec;
		}
	}
};

int sb = NULL;  int mb = NULL; int hb = NULL;

int main()
{
	TimerCycle CountWith;
	SetConsoleTitleA("Clock");
	HANDLE const Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, 14);
	printf("\nThis is a simple clock:\n\n\tEnter - Stopwatch\n\tF1 - Stop\n\t\F2 - Pause\n\tBackspase - Timer\n");
	if (sb != NULL || mb != NULL || hb != NULL) printf("\nA timer is set for %d:%d:%d",hb,mb,sb);
	int input = _getch();
	switch (input) {
	case 0x0D: //Enter (Stopwatch)
		system("cls");
		if (sb == NULL && mb == NULL && hb == NULL) CountWith.NoBp();
		else {
			CountWith.Bp(sb, mb, hb);
			sb = NULL; mb = NULL; hb = NULL;
		}
		system("cls");
		printf("\n\aTotal time: %dhr %dmin %.0fsec\n", CountWith.hour, CountWith.min, CountWith.sec);
		system("pause");
		system("cls");
		return main();
	case 0x08: //Backspace (Breakpoint)
		system("cls");
		printf("\nPlease enter a breakpoint in hour:minute:second format (ex. 0 0 40, 0 3 52, 1 3 10)\n");
		try {
			std::cin >> hb; std::cin >> mb; std::cin >> sb;
			if ((hb | mb | sb) < 0) throw "\n\tYou've entered negative values\t\n\n";
			if ((hb & mb & sb) == 0) { system("cls"); return main(); }
		}
		catch (const char* err) {
			system("cls");
			std::cerr << err;
			system("pause");
			system("cls");
			sb = NULL; mb = NULL; hb = NULL;
			return main();
		}
		system("cls");
		return main();
	default:
		system("cls");
		return main();
	}

}
