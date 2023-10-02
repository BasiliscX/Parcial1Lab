#ifndef JUGADORESARCHIVO_H_INCLUDED
#define JUGADORESARCHIVO_H_INCLUDED

#include<iostream>
#include<cstring>
using namespace std;
#include"Jugadores.h"

class JugadoresArchivo{
private:
    char nombre[30];
public:
    JugadoresArchivo(const char*n){ strcpy(nombre,n); }
    bool AgregarJugador(Jugadores);
    bool ListarJugador(bool);
    int getJugadorDNI(int);
    Jugadores getRegistro(int);
    int ContarJugadores();
    bool ModificarJugador(int,Jugadores);
};
bool JugadoresArchivo::AgregarJugador(Jugadores reg){
    FILE*p=fopen(nombre,"ab");
    if(p==NULL){ return false; }

    fwrite(&reg,sizeof(Jugadores),1,p);
    fclose(p);
    return true;
}
bool JugadoresArchivo::ListarJugador(bool soloActivos=true){
    Jugadores reg;
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return false; }
    while(fread(&reg,sizeof(Jugadores),1,p)){
        if(soloActivos){
            if(reg.getEstado()){
                reg.Mostrar();
                cout<<endl;
            }
        }
        else{
            reg.Mostrar();
            cout<<endl;
        }
    }
    fclose(p);
    return true;
}
int JugadoresArchivo::getJugadorDNI(int dni){
    int cont=0;
    Jugadores reg;
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return -1; }
    while(fread(&reg,sizeof(Jugadores),1,p)){
        if(reg.getDNI()==dni){
            fclose(p);
            return cont;
        }
        cont++;
    }
    fclose(p);
    return -2;
}
Jugadores JugadoresArchivo::getRegistro(int pos){
    Jugadores reg;
    pos--;
    reg.setDNI(-1);
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return reg; }
    fseek(p,sizeof(Jugadores)*pos,0);
    fread(&reg,sizeof(Jugadores),1,p);
    fclose(p);
    return reg;
}
int JugadoresArchivo::ContarJugadores(){
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return -1; }
    fseek(p,0,2);//ultima posicion
    int cantBytes=ftell(p);//tamaño desde 0 a posicion
    return cantBytes/sizeof(Jugadores);
}
bool JugadoresArchivo::ModificarJugador(int pos,Jugadores reg){
    FILE*p=fopen(nombre,"rb+");
    if(p==NULL){ return false; }
    pos--;
    fseek(p,sizeof(Jugadores)*pos,0);
    fwrite(&reg,sizeof(Jugadores),1,p);
    fclose(p);
    return true;
}

#endif // JUGADORESARCHIVO_H_INCLUDED
