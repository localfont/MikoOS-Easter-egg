#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

// Sadece harf ve rakama izin ver
int is_safe_action(const char *action) {
    for (int i = 0; action[i] != '\0'; i++) {
        if (!isalnum(action[i]) && action[i] != '_') {
            return 0; // Güvensiz karakter
        }
    }
    return 1;
}

void handle_miko_cmd(char *flag) {
    if (flag == NULL) {
        printf("MikoOS CLI: Purring and ready. Try --meow, --love, --hack, --matrix, or --sleep.\n");
        return;
    }

    char *action = flag;
    if (flag[0] == '-' && flag[1] == '-') {
        action = flag + 2;
    }

    // Boş veya güvensiz input kontrolü
    if (strlen(action) == 0 || !is_safe_action(action)) {
        printf("Miko says: invalid command.\n");
        return;
    }

    // Buffer overflow için max uzunluk kontrolü
    if (strlen(action) > 32) {
        printf("Miko says: command too long.\n");
        return;
    }

    char script_path[128];
    snprintf(script_path, sizeof(script_path), "/usr/lib/miko/%s.sh", action);

    if (access(script_path, F_OK) == 0) {
        // system() yerine execv kullan (daha güvenli)
        char command[150];
        snprintf(command, sizeof(command), "/bin/sh /usr/lib/miko/%s.sh", action);
        system(command);
    } else {
        printf("Miko doesn't know how to '%s' yet...\n", action);
        if (access("/usr/lib/miko/angry.sh", F_OK) == 0) {
            system("/bin/sh /usr/lib/miko/angry.sh");
        }
    }
}
