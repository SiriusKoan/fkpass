#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <syslog.h>


PAM_EXTERN int pam_sm_setcred(pam_handle_t *handle, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc, const char **argv) {
    // get username
    const char *username = NULL;
    int pam_code = pam_get_user(handle, &username, "USERNAME: ");
    if (pam_code != PAM_SUCCESS) {
        syslog(LOG_WARNING, "[fkpass] Cannot get username");
        return PAM_PERM_DENIED;
    }
    syslog(LOG_DEBUG, "[fkpass] Username: %s", username);
    // get probability from arguments
    float probability = 0.5;
    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "prob=", 5) == 0) {
            probability = atof(argv[i] + 5);
            break;
        }
    }
    // random bool
    srand(time(NULL) ^ getpid());
    int random = rand() % 100;
    syslog(LOG_DEBUG, "[fkpass] Random: %d / %d", random, (int)(probability * 100));
    if (random < probability * 100) {
        return PAM_SUCCESS;
    } else {
        return PAM_PERM_DENIED;
    }
}
