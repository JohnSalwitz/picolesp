/* An interactive Picol interpreter. */
/* -------------------------------------------------------------------------- */

#define PICOL_CONFIGURATION

#define PICOL_MAX_STR        256
#ifdef _MSC_VER
#    define PICOL_MAX_LEVEL  10
#else
#    define PICOL_MAX_LEVEL  30
#endif

#ifdef __MINGW32__
#    include <_mingw.h> /* For __MINGW64_VERSION_MAJOR. */
#endif

/* Optional features. Define as zero to disable. */
#define PICOL_FEATURE_ARRAYS    0
#if defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR)
/*                       ^^^ MinGW-w64 lacks glob.h. */
#    define PICOL_FEATURE_GLOB  0
#else
#    define PICOL_FEATURE_GLOB  0
#endif
#define PICOL_FEATURE_INTERP    0
#define PICOL_FEATURE_IO        0
#define PICOL_FEATURE_PUTS      1



#include "picol.h"
#include "vendor/regexp.h"

#define REGEXP_WRAPPER_IMPLEMENTATION

#include "extensions/regexp-wrapper.h"

int set_interp_argv(picolInterp *interp, int offset, int argc, char **argv) {
    char buf[PICOL_MAX_STR] = "";
    int i;
    picolSetIntVar(interp, "argc", argc - offset);
    for (i = offset; i < argc; i++) {
        LAPPEND(buf, argv[i]);
    }
    picolSetVar(interp, "argv", buf);
    return PICOL_OK;
}

// picolSetVar -- Sets a picol variable from c (glue)

int main(int argc, char **argv) {
    char buf[PICOL_MAX_STR] = "";
    int rc = 0;
    FILE *fp;
    picolInterp *interp = picolCreateInterp();
    picolRegisterCmd(interp, "regexp", picol_regexp, NULL);
    fp = fopen("init.pcl", "r");
    picolSetVar(interp, "argv0", argv[0]);
    picolSetVar(interp, "argv", "");
    picolSetVar(interp, "argc", "0");
    picolSetVar(interp, "auto_path", "");

    /* The array ::env is lazily populated with the environment variables'
       values. */
    picolEval(interp, "array set env {}");
    if (fp != NULL) {
        fclose(fp);
        rc = picolSource(interp, "init.pcl");
        if (rc != PICOL_OK) {
            puts(interp->result);
        }
        interp->current = NULL; /* Prevent a misleading error traceback. */
    }
    if (argc == 1) { /* No arguments - interactive mode. */
        while (1) {
            printf("picol> ");
            fflush(stdout);
            if (fgets(buf, sizeof(buf), stdin) == NULL) {
                return 0;
            }
            rc = picolEval(interp, buf);
            if (interp->result[0] != '\0' || rc != PICOL_OK) {
                printf("[%d] %s\n", rc, interp->result);
            }
        }
    } else if (EQ(argv[1], "-e")) { /* A script in argv[2]. */
        set_interp_argv(interp, 1, argc, argv);
        rc = picolEval(interp, argv[2]);
        if (rc != PICOL_OK) {
            picolVar *v = picolGetVar(interp, "::errorInfo");
            if (v != NULL) {
                puts(v->val);
            }
        } else {
            puts(interp->result);
        }
    } else { /* The first arg is the file to source; the rest goes into argv. */
        picolSetVar(interp, "argv0", argv[1]);
        set_interp_argv(interp, 2, argc, argv);
        rc = picolSource(interp, argv[1]);
        if (rc != PICOL_OK) {
            picolVar *v = picolGetVar(interp, "::errorInfo");
            if (v != NULL) {
                puts(v->val);
            }
        }
    }
    return rc & 0xFF;
}
