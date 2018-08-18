void webListenForClients() {
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      byte remoteMac[6];

      // a device has connected to the AP
      Serial.print("Device connected to AP, MAC address: ");
      WiFi.APClientMacAddress(remoteMac);
      Serial.print(remoteMac[5], HEX);
      Serial.print(":");
      Serial.print(remoteMac[4], HEX);
      Serial.print(":");
      Serial.print(remoteMac[3], HEX);
      Serial.print(":");
      Serial.print(remoteMac[2], HEX);
      Serial.print(":");
      Serial.print(remoteMac[1], HEX);
      Serial.print(":");
      Serial.println(remoteMac[0], HEX);
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    // an http request ends with a blank line
    String currentLine = "";                // make a String to hold incoming data from the client
    boolean currentLineIsBlank = true;
    String requestedUrl = "";
    String requestVerb = "";
    int contentLength = -1;
    bool inContent = false;
    String content = "";
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank && contentLength == -1) {

          Serial.println("REQUESTED URL: [" + requestedUrl + "]" + " (" + requestVerb + ")");

          process_request(requestedUrl, requestVerb, content);
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          
          client.println(Html_Config());

          requestedUrl = "";
          requestVerb = "";
          break;
        }
        if (c == '\n' && currentLineIsBlank && contentLength >= 0) {
          inContent = true;
        }
        if(inContent == true){
          content = (content + c);
          if (content.length() > contentLength) {
            process_request(requestedUrl, requestVerb, content);
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");  // the connection will be closed after completion of the response
            //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            
            client.println(Html_Config());
  
            requestedUrl = "";
            requestVerb = "";
            break;
          }
        }
        if (c == '\n' && inContent == false) {
          // you're starting a new line
          Serial.println("LINE: " + currentLine);

          if (currentLine.startsWith("GET ")) {
            requestVerb = "GET";
            requestedUrl = currentLine.substring(4, (currentLine.indexOf(" ", 4)));
            Serial.println("Dins de GET, rebem " + requestedUrl );

            if (requestedUrl.endsWith("/gotoa")) {
                go_to_a();
            }

            if (requestedUrl.endsWith("/gotob")) {
                go_to_b();
            }
          }

          if (currentLine.startsWith("POST ")) {
            requestVerb = "POST";
            requestedUrl = currentLine.substring(5, (currentLine.indexOf(" ", 5)));
          }

          if (currentLine.startsWith("Content-Length: ")) {
            contentLength = currentLine.substring(16, (currentLine.indexOf(" ", 16))).toInt();
          }

          // reset line-tracking for next line
          currentLine = "";
          currentLineIsBlank = true;
        } else if (c != '\r' && inContent == false) {
          // you've gotten a character on the current line
          currentLine = (currentLine + c);
          currentLineIsBlank = false;
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void process_request(String requestedUrl, String verb, String content) {
  Serial.println("processing URL: (" + verb + ") " + requestedUrl);
  Serial.println("Content: " + content);
  
  if (verb == "POST" && content.length() > 0) {
    distance = GetQueryStringValue(content, "distance").toFloat();
    distance_mm_multiplier = GetQueryStringValue(content, "distance_mm_multiplier").toFloat();
    duration = GetQueryStringValue(content, "duration").toFloat();
    duration_sec_multiplier = GetQueryStringValue(content, "duration_sec_multiplier").toFloat();
    direction = GetQueryStringValue(content, "direction").toInt();
    pull_distance_over_time(distance * direction, distance_mm_multiplier, duration, duration_sec_multiplier);
  }
  
}

String GetQueryStringValue(String query, String param) {
  String value = "";
  int paramLoc = query.indexOf(param);
  if (paramLoc > -1) {
    // value exists, go get it
    int valueStartLoc = query.indexOf("=",paramLoc) + 1;
    int valueEndLoc = (query + "&").indexOf("&",valueStartLoc);
    value = query.substring(valueStartLoc, valueEndLoc);
  }
  Serial.println("Extracted value: " + param + " = " + value);
  return value;
}
