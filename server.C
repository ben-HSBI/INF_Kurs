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
    string myResponse(string string);
};




int main(){
	srand(time(nullptr));
	MySrv srv(2023,64);
	srv.run();
}

string MySrv::myResponse(string input){
    int x,y, e;

    if (input.compare(0,7,"NEW_GAME")==0){
        if (w!=nullptr){
        delete w; // löschen einr vorhandenen Welt
        }

        w = new  TASK3::World(); // Erzeugen einer neuen Welt

        return string("OK");
    }

     if (input.compare(0,5,"SHOT[")==0){

        e =sscanf(input.c_str(),"SHOT[%d,%d]",&x,&y);
        if(e !=2) {
            return string("ERROR");
        }else{
            return (to_string(x+y));
        }
    }

    return string("UNKNOWNCMD");
}



