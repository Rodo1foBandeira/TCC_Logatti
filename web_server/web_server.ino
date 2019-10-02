#include <ESP8266WiFi.h>

const char* ssid = "Rep Tio Pepao 2";
const char* password = "baltazar";

WiFiServer server(80);

String HTTP_req;

const byte qtdePinosES = 4;
const byte pinosES[qtdePinosES]   =	{ 0     , 2     , 4 	      , 5            };
const byte modoPinos[qtdePinosES] =	{ OUTPUT, OUTPUT, INPUT_PULLUP, INPUT_PULLUP };

void setup(){
  
   Serial.begin(115200);
   
	// Configura o modo dos pinos digitais
	for (int nP=0; nP < qtdePinosES; nP++) {
		pinMode(pinosES[nP], modoPinos[nP]);
		digitalWrite(pinosES[nP], LOW);
	}
	
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	
	Serial.println("");
	Serial.println("WiFi conectado.");
	Serial.print("IP: ");
	Serial.println(WiFi.localIP());
	server.begin();
}

void loop(){
	WiFiClient  client = server.available();   
	if (client) { 
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				HTTP_req += c;
              
				if (c == '\n' && currentLineIsBlank ) { 
					String params = getURLRequest(&HTTP_req);
          if(params.indexOf("digital=") != -1){
            byte posicaoPassagemParam = params.indexOf("=") + 1;
            byte pino = params.substring(posicaoPassagemParam, posicaoPassagemParam + 1).toInt();
            digitalWrite(pino, HIGH);
            delay(350);
            digitalWrite(pino, LOW);
            delay(10);
          }
                
					client.println("HTTP/1.1 200 OK");
          if (params.indexOf("api") != -1){
            client.println("Content-Type: application/json");
            client.println();
            client.print("[{\"pin\":4, \"status\":" + String(digitalRead(4) == HIGH) + "}, {\"pin\":5, \"status\":" + String(digitalRead(5) == HIGH) + "}]");
          }else{
            client.println("Content-Type: text/html");
            client.println();
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<meta charset='UTF-8'>");
           
            client.println("<!--Import Google Icon Font-->");
            client.println("<link href='https://fonts.googleapis.com/icon?family=Material+Icons' rel='stylesheet'>");
            client.println("<!--Import materialize.css-->");
            client.println("<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css'>");
  
            client.println("<!--Let browser know website is optimized for mobile-->");
            client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'/>");
  
            client.println("</head>");
  
            client.println("<body>");
            client.println("<div class='container'>");
            client.println("<div class='row'>");
            client.println("<div class='card-panel col s12 blue-grey lighten-4'>");
            client.println("<h4 class='center-align'>Sistema de pré-automatização residencial</h4>");
            client.println("</div>");
            client.println("<div class='center-align'>");
            
            client.println("<!-- Quarto lado cozinha -->");
            client.println("<a onclick='comutar(0)' class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 8px;margin-top: 9px;'><i class='material-icons'>wb_sunny</i></a>");
            client.println("<a id='btn0' class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 52px;margin-top: 9px;'><i class='material-icons'>power</i></a>");
  
            client.println("<!-- Cozinha -->");
            client.println("<a id='btn2' onclick='comutar(2)' class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 200px;margin-top: 9px;'><i class='material-icons'>wb_sunny</i></a>");           
            
            client.println("<a class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 244px;margin-top: 9px;'><i class='material-icons'>power</i></a>");
  
            client.println("<!-- Quarto meio -->");
            client.println("<a class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 8px;margin-top: 208px;'><i class='material-icons'>wb_sunny</i></a>");
            client.println("<a class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 52px;margin-top: 208px;'><i class='material-icons'>power</i></a>");
  
            client.println("<!-- Quarto lado sala -->");
            client.println("<a class='btn-floating  blue-grey lighten-2' style='position: absolute;margin-left: 8px;margin-top: 480px;'><i class='material-icons'>wb_sunny</i></a>");
            client.println("<a class='btn-floating  blue-grey lighten-2' style='position: absolute;margin-left: 52px;margin-top: 480px;'><i class='material-icons'>power</i></a>");
  
            client.println("<!-- Sala -->");
            client.println("<a class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 200px;margin-top: 480px;'><i class='material-icons'>wb_sunny</i></a>");
            client.println("<a class='btn-floating blue-grey lighten-2' style='position: absolute;margin-left: 244px;margin-top: 480px;'><i class='material-icons'>power</i></a>");
            
            client.println("<img class='responsive-img' src='https://raw.githubusercontent.com/Rodo1foBandeira/TCC_Logatti/master/Layout/img/Planta.jpg'>");
  
            client.println("</div>");
            client.println("</div>");
            client.println("</div>");
  
            client.println("<!--JavaScript at end of body for optimized loading-->");
            client.println("<script src='https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js'></script>");
            client.println("<script src='https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js' integrity='sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo=' crossorigin='anonymous'></script>");

            // pulse
            // blue-grey 
            client.println("<script></script>");
            
            client.println("</body>");
            client.println("</html>");
          }
          
					HTTP_req = "";    
					break;
				}
				
				if (c == '\n') {
					currentLineIsBlank = true;
				} else if (c != '\r') {
					currentLineIsBlank = false;
				}
			}
		}
		delay(1);     
		client.stop(); 
	}
}

String getURLRequest(String *requisicao) {
	int inicio, fim;
	String retorno;

	inicio = requisicao->indexOf("GET") + 3;
	fim = requisicao->indexOf("HTTP/") - 1;
	retorno = requisicao->substring(inicio, fim);
	retorno.trim();

	return retorno;
}
