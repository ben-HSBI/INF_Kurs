/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include <string> // (neu)

#include "SIMPLESOCKET.H"
#include "TASK3.H"

/**
 *
 *  \class MySrv
 *  \brief     The class defining our communication protocol
                (Server-Client communication).
 *
 */

class MySrv : public TCPserver{
public:
    MySrv(int port, int bsize) : TCPserver(port, bsize){w=new TASK3::World();}; //sicherstellen dass eine Welt vorhanden ist
    // bsize = buffersize   TCPServer(Parameterübergabe) {leere Methodendefinition}
protected:
    TASK3::World *w; //Objekt Welt mit dem Namen w
    string myResponse(string string); //Funktionsdeklaration
};




int main(){
	srand(time(nullptr));
	MySrv srv(2023,64);
	srv.run();
}

// Funktionsdefinition
string MySrv::myResponse(string input){
    int x,y, e;

    if (input.compare(0,7,"NEWGAME")==0){
        if (w!=nullptr){
        delete w; // löschen einr vorhandenen Welt
        }

        w = new  TASK3::World(); // Erzeugen einer neuen Welt

        return string("OK\n");
    }

     if (input.compare(0,2,"S[")==0){

        e =sscanf(input.c_str(),"S[%d,%d]",&x,&y);
        if(e !=2) {
            return string("ERROR\n");
        }
        TASK3::ShootResult r; //neue Variable r direkt erzeugt
        r = w -> shoot(x,y);
        w -> printBoard();
        switch (r){
            case TASK3::WATER: return(string("WATER\n"));
            case TASK3::SHIP_HIT: return(string("HIT\n"));
            case TASK3::SHIP_DESTROYED: return(string("SUNKEN\n"));
            case TASK3::GAME_OVER: return(string("GAME_OVER\n"));
            default: return(string("ERROR"));
        }
    }

    return string("UNKNOWNCMD\n");
}



