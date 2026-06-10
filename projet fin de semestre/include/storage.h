#ifndef STORAGE_H
#define STORAGE_H

#include "translation_common.h"

int init_database(void);
int save_translation_history(const char *source_text, const char *target_language, TranslationStyle style, const char *translated_text);
int show_translation_history(void);
int add_vocabulary(const char *source_word, const char *target_word);
int clear_translation_history(void);
int search_translation_history(const char *language);
int export_translation_history_csv(void);
int close_database(void);

#endif
