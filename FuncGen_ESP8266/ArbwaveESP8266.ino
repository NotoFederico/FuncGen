#include <FS.h>   // Include the SPIFFS library
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <Wire.h>



ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80
WebSocketsServer webSocket(81);    // create a websocket server on port 81

String getContentType(String filename); // convert the file extension to the MIME type
bool handleFileRead(String path);       // send the right file to the client (if it exists)
void handleFileUpload();                // upload a new file to the SPIFFS
File fsUploadFile;              // a File object to temporarily store the received file

void setup()
  {
  //wdt_disable();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.begin();
  //Wire.setClock(400000);
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin("Noto", "LaNotoCas@14");
  Serial.println('\n');
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(".");
    }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");

  if (!MDNS.begin("esp8266"))
    {
    Serial.println("Error setting up MDNS responder!");

    while (1)
      {
      delay(1000);
      }
    }

  Serial.println("mDNS responder started");
  SPIFFS.begin();                           // Start the SPI Flash Files System
  server.on("/", HTTP_GET, handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.on("/send", HTTP_POST, handleSend);
  server.on("/delete", HTTP_POST, handleDelete);
  server.onNotFound([]()                                // If the client requests any URI
    {
    if (!handleFileRead(server.uri()))                  // send it if it exists
      { server.send(404, "text/plain", "404: URi Not Found"); } // otherwise, respond with a 404 (Not Found) error
    });
  server.on("/upload", HTTP_GET, []()                   // if the client requests the upload page
    {
    if (!handleFileRead("/upload.html"))                // send it if it exists
      { server.send(404, "text/plain", "404: Not Found (Upload)"); } // otherwise, respond with a 404 (Not Found) error
    });
  server.on("/upload", HTTP_POST,                       // if the client posts to the upload page
            []()
    {
    server.send(200);
    },                          // Send status 200 (OK) to tell the client we are ready to receive
  handleFileUpload                                    // Receive and save the file
           );
  // Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
  }

void loop()
  {
  webSocket.loop();                           // constantly check for websocket events
  MDNS.update();
  server.handleClient();                    // Listen for HTTP requests from clients
  }

void handleRoot()
  {
  //server.send(200, "text/plain", "Hello world!");   // Send HTTP status 200 (Ok) and send some text to the browser/client
  //server.send(200, "text/html", s);
  File file = SPIFFS.open("/pagina_principal.html", "r");                 // Open it
  size_t sent = server.streamFile(file, "text/html"); // And send it to the client
  //file.print("<h2 style=text-align: center;><span style=color: #ff0000; data-darkreader-inline-color=><em><strong>Ya es hora de merendar!</strong></em></span></h2>");
  file.close();
  }

void handleLED()                            // If a POST request is made to URI /LED
  {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));     // Change the state of the LED
  FSInfo fs_info;
  Dir dir = SPIFFS.openDir("/");

  if (SPIFFS.info(fs_info))
    {
    Serial.printf("Total Bytes %s \n",fs_info.totalBytes);
    Serial.printf("Used Bytes %s \n",fs_info.usedBytes);
    Serial.printf("Block Size %s \n",fs_info.blockSize);
    Serial.printf("Page Size %s \n",fs_info.pageSize);
    Serial.printf("Max Open Fles %s \n",fs_info.maxOpenFiles);
    Serial.printf("Max Path Lenght %s \n",fs_info.maxPathLength);

    while (dir.next())
      {
      Serial.println(dir.fileName());
      }
    }

  server.sendHeader("Location", "/");       // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
  }


String getContentType(String filename)   // convert the file extension to the MIME type
  {
  if (filename.endsWith(".html")) { return "text/html"; }

  else
    if (filename.endsWith(".css")) { return "text/css"; }

    else
      if (filename.endsWith(".csv")) { return "text/csv"; }

      else
        if (filename.endsWith(".js")) { return "application/javascript"; }

        else
          if (filename.endsWith(".png")) { return "image/png"; }

          else
            if (filename.endsWith(".pdf")) { return "application/pdf"; }

            else
              if (filename.endsWith(".doc")) { return "application/msword"; }

              else
                if (filename.endsWith(".txt")) { return "text/txt"; }

                else
                  if (filename.endsWith(".ico")) { return "image/x-icon"; }

  return "text/plain";
  }

bool handleFileRead(String path)   // send the right file to the client (if it exists)
  {
  Serial.println("handleFileRead: " + path);

  if (path.endsWith("/")) { path += "index.html"; }         // If a folder is requested, send the index file

  String contentType = getContentType(path);            // Get the MIME type

  if (SPIFFS.exists(path))                              // If the file exists
    {
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server.streamFile(file, contentType); // And send it to the client
    file.close();                                       // Then close the file again
    return true;
    }

  Serial.println("\tFile Not Found");
  return false;                                         // If the file doesn't exist, return false
  }

void handleFileUpload()   // upload a new file to the SPIFFS
  {
  HTTPUpload &upload = server.upload();

  if (upload.status == UPLOAD_FILE_START)
    {
    String filename = upload.filename;

    if (!filename.startsWith("/")) { filename = "/" + filename; }

    Serial.print("handleFileUpload Name: ");
    Serial.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
    filename = String();
    }

  else
    if (upload.status == UPLOAD_FILE_WRITE)
      {
      if (fsUploadFile)
        { fsUploadFile.write(upload.buf, upload.currentSize); } // Write the received bytes to the file
      }

    else
      if (upload.status == UPLOAD_FILE_END)
        {
        if (fsUploadFile)                                     // If the file was successfully created
          {
          fsUploadFile.close();                               // Close the file again
          Serial.print("handleFileUpload Size: ");
          Serial.println(upload.totalSize);
          server.sendHeader("Location", "/success.html");     // Redirect the client to the success page
          server.send(303);
          }

        else
          {
          server.send(500, "text/plain", "500: couldn't create file");
          }
        }
  }

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t lenght)  // When a WebSocket message is received
  {
  FSInfo fs_info;
  Dir dir = SPIFFS.openDir("/");
  String paquete;
  paquete = "<p>";

  while (dir.next())
    {
    if (dir.fileName().endsWith(".csv"))
      {
      paquete += "<strong>";
      paquete += dir.fileName();
      paquete += "</strong></p>";
      paquete += "<p>";
      }
    }

  switch (type)
    {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED:
      {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      // send message to client
      webSocket.sendTXT(num, "Connected");
      }
    break;

    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      //FSInfo fs_info;
      // Dir dir = SPIFFS.openDir("/");
      // send message to client
      // webSocket.sendTXT(num, "message here");
      // send data to all connected clients
      webSocket.broadcastTXT(paquete);
      break;

    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
    }
  }

void handleSend()
  {
    
  if (server.arg("path") == NULL)
    {
    server.send(400, "text/plain", "400: Invalid Request");
    }

  Serial.print("Archivo a enviar: ");
  Serial.print(server.arg("path"));
  Serial.println("");
  
  File file2 = SPIFFS.open(server.arg("path"), "r");
 
  if (!file2) {
    Serial.println("Failed to open file for reading");
    return;
  }
  
    int occ = 0;
    int p = 0;
    char data = NULL;
    char c = '\0';
    char aux = '\0';
    
    String arr; 
    //arr = (char*) malloc (sizeof(char));
   /*separa el sample rate y la cantidad de muestras del archivo*/
   while (file2.available()&&occ<6) 
    {
      ESP.wdtFeed();
      data = file2.read(); 
      if(data==','){
        if((++occ > 3) && (occ % 2 == 0))
           //arr[p++] = ',';
           arr.concat(',');
      }
      else{
        if(data>='0' && data<='9')
           arr.concat(data);    
      }
    }

 Serial.println(arr);
 
  int tx_status = 0;
  int estado = 0;
  int cnt = 0;
  String i2c_data;
  char data_array[5];
  String data_string;
  int comma_cnt = 0;
  char aux_buffer[5] = {NULL};
  char print_buffer[50];
  while(estado!=3)
  {

    switch(estado)
    {

    case 0:
    
      do{
      Wire.beginTransmission(0x14);
      Wire.write(arr.length());
      tx_status = Wire.endTransmission();
      }while(tx_status!=0);
      estado = 1;

    break;
    
    case 1:

      do{
      Wire.beginTransmission(0x14);
      Wire.write(arr.c_str()); 
      tx_status = Wire.endTransmission();
      }while(tx_status!=0);      
      estado = 2;
     
   break;

   case 2:

   while (file2.available()) 
    {
      ESP.wdtFeed();
      data = file2.peek(); 
      if(data!='\n' && data!='\r' && file2.available())
      {
          p=0;
          for(int i=0; i<6; i++)
          {
             aux_buffer[i] = NULL;
          } 
     
          do{
             data_string.concat((char)file2.peek()); 
             data =  file2.read();  
           } while(data!=',' && file2.available());


         
            while(data_string.length()<5)
            {
             data_string = '0' + data_string;
            }

           data_string.toCharArray(aux_buffer,5);
           data_string = "";
           Serial.println(aux_buffer);
           delay(1);
            do{
            ESP.wdtFeed();    
            Wire.beginTransmission(0x14);
            Wire.write(aux_buffer); 
            tx_status = Wire.endTransmission();
            
              if(tx_status == 2)
              {
                delay(10);
              }
              else
              if(tx_status == 3)
              {
                delay(10);
              }
            
            }while(tx_status!=0); 
            
          file2.read();  
      }
      else
      {
       file2.read();
      }    
     } 

     file2.close();
     
   estado = 3;

   break;
  
    case 3:
    Serial.println("Salgo del switch-case");
    break;

    }
  }
  Serial.println("Fin de programa"); 
 
 /*
  FSInfo fs_info;
  if (SPIFFS.info(fs_info))
    {
    Serial.printf("Total Bytes %s \n",fs_info.totalBytes);
    Serial.printf("Used Bytes %s \n",fs_info.usedBytes);
    Serial.printf("Block Size %s \n",fs_info.blockSize);
    Serial.printf("Page Size %s \n",fs_info.pageSize);
    Serial.printf("Max Open Fles %s \n",fs_info.maxOpenFiles);
    Serial.printf("Max Path Lenght %s \n",fs_info.maxPathLength);
    }
  */
      //ESP.wdtFeed();
      server.sendHeader("Location", "/");     // Redirect the client 
      server.send(303);
  }

void handleDelete()
  {
  Serial.println(server.arg("path"));

  if (server.arg("path") == NULL)
    {
    server.send(400, "text/plain", "400: Invalid Request");
    }

  if (SPIFFS.exists(server.arg("path")))
    {
    SPIFFS.remove(server.arg("path"));

    if (!SPIFFS.exists(server.arg("path")))
      {
      server.sendHeader("Location", "/success.html");     // Redirect the client to the success page
      server.send(303);
      }
    }

  else
    {
    server.send(409, "text/plain", "409: Conflict trying to delete the file");
    }
  } 
