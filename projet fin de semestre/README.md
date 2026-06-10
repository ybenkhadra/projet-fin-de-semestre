# Assistant de traduction contextuel — Projet ESISA

**Projet de fin de semestre ESISA** basé sur un cœur logique en C, avec une API IA externe pour la traduction et l'amélioration du texte, plus une base SQLite pour mémoriser le vocabulaire et l'historique.

**Soutenance:** 30 mai 2026  
**Equipe:** [À remplir]  
**Supervision:** Prof. Chafik Boulealam

## Idée du projet

L'application est un assistant de traduction contextuel qui va au-delà d'une traduction basique. Elle:
- analyse le contexte du texte à traduire,
- propose trois styles de traduction: littéral, naturel et professionnel,
- conserve un dictionnaire personnel local en SQLite pour réutiliser les termes fréquents,
- enregistre l'historique complet des traductions pour consultation ultérieure.

## Valeur ajoutée

- **Traduction contextuelle** au lieu d'une simple traduction brute
- **Trois styles de sortie**: littéral, naturel et professionnel (adaptés au registre)
- mémoire locale du vocabulaire dans SQLite
- historique des traductions consultable plus tard
- **Intégration API IA** (OpenAI, Gemini, Mistral) pour traduction de qualité
- **Base de données locale** (SQLite) pour portabilité et tests hors-ligne

## Fonctionnalités prévues

1. saisir un texte à traduire
2. choisir la langue cible
3. choisir un style de traduction (littéral, naturel, professionnel)
4. envoyer la demande à une API IA externe (REST)
5. afficher la traduction et une version reformulée
6. enregistrer le résultat dans la base SQLite locale
7. consulter l'historique complet des traductions
8. gérer un vocabulaire personnel pour les termes récurrents

## Architecture simple

```text
Utilisateur
	↓
Interface Interactive (C)
	↓
Moteur métier (C)
	├─ préparation de la requête
	├─ appel API IA
	├─ parsing JSON
	└─ stockage SQLite
	↓
Résultat affiché + Persistance
```

## Déclinaison technique

- **C (C11)** pour le cœur applicatif
- libcurl pour appeler l'API IA
- JSON parsing (cJSON ou jansson) pour lire la réponse
- SQLite pour stocker l'historique et le glossaire
- MinGW (Windows) ou GCC (Unix-like) pour la compilation

## Découpage des fichiers

```text
include/
├─ app.h                      # Menu principal
├─ api_client.h               # Client HTTP pour API IA
├─ storage.h                  # Persistance SQLite
├─ translation_common.h       # Types partagés
└─ translator.h               # Logique métier

src/
├─ app.c                      # Menu et orchestration
├─ api_client.c               # Implémentation client HTTP
├─ main.c                     # Point d'entrée
├─ storage.c                  # Implémentation SQLite
└─ translator.c               # Logique de traduction

docs/
└─ architecture.md            # Documentation technique détaillée

data/
├─ schema.sql                 # Schéma SQLite
└─ local.db                   # Base de données locale (générée)

tests/
└─ test_translation.c         # Tests unitaires

scripts/
├─ init_db.sh                 # Init DB (Unix/Linux)
└─ init_db.ps1                # Init DB (Windows PowerShell)

Makefile                       # Build, tests, clean
README.md                      # Ce fichier
```

## Rôle des modules

- **app**: orchestre le scénario principal et le menu utilisateur
- **api_client**: prépare et envoie la requête HTTP vers l'API IA, parse la réponse JSON
- **translator**: gère la logique métier autour du texte, des styles et de la reformulation
- **storage**: sauvegarde l'historique et le vocabulaire dans SQLite, gère les requêtes DB
- **translation_common**: types partagés (TranslationStyle enum, etc.)

## Version minimale attendue

La première version peut simplement:

1. afficher un menu dans le terminal
2. accepter un texte à traduire
3. appeler l'API IA avec clé fournie via variable d'environnement
4. sauvegarder le résultat dans SQLite
5. afficher l'historique sur demande

## Démarrage rapide

### Windows (MinGW)

```bash
# Compilation
mingw32-make

# Lancer l'application
bin\app.exe

# Tests
mingw32-make test
bin\test.exe

# Nettoyer
mingw32-make clean
```

### Linux / macOS (GCC)

```bash
make
./bin/app

make test
./bin/test

make clean
```

## Configuration API

### Variables d'environnement

```bash
# Pour OpenAI
export OPENAI_API_KEY="sk-..."
export TRANSLATION_API_MODE="openai"

# Pour Gemini
export GEMINI_API_KEY="..."
export TRANSLATION_API_MODE="gemini"
```

### Sans clé API (mode démo)

L'application fonctionne en mode démo si aucune clé API n'est fournie.

## Base de données locale

La base SQLite locale stocke:
- **Table `translations`**: historique complet des traductions
- **Table `vocabulary`**: dictionnaire personnel et fréquence des termes

Le fichier `data/local.db` est généré automatiquement à la première exécution.

## Points d'évaluation (ESISA)

```bash
- Fonctionnalité & Qualité (20%): Application fonctionne selon spécification
- Intégration IA (20%): API IA externe utilisée correctement avec gestion d'erreurs
- Qualité du code & tests (10%): Code C propre, organisation modulaire, tests automatisés
- Déploiement & accessibilité (10%): Application accessible et déployée
- Présentation & vidéo (40%): Soutenance professionnelle, démo claire, branding
```

## Livrables attendus

- [x] Dépôt GitHub public
- [x] README complet avec architecture et instructions
- [x] Backend C compilable avec Makefile
- [x] Tests automatisés
- [ ] URL de déploiement (Vercel ou équivalent)
- [ ] Vidéo de démo (5–10 min)
- [ ] Documentation technique complète

## Contact

**Supervision:** Prof. Chafik Boulealam (ch.boulealam@esisa.ac.ma)

## Structure du projet

```text
.
├─ Makefile
├─ README.md
├─ docs/
│  └─ architecture.md
├─ include/
│  ├─ app.h
│  ├─ api_client.h
│  ├─ storage.h
│  ├─ translation_common.h
│  └─ translator.h
├─ src/
│  ├─ app.c
│  ├─ api_client.c
│  ├─ main.c
│  ├─ storage.c
│  └─ translator.c
├─ tests/
│  └─ test_translation.c
├─ data/
│  ├─ schema.sql
│  └─ local.db (généré)
├─ scripts/
│  ├─ init_db.sh
│  └─ init_db.ps1
└─ bin/ (généré)
```

## Notes de développement

- Tous les modules sont complètement indépendants
- Code C11-compliant avec -Wall -Wextra -Wpedantic
- Tests automatisés avec `make test`
- Base SQLite automatiquement créée à la première exécution
- Support complet de Windows (MinGW) et Unix-like systems
