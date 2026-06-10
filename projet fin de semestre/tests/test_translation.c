#include <stdio.h>
#include <string.h>

#include "api_client.h"
#include "translator.h"
#include "storage.h"

int test_translate_text(void) {
    char output[512];
    int result;

    result = translate_text("Hello world", "francais", TRANSLATION_STYLE_NATURAL, output, sizeof output);
    if (!result) {
        fprintf(stderr, "test_translate_text FAILED: translate_text returned 0\n");
        return 0;
    }

    if (strlen(output) == 0) {
        fprintf(stderr, "test_translate_text FAILED: output is empty\n");
        return 0;
    }

    printf("test_translate_text PASSED: output = %s\n", output);
    return 1;
}

int test_style_names(void) {
    const char *name;

    name = translation_style_name(TRANSLATION_STYLE_LITERAL);
    if (strcmp(name, "literal") != 0) {
        fprintf(stderr, "test_style_names FAILED: expected 'literal', got '%s'\n", name);
        return 0;
    }

    name = translation_style_name(TRANSLATION_STYLE_NATURAL);
    if (strcmp(name, "naturel") != 0) {
        fprintf(stderr, "test_style_names FAILED: expected 'naturel', got '%s'\n", name);
        return 0;
    }

    name = translation_style_name(TRANSLATION_STYLE_PROFESSIONAL);
    if (strcmp(name, "professionnel") != 0) {
        fprintf(stderr, "test_style_names FAILED: expected 'professionnel', got '%s'\n", name);
        return 0;
    }

    printf("test_style_names PASSED\n");
    return 1;
}

int test_storage_persistence(void) {
    int result;

    result = init_database();
    if (!result) {
        fprintf(stderr, "test_storage_persistence FAILED: init_database returned 0\n");
        return 0;
    }

    result = save_translation_history("Test", "spanish", TRANSLATION_STYLE_NATURAL, "Prueba");
    if (!result) {
        fprintf(stderr, "test_storage_persistence FAILED: save_translation_history returned 0\n");
        close_database();
        return 0;
    }

    result = add_vocabulary("dog", "perro");
    if (!result) {
        fprintf(stderr, "test_storage_persistence FAILED: add_vocabulary returned 0\n");
        close_database();
        return 0;
    }

    close_database();
    printf("test_storage_persistence PASSED\n");
    return 1;
}

int test_api_initialization(void) {
    int result;

    result = init_api_client();
    if (!result) {
        fprintf(stderr, "test_api_initialization FAILED: init_api_client returned 0\n");
        return 0;
    }

    printf("test_api_initialization PASSED\n");
    return 1;
}

int test_empty_translation(void) {
    char output[512];
    int result;

    result = translate_text("", "francais", TRANSLATION_STYLE_NATURAL, output, sizeof output);
    if (result) {
        fprintf(stderr, "test_empty_translation FAILED: should reject empty text\n");
        return 0;
    }

    printf("test_empty_translation PASSED (correctly rejected empty text)\n");
    return 1;
}

int main(void) {
    int passed = 0;
    int total = 0;

    total++;
    if (test_translate_text()) {
        passed++;
    }

    total++;
    if (test_style_names()) {
        passed++;
    }

    total++;
    if (test_storage_persistence()) {
        passed++;
    }

    total++;
    if (test_api_initialization()) {
        passed++;
    }

    total++;
    if (test_empty_translation()) {
        passed++;
    }

    printf("\n=== Test Results ===\n");
    printf("Passed: %d / %d\n", passed, total);

    return passed == total ? 0 : 1;
}
