#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define INTERVAL 10 //scan interval in seconds


//event handler for ESP32
static esp_err_t event_handler(void * ctx, system_event_t *event) {
  return ESP_OK;
}

//auth mode 
static char *auth_mode_type(wifi_auth_mode_t auth_mode)
{
  char *types[] = {"OPEN", "WEP", "WPA PSK", "WPA2 PSK", "WPA WPA2 PSK", "MAX"};
  return types[auth_mode];
}

//initializa wifi
void wifiInit() {
  ESP_ERROR_CHECK(nvs_flash_init());
  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

  wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_start());

}

void setup() {
  Serial.begin(115200);
  wifiInit();
  Serial.println("ESP32S3 initialization done");
}

//wifi scan function
void wifi_perform_scan(){
  wifi_scan_config_t scan_config = { 0 };
  uint8_t i;
  uint16_t g_scan_ap_num = 0;

  esp_wifi_scan_start(&scan_config, true);

  esp_wifi_scan_get_ap_num(&g_scan_ap_num);
  if (g_scan_ap_num == 0) {
      Serial.println("No matching AP found");
  }
  
  wifi_ap_record_t g_ap_list_buffer[g_scan_ap_num];
  memset(g_ap_list_buffer, 0, sizeof(g_ap_list_buffer));
  
  if (g_ap_list_buffer == NULL) {
      Serial.println("Failed to alloc buffer to print scan results");
  }
    
  if (esp_wifi_scan_get_ap_records(&g_scan_ap_num, g_ap_list_buffer) == ESP_OK) {
    Serial.println("              SSID             | Channel | RSSI |     Auth     | FTM |         MAC        ");
    Serial.println("******************************************************************************************");
    for (i = 0; i < g_scan_ap_num; i++) {
        printf("%30s | %7d | %4d | %12s | %3d | %X:%X:%X:%X:%X:%X \n", (char *)g_ap_list_buffer[i].ssid, g_ap_list_buffer[i].primary, g_ap_list_buffer[i].rssi, auth_mode_type(g_ap_list_buffer[i].authmode), g_ap_list_buffer[i].ftm_responder, g_ap_list_buffer[i].bssid[0], g_ap_list_buffer[i].bssid[1], g_ap_list_buffer[i].bssid[2], g_ap_list_buffer[i].bssid[3], g_ap_list_buffer[i].bssid[4], g_ap_list_buffer[i].bssid[5]);

    }
    Serial.println("*******************************************************************************************");
  }  

  Serial.println("WiFi scan done");
}

void loop() {
    Serial.println("Scanning");
    wifi_perform_scan();
    delay(INTERVAL*1000);
    //Serial.println(ESP.getFreeHeap());
}
