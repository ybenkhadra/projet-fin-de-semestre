#include "storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

static const char *g_history_path = "data/translations.jsonl";

int init_database(void) {
    FILE *f = fopen("data/.keep", "a");
    if (f == NULL) {
        return 0;
    }
    fclose(f);

    printf("[DB] Database initialized (JSON format at %s)\n", g_history_path);
    return 1;
}

int save_translation_history(const char *source_text, const char *target_language, TranslationStyle style, const char *translated_text) {
    FILE *f;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char timestamp[32];

    if (source_text == NULL || target_language == NULL || translated_text == NULL) {
        return 0;
    }

    f = fopen(g_history_path, "a");
    if (f == NULL) {
        fprintf(stderr, "[DB] Failed to open history file\n");
        return 0;
    }

    strftime(timestamp, sizeof timestamp, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(f,
            "{\"timestamp\":\"%s\",\"source\":\"%s\",\"target\":\"%s\",\"style\":%d,\"result\":\"%s\"}\n",
            timestamp, source_text, target_language, (int)style, translated_text);

    fclose(f);
    return 1;
}

int add_vocabulary(const char *source_word, const char *target_word) {
    FILE *f;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char timestamp[32];

    if (source_word == NULL || target_word == NULL) {
        return 0;
    }

    f = fopen("data/vocabulary.jsonl", "a");
    if (f == NULL) {
        return 0;
    }

    strftime(timestamp, sizeof timestamp, "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(f, "{\"timestamp\":\"%s\",\"source\":\"%s\",\"target\":\"%s\"}\n",
            timestamp, source_word, target_word);

    fclose(f);
    return 1;
}

int show_translation_history(void) {
    FILE *f;
    char line[1024];
    int count = 0;

    f = fopen(g_history_path, "r");
    if (f == NULL) {
        puts("Aucun historique disponible.");
        return 0;
    }

    puts("\n=== Historique des traductions ===");
    while (fgets(line, sizeof line, f) != NULL) {
        printf("%d. %s", ++count, line);
    }

    fclose(f);

    if (count == 0) {
        puts("Aucun historique disponible.");
        return 0;
    }

    return 1;
}

int clear_translation_history(void) {
    if (remove(g_history_path) != 0 && errno != ENOENT) {
        fprintf(stderr, "[DB] Failed to clear history\n");
        return 0;
    }
    puts("Historique des traductions supprime.");
    return 1;
}

int search_translation_history(const char *language) {
    FILE *f;
    char line[1024];
    int count = 0;

    if (language == NULL || language[0] == '\0') {
        return 0;
    }

    f = fopen(g_history_path, "r");
    if (f == NULL) {
        puts("Aucun historique disponible.");
        return 0;
    }

    printf("\n=== Recherche: %s ===\n", language);
    while (fgets(line, sizeof line, f) != NULL) {
        if (strstr(line, language) != NULL) {
            printf("%d. %s", ++count, line);
        }
    }

    fclose(f);

    if (count == 0) {
        printf("Aucune traduction trouvee pour '%s'.\n", language);
    }

    return count > 0 ? 1 : 0;
}

int export_translation_history_csv(void) {
    FILE *src, *dst;
    char line[1024];
    int count = 0;

    src = fopen(g_history_path, "r");
    if (src == NULL) {
        puts("Aucun historique a exporter.");
        return 0;
    }

    dst = fopen("data/export_translations.csv", "w");
    if (dst == NULL) {
        fprintf(stderr, "[DB] Failed to create CSV file\n");
        fclose(src);
        return 0;
    }

    fprintf(dst, "timestamp,source,target,style,result\n");

    while (fgets(line, sizeof line, src) != NULL) {
        fprintf(dst, "%s", line);
        count++;
    }

    fclose(src);
    fclose(dst);

    printf("Export CSV complete: %d entrees dans data/export_translations.csv\n", count);
    return 1;
}

int close_database(void) {
    printf("[DB] Database closed\n");
    return 1;
}
