# SwitchRelaySplit
Sketch to control Lights using MySensors

This library helps to add multiple smart Lights/Relays to one Arduino board (preferably Arduino MEGA) by just adding one line of code per Light. It is based on MySensors library. Tested with Domoticz, but also worked for Home Assistant (feedback from community).

To Use the code:
- download newest .ino file and all other files to one folder - same name as newest .ino file
- change the declaration in .ino file, for example:




{1, 22, 38, 50, 0, "światło w kotłowni"},

{2, 23, 39, 50, 0, "światło w kotłowni"},

{3, 24, 40, 50, 0, "halogeny nad zlewem + roleta wewn."},

{4, 25, 41, 50, 0, "lampa w kuchni na suficie"},

{5, 26, 42, 50, 0, "okap"},

{6, 27, 43, 50, 0, "pasek LED + roleta wewn."},

{7, 28, 44, 50, 0, "halogeny w lewo od HS + roleta wewn. HS lewa"},

{8, 29, 45, 50, 0, "lampa nad stołem"},

{9, 30, 46, 50, 0, "lampa nad sofą"},

{10, 31, 47, 50, 0, "lampa nad stolikiem kawowym"},

{11, 32, 48, 50, 0, "halogeny nad HS + roleta wewn. HS prawa"},

{12, 33, 49, 50, 0, "halogeny w prawo od HS + roleta wewn. FIX"},

{13, 34, 50, 50, 0, "lampa przy schodach od strony wiatrołapu"},

{14, 35, 51, 50, 0, "lampa przy schodach od strony kotłowni"},

{15, 36, 52, 50, 0, "lampa pod schodami przy słupie"},

{16, 37, 53, 50, 0, "lampa nad lustrem w WC na dole"},

{17, A0, A8, 50, 0, "lampa w gabinecie"},

{18, A1, A9, 50, 0, "lampa w gabinecie"},

{19, A2, A10, 50, 0, "lampa w wiatrołapie"},

{20, A3, A11, 50, 0, "lampa w wiatrołapie"},

{21, A4, A12, 50, 0, "lampa w WC na dole"},

{22, A5, A13, 50, 0, "lampa w łazience na dole"},

{23, A6, A14, 50, 0, "lampa w łazience na dole"},

{24, A7, A15, 50, 0, "lampa w łazience na dole"}





The values are representing:
1. Child ID of your Light/Device (Controller like Domoticz, Home Assistant will show this as device number) KEEP ALL Child ID UNIQUE !!!
2. Pin number of the Button
3. Pin number of the Relay
4. Debounce time - if you don't know what it is, just set it to 50 ms
5. Inverted output - For High Level Trigger need to be 0; for Low level Trigger set 1
6. Description - your Light/Device will show this description to your controller
