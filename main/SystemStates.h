#ifndef SystemStates_h
#define SystemStates_h

/*
 UNINITIALIZED - The system is in the initial state, possibly awaiting configuration
 AP_MODE - The system is operating as an Access Point for WiFi configuration
 STA_MODE - The system is connected to a WiFi network (Station mode)
 OFFLINE_MODE - The system is operating without WiFi connectivity
 ERROR_MODE - The system has encountered an error and is in an error handling state
 UPDATE_MODE - The system is in firmware update mode (e.g., OTA updates)
*/
enum class SystemState {
    UNINITIALIZED, 
    AP_MODE,       
    STA_MODE,     
    OFFLINE_MODE,
    ERROR_MODE, 
    UPDATE_MODE  
};

extern SystemState systemState = SystemState::UNINITIALIZED;

#endif