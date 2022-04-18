// Includes
#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// Colors for easier using inside the code
#define BLACK "\x1b[30m"
#define RESET "\x1b[m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define PINK "\x1b[35m"
#define CYAN "\x1b[36m"

#define LBLACK "\x1b[30;1m"
#define LRED "\x1b[31;1m"
#define LGREEN "\x1b[32;1m"
#define LYELLOW "\x1b[33;1m"
#define LBLUE "\x1b[34;1m"
#define LPINK "\x1b[35;1m"
#define LCYAN "\x1b[36;1m"

//defines for the version
#define V1 1
#define V2 0
#define V3 2

// Defines used for the menu
#define N 6                // menu size
#define COLUMN 10          // column of the menu
#define ROW ((26 - N) / 2) // row of the menu

// Refresh the screen everytime the menu pointer move
void refresh(int option, PrintConsole topScreen, char *menu[], int n) {
	consoleSelect(&topScreen);
	for (int i = 0; i < n; i++) {
		if (i == option)
			printf("\x1b[%d;%dH%s> %s%s", ROW + i, COLUMN, LYELLOW, menu[i], RESET);
		else
			printf("\x1b[%d;%dH  %s", ROW + i, COLUMN, menu[i]);
	}
}

// Show the keyboard to set the custom SYS/EMU version
void setString(char* path) {
	static SwkbdState swkbd;
	static char buf[20];

	SwkbdButton button = SWKBD_BUTTON_NONE;
	swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 2, 19);
	swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Cancel", false);
	swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, SWKBD_FILTER_DIGITS, 19);
	swkbdSetFeatures(&swkbd, SWKBD_MULTILINE);
	swkbdSetHintText(&swkbd, "RESET: %d.%d.%d-%d%ls\n3DS: 3DSpoof ");
	//
	swkbdSetFeatures(&swkbd, SWKBD_PREDICTIVE_INPUT);
	SwkbdDictWord words[73];
			//CUSTOM
			swkbdSetDictWord(&words[0], "RESET", "%d.%d.%d-%d%ls");
			swkbdSetDictWord(&words[1], "ZT", "ZeraTron");
			swkbdSetDictWord(&words[2], "SHRUG", "¯\\_(ツ)_/¯");
			swkbdSetDictWord(&words[3], "DEX", "4.46 REBUG");
			swkbdSetDictWord(&words[4], "3DS", "3DSpoof ");
			//SYSTEM
			swkbdSetDictWord(&words[5], "SYSABTN", "");
			swkbdSetDictWord(&words[6], "SYSBBTN", "");
			swkbdSetDictWord(&words[7], "SYSXBTN", "");
			swkbdSetDictWord(&words[8], "SYSYBTN", "");
			swkbdSetDictWord(&words[9], "SYSLB", "");
			swkbdSetDictWord(&words[10], "SYSRB", "");
			swkbdSetDictWord(&words[11], "SYSCIRCLEPAD", "");
			swkbdSetDictWord(&words[12], "SYSDPAD", "");
			swkbdSetDictWord(&words[13], "SYSDUP", "");
			swkbdSetDictWord(&words[14], "SYSDDOWN", "");
			swkbdSetDictWord(&words[15], "SYSDLEFT", "");
			swkbdSetDictWord(&words[16], "SYSDRIGHT", "");
			swkbdSetDictWord(&words[17], "SYSDUPDOWN", "");
			swkbdSetDictWord(&words[18], "SYSDLEFTRIGHT", "");
			swkbdSetDictWord(&words[19], "SYSPWR", "");
			swkbdSetDictWord(&words[20], "SYSVID", "");
			swkbdSetDictWord(&words[21], "SYSBACKARROW", "");
			swkbdSetDictWord(&words[22], "SYSCLOSE", "");
			swkbdSetDictWord(&words[23], "SYSCLOSE2", "");
			swkbdSetDictWord(&words[24], "SYSCAM", "");
			swkbdSetDictWord(&words[25], "SYSHOME", "");
			swkbdSetDictWord(&words[26], "SYSPDMETER", "");
			swkbdSetDictWord(&words[27], "SYSPLAYCOIN", "");
			//PICTOCHAT
			swkbdSetDictWord(&words[28], "PCTHAPPY", "");
			swkbdSetDictWord(&words[29], "PCTANGRY", "");
			swkbdSetDictWord(&words[30], "PCTSAD", "");
			swkbdSetDictWord(&words[31], "PCTSLEEPY", "");
			swkbdSetDictWord(&words[32], "PCTSUN", "");
			swkbdSetDictWord(&words[33], "PCTCLOUD", "");
			swkbdSetDictWord(&words[34], "PCTUMBRELLA", "");
			swkbdSetDictWord(&words[35], "PCTSNOWMAN", "");
			swkbdSetDictWord(&words[36], "PCTMAIL", "");
			swkbdSetDictWord(&words[37], "PCTPHONE", "");
			swkbdSetDictWord(&words[38], "PCTCLOCK", "");
			swkbdSetDictWord(&words[39], "PCTSPADE", "");
			swkbdSetDictWord(&words[40], "PCTDIAMOND", "");
			swkbdSetDictWord(&words[41], "PCTHEART", "");
			swkbdSetDictWord(&words[42], "PCTCLUBS", "");
			swkbdSetDictWord(&words[43], "PCTRARROW", "");
			swkbdSetDictWord(&words[44], "PCTLARROW", "");
			swkbdSetDictWord(&words[45], "PCTUARROW", "");
			swkbdSetDictWord(&words[46], "PCTDARROW", "");
			swkbdSetDictWord(&words[47], "PCTBOXX", "");
			swkbdSetDictWord(&words[48], "PCTLOAD1", "");
			swkbdSetDictWord(&words[49], "PCTLOAD2", "");
			swkbdSetDictWord(&words[50], "PCTLOAD3", "");
			swkbdSetDictWord(&words[51], "PCTLOAD4", "");
			swkbdSetDictWord(&words[52], "PCTLOAD5", "");
			swkbdSetDictWord(&words[53], "PCTLOAD6", "");
			swkbdSetDictWord(&words[54], "PCTLOAD7", "");
			swkbdSetDictWord(&words[55], "PCTLOAD8", "");
			swkbdSetDictWord(&words[56], "PCTCROSS", "");
			swkbdSetDictWord(&words[57], "PCTROOMA", "");
			swkbdSetDictWord(&words[58], "PCTROOMB", "");
			swkbdSetDictWord(&words[59], "PCTROOMC", "");
			swkbdSetDictWord(&words[60], "PCTROOMD", "");
			swkbdSetDictWord(&words[61], "PCTQUESTION", "");
			swkbdSetDictWord(&words[62], "PCTEXCLAMATION", "");
			swkbdSetDictWord(&words[63], "PCTDSAUTO", "");
			swkbdSetDictWord(&words[64], "PCTDSMANUAL", "");
			swkbdSetDictWord(&words[65], "PCTPLOGO", "");
			swkbdSetDictWord(&words[66], "PCTILOGO", "");
			swkbdSetDictWord(&words[67], "PCTCLOGO", "");
			swkbdSetDictWord(&words[68], "PCTTLOGO", "");
			swkbdSetDictWord(&words[69], "PCTHLOGO", "");
			swkbdSetDictWord(&words[70], "PCTALOGO", "");
			swkbdSetDictWord(&words[71], "PCTSMALLINVCROSS", "");
			swkbdSetDictWord(&words[72], "PCTLARGEINVCROSS", "");

			swkbdSetDictionary(&swkbd, words, sizeof(words)/sizeof(SwkbdDictWord));
	button = swkbdInputText(&swkbd, buf, sizeof(buf));
	// Write the custom SYS/EMU version (?)
	static char string[20];
	for (int i = 0; i < 20; i++)
		string[i] = 0;
	memcpy(string, buf, 20);
	string[19] = '\0';

	if (button != SWKBD_BUTTON_NONE) {
		FILE *set = fopen(path, "wb");
		fwrite(string, 1, 19, set);
		fclose(set);
	}
}

int main()
{
	//Initializations
	gfxInitDefault(); // graphics
	u32 kDown;        // keys down
  u32 kHeld;        // keys pressed
  //u32 kUp;          // keys up

	// Console initializations
	PrintConsole topScreen;
	consoleInit(GFX_TOP, &topScreen);
	consoleSelect(&topScreen);

	// Dunno yet
	mkdir("sdmc:/luma", 0777);

	// Set the option to the first in the list + create the menu
	int option = 0;
	char* menu[N] = {
		"Set Sysnand custom version",
		"Remove all custom versions",
		"Set Emunand1 custom version",
		"Set Emunand2 custom version",
		"Set Emunand3 custom version",
		"Set Emunand4 custom version",
	};
	// IMPORTANT: put this after every menu functions otherwise-
	// -it will not display on the screen everything after the menu
	refresh(option, topScreen, menu, N);
	consoleSelect(&topScreen);

	// To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
	// The top screen has 30 rows and 50 columns
	// The bottom screen has 30 rows and 40 columns
	printf("\x1b[6;19H%s3DSpoof %sv%d.%d.%d%s", GREEN, LBLACK, V1, V2, V3, RESET);
	printf("\x1b[20;%dHPress %sA%s to choose an option.", COLUMN + 2, GREEN, RESET);
	printf("\x1b[29;8H%shttps://github.com/ZeraTron/3DSpoof %s", LBLACK, RESET);

	// Main loop
	while (aptMainLoop())
	{

		// Read which buttons are currently pressed or not
    hidScanInput();
    kDown = hidKeysDown();
    kHeld = hidKeysHeld();
    //kUp = hidKeysUp();

		// Controls for the menu
		if (kDown & KEY_DUP) {
			if (option == 0) option = N - 1;
			else if (option > 0) option--;

			refresh(option, topScreen, menu, N);
		}

		if (kDown & KEY_DDOWN) {
			if (option == N - 1) option = 0;
			else if (option < N - 1) option++;

			refresh(option, topScreen, menu, N);
		}

		if (kDown & KEY_A) {
			switch (option) {
				case 0 : {
					setString("/luma/customversion_sys.txt");
					break;
				}
				case 1 : {
					remove("/luma/customversion_sys.txt");
					remove("/luma/customversion_emu.txt");
					remove("/luma/customversion_emu2.txt");
					remove("/luma/customversion_emu3.txt");
					remove("/luma/customversion_emu4.txt");
					break;
				}
				case 2 : {
					setString("/luma/customversion_emu.txt");
					break;
				}
				case 3 : {
					setString("/luma/customversion_emu2.txt");
					break;
				}
				case 4 : {
					setString("/luma/customversion_emu3.txt");
					break;
				}
				case 5 : {
					setString("/luma/customversion_emu4.txt");
					break;
				}
			}
		}
		// IMPORTANT: put this after every menu functions otherwise-
		// -it will not display on the screen everything after the menu
		refresh(option, topScreen, menu, N);
		consoleSelect(&topScreen);

		// Break the loop and go back to HBLmenu
		if ((kHeld & KEY_SELECT) && (kHeld & KEY_START)) break;
		// Color the Select and Start strings when the buttons are held
		if (kHeld & KEY_SELECT) {
			printf("\x1b[22;11HPress %sSelect%s and %sStart%s to exit.", LYELLOW, RESET, LBLACK, RESET);
		}else if (kHeld & KEY_START) {
					printf("\x1b[22;11HPress %sSelect%s and %sStart%s to exit.", LBLACK, RESET, LYELLOW, RESET);
				}else{
			printf("\x1b[22;11HPress %sSelect%s and %sStart%s to exit.", LBLACK, RESET, LBLACK, RESET);
		}
		///////////////////////////// PROTOTYPES  HERE /////////////////////////////





		////// ////// ////// ////// ////// ////// ////// ////// ////// ////// //////

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		// Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}

//////////////////////////////// EXAMPLES  HERE ////////////////////////////////

// Show the prinf value only when the input is held
/*if (kHeld & KEY_A) {
	printf("\x1b[10;19HI'm seen only when %sA%s is held !", LRED, RESET);
}else{
	printf("\x1b[15;19H                                   ");
}*/



////////////////////////////////////////////////////////////////////////////////
