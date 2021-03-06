#include "controlador_entorno.hpp"

Controlador_entorno::Controlador_entorno(){}
Controlador_entorno::Controlador_entorno( Entorno entorno ){
    this->entorno = entorno;
}
Controlador_entorno::~Controlador_entorno(){}
Entorno Controlador_entorno::cargar_entorno( std::string ubicacion ){

    std::vector< std::vector< std::string > > mapa; //2D
    std::vector< std::vector< std::vector< std::string > > > mapa3D; // [No implementado]

    std::vector < std::string > lineas;
    std::ifstream flujo_entrada( ubicacion.c_str() );
    std::string linea = "";

    while( std::getline( flujo_entrada, linea ) ){
        if( linea[0] == 'F' ){
            lineas.push_back( linea );
        }
    }

    flujo_entrada.close();

    std::vector < std::vector < std::string > > mapa_tmp;
    int posicion_inicial_tmp[2];

    for(int i = 0; i < lineas.size(); i++){

        std::stringstream ss_linea_mapa( lineas[i] );
        std::vector < std::string > substrings_definicion_mapa;
        std::string substring = "";

        substrings_definicion_mapa.push_back( "1" ); // Lado izquierdo de la frontera
        while( ss_linea_mapa >> substring ){
            if( substring.length() > 1 ){
                if( substring[0] == 'X' ){
                    substrings_definicion_mapa.push_back( substring );
                }
            }else{
                if( ( substring == "0" ) || ( substring == "1" ) || ( substring == "M" ) ){
                     substrings_definicion_mapa.push_back( substring );
                }else if( substring == "S" ){
                    substrings_definicion_mapa.push_back( substring );
                    posicion_inicial_tmp[0] = ( i + 1 );
                    posicion_inicial_tmp[1] = ( substrings_definicion_mapa.size() );
                }
            }
        }
        substrings_definicion_mapa.push_back( "1" ); // Lado derecho de la frontera
        mapa_tmp.push_back( substrings_definicion_mapa );
    }

    // Frontera superior
    std::vector < std::string > frontera_superior_inferior;
    for(int i = 0; i < mapa_tmp[0].size(); i++){
        frontera_superior_inferior.push_back( "1" );
    }
    mapa.push_back( frontera_superior_inferior );
    for(int i = 0; i < mapa_tmp.size(); i++){
        mapa.push_back( mapa_tmp[i] );
    }
    // Frontera inferior
    
    mapa.push_back( frontera_superior_inferior );
    
    Entorno entorno;
    entorno.set_mapa( mapa );
    entorno.set_posicion_inicial( posicion_inicial_tmp );

    return entorno;
}

void Controlador_entorno::pintar_entorno( Entorno entorno ){    
    this->entorno = entorno;
    this->pintar_entorno();
}

std::vector < std::string > Controlador_entorno::get_informacion_entorno_pos( Entorno entorno, int pos[2] ){
    this->entorno = entorno;
    return this->get_informacion_entorno_pos( pos );
};

std::vector < std::string > Controlador_entorno::get_informacion_entorno_pos( int pos[2] ){
    std::vector < std::string > informacion;
    std::string arriba = this->entorno.get_mapa()[ pos[0] - 1 ][ pos[1] ] ;
    std::string izquierda = this->entorno.get_mapa()[ pos[0] ][ pos[1] -1 ] ;
    std::string abajo = this->entorno.get_mapa()[ pos[0] + 1 ][ pos[1] ] ;
    std::string derecha = this->entorno.get_mapa()[ pos[0] ][ pos[1] + 1 ] ;
    std::string actual = this->entorno.get_mapa()[ pos[0]][ pos[1] ] ;
    informacion.push_back( arriba );
    informacion.push_back( izquierda );
    informacion.push_back( abajo );
    informacion.push_back( derecha );
    informacion.push_back( actual );
    return informacion;
};

void Controlador_entorno::pintar_entorno(){    
    Entorno entorno = this->entorno;
    std::vector<int> posicion_inicial = entorno.get_posicion_inicial();
    
    std::cout << "Punto de partida: Fila => " << ( posicion_inicial[0] + 1 ); 
    std::cout << " :: Columna => " << posicion_inicial[1] << std::endl << std::endl;
    for(int i = 0; i < entorno.get_mapa().size(); i++){
        for(int j = 0; j < entorno.get_mapa()[i].size(); j++){
            std::cout << '|' << entorno.get_mapa()[i][j];
            if( j == ( entorno.get_mapa()[i].size() - 1 ) ){
                std::cout << '|' << std::endl;;
            }
        }
    }
}