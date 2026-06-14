#include "headers.hpp"
#include <fstream>
#include <3ds.h>

// Function to handle the first-time welcome screens
void showWelcomeScreen() {
    // 1. Initialize the console screens for text drawing
    // Top screen for image placeholder (or text for now), bottom for your mockup
    gfxInitDefault();
    PrintConsole topScreen, bottomScreen;
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);

    int currentScreen = 1;

    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();

        // Clear screens each frame
        consoleSelect(&topScreen);
        consoleClear();
        consoleSelect(&bottomScreen);
        consoleClear();

        if (currentScreen == 1) {
            // --- TOP SCREEN (Screen 1) ---
            consoleSelect(&topScreen);
            printf("\n\n\n      [ BETTER FOURTHTUBE IMAGE ]\n");
            printf("   (Top screen full-image placeholder)\n");

            // --- BOTTOM SCREEN (Screen 1) ---
            consoleSelect(&bottomScreen);
            printf("========================================\n");
            printf("       Welcome to Better_FourthTube!\n");
            printf("========================================\n\n");
            printf("  Thank you for installing this custom\n");
            printf("  build. This app allows you to watch\n");
            printf("  and stream your favorite content right\n");
            printf("  from your 3DS console.\n\n");
            printf("----------------------------------------\n");
            printf("       Press A to see what's new        \n");
            printf("----------------------------------------\n");

            if (kDown & KEY_A) {
                currentScreen = 2; // Move to next screen
            }
        } 
        else if (currentScreen == 2) {
            // --- TOP SCREEN (Screen 2) ---
            consoleSelect(&topScreen);
            printf("\n\n\n      [ FEATURES / INFO IMAGE ]\n");

            // --- BOTTOM SCREEN (Screen 2) ---
            consoleSelect(&bottomScreen);
            printf("========================================\n");
            printf("              What's New\n");
            printf("========================================\n\n");
            printf("  * Smoother playback optimizations\n");
            printf("  * Custom file-naming structures\n");
            printf("  * Built-in error logging\n\n");
            printf("  Everything is ready to go!\n\n");
            printf("----------------------------------------\n");
            printf("         Press A to Finish Setup        \n");
            printf("----------------------------------------\n");

            if (kDown & KEY_A) {
                break; // Exit the welcome loop
            }
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    // 2. Create the first_boot.txt file so this loop is skipped next time
    std::ofstream flagFile("sdmc:/3ds/Better_FourthTube_boot.txt");
    if (flagFile.is_open()) {
        flagFile << "initialized";
        flagFile.close();
    }

    // 3. Reset graphics back to default state so Menu_init() can take over cleanly
    gfxExit();
}

int main() {
    // Check if the app has run before
    std::ifstream flagFile("sdmc:/3ds/Better_FourthTube_boot.txt");
    bool isFirstBoot = !flagFile.good();
    flagFile.close();

    if (isFirstBoot) {
        showWelcomeScreen();
    }

    // Hand over control to the main app menus
    Menu_init();

    // Main loop
    while (aptMainLoop()) {
        if (!Menu_main()) {
            break;
        }
    }

    Menu_exit();
    return 0;
}
