/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"

#include <string>

using namespace std;

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	int algorythm = 1; //1, 2 oder 3 für die verschiedenen Algorythmen

	/*  Algorythmus 1:  Zufällige Schüsse
     *  Algorythmus 2:  Linieare abarbeitung von Oben nach Unten, Links nach Rechts
	 *  Algorythmus 3:  Zufällige Schüsse mit Erinnerung
	 */

	//connect to host
	c.conn(host , 2023);

    int r=0; // Runden Zählen
	int i=1; // Gebrauchte Versuche

    while(r < 100){

    bool goOn=true;
	string msgSrv = " ";
    int x = 1;
    int y = 1;
    bool fired[10][10] = {false}; // Bereits beschossene Felder


	while(goOn){ // send and receive data
		if(msgSrv.find("GAME_OVER") != string::npos){

			msg = string("NEWGAME");
			goOn = false;
		}else{
            switch (algorythm) {
                case 1: {
                    x = rand() % 10 + 1;
                    y = rand() % 10 + 1;
                    msg = string("S[") + to_string(x) + "," + to_string(y) + "]";
                    break;
                }

                case 2: {
                    if(x > 10){
                        x = 1;
                        y++;
                    }
                    msg = string("S[") + to_string(x) + "," + to_string(y) + "]";
                    x++;
                    break;
                }

                case 3: {
                    do {
                        x = rand() % 10;
                        y = rand() % 10;
                    } while (fired[x][y]);

                    fired[x][y] = true;
                    x++;
                    y++;
                    msg = string("S[") + to_string(x) + "," + to_string(y) + "]";
                break;
                }


                default: {
                    msg = string("BYEBYE");
                }
			}
			i++;
		}
		//cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msgSrv = c.receive(320);
		//cout << "got response:" << msgSrv << endl;
		//if (goOn == false) {cout << "Anzahl Runden:" << i << endl;}
		if (goOn == false) {
		cout << i << endl;
		i=0;
		}
		//sleep(1);

	}
	r++;
	}
	c.sendData(string("BYEBYE"));
}


