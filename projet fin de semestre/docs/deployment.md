# Guide de déploiement - Projet Assistant de Traduction

## Déploiement en production

### Option 1: Vercel (Recommandé)

Vercel est la plateforme la plus simple pour déployer des applications C/Node.js.

#### Prérequis
- Un compte Vercel (vercel.com)
- Le dépôt GitHub lié à Vercel
- Une clé API OpenAI ou Gemini

#### Étapes

1. **Créer un wrapper Node.js**
   ```javascript
   // api/translate.js
   const { spawn } = require('child_process');
   
   module.exports = async (req, res) => {
     const { text, language, style } = req.body;
     const child = spawn('./bin/app', [text, language, style]);
     
     let output = '';
     child.stdout.on('data', (data) => output += data);
     child.on('close', (code) => {
       res.status(code === 0 ? 200 : 500).json({ result: output });
     });
   };
   ```

2. **Configurer vercel.json**
   ```json
   {
     "buildCommand": "mingw32-make || make",
     "outputDirectory": "bin"
   }
   ```

3. **Ajouter les secrets Vercel**
   - `OPENAI_API_KEY` ou `GEMINI_API_KEY`
   - `TRANSLATION_API_MODE`

4. **Déployer**
   ```bash
   vercel deploy --prod
   ```

### Option 2: Docker + Heroku / Railway

#### Dockerfile
```dockerfile
FROM gcc:latest

WORKDIR /app
COPY . .

RUN apt-get update && apt-get install -y sqlite3 libcurl4-openssl-dev

RUN make

EXPOSE 8080
CMD ["./bin/app"]
```

#### Déploiement
```bash
heroku create <app-name>
heroku config:set OPENAI_API_KEY="sk-..."
git push heroku main
```

## Intégration API IA

### Modèles d'API supportés

1. **OpenAI (ChatGPT)**
   - Endpoint: `https://api.openai.com/v1/chat/completions`
   - Clé: `OPENAI_API_KEY=sk-...`
   - Coût: ~$0.002 par 1K tokens

2. **Google Gemini**
   - Endpoint: `https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent`
   - Clé: `GEMINI_API_KEY=...`
   - Avantage: Gratuit jusqu'à 60 requêtes/minute

3. **Mistral AI**
   - Endpoint: `https://api.mistral.ai/v1/chat/completions`
   - Clé: `MISTRAL_API_KEY=...`

### Exemple de requête API (cURL)

```bash
# OpenAI
curl -X POST https://api.openai.com/v1/chat/completions \
  -H "Authorization: Bearer $OPENAI_API_KEY" \
  -H "Content-Type: application/json" \
  -d '{
    "model": "gpt-3.5-turbo",
    "messages": [
      {
        "role": "system",
        "content": "You are a professional translator. Translate the following text to the target language with the specified style."
      },
      {
        "role": "user",
        "content": "Translate this text to francais with natural style: Hello world"
      }
    ]
  }'
```

### Intégration dans le code C

Voir `src/api_client.c` pour un exemple d'intégration libcurl.

## Base de données en production

### Option 1: Supabase (PostgreSQL)

1. Créer une base Supabase: https://supabase.com
2. Récupérer les credentials
3. Adapter le code `storage.c` pour PostgreSQL au lieu de SQLite
4. Ajouter les variables d'environnement

### Option 2: MongoDB

1. Créer un cluster MongoDB Atlas: https://www.mongodb.com/cloud/atlas
2. Récupérer la connection string
3. Adapter le code pour libmongoc

### Option 3: SQLite avec Litestream (Backup automatique)

SQLite est suffisant pour une petite application. Utiliser Litestream pour les backups.

## Checklist de déploiement

- [ ] Code compilé sans erreurs
- [ ] Tests unitaires passent
- [ ] Variables d'environnement configurées
- [ ] Clé API en place et testée
- [ ] Base de données initialisée
- [ ] Logs de déploiement vérifiés
- [ ] Application accessible publiquement
- [ ] Monitoring configuré

## Monitoring et Logs

### Logs locaux
```bash
make clean
make
./bin/app 2>&1 | tee app.log
```

### Logs Vercel
```bash
vercel logs <app-name>
```

## Support et assistance

- Documentation API: https://api.openai.com/docs
- Exemples curl: https://curl.se/docs/
- Questions: Prof. Chafik Boulealam (ch.boulealam@esisa.ac.ma)
