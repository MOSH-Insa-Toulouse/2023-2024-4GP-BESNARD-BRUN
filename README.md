# 2023-2024 : Capteur low-tech Graphite (Niels Brun &amp; Paul Besnard)

## SOMMAIRE
*** 
  - [Contexte](#contexte)
  - [Livrables](#livrables)
  - [Matériel nécessaire](#matériel-nécessaire)
  - [1. Simulation électronique du capteur sous LTSpice](#simulation-électronique-du-capteur-sous-ltspice)
  - [2. Design du PCB sous KiCad](#design-du-pcb-sous-kicad)
  - [3. Code arduino](#code-arduino)
  - [4. Application android APK sous MIT App Inventor](#application-android-apk-sous-mit-app-inventor)
  - [5. Réalisation du shield](#réalisation-du-shield)
  - [6. Banc de test](#banc-de-test)
  - [7. Datasheet](#datasheet)
  - [Contact](#contact) 
  

*** 

## Contexte
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Dans le cadre de l'UF "Du capteur au banc de test" se déroulant en 4ème année de Génie Physique de l’INSA Toulouse, nous avons développé un dispositif permettant de mesurer la contrainte. Le capteur du dispositif est basé sur l'article "Pencil Drawn Strain Gauges and Chemiresistors on Paper" (Cheng-Wei Lin*, Zhibo Zhao*, Jaemyung Kim & Jiaxing Huang). Il est simplement composé d'un bout de papier avec du crayon à papier. En déformant le papier, le nombre de particules de graphite composant le crayon à papier déposé sur le papier, reliées varie en fonction du type de déformation. Ce système granulaire subit une modification de résistance et de conductance. Grâce à cela, on  pourra remonter à la déformation tel une jauge de contrainte traditionnel. \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;L'objectif est donc de pouvoir réaliser un dispositif permettant la mesure de déformation à partir d'un capteur low-tech. En passant par différentes étapes : simulations électroniques, design du PCB, code arduino et réalisation de datasheet.

## Livrables
- Un Shield PCB relié à une carte arduino UNO avec différents composants : un capteur graphite, un amplificateur transimpédance et un module bluetooth. Il peut également avoir un écran OLED, un flex sensor commercial, un potentiomètre digital, encodeur rotatoire ou des boutons.
- Un code arduino qui gère les différents composants cités précédemments (mesures de contraintes, échanges bluetooth et OLED, potentiomètre digital et boutons)
- Une application Android (sous MIT App Inventor) interfaçant le PCB et le code arduino.
- Un code arduino réalisant les essais de banc de test sur les mesures de contraintes.
- Une datasheet sur le capteur de contrainte.

Nous avons opté pour l'ajout d'un écran OLED, du flex sensor commercial, du potentiomètre digital. Egalement, nous avons choisi l'implémentation de 3 boutons plutôt que de l'encodeur rotatoire.

## Matériel nécessaire
Pour réaliser notre dispositif électronique, voici la liste des composants nécessaires :

- Résistances : 1 de 1 $k\ohm$, 1 de $10k\ohm$, 2 de $100k\ohm$ pour l'amplificateur transimpédance. 3 de $10k\ohm$ pour les boutons (peuvent être éviter en utilisant les résistances internes de l'arduino). 1 de $47k\ohm$ pour le flex sensor.
- Capacités : 3 de 100 nF, 1 de 1 uF
- Arduino Uno
- Amplificateur opérationnel LTC1050
- Potentiomètre digital MCP41050
- Module Bluetooth HC05
- Ecran OLED 128x64
- Flex Sensor
- 3 boutons


## Simulation électronique du capteur sous LTSpice
Notre capteur de graphite possède une résistance variable de l'ordre du gigaohm. Le courant alors généré lorsque l'on applique une tension de 5V aux bornes du capteur est très faible (de l'ordre de la dizaine de nanoampères). Ainsi, pour récupérer et pouvoir analyser ce signal, nous devons l'amplifier. C'est pourquoi nous avons utilisé un montage transimpédance constitué d'un amplificateur opérationnel (AOP) pour fournir un signal en tension suffisant au convertisseur analogique-numérique (ADC) d'une carte Arduino UNO. Nous avons testé ce montage sur le logiciel LTspice. Voici son schéma :

![capteur_graphite](https://github.com/NieBrun/2023-2024-4GP-BESNARD-BRUN/blob/main/Images/LTspice/schema_complet.png)

Concernant le choix de notre AOP, celui-ci devait être capable d'accepter en entrée un très faible courant. Il doit également avoir un offset de tension très faible afin de ne pas fausser les valeurs de tension transmises à l'ADC qui seront ensuite analysées. C'est pourquoi nous avons choisi le LTC 1050.
A ce circuit amplificateur, nous avons ajouté trois filtres pour notre signal :

- à l'entrée, un filtre passe-bas passif (R1,C1) de fréquence de coupure de 16 Hz. Il permet de filtrer les bruits en courant sur le signal d'entrée
- un autre filtre passe bas de fréquence de coupure de 1.6 Hz (R3,C4) couplé à l'AOP. Ce filtre actif permet de filtrer la composante du bruit à 50 Hz provenant du réseau électrique
- à la sortie de l'amplificateur, un dernier filtre (R6,C2) de 1.6 kHz permet de retirer le bruit créé en cours de traitement (bruits des alimentation, de l'horloge etc...)

Egalement, nous avons placé la capacité C3 de sorte à ce qu'elle filtre le bruit de l'alimentation. Aussi, la résistance R5 en entrée protège l'AOP contre les décharges électrostatiques en plus de formé avec la capacité C1 un filtre pour les bruits en tension. Enfin, la résistance R2 sera remplacé plus tard par un potentiomètre digital. Cela nous permettra de régler le gain de notre AOP en fonction de nos besoins.

Nous avons donc testé notre circuit afin de savoir si nos filtres seraient efficients :


Voici la réponse de notre circuit pour vérfier que le capteur soit correctement amplifié : 
IMAGE EN TRANSIENT
Le signal est amplifié à 1V donc l'arduino UNO pourra le mesurer.

Enfin, voici la réponse lors qu'on simule un courant alternatif pour vérifier que le bruit est bien filtré.
IMAGE EN AC
On voit que le bruit est bien atténué, à 50Hz, il est atténue de xx dB.



## Design du PCB sous KiCad

## Code arduino
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Nous avons utilisé l'IDE Arduino 2.3.2. Nous avons utilisé les librairies SoftwareSerial pour le bluetooth et Adafruit_SSD1306 pour l'écran OLED. Sur cette dernière, elle utilise beaucoup de RAM pour les buffers, cette utilisation de RAM n'est pas affiché par l'IDE Arduino. Il se peut que le programme ne se lance pas si un attention n'a pas été porté sur cette utilisation de RAM. Pour éviter cela, on peut utiliser  la fonction ["F()"](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/) ,utiliser des librairies pour l'écran OLED moins gourmande ou enfin diminuer la résolution de l'écran.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Dans le [dossier arduino](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BESNARD-BRUN/tree/main/Arduino) se trouve les différents fichiers pour tester les multiples éléments du dispositif. \
Concernant le [fichier principal](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BESNARD-BRUN/blob/main/Arduino/Main/Main.ino) : lors de la mise sous tension de l'arduino, une première calibration du potentiomètre digitale est faite en fonction de la valeur mesurée sur le capteur graphite. 
Suite à cela, le dispositif est par défaut dans le menu déroulant avec 4 choix : 
- une mesure instantannée toutes les 500 ms
- une mesure moyennée sur 2500 ms
- une mesure du flex sensor commercial et enfin 
- une calibration du potentiomètre digital

![](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BESNARD-BRUN/tree/main/Images/Menu.jpg)

Le choix de menu se fait grâce aux 3 boutons : un pour descendre dans le menu, un pour monter dans le menu et un troisième pour valider le choix. Ce dernier bouton de validation sert également à sortir du menu choisi.

IMAGE à rajouter

Chaque choix du menu appel une fonction différente qui réalise sa mesure et qui est envoyé à la fonction DisplayAndTransmitter afin de l'afficher sur l'écran OLED et l'envoyer sur l'application bluetooth. Tant que le bouton central de "validation" n'est pas appuyé, on reste dans cette boucle de mesure et d'affichage.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Le calcul de la résistance du capteur en graphite se fait avec : $$Res=R1*(1+\frac{R3}{R2})*\frac{Vcc}{Vadc}-R1-R5$$ \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Et dans notre cas, notre résistance R2 est variable : c'est celle du potentiomètre digital qui est calculé avec : $`R2=\frac{47500*pos}{256}+125`$ où notre $47000$ correspond à la valeur de résistance maximale de notre MCP41050 et $pos$ la position du potentiomètre parmi les 256 valeurs.


## Application android APK sous MIT App Inventor
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Une application est également disponible avec le dispositif : développé sous [MIT App Inventor](https://appinventor.mit.edu/) . 

L'application reçoit les données transmis par le module bluetooth HC-05. Elle affiche ensuite la valeur tranmis (des $M\ohm$ pour le capteur graphite ou des Ohms pour le flex sensor.

![](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-BESNARD-BRUN/tree/main/Images/Appli_Android.jpg)

L'application peut s'installer [sous android ici](f.lien.apk) et toutes les informations liées à l'application son dans [le dossier Application Android](dossier application android)

## Réalisation du shield

## Banc de test

## Datasheet

## Contact