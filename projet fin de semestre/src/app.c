#include "app.h"
#include "storage.h"
#include "translator.h"
#include "api_client.h"

#include <stdio.h>
#include <string.h>

static void trim_newline(char *text) {
    size_t length;

    if (text == NULL) {
        return;
    }

    length = strlen(text);
    if (length > 0U && text[length - 1U] == '\n') {
        text[length - 1U] = '\0';
    }
}

static int read_line(const char *prompt, char *buffer, unsigned int size) {
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    trim_newline(buffer);
    return 1;
}

static TranslationStyle read_style(void) {
    char choice[16];

    if (!read_line("Style (1=literal, 2=naturel, 3=professionnel): ", choice, sizeof choice)) {
        return TRANSLATION_STYLE_NATURAL;
    }

    switch (choice[0]) {
        case '1':
            return TRANSLATION_STYLE_LITERAL;
        case '3':
            return TRANSLATION_STYLE_PROFESSIONAL;
        case '2':
        default:
            return TRANSLATION_STYLE_NATURAL;
    }
}

void run_app(void) {
    char text[512];
    char language[64];
    char translated[1024];
    char command[16];
    TranslationStyle style;
    int running = 1;

    if (!init_database()) {
        fprintf(stderr, "Erreur: Impossible d'initialiser la base de donnees\n");
        return;
    }

    if (!init_api_client()) {
        fprintf(stderr, "Erreur: Impossible d'initialiser l'API\n");
        close_database();
        return;
    }

    while (running) {
        puts("\n=== Assistant de traduction contextuel ===");
        puts("1. Traduire un texte");
        puts("2. Voir l'historique");
        puts("3. Rechercher par langue");
        puts("4. Supprimer l'historique");
        puts("5. Exporter en CSV");
        puts("6. Quitter");

        if (!read_line("Choix (1-6): ", command, sizeof command)) {
            puts("Lecture interrompue.");
            break;
        }

        switch (command[0]) {
            case '2':
                show_translation_history();
                break;

            case '3':
                if (!read_line("Langue a rechercher: ", language, sizeof language)) {
                    puts("Langue invalide.");
                } else {
                    search_translation_history(language);
                }
                break;

            case '4':
                clear_translation_history();
                break;

            case '5':
                export_translation_history_csv();
                break;

            case '6':
                running = 0;
                break;

            case '1':
                if (!read_line("Texte a traduire: ", text, sizeof text)) {
                    puts("Texte invalide.");
                    break;
                }

                if (strlen(text) == 0) {
                    puts("Le texte ne peut pas etre vide.");
                    break;
                }

                if (!read_line("Langue cible (ex: francais, anglais): ", language, sizeof language)) {
                    puts("Langue invalide.");
                    break;
                }

                if (strlen(language) == 0) {
                    puts("La langue ne peut pas etre vide.");
                    break;
                }

                style = read_style();

                if (!translate_text(text, language, style, translated, sizeof translated)) {
                    puts("Echec de la traduction.");
                    break;
                }

                printf("\nStyle choisi: %s\n", translation_style_name(style));
                printf("Texte source: %s\n", text);
                printf("Langue cible: %s\n", language);
                printf("Traduction: %s\n\n", translated);
                puts("Traduction sauvegardee en base de donnees.");
                break;

            default:
                puts("Choix invalide. Tapez 1, 2, 3, 4, 5 ou 6.");
                break;
        }
    }

    close_database();
    puts("\nAu revoir!");
}
