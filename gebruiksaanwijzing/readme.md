# Gebruiksaanwijzing

### opladen / vervangen batterijen
1. Zet de robot uit met de schuifschakelaar
2. Doe de batterijen uit de batterij houder
3. Steek nieuwe batterijen in de batterij houder
4. Zet de motor aan met de schuifschakelaar

### draadloze communicatie
#### verbinding maken
1. Zet de robot aan
2. Zorg dat in je code de robot kan verbinden met de wifi door de SSID te weten van je robot en de inloggevens van de wifi.
3. Zet je de robot aan en het blauwe lampje van de robot brandt dan is hij verbonden met het wifi netwerk.
4. Als je de het dasboard van Arduino Cloud opent dan kan je de robot starten.

#### commando's
debug [on/off]: Typ in je seriele monitor 'debug' en dan zie je de sensorwaarden en cyclustijd.
start: je zet de schakelaar op het dasboard van Arduino Cloud op aan of je typt in de seriele monitor 'run'.
stop: je zet de schakelaar op het dasboard van Arduino Cloud op uit.
set cycle [µs]: bepaalt de looptijd van één regelcyclus in microseconden.
set power [0..255]: basisvermogen waarmee beide motoren draaien.
set diff [0..1]: maximale snelheidsafwijking tussen linker en rechter motor.
set kp [0..]: proportionele versterking voor de regelaar.
set ki [0..]: integrale versterking.
set kd [0..]: differentiële versterking.
calibrate black: registreert min/max-waarden op zwarte lijn.
calibrate white: registreert min/max-waarden op witte achtergrond.

### kalibratie
1. Je zet de sensor op een zwart vlak en typt in de seriele monitor 'calibrate black', nu is zwart gekalibreerd.
2. Je zet de sensor op een wit vlak en typt in de seriele monitor 'calibrate white', nu is wit gekalibreerd.

### settings
De robot rijdt stabiel met volgende parameters: 
set power 55
set diff 0.1
set kp 4.150
set ki 0.00
set kd 0.00
set cycle 2000

### start/stop button
uitleg locatie + werking start/stop button
Als je via de Arduino Cloud de schuifschakelaar op 'on' zet dan gaat de robot beginnen.
Zet je deze weer op 'off' dan stopt de robot.
Je kan de robot ook doen starten in de seriele monitor 'run' in te typen.

