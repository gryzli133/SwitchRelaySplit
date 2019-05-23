#define PRESENT_MESSAGE "Switch Relay by Marek"
bool IS_ACK = false; //is to acknowlage

class SwitchRelay
{ 
  uint8_t CHILD_ID_RELAY;
  uint8_t CHILD_ID_DOUBLE;
  uint8_t CHILD_ID_SHORT;
  uint8_t CHILD_ID_LONG;
  int buttonPin;
  int relayPin;
  bool relayON;
  bool relayOFF;

  bool setupMode = false;   // true = setup mode activated -> pass-through mode, Button write directly to relay.

  static bool initial_state_sent;
  uint8_t checksum_initialization;      //store the checksum for the initialization
  int value = 0;
  int oldValueUp = 0;
  int oldValueDown = 0;

  Bounce debouncer = Bounce();
  
  bool serviceMode = 0;
  
  public:
  SwitchRelay(int childId, int button, int relay, int debaunce, bool invertedRelay) : msg(childId, V_LIGHT)
  {
    CHILD_ID_RELAY = childId;
    buttonPin = button;
    relayPin = relay;
    relayON = !invertedRelay;
    relayOFF = invertedRelay;
    pinMode(buttonPin, INPUT_PULLUP);
    debouncer.attach(buttonPin);
    debouncer.interval(debaunce);
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, loadState(CHILD_ID_RELAY)?relayON:relayOFF); 
  }
  
  MyMessage msg;

  void enterServiceMode()
  {
      serviceMode = 1;
  }

  void Update()
  {
    if (debouncer.update()) 
    {
      // Get the update value.
      int value = debouncer.read();
      // Send in the new value.
      if(value == LOW)
      {
         saveState(CHILD_ID_RELAY, !loadState(CHILD_ID_RELAY));
         digitalWrite(relayPin, loadState(CHILD_ID_RELAY)?relayON:relayOFF);
         SyncController();
      }
    }    
  }       
  

  void SyncController()
  {
    send(msg.set(loadState(CHILD_ID_RELAY)));
  }
  
  void SetupMode(bool active)
  {
    setupMode = active;
  }  
  
  void Present()
  {
    // Register all sensors to gw (they will be created as child devices)
     present(CHILD_ID_RELAY, S_COVER, PRESENT_MESSAGE, IS_ACK);
  }

  void Receive(const MyMessage &message)
  {
    // We only expect one type of message from controller. But we better check anyway.
    if (message.type==V_LIGHT && message.sensor==CHILD_ID_RELAY) 
    {
       // Change relay state
       digitalWrite(relayPin, message.getBool()?relayON:relayOFF);
       // Store state in eeprom
       saveState(message.sensor, message.getBool());
       // Write some debug info
       Serial.print("Incoming change for sensor:");
       Serial.print(message.sensor);
       Serial.print(", New status: ");
       Serial.println(message.getBool());
     }     
      return;
    }     
};
