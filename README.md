# Librairie IoT BLE Adafruit Feather 32u4
____
## Sommaire

1. __Classes C++__
    - IoT_BLE
    - BleSingleton
    - CommandParser
    - ConfigGatt
    - ConfigDev
    - HexUtils
1. __Configuration__
    - Connexion BLE UART
    - Utilisation des commandes
    - Commandes disponibles
1. __Didacticiel__
    - Se connecter à la carte
    - Utiliser une commande
    - Ajouter un service GATT
    - Ajouter une caractéristique GATT
    - Modifier le nom et le mot de passe par défaut.
1. __Problèmes connus__
    - Apparition du message "cmd invalide" lors de l'exécution d'une commande valide
1. __FAQ__


____

## Description des classes
Dans cette première partie, vous trouverez une description brève des différentes classes qui composent cette librairie.

### IoT_BLE
La classe __IoT_BLE__ est la classe principale de la librairie. Elle contient toutes les fonctions publiques que cette dernière propose. 

Les fonctions publiques de la librairie permettent de :
    - Lire et écrire sur la connexion UART du module
    - Ajouter des services et des caractéristiques GATT
    - Déclencher une commande de configuration
    - Vérifier le buffer UART pour détecter des commandes

C'est cette dernière fonctionnalité qui permet la configuration sans fil du module, en passant par la connexion UART.

### BleSingleton
La classe __BleSingleton__ est une classe donnant accès à l'objet permettant l'utilisation du module BLE de la carte _Feather 32u4_. Il est conçu en suivant le patron de conception _singleton_ qui permet l'instanciation d'un unique objet.

### CommandParser
La classe __CommandParser__ contient la logique de reconnaissance des commandes de configuration. Elle a pour but de reconnaître les noms des commandes dans les chaînes de caractères reçues pour déterminer les actions à effectuer. C'est dans cette classe que les chaînes correspondant aux commandes sont écrites.

### ConfigGatt
La classe __ConfigGatt__ encapsule la logique de traitement des actions en rapport avec le profil GATT du module (services et caractéristiques).

### ConfigDev
La classe __ConfigDev__ encapsule la logique de traitement des actions en rapport avec le module BLE lui-même, comme le changement de nom, le redémarrage, etc...
C'est également cette classe qui gère l'identification et qui stocke le mot de passe.

### HexUtils
Cette classe est une classe utilitaire permettant de convertir des entiers en chaînes de caractères représentant leurs valeurs hexadécimales.
____

## Configuration
Cette section est dédié à la description de la configuration sans fil de la librairie.

### Connexion BLE UART
La configuration sans fil est possible grâce à la connexion UART via *Bluetooth Low Energy*. Pour pouvoir en profiter à partir de votre téléphone, utiliser une application permettant ce genre ce connexion, comme l'application _Adafruit Bluefruit LE Connect_ par exemple, disponible gratuitement sur *Google Play* (pour Android).

### Utilisation des commandes

Pour utiliser les commandes de configuration sans fil, il suffit d'envoyer une commande via UART.

Certaines commandes ne vont fonctionner que si vous êtes connecté en mode admin (via la commande login).

Certaines commandes vont demander des paramètres. Pour cela, envoyer juste le nom de la commande dans un premier temps, vous aurez ensuite un retour du module vous demandant le paramètre. Saisissez-le alors pour lancer la commande. 
La majorité des commandes demandant des paramètres ont un système de *timeout* (délai maximum pour saisir les paramètres) pour éviter que la carte ne reste bloquée trop longtemps. Par défaut, le délai est de 15 secondes.

### Commandes disponibles
Vous avez à votre disposition les commandes de configuration suivantes :
    - **login** : demande la connexion en mode admin
    - **logout** : demande la déconnexion du mode admin
    - **getlog** : renvoie l'état actuel de connexion admin (admin connecté / admin non connecté)
    - **setadvon** : active l'avertissement des services GATT aux appareils alentours
    - **setadvoff** : désactive l'avertissement des services GATT aux appareils alentours
    - **getadv** : renvoie la politique actuelle d'avertissement des service GATT aux appareils alentours
    - **reset** : redémarre le module BLE
    - **disconnect** : déconnecte **tous** les appareils connectés au module BLE
    - **setpwd** : change le mot de passe du mode configuration
    - **setconon** : active la possibilité de se connecter sans fil au module BLE 
    - **setconoff** : désactive la possibilité de se connecter sans fil au module BLE 
    - **getcon** : renvoie la politique actuelle d'autorisation de connexion sans fil au module BLE
    - **getdevname** : renvoie le nom actuel du module BLE
    - **setdevname** : modifie le nom du module BLE

___

## Didacticiel

### Utiliser la librairie
Pour utiliser la librairie, il suffit d'instancier la classe __IoT_BLE__ et d'appeler sa fonction _start()_.
Cette fonction permet l'initialisation de la librairie, et renvoie _true_ si cette dernière a été initialisé avec succès.

### Se connecter à la carte
Pour se connecter à la carte via *Bluetooth Low Energy* avec votre téléphone, il vous suffit d'utiliser une application permettant des connexions UART via BLE, comme _Adafruit Bluefruit LE Connect_ disponible gratuitement sur *Google Play* (pour Android).
La carte doit être alimentée et un sketch Arduino utilisant la librairie doit être sur la carte. Assurez-vous d'avoir instancié la classe __IoT_BLE__ et d'avoir appelé sa fonction _start()_ avec succès (valeur _true_ renvoyée).

### Utiliser une commande
__*Voir section "Configuration > Utilisation des commandes"*__

### Ajouter un service GATT
Pour ajouter un service GATT, il vous suffit d'appeler la fonction *IoT_BLE::addService(...)*. Cette fonction prend en paramètre l'identifiant que vous voulez utiliser pour ce service.
La fonction *IoT_BLE::addService(...)* existe en deux versions différentes : 
    - *addService(uint16_t uuid16)* prend un id hexadécimal de 4 caractères défini par le standard GATT (Liste des services définis par le standard : ***https://www.bluetooth.com/specifications/gatt/services***).
    - *addService(uint8_t uuid128[])* prend un id hexadécimal de 16 caractères de long, sous la forme d'un tableau de paires de caractères de longueur 8. Cette fonction permet la spécification de nouveaux services, non définis dans le standard.
Ces fonctions renvoies l'indice correspondant au service, indice fournit par le module BLE. Cet indice est toujours supérieur ou égal à 1, et est généré en partant de 1 (pour le premier service ajouté) et en incrémentant à chaque nouveau service.
### Ajouter une caractéristique GATT
Pour ajouter une caractéristique GATT, il vous suffit d'appeler la fonction *IoT_BLE::addChar(...)*. Cette fonction existe en deux versions différentes pour le mêmes raisons que la fonction *IoT_BLE::addService(...)* (Voir "Ajout d'un service GATT"). la liste des identifiants définis par le standard est disponible ici : ***https://www.bluetooth.com/specifications/gatt/characteristics***.

Ces fonction prennent également d'autres paramètres :
    - *properties* : les propriétés d'une caractéristiques correspondent à ses permissions, qui décrivent les actions possibles avec les caractéristiques. Il en existe actuellement 5 (*READ*, *WRITE_WITHOUT_RESPONSE*, *WRITE*, *NOTIFY*, *INDICATE*).
    - minlen : longueur minimale de la valeur de la caractéristique.
    - maxlen : longueur maximale de la valeur de la caractéristique.
    - value : valeur initiale de la caractéristique.

### Modifier le nom et le mot de passe par défaut.
Pour modifier le nom par défaut du module, vous devez modifier la valeur de la variable *DEVICE_NAME* présente en haut du fichier *IoT_BLE.h*.
Vous pouvez également modifier manuellement le nom une fois la carte démarrée via les commandes de configuration sans fil, mais le nom ainsi paramétré ne sera utilisé que tant que la carte est sous-tension. AU premier redémarrage, le nom par défaut sera utilisé.

La modification du mot de passe par défaut suit la même procédure, à la seule différence que la variable à modifier est la variable *PASSWORD*, présente elle aussi en haut du fichier *IoT_BLE.h*.
___

## Problèmes connus

### Apparition du message "cmd invalide" lors de l'exécution d'une commande valide
Certaines commandes, lors de leurs utilisations, entraînent l'affichage de *"cmd invalide"* après les autres retours attendus. Cependant, l'action de la commande est bien effectuée correctement.

Pour le moment, les commandes suivantes sont sujettes à ce comportement :
    - setadvon
    - setadvoff
    - setconon
    - setconoff

Ce message *"cmd invalide"* est dû à un code d'erreur levé en interne par le module BLE. Nous ne savons pour le moment pas pourquoi ce code d'erreur est levé, ni à quoi il correspond.

Si vous avez ce type de retour, vérifiez si l'action a bien été effectuée. Si elle ne l'a pas été, vérifiez l'orthographe de la commande. Si l'orthographe de la commande que vous avez saisit était valide, merci de nous contacter par mail.
___

## FAQ
Si vous avez lu cette documentation et qu'il vous reste des questions, nous serons heureux d'y répondre. Veuillez nous contacter par mail.