#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void handle_miko_cmd(char *flag) {
    // Flag yoksa (sadece "miko" yazıldıysa)
    if (flag == NULL) {
        printf("MikoOS CLI: Purring and ready. Try --meow, --love, --hack, --matrix, or --sleep.\n");
        return;
    }

    // Flag '--' ile başlıyorsa (örn: --meow -> meow)
    char *action = flag;
    if (flag[0] == '-' && flag[1] == '-') {
        action = flag + 2; 
    }

    // Dosya yolunu oluştur: /usr/lib/miko/[action].sh (egg_ kaldırıldı)
    char script_path[128];
    snprintf(script_path, sizeof(script_path), "/usr/lib/miko/%s.sh", action);

    // Dosya var mı kontrol et
    if (access(script_path, F_OK) == 0) {
        char command[150];
        snprintf(command, sizeof(command), "sh %s", script_path);
        system(command);
    } else {
        // Dosya bulunamadıysa varsayılan kızgın kedi
        printf("Miko doesn't know how to '%s' yet...\n", action);
        // Burada da egg_angry.sh yerine angry.sh kullanıyoruz
        if (access("/usr/lib/miko/angry.sh", F_OK) == 0) {
            system("sh /usr/lib/miko/angry.sh");
        }
    }
}
