# Plan de travail - Équipe Projet

## Objectif général
Créer un assistant de traduction contextuel avec intégration API IA et base de données SQLite, conforme aux exigences ESISA.

## Jalons (Semaines)

### Semaine 1: Fondations et architecture ✓
- [x] Initialiser le dépôt GitHub
- [x] Mettre en place la structure C avec Makefile
- [x] Documenter l'architecture (`docs/architecture.md`)
- [x] Créer un prototype minimal compilable
- **Livrables**: Code exécutable, README, architecture

### Semaine 2: Intégration API et prototype
- [ ] Tester les requêtes API avec curl
- [ ] Implémenter le parsing JSON (cJSON ou jansson)
- [ ] Brancher libcurl dans `api_client.c`
- [ ] Tester avec une vraie clé API (OpenAI ou Gemini)
- **Livrables**: Appels API fonctionnels, tests

### Semaine 3: Persistance et tests
- [ ] Initialiser SQLite pour les tables `translations` et `vocabulary`
- [ ] Implémenter les requêtes SQL dans `storage.c`
- [ ] Écrire des tests unitaires complets
- [ ] Configurer CI (GitHub Actions)
- **Livrables**: Base de données opérationnelle, tests CI

### Semaine 4: Déploiement et présentation
- [ ] Déployer sur Vercel ou équivalent
- [ ] Préparer la vidéo de démo (5–10 min)
- [ ] Rédiger les slides de soutenance
- [ ] Publier sur LinkedIn
- [ ] Finaliser le README et la documentation
- **Livrables**: Application en production, démo vidéo, présentation

## Tâches par rôle

### Lead Dev / Architecture
- [ ] Vérifier la qualité du code C
- [ ] Coordonner l'intégration des modules
- [ ] Manager les dépendances (curl, SQLite, JSON)

### Dev Backend (API)
- [ ] Implémenter `api_client.c` avec libcurl
- [ ] Tester les appels à OpenAI/Gemini
- [ ] Gérer les erreurs réseau et les timeouts

### Dev Base de données
- [ ] Concevoir le schéma SQLite (`data/schema.sql`)
- [ ] Implémenter `storage.c`
- [ ] Préparer les scripts d'initialisation

### QA / Tests
- [ ] Écrire les tests unitaires (`tests/test_translation.c`)
- [ ] Tester les flux complets (end-to-end)
- [ ] Vérifier la gestion des erreurs

### DevOps / Déploiement
- [ ] Configurer Vercel
- [ ] Mettre en place les variables d'environnement
- [ ] Préparer les logs et monitoring

### Marketing / Présentation
- [ ] Enregistrer la vidéo de démo
- [ ] Préparer les slides
- [ ] Publier sur LinkedIn avec hashtags #ESISA #IA

## Points clés à respecter

✅ **Sécurité**: Aucune clé API en clair dans le dépôt  
✅ **Qualité du code**: C11, Wall -Wextra -Wpedantic  
✅ **Tests**: `make test` doit réussir  
✅ **Documentation**: README complet, architecture expliquée  
✅ **Accessibilité**: Application déployée et publique  
✅ **Professionnalisme**: Soutenance claire et vidéo de qualité

## Ressources utiles

- API OpenAI: https://platform.openai.com/docs/api-reference
- API Gemini: https://ai.google.dev/
- Curl: https://curl.se/docs/
- SQLite: https://www.sqlite.org/docs.html
- Vercel Docs: https://vercel.com/docs

## Contacts

**Supervision**: Prof. Chafik Boulealam (ch.boulealam@esisa.ac.ma)  
**Soutenance**: 30 mai 2026
