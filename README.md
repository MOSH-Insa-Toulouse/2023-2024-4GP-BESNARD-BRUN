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

- Résistances : 2 de 1 kOhms, 5 de 10 kOhms, 2 de 100 kOhms
- Capacités : 2 de 100 nF, 1 de 1 uF
- Arduino Uno
- Amplificateur opérationnel LTC1050
- Potentiomètre digital MCP41500
- Module Bluetooth HC05
- Ecran OLED 128x64
- Flex Sensor
- 3 boutons


## Simulation électronique du capteur sous LTSpice
Notre capteur de graphite possède une résistance variable de l'ordre du gigaohm. Le courant alors généré lorsque l'on applique une tension de 5V aux bornes du capteur est très faible (de l'ordre de la dizaine de nanoampères). Ainsi, pour récupérer et pouvoir analyser ce signal, nous devons l'amplifier. C'est pourquoi nous avons utilisé un montage transimpédance constitué d'un amplificateur opérationnel (AOP) pour fournir un signal en tension suffisant au convertisseur analogique-numérique (ADC) d'une carte Arduino UNO. Nous avons élaboré et testé ce montage sur le logiciel LTspice. Voici son schéma :

![capteur_graphite](https://github.com/NieBrun/2023-2024-4GP-BESNARD-BRUN/blob/main/Images/LTspice/sch%C3%A9ma_global_ampli.png)
(revoir l'image)
Concernant le choix de notre AOP, celui-ci devait être capable d'accepter en entrée un très faible courant. Il doit également avoir un offset de tension très faible afin de ne pas fausser les valeurs de tension transmises à l'ADC qui seront ensuite analysées. C'est pourquoi nous avons choisi le LTC 1050.
A ce circuit amplificateur, nous avons ajouté trois filtres pour notre signal :

- à l'entrée, un filtre passe-bas passif (R1,C1) de fréquence de coupure de 16 Hz. Il permet de filtrer les bruits en courant sur le signal d'entrée
- un autre filtre passe bas de fréquence de coupure de 1.6 Hz (R3,C2) couplé à l'AOP. Ce filtre actif permet de filtrer la composante du bruit à 50 Hz provenant du réseau électrique
- à la sortie de l'amplificateur, un dernier filtre (R4,C4) de 1.6 kHz permet de retirer le bruit créé en cours de traitement (bruits des alimentation, de l'horloge etc...)

Egalement, nous avons placé la capacité C3 de sorte à ce qu'elle filtre le bruit de l'alimentation. Aussi, la résistance R5 en entrée protège l'AOP contre les décharges électrostatiques en plus de formé avec la capacité C1 un filtre pour les bruits en tension. Enfin, la résistance R2 sera remplacé plus tard par un potentiomètre digital. Cela nous permettra de le gain de notre AOP en fonction de nos besoins.

Nous avons donc testé notre circuit afin de savoir si nos filtres seraient efficients :

![capteur_graphite](https://github.com/NieBrun/2023-2024-4GP-BESNARD-BRUN/blob/main/Images/LTspice/test_circuits_filtres.png)

Voici la réponse de notre circuit : 
![capteur_graphite](https://github.com/NieBrun/2023-2024-4GP-BESNARD-BRUN/blob/main/Images/LTspice/tests_circuits_filtres_reponse.png)


![capteur_graphite](https://github.com/NieBrun/2023-2024-4GP-BESNARD-BRUN/blob/main/Images/LTspice/capteur.png)
(pas bien compris à quoi ça sert et il faut vérifier que le signal en sortie est mesurable => retirer l'erreur des sources de tension à 0)

## Design du PCB sous KiCad

## Code arduino

## Application android APK sous MIT App Inventor

## Réalisation du shield

## Banc de test

## Datasheet

## Contact
