# Architecture du projet

## Vue générale

L'application est un assistant de traduction contextuel qui combine:
- un cœur logique en C
- une API IA externe pour la traduction
- une base de données SQLite locale
- une interface interactive en ligne de commande

## Flux utilisateur

```
User Input
    ↓
Main App (app.c)
    ↓
Translator Module (translator.c)
    ├─ Fetch Translation via API (api_client.c)
    ├─ Parse JSON Response (api_client.c)
    └─ Save to Database (storage.c)
    ↓
Display Result to User
```

## Modules

### app.c / app.h
Orchestration du menu principal, gestion des entrées utilisateur.

### translator.c / translator.h
Logique métier: traduction, gestion des styles (littéral, naturel, professionnel).

### api_client.c / api_client.h
Communication HTTP vers l'API IA (OpenAI, Gemini, etc.).
Utilise `curl` pour les requêtes HTTPS.

### storage.c / storage.h
Persistance SQLite: historique et vocabulaire personnel.

## Structure de base de données

### Table: translations
```
id (INTEGER PRIMARY KEY)
source_text (TEXT)
target_language (TEXT)
style (INTEGER: 0=literal, 1=natural, 2=professional)
translated_text (TEXT)
timestamp (DATETIME)
```

### Table: vocabulary
```
id (INTEGER PRIMARY KEY)
source_word (TEXT UNIQUE)
target_word (TEXT)
frequency (INTEGER)
last_used (DATETIME)
```

## Sécurité

- Clés API stockées dans des variables d'environnement
- Validation des entrées utilisateur
- Gestion des erreurs réseau robuste
- Aucun secret committé dans le dépôt

## Dépendances

- C11 ou plus
- MinGW (Windows) ou GCC (Unix)
- curl (pour appels HTTP)
- SQLite3 (pour base locale)
- Optionnel: cJSON (pour parsing JSON)

## Prochaines étapes

1. Intégration réelle d'une API IA (OpenAI, Gemini, Mistral)
2. Interface web via wrapper ou microservice
3. Tests unitaires complets
4. Déploiement en production
