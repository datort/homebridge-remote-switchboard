String oAuthAccessToken;

bool refreshAuth(void *) {
  DynamicJsonDocument postData(2048);
  postData["username"] = "admin";
  postData["password"] = "admin";

  String json;
  serializeJson(postData, json);

  http.begin(client, "http://basement:8581/api/auth/login");
  http.addHeader("Content-Type", "application/json");

  
  int responseCode = http.POST(json);

  if (responseCode == 201) {
    DynamicJsonDocument recvData(2048);
    deserializeJson(recvData, http.getStream());

    oAuthAccessToken = recvData["access_token"].as<String>();
    Serial.print("oAuth token received: ");
    Serial.println(oAuthAccessToken);
  }

  http.end();

  return true;
}

bool refreshAccessories(void *) {
  if (oAuthAccessToken.length() == 0) {
    Serial.println("Not refreshing Accessories: No oAuthToken present");
    return true;
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    accessoryState[i] = getAccessory(accessoryIds[i]);
  }
  
  return true;
}

bool getAccessory(String uniqueId) {
  http.begin(client, "http://basement:8581/api/accessories/" + uniqueId);
  http.addHeader("Authorization", "Bearer " + oAuthAccessToken);
  http.GET();

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, http.getStream());

  bool state = doc["values"]["On"].as<bool>();
  
  http.end();

  return state;
}

void toggleAccessory(String uniqueId, bool state) {
  DynamicJsonDocument putData(2048);
  putData["characteristicType"] = "On";
  putData["value"] = state ? 1 : 0;

  String json;
  serializeJson(putData, json);
  
  http.begin(client, "http://basement:8581/api/accessories/" + uniqueId);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + oAuthAccessToken);
  http.PUT(json);

  http.end();
}
