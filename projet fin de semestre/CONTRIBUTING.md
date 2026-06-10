# Guide de contribution

## Avant de commencer

1. **Fork le dépôt** sur GitHub
2. **Clone** votre fork: `git clone https://github.com/YOUR_USERNAME/project-groupe-traduction.git`
3. **Créez une branche** pour votre tâche: `git checkout -b feature/ma-feature`

## Normes de code

### C
- Standard: C11
- Compilateur: GCC (MinGW sur Windows)
- Flags: `-std=c11 -Wall -Wextra -Wpedantic`
- Indentation: 4 espaces
- Longueur max ligne: 100 caractères

### Nommage
- **Fichiers**: `module_name.c` / `module_name.h`
- **Fonctions**: `module_function_name()`
- **Variables globales**: `g_module_variable`
- **Constantes**: `MODULE_CONSTANT`
- **Types**: `ModuleType`

### Exemple de fonction
```c
/**
 * Translate text to target language with specified style
 * @param text Source text to translate
 * @param lang Target language
 * @param style Translation style (0=literal, 1=natural, 2=professional)
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 1 on success, 0 on failure
 */
int translate_text(const char *text, const char *lang, 
                   TranslationStyle style, char *output, 
                   unsigned int output_size);
```

## Processus de commit

1. **Commit réguliers**: Un commit = une tâche logique
2. **Messages clairs**: 
   ```
   feat: Add translation style selector
   fix: Handle empty input in api_client
   docs: Update README with deployment steps
   test: Add tests for translation module
   ```
3. **Test avant commit**: `make test` doit réussir

## Pull Request

1. **Poussez votre branche**: `git push origin feature/ma-feature`
2. **Ouvrez une PR** avec description claire
3. **Attendez la review** et les tests CI
4. **Répondez aux commentaires** et commitez les changements
5. **Merge** une fois approuvé

## Tests

Tous les tests doivent passer avant une PR:
```bash
make clean
make
make test
```

## Documentation

- Mettez à jour le README si les fonctionnalités changent
- Documentez les fonctions avec des commentaires Doxygen
- Mettez à jour PLAN_TRAVAIL.md avec votre progression

## Questions?

Contactez Prof. Chafik Boulealam: ch.boulealam@esisa.ac.ma
