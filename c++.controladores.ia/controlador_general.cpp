#include "controlador_general.hpp"

Controlador_general::Controlador_general( std::string ubicacion_entorno, std::string ubicacion_agente ){
    this->entorno = this->c_entorno.cargar_entorno( ubicacion_entorno );
    this->agente = this->c_agente.cargar_agente( ubicacion_agente );
}
Controlador_general::~Controlador_general(){}
Controlador_entorno Controlador_general::get_controlador_entorno(){
    Controlador_entorno c_e( this->entorno );
    return c_e;
}
Controlador_agente Controlador_general::get_controlador_agente(){
    Controlador_agente c_a( this->agente );
    return c_a;
}

Entorno Controlador_general::get_entorno(){
    return this->entorno;
};

Agente Controlador_general::get_agente(){
    return this->agente;
};

void Controlador_general::set_entorno( Entorno entorno ){
    this->entorno = entorno;
};

void Controlador_general::set_agente( Agente agente ){
    this->agente = agente;
};

void Controlador_general::jugar( Entorno entorno, Agente agente ){
    this->entorno = entorno;
    this->agente = agente;
    this->jugar();
};

void Controlador_general::jugar(){

    int posicion_actual[2];
    posicion_actual[0] = this->entorno.get_posicion_inicial()[0];
    posicion_actual[1] = this->entorno.get_posicion_inicial()[1];

    std::vector < std::string > informacion_pos = this->get_controlador_entorno().get_informacion_entorno_pos( posicion_actual );
    while(informacion_pos[4] != "M"){
        
        int arriba, izquierda, abajo, derecha = -1;
        if( ( informacion_pos[0] == "0" ) || ( informacion_pos[0] == "M" ) || ( informacion_pos[0] == "S" ) ){
            arriba = 0;
        }else if( ( informacion_pos[0] == "1" ) ){
            arriba = 1;
        }
        if( ( informacion_pos[1] == "0" ) || ( informacion_pos[1] == "M" ) || ( informacion_pos[1] == "S" ) ){
            izquierda = 0;
        }else if( ( informacion_pos[1] == "1" ) ){
            izquierda = 1;
        }
        if( ( informacion_pos[2] == "0" ) || ( informacion_pos[2] == "M" ) || ( informacion_pos[2] == "S" ) ){
            abajo = 0;
        }else if( ( informacion_pos[2] == "1" ) ){
            abajo = 1;
        }
        if( ( informacion_pos[3] == "0" ) || ( informacion_pos[3] == "M" ) || ( informacion_pos[3] == "S" ) ){
            derecha = 0;
        }else if( ( informacion_pos[3] == "1" ) ){
            derecha = 1;
        }
        std::string accion = this->agente.get_percepciones()[arriba][izquierda][abajo][derecha][0][0];
        if( accion == "A" ){
            posicion_actual[0] = posicion_actual[0] - 1;
            posicion_actual[1] = posicion_actual[0];
        }else if( accion == "X" ){
            posicion_actual[0] = posicion_actual[0] + 1;
            posicion_actual[1] = posicion_actual[0];
        }else if( accion == "I" ){
            posicion_actual[0] = posicion_actual[0];
            posicion_actual[1] = posicion_actual[0] - 1;
        }else if( accion == "D" ){
            posicion_actual[0] = posicion_actual[0];
            posicion_actual[1] = posicion_actual[0] + 1;
        }
        std::cout << posicion_actual[0] << " - "  << posicion_actual[1] << " =>" << accion << " Valor " << informacion_pos[4] << std::endl;
        usleep(2 * 1000);
        informacion_pos = this->get_controlador_entorno().get_informacion_entorno_pos( posicion_actual );
        
    }

};


