#include "mbed.h"
#include <stdio.h>
#include "SpwfSAInterface.h"
#include "SPWFSAxx.h"
#include "TLSSocket.h"
#include "ConditionlyDaikin.h"
#include "mbed_trace.h"
#include "https_request.h"

WiFiInterface *wifi;

static const char SSL_CA_PEM[] = "-----BEGIN CERTIFICATE-----\n"
                                 "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF"
                                 "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6"
                                 "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL"
                                 "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv"
                                 "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj"
                                 "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM"
                                 "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw"
                                 "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6"
                                 "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L"
                                 "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm"
                                 "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC"
                                 "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA"
                                 "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI"
                                 "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs"
                                 "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv"
                                 "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU"
                                 "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy"
                                 "rqXRfboQnoZsG4q5WTP468SQvvG5"
                                 "-----END CERTIFICATE-----";

int init_wifi()
{
    // init the wifi module
    wifi = WiFiInterface::get_default_instance();
    if (!wifi) {
        printf("ERROR: No Interface found. Make sure it is connected\n");
        return -1;
    }

    // connect to the wifi network specified in the mbed.json
    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    int ret = wifi->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA2);
    if (ret != 0) {
        printf("\nConnection error: %d\n", ret);
        return -1;
    }
    printf("Successful connection\n\n");
    return 1;
}

bool callForServer(ConditionlyDaikin irdaikin)
{
    NetworkInterface *network = (NetworkInterface *)wifi;


    HttpsRequest *request = new HttpsRequest(network, SSL_CA_PEM, HTTP_GET, "https://asemilrmob.execute-api.us-east-2.amazonaws.com/beta/command");
    HttpResponse *response;
    response = request->send(NULL, 0);
    if((response !=NULL)       ) {
        //////////////////////////////////////////////////////////////////////
        
        printf("Received command:\n%s\n", response->get_body_as_string().c_str());

        irdaikin.sendFromJson( response->get_body_as_string().c_str() );

        /////////////////////////////////////////////////////////////////////



        if(strcmp("null",response->get_body_as_string().c_str()) == 0) {
            delete request;

            return false;
        } else {
            delete request;
            return true;
        }
    }
    delete request;
    return false;
}


int main()
{
    mbed_trace_init();
    ConditionlyDaikin irdaikin(LED1);

#ifdef MBED_MAJOR_VERSION
    printf("Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

    init_wifi()>0;
    callForServer(irdaikin);
    while (1) {
    wait_ms(20000);
        //ConditionlyDaikin irdaikin(LED1);
        //const  char * json = "{\"power\":true, \"mode\":4, \"fan\":5, \"swing\":true, \"swingLR\":true, \"temp\":19}";
        //irdaikin.sendFromJson( json );
        callForServer(irdaikin);

    }
    wifi->disconnect();
    printf("\End of the Execution\n");
}
