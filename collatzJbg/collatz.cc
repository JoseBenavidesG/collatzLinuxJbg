/**


*************************************************************
* File: collatz.cpp
* Descripción:
* 	Pequeña documentación del archivo
* 	Este archivo utiliza la libhreria glove, creada por 
* 	Gaspar Fernández <blakeyed@totaki.com>
* 	Se escribe este programa para que genere la conjetura de Collatz
* 
* 	Antes se uso otro libreria para hacerlo para windows, pero luego se pidio que 
* 	se requeria para Linux y se creo este programa
*
*
* author Jose Benavides G. josebenavidesg@gmail.com
* version 1.0.0
* date 23 Jan 2020
* History:
* ........20200123...JBG:	Initial code 
*.......................	Este es el codigo inicial, para el
*.......................	manejo de conjetura Collatz.  
*
* Compilation:
* 	Use el script ./compileAndRun.sh, que compila y pone en ejecucion el servicio
*
* Use:
* 	Como ya lo compilo y quedo ejecutandose atendiendo en el puerto 8080
* 	ahora para probarlo desde una consola puede probarlo, usando:
*
*  	curl http://localhost:8080/18/
*
* 	esto le entregara un mensaje JSON son la secuencia Collatz, como se esta :
*
* 	[9, 28, 14, 7, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1]
*
* Note:
* 	si usted, quiere solo ejecutar el servidor, sin tener que compilarlo, cada vez que lo ejecuta, despues
* 	de comnpilar, ejecute el sgte comando:
* 	./serverCollatz 
*
*	y el servidor estara esperando por un numero natural.
*
*************************************************************/

#include "./glove/glovehttpserver.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>




class Collatz
{
public:
	Collatz()
	{
	}
	~Collatz()
	{
	}


public:
	bool isOk(std::string x) {

		while(s.size() > 1 && x[0] == ' ')
			x.erase(x.begin());

		int ini = x[0] == '-';

		for(int i=ini;i<x.size();i++)
			if('0' <= x[i] && x[i] <= '9')
				continue;
			else
				return false;

		return true;

	}

	bool is_number(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}

	std::string generateCollatz(std::string naturalNumber) {

		std::string json;

		if  ( (is_number(naturalNumber)) && (naturalNumber.length() > 0) && (std::stoi(naturalNumber) > 0)  )
		    {
				
				bool firtsElement=true;
				std::cout << "naturalNumber:" << naturalNumber << std::endl;

				unsigned nCollatz = std::stoi(naturalNumber);
				bool notInfinite = true;
				do  {
					if (!firtsElement) json += ", ";
					if (nCollatz % 2 == 0) {
						nCollatz /= 2;
					} else {
						nCollatz = 3 * nCollatz + 1;
					}
					if (firtsElement) {
						json = "[";
						firtsElement = false;
					}
					json += std::to_string(nCollatz);
					if (nCollatz == 1) notInfinite=false;
        		}while(notInfinite);
        		json += "]";

				std::cout << json << std::endl;

			}else{
				json  = "{";
				json += "   \"error\": {\n";
				json +=	"          \"id\":\"404 Not Found\",\n";
				json += "          \"value\": \"URL Incorrecta, solo numeros naturales (1,2,3,4....) use el sgte formato de URL : curl http://localhost:8080/18/\"\n";
				json += "    }\n";
				json += "}\n";

		 	}
		return json;

	}

	std::string getCollatz(std::string naturalNumber)
	{
		std::string out;
		std::string collatz = generateCollatz(naturalNumber);
		if (!collatz.empty())
			return collatz;
		return "error";
	}

private:	
	std::string s;

};


class CollatzApi
{
public:
	CollatzApi()
	{
	}	
	
	void get(GloveHttpRequest &request, GloveHttpResponse& response)
	{	

		response.contentType("text/json");
		auto res = collatzs.getCollatz(request.special["naturalNumber"]);
		if (res.empty())
			throw GloveApiException(3, "No collatz generated");
		response << res;

	}

private:
	Collatz collatzs;
};


int main(int argc, char *argv[])
{
	CollatzApi collatzNaturalNumber;

  	GloveHttpServer serv(8080, "", 2048);
	serv.compression("gzip, deflate");
	namespace ph = std::placeholders;
	
	serv.addRest("/$naturalNumber", 1,
							 GloveHttpServer::jsonApiErrorCall,
							 std::bind(&CollatzApi::get, &collatzNaturalNumber, ph::_1, ph::_2)
	);


	std::cout << "example to use: curl http://localhost:8080/18/" << std::endl;
  	std::cout << "collatz server READY !!!"<<std::endl;
  while(1)
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }


}

