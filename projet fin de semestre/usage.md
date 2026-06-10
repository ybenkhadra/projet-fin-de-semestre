# 📖 Guide d'utilisation - Assistant de Traduction

Un tutoriel interactif étape par étape pour utiliser l'application.

## 📋 Table des matières

1. [Démarrage](#démarrage)
2. [Menu principal](#menu-principal)
3. [Traduire du texte](#traduire-du-texte)
4. [Consulter l'historique](#consulter-lhistorique)
5. [Rechercher par langue](#rechercher-par-langue)
6. [Gérer l'historique](#gérer-lhistorique)
7. [Exporter les données](#exporter-les-données)
8. [FAQ](#faq)

---

## 🚀 Démarrage

### Windows
```bash
cd "c:\path\to\projet fin de semestre"
bin\app.exe
```

### Linux/macOS
```bash
cd project_folder
./bin/app
```

Vous verrez le menu principal s'afficher.

---

## 🎯 Menu principal

```
=== Assistant de traduction contextuel ===
1. Traduire un texte
2. Voir l'historique
3. Rechercher par langue
4. Supprimer l'historique
5. Exporter en CSV
6. Quitter
Choix (1-6): _
```

Tapez le numéro de l'option désirée et appuyez sur Entrée.

---

## 1️⃣ Traduire du texte

### Étapes

1. **Sélectionner l'option 1**
   ```
   Choix (1-6): 1
   ```

2. **Entrer le texte à traduire**
   ```
   Texte a traduire: Hello world
   ```

3. **Spécifier la langue cible**
   ```
   Langue cible (ex: francais, anglais): francais
   ```
   - Accepte n'importe quel nom de langue
   - Exemples: `francais`, `english`, `spanish`, `deutsch`, `italiano`

4. **Choisir un style de traduction**
   ```
   Style (1=literal, 2=naturel, 3=professionnel): 2
   ```
   - **1 = Littéral**: Traduction mot-à-mot
   - **2 = Naturel** (recommandé): Traduction fluide et naturelle
   - **3 = Professionnel**: Vocabulaire formalisé, tone business

### Résultat

```
Style choisi: naturel
Texte source: Hello world
Langue cible: francais
Traduction: [naturel -> francais | demo mode] Traduction contextuelle: Hello world

Traduction sauvegardee en base de donnees.
```

✅ La traduction est automatiquement sauvegardée avec timestamp!

---

## 2️⃣ Consulter l'historique

### Étapes

1. **Sélectionner l'option 2**
   ```
   Choix (1-6): 2
   ```

2. **Voir toutes les traductions**
   ```
   === Historique des traductions ===
   1. {"timestamp":"2026-06-10 17:07:32","source":"Hello world","target":"francais","style":1,"result":"[...]"}
   2. {"timestamp":"2026-06-10 17:13:40","source":"Test2","target":"francais","style":1,"result":"[...]"}
   ```

### Informations affichées
- **timestamp**: Date et heure exactes (format ISO 8601)
- **source**: Texte original
- **target**: Langue cible
- **style**: Numéro du style (0=littéral, 1=naturel, 2=professionnel)
- **result**: Texte traduit avec métadonnées

---

## 3️⃣ Rechercher par langue

### Étapes

1. **Sélectionner l'option 3**
   ```
   Choix (1-6): 3
   ```

2. **Entrer la langue à rechercher**
   ```
   Langue a rechercher: francais
   ```

### Résultat
```
=== Recherche: francais ===
1. {"timestamp":"2026-06-10 17:07:32","source":"Hello world","target":"francais",...}
2. {"timestamp":"2026-06-10 17:13:40","source":"Test2","target":"francais",...}
```

### Cas spéciaux
- Si aucune traduction trouvée: `Aucune traduction trouvee pour 'X'.`
- Recherche **insensible à la casse** (accepte `Francais`, `FRANCAIS`, etc.)

---

## 4️⃣ Gérer l'historique

### Supprimer complètement

1. **Sélectionner l'option 4**
   ```
   Choix (1-6): 4
   ```

2. **Confirmation**
   ```
   Historique des traductions supprime.
   ```

⚠️ **Attention**: Cette action est irréversible!

---

## 5️⃣ Exporter les données

### Exporter en CSV

1. **Sélectionner l'option 5**
   ```
   Choix (1-6): 5
   ```

2. **Fichier généré**
   ```
   Export CSV complete: 42 entrees dans data/export_translations.csv
   ```

### Fichier généré
Créé à `data/export_translations.csv`:
```csv
timestamp,source,target,style,result
2026-06-10 17:07:32,Hello world,francais,1,[naturel -> francais | demo mode] Traduction contextuelle: Hello world
2026-06-10 17:13:40,Test2,francais,1,[naturel -> francais | demo mode] Traduction contextuelle: Test2
```

### Utilisation
- Ouvrez dans Excel, Google Sheets, etc.
- Filtrez, triez, analysez vos données
- Partagez avec votre équipe

---

## 6️⃣ Quitter

### Étapes

1. **Sélectionner l'option 6**
   ```
   Choix (1-6): 6
   ```

2. **Fermeture gracieuse**
   ```
   [DB] Database closed
   Au revoir!
   ```

---

## ❓ FAQ

### Q: Puis-je traduire le même texte plusieurs fois?
**R:** Oui! Chaque traduction avec un style ou une langue différente est enregistrée comme une nouvelle entrée.

### Q: Mes traductions sont-elles sauvegardées?
**R:** Oui, automatiquement! Elles sont stockées dans `data/translations.jsonl` au format JSON.

### Q: Puis-je modifier mon historique?
**R:** Actuellement, vous pouvez:
- ✅ Consulter l'historique
- ✅ Rechercher par langue
- ✅ Supprimer tout l'historique
- ❌ Modifier une entrée individuelle (future v2)

### Q: Comment utiliser l'API OpenAI ou Gemini?
**R:** Définissez les variables d'environnement:
```bash
set OPENAI_API_KEY=sk-...
set TRANSLATION_API_MODE=openai
bin\app.exe
```

### Q: Quelles langues sont supportées?
**R:** Toutes les langues! L'app accepte n'importe quel texte:
- Français, Anglais, Espagnol, Allemand, Portugais
- Chinois, Japonais, Coréen, Russe, Arabe
- Ou n'importe quel texte Unicode

### Q: Mon historique est très volumineux, comment optimiser?
**R:** Vous pouvez:
1. Exporter en CSV (`option 5`)
2. Archiver le fichier `data/translations.jsonl`
3. Supprimer l'historique (`option 4`)

### Q: Comment réinitialiser l'application?
**R:** Supprimez les fichiers de données:
```bash
del data\translations.jsonl
del data\vocabulary.jsonl
del data\export_translations.csv
bin\app.exe  # Redémarrez
```

---

## 💡 Conseils d'utilisation

1. **Essayez les 3 styles**: Chacun produit une traduction différente. Découvrez lequel correspond le mieux à vos besoins.

2. **Créez un vocabulaire**: Utilisez régulièrement les mêmes traductions pour construire un corpus personnel.

3. **Utilisez la recherche**: Pour retrouver facilement toutes les traductions vers une langue donnée.

4. **Exportez régulièrement**: Faites des sauvegardes périodiques en CSV.

5. **Consultez l'historique**: Exploitez vos traductions précédentes comme référence.

---

## 🆘 Dépannage

### L'app ne démarre pas
```
Erreur: Impossible d'initialiser la base de donnees
```
✅ Solution: Vérifiez que le dossier `data/` existe et est accessible.

### Les traductions ne s'enregistrent pas
```
Failed to save to database
```
✅ Solution: Vérifiez les permissions d'écriture sur `data/translations.jsonl`.

### Texte invalide
```
Le texte ne peut pas etre vide.
```
✅ Solution: Assurez-vous d'avoir tapé du texte non vide.

---

**Besoin d'aide?** Consultez [README.md](README.md) ou [architecture.md](docs/architecture.md).

Bon traduction! 🌍✨
