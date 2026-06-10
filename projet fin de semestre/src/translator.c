#include "api_client.h"
#include "storage.h"
#include "translator.h"

#include <stdio.h>

const char *translation_style_name(TranslationStyle style) {
    switch (style) {
        case TRANSLATION_STYLE_LITERAL:
            return "literal";
        case TRANSLATION_STYLE_NATURAL:
            return "naturel";
        case TRANSLATION_STYLE_PROFESSIONAL:
            return "professionnel";
        default:
            return "inconnu";
    }
}

int translate_text(const char *text, const char *target_language, TranslationStyle style, char *output, unsigned int output_size) {
    int success;

    if (output == NULL || text == NULL || target_language == NULL) {
        return 0;
    }

    if (text[0] == '\0' || target_language[0] == '\0') {
        return 0;
    }

    success = fetch_translation(text, target_language, style, output, output_size);
    if (!success) {
        fprintf(stderr, "Translation failed: %s\n", get_api_error());
        return 0;
    }

    success = save_translation_history(text, target_language, style, output);
    if (!success) {
        fprintf(stderr, "Failed to save to database\n");
        return 0;
    }

    return 1;
}
