# 🛡️ Keylogger en C - Éducatif

**Auteur** : VLADCRACK  
**Contact** : [The VLADCRACK](https://t.me/TheVLADCRACK_237)  

Ce programme en C est un **keylogger** simple conçu à des fins éducatives. Il capture les frappes du clavier en temps réel et les enregistre dans un fichier de log nommé `keylog.txt`.

---

## ⚠️ Avertissement
**Ce projet est uniquement destiné à des fins éducatives et à la sensibilisation à la sécurité informatique.**  
L'auteur **décline toute responsabilité quant à l'utilisation abusive** ou illégale de ce programme. Assurez-vous de respecter les lois de votre juridiction avant de l'utiliser.

---

## 🛠️ Fonctionnalités
- Capture en temps réel des frappes clavier sur un périphérique d'entrée spécifique.
- Écrit les touches capturées dans un fichier de log.
- Gère les touches spéciales telles que `<BACKSPACE>` ou `<ENTER>`.
- Utilise une table de correspondance pour afficher les caractères capturés.

---

## 🚀 Utilisation
### 1. Prérequis
- **Système Linux** (le programme utilise le fichier `/dev/input/event4`).
- Droits administratifs pour accéder aux périphériques d'entrée.

### 2. Compilation
Compilez le programme avec GCC :

```bash
gcc -o keylogger keylogger.c
```

### 3. Execution

```bash
./keylogger
```
