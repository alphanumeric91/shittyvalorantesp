#include "include.h"
#include "driver.h"
#include "cheats.h"
#include "skStr.h"
ImFont* info = nullptr;


int main()
{
    SetConsoleTitleA("SpeedyGonzales - VALORANT External Software");
    map_the_driver();
    system("color e");

        if (mem::find_driver()) {
            system("cls");
            std::cout << "\n\n Driver found. Waiting...";
        }
        else {
            system("cls");
            system("color c");
            std::cout << "\n\n Driver not found. Exiting...\n";
            Sleep(2000);
            exit(0);
        }

        if (mem::find_process(L"VALORANT-Win64-Shipping.exe")) {
            virtualaddy = retrieve_guarded(); //guarded region offset
            check::guard = virtualaddy;
            baseee = mem::find_image();
            system("cls");
            std::cout << "\n[+] Cheat active. Good luck.";
            //std::cout << FpsInfo << std::endl; -> Write the Overlay FPS
            game::start_cheat();
            Sleep(-1);
            return NULL;

        }
        else {
            system("cls");
            system("color c");
            std::cout << "\n \n [-] Please open the game.";
            Sleep(2000);
            exit(0);
        }

}