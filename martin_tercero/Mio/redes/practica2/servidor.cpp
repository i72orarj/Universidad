
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include "funciones.hpp"

using namespace std;

#define MSG_SIZE 250
#define MAX_USERS 40
#define MAX_GAMES 10


std::vector<Game> games;
char buffer[MSG_SIZE];

void sigint(int signum){
  std::cout << "Para salir escriba SALIR." << std::endl;
}


int main(int argc, char const *argv[]){
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd == -1){
    perror("Socket error\n");
  }
  int on = 1;
  int ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  struct sockaddr_in sockname;
  sockname.sin_family = AF_INET;
  sockname.sin_port = htons(2050);
  sockname.sin_addr.s_addr = inet_addr("192.168.1.105");

  if(bind(sd, (struct sockaddr *) &sockname, sizeof(sockname)) == -1){
    perror("Bind error\n");
    return EXIT_FAILURE;
  }

  if(listen(sd, 1) == -1){
    perror("Listen error\n");
    return EXIT_FAILURE;
  }

  fd_set readfds, auxfds;
  FD_ZERO(&readfds);
  FD_ZERO(&auxfds);
  FD_SET(sd, &readfds);
  FD_SET(0, &readfds);

  std::signal(SIGINT, sigint);

  std::signal(SIGALRM, turn);
  alarm(CAGE_TIMEOUT);

  struct sockaddr_in from;
  socklen_t from_len = sizeof(from);
  std::vector<User> users;
  std::vector<User> queue;
  int new_sd;
  while(true){
    auxfds = readfds;
    if(select(FD_SETSIZE, &auxfds, NULL, NULL, NULL) > 0){
      for(int i = 0; i < FD_SETSIZE; i++){
        if(FD_ISSET(i, &auxfds)){
          if(i == sd){
            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
              perror("Accept error\n");
            }else{
              if(users.size() < MAX_USERS){
                users.push_back(User(new_sd));
                FD_SET(new_sd, &readfds);
                bzero(buffer, sizeof(buffer));
                strcpy(buffer, "+OK. Usuario conectado");
                send(new_sd, buffer, strlen(buffer), 0);
              }else{
                bzero(buffer, sizeof(buffer));
                strcpy(buffer, "-ERR. Demasiados usuarios conectados simultáneamente");
                send(new_sd, buffer, strlen(buffer), 0);
                close(new_sd);
              }
            }
          }else if(i == 0){
            bzero(buffer, sizeof(buffer));
            fgets(buffer, sizeof(buffer), stdin);
            if(strcmp(buffer, "SALIR\n") == 0){
              bzero(buffer, sizeof(buffer));
              strcpy(buffer, "-ERR. Desconexión del servidor");
              for(int j = 0; j < users.size(); j++){
                send(users[j].sd(), buffer, strlen(buffer), 0);
                close(users[j].sd());
                FD_CLR(users[j].sd(), &readfds);
              }
              close(sd);
              return EXIT_SUCCESS;
            }
          }else{
            bzero(buffer, sizeof(buffer));
            if(recv(i, buffer, sizeof(buffer), 0) > 0){
              std::vector<std::string> splitted_buffer = split(std::string(buffer), " ");
              if(splitted_buffer[0] == "USUARIO"){
                std::ifstream f("users.txt");
                std::string name, password;
                bool is_user = false;
                while(f >> name >> password){
                  if(splitted_buffer[1] == name){
                    for(int j = 0; j < users.size(); j++){
                      if(i == users[j].sd()){
                        is_user = true;
                        users[j].name(name);
                        users[j].password(password);
                        users[j].state(0);
                        break;
                      }
                    }
                  }
                }
                f.close();
                bzero(buffer, sizeof(buffer));
                if(is_user){
                  strcpy(buffer, "+OK. Usuario correcto");
                }else{
                  for(int j = 0; j < users.size(); j++){
                    if(i == users[j].sd()){
                      users[j].state(-1);
                    }
                  }
                  strcpy(buffer, "-ERR. Usuario incorrecto");
                }
                send(i, buffer, strlen(buffer), 0);
              }else if(splitted_buffer[0] == "PASSWORD"){
                bzero(buffer, sizeof(buffer));
                for(int j = 0; j < users.size(); j++){
                  if(i == users[j].sd()){
                    if(users[j].state() >= 0){
                      if(users[j].password() == splitted_buffer[1]){
                        users[j].state(1);
                        strcpy(buffer, "+OK. Usuario validado");
                      }else{
                        users[j].state(0);
                        strcpy(buffer, "-ERR. Error en la validación");
                      }
                    }else{
                      strcpy(buffer, "-ERR. Usuario no introducido");
                    }
                    break;
                  }
                }
                send(i, buffer, strlen(buffer), 0);
              }else if(splitted_buffer[0] == "REGISTRO"){
                bzero(buffer, sizeof(buffer));
                if(splitted_buffer.size() == 5 and
                   splitted_buffer[1] == "-u" and
                   splitted_buffer[3] == "-p"){
                  std::ifstream inf("users.txt");
                  std::string name, password;
                  bool is_user = false;
                  while(inf >> name >> password){
                    if(name == splitted_buffer[2]){
                      is_user = true;
                      break;
                    }
                  }
                  inf.close();
                  if(!is_user){
                    std::ofstream outf("users.txt", std::ios_base::app);
                    for(int j = 0; j < users.size(); j++){
                      if(i == users[j].sd()){
                        users[j].name(splitted_buffer[2]);
                        users[j].password(splitted_buffer[4]);
                        outf << users[j].name() + "\t" + users[j].password() << std::endl;
                        users[j].state(1);
                        strcpy(buffer, "+OK. Usuario registrado");
                        break;
                      }
                    }
                    outf.close();
                  }
                }
                send(i, buffer, strlen(buffer), 0);
              }else if(splitted_buffer[0] == "INICIAR-PARTIDA"){
                bzero(buffer, sizeof(buffer));
                if(games.size() != MAX_GAMES){
                  for(int j = 0; j < users.size(); j++){
                    if(i == users[j].sd()){
                      if(users[j].state() == 1){
                        users[j].state(2);
                        queue.push_back(users[j]);
                        strcpy(buffer, "+OK. Petición recibida. Quedamos a la espera de más jugadores");

                  }
                }else{
                  strcpy(buffer, "-ERR. Demasiadas partidas simultáneas");
                }
                send(i, buffer, strlen(buffer), 0);
                sleep(2);
                if(queue.size() == USERS_PER_GAME){
                  bzero(buffer, sizeof(buffer));
                  strcpy(buffer, "+OK. Empieza la partida");
                  for(int j = 0; j < queue.size(); j++){
                    send(queue[j].sd(), buffer, strlen(buffer), 0);
                    for(int k = 0; k < users.size(); k++){
                      if(users[k].sd() == queue[j].sd()){
                        users[k].state(3);
                        }
                    }
                    queue[j].state(3);
                  }
                  //empezar juego
