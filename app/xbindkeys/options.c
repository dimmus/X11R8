/***************************************************************************
        xbindkeys : a program to bind keys to commands under X11.
                           -------------------
    begin                : Sat Oct 13 14:11:34 CEST 2001
    copyright            : (C) 2001 by Philippe Brochard
    email                : hocwp@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <ctype.h>
#include "options.h"
#include "xbindkeys.h"
#include "keys.h"
#include "grab_key.h"

char *display_name = NULL;
char  rc_file[512];
int   verbose                 = 0;
int   poll_rc                 = 0;
int   have_to_show_binding    = 0;
int   have_to_get_binding     = 0;
int   have_to_start_as_daemon = 1;
int   detectable_ar           = 0;
char *geom                    = NULL;

static void show_version(void);
static void show_help(void);
static void show_defaults_rc(void);

void
get_options(int argc, char **argv)
{
    int   i;
    char *home;

    strncpy(rc_file, "", sizeof(rc_file));

    verbose                 = 0;
    have_to_show_binding    = 0;
    have_to_get_binding     = 0;
    have_to_start_as_daemon = 1;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--version") == 0)
        {
            show_version();
            exit(1);
        }
        else if ((strcmp(argv[i], "-X") == 0 ||
                  strcmp(argv[i], "--display") == 0) &&
                 i + 1 < argc)
        {
            display_name = argv[++i];
        }
        else if ((strcmp(argv[i], "-f") == 0 ||
                  strcmp(argv[i], "--file") == 0) &&
                 i + 1 < argc)
        {
            strncpy(rc_file, argv[++i], sizeof(rc_file) - 1);
        }
        else if (strcmp(argv[i], "-p") == 0 ||
                 strcmp(argv[i], "--poll-rc") == 0)
        {
            poll_rc = 1;
        }
        else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--show") == 0)
        {
            have_to_show_binding = 1;
        }
        else if (strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--key") == 0)
        {
            have_to_get_binding = 1;
        }
        else if (strcmp(argv[i], "-mk") == 0 ||
                 strcmp(argv[i], "--multikey") == 0)
        {
            have_to_get_binding = 2;
        }
        else if (strcmp(argv[i], "-v") == 0 ||
                 strcmp(argv[i], "--verbose") == 0)
        {
            verbose                 = 1;
            have_to_start_as_daemon = 0;
        }
        else if (strcmp(argv[i], "-d") == 0 ||
                 strcmp(argv[i], "--defaults") == 0)
        {
            show_defaults_rc();
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            show_help();
            exit(1);
        }
        else if ((strcmp(argv[i], "-g") == 0 ||
                  strcmp(argv[i], "--geometry") == 0) &&
                 i + 1 < argc)
        {
            geom = argv[++i];
        }
        else if (strcmp(argv[i], "-n") == 0 ||
                 strcmp(argv[i], "--nodaemon") == 0)
        {
            have_to_start_as_daemon = 0;
        }
        else if (strcmp(argv[i], "-sd") == 0 ||
                 strcmp(argv[i], "--detectable-ar") == 0)
        {
            detectable_ar = 1;
        }
        else
        {
            show_help();
            exit(1);
        }
    }

    if (strcmp(rc_file, "") == 0)
    {
        home = getenv("HOME");
        strncpy(rc_file, home, sizeof(rc_file) - 20);
        strncat(rc_file, "/.xbindkeysrc", 20);
    }
}

void
show_options(void)
{
    if (verbose)
    {
        printf("displayName = %s\n", display_name);
        printf("rc file = %s\n", rc_file);
    }
}

static void
show_version(void)
{
    fprintf(stderr, "xbindkeys %s by Philippe Brochard\n", XBK_PACKAGE_VERSION);
}

static void
show_help(void)
{
    show_version();

    fprintf(stderr, "usage: xbindkeys [options]\n");
    fprintf(stderr, "  where options are:\n");

    fprintf(stderr, "  -V, --version           Print version and exit\n");
    fprintf(stderr, "  -d, --defaults          Print a default rc file\n");
    fprintf(stderr, "  -f, --file              Use an alternative rc file\n");
    fprintf(
        stderr,
        "  -p, --poll-rc           Poll the rc/guile configs for updates\n");
    fprintf(stderr, "  -h, --help              This help!\n");
    fprintf(stderr, "  -X, --display           Set X display to use\n");
    fprintf(stderr,
            "  -v, --verbose           More information on xbindkeys when it "
            "run\n");
    fprintf(stderr, "  -s, --show              Show the actual keybinding\n");
    fprintf(stderr, "  -k, --key               Identify one key pressed\n");
    fprintf(stderr, " -mk, --multikey          Identify multi key pressed\n");
    fprintf(stderr,
            "  -g, --geometry          size and position of window open with "
            "-k|-mk option\n");
    fprintf(stderr, "  -n, --nodaemon          don't start as daemon\n");
}

static void
show_defaults_rc(void)
{
    printf("# For the benefit of emacs users: -*- shell-script -*-\n");
    printf("###########################\n");
    printf("# xbindkeys configuration #\n");
    printf("###########################\n");
    printf("#\n");
    printf("# Version: %s\n", XBK_PACKAGE_VERSION);
    printf("#\n");
    printf("# If you edit this file, do not forget to uncomment any lines\n");
    printf("# that you change.\n");
    printf("# The pound(#) symbol may be used anywhere for comments.\n");
    printf("#\n");

    printf("# To specify a key, you can use 'xbindkeys --key' or\n");
    printf("# 'xbindkeys --multikey' and put one of the two lines in this "
           "file.\n");
    printf("#\n");
    printf("# The format of a command line is:\n");
    printf("#    \"command to start\"\n");
    printf("#       associated key\n");
    printf("#\n");
    printf("#\n");
    printf("# A list of keys is in /usr/include/X11/keysym.h and in\n");
    printf("# /usr/include/X11/keysymdef.h\n");
    printf("# The XK_ is not needed.\n");
    printf("#\n");
    printf("# List of modifier:\n");
    printf("#   Release, Control, Shift, Mod1 (Alt), Mod2 (NumLock),\n");
    printf("#   Mod3 (CapsLock), Mod4, Mod5 (Scroll).\n");
    printf("#\n");
    printf("\n");
    printf(
        "# The release modifier is not a standard X modifier, but you can\n");
    printf("# use it if you want to catch release events instead of press "
           "events\n");
    printf("\n");
    printf(
        "# By defaults, xbindkeys does not pay attention with the modifiers\n");
    printf("# NumLock, CapsLock and ScrollLock.\n");
    printf(
        "# Uncomment the lines above if you want to pay attention to them.\n");
    printf("\n");
    printf("#keystate_numlock = enable\n");
    printf("#keystate_capslock = enable\n");
    printf("#keystate_scrolllock= enable\n");
    printf("\n");
    printf("# Examples of commands:\n");
    printf("\n");

    printf("\"xbindkeys_show\" \n");
    printf("  control+shift + q\n");
    printf("\n");
    printf("# set directly keycode (here control + f with my keyboard)\n");
    printf("\"xterm\"\n");
    printf("  c:41 + m:0x4\n");
    printf("\n");
    printf("# specify a mouse button\n");
    printf("\"xterm\"\n");
    printf("  control + b:2\n");
    printf("\n");
    printf("#\"xterm -geom 50x20+20+20\"\n");
    printf("#   Shift+Mod2+alt + s\n");
    printf("#\n");
    printf("## set directly keycode (here control+alt+mod2 + f with my "
           "keyboard)\n");
    printf("#\"xterm\"\n");
    printf("#  alt + c:0x29 + m:4 + mod2\n");
    printf("#\n");
    printf("## Control+Shift+a  release event starts rxvt\n");
    printf("#\"rxvt\"\n");
    printf("#  release+control+shift + a\n");
    printf("#\n");
    printf("## Control + mouse button 2 release event starts rxvt\n");
    printf("#\"rxvt\"\n");
    printf("#  Control + b:2 + Release\n");

    printf("\n");
    printf("##################################\n");
    printf("# End of xbindkeys configuration #\n");
    printf("##################################\n");

    exit(1);
}

static int
file_exist(char *filename)
{
    FILE *stream;

    if ((stream = fopen(filename, "r")) == NULL) return 0;

    fclose(stream);
    return 1;
}

int
rc_file_exist(void)
{
    if (!file_exist(rc_file))
    {
        fprintf(stderr,
                "Error : %s not found or reading not allowed.\n",
                rc_file);
        fprintf(stderr,
                "please, create one with 'xbindkeys --defaults > %s'.\n",
                rc_file);
        return 0;
    }

    return 1;
}

int
get_rc_file(void)
{
    char         line[1024];
    char         line2[1024];
    char         command[1024];
    KeyType_t    type;
    EventType_t  event_type;
    KeySym       keysym;
    KeyCode      keycode;
    unsigned int button;
    unsigned int modifier;
    FILE        *stream = NULL;
    char        *pos1;
    char        *pos2;
    char        *p;
    int          i;

    if (init_keys() != 0) return (-1);

  /* Open RC File */
    if ((stream = fopen(rc_file, "r")) == NULL)
    {
        fprintf(stderr,
                "Error : %s not found or reading not allowed.\n",
                rc_file);
        fprintf(stderr,
                "please, create one with 'xbindkeys --defaults > %s'.\n",
                rc_file);
        return (-1);
    }

  /* Read RC file */
    while (fgets(line, sizeof(line), stream))
    {
      /* search for keystate options */
        if (strstr(line, "keystate_numlock") != NULL)
        {
      /* search for comment or command line */
            pos1 = strchr(line, '"');
            pos2 = strchr(line, '#');
            if (!pos1 && !pos2)
            {
                if (strstr(line, "enable") != NULL)
                {
                    numlock_mask = 0;
                }
                if (verbose)
                    printf("keystate_numlock: %s\n",
                           numlock_mask == 0 ? "Enabled" : "Disabled");

                continue;
            }
        }

        if (strstr(line, "keystate_capslock") != NULL)
        {
      /* search for comment or command line */
            pos1 = strchr(line, '"');
            pos2 = strchr(line, '#');
            if (!pos1 && !pos2)
            {
                if (strstr(line, "enable") != NULL)
                {
                    capslock_mask = 0;
                }
                if (verbose)
                    printf("keystate_capslock: %s\n",
                           capslock_mask == 0 ? "Enabled" : "Disabled");

                continue;
            }
        }

        if (strstr(line, "keystate_scrolllock") != NULL)
        {
      /* search for comment or command line */
            pos1 = strchr(line, '"');
            pos2 = strchr(line, '#');
            if (!pos1 && !pos2)
            {
                if (strstr(line, "enable") != NULL)
                {
                    scrolllock_mask = 0;
                }
                if (verbose)
                    printf("keystate_scrolllock: %s\n",
                           scrolllock_mask == 0 ? "Enabled" : "Disabled");

                continue;
            }
        }

        pos1 = strchr(line, '"');
        if (pos1)
        {
            pos2 = strchr(line, '#');

            if (!pos2 || pos2 > pos1)
            {
          /* search for command line */
                pos2 = strrchr(line, '"');
                if (pos2 && pos1 < pos2)
                {
                    command[0] = '\0';
                    type       = SYM;
                    event_type = PRESS;
                    keysym     = 0;
                    keycode    = 0;
                    button     = 0;
                    modifier   = 0;

                    for (p = pos1 + 1, i = 0; p < pos2 && i < sizeof(command);
                         p++, i++)
                    {
                        command[i] = *p;
                    }
                    command[i] = '\0';

          /* get associated keys */
                    if (fgets(line, sizeof(line), stream))
                    {
                        pos1 = line;

                        while (*pos1 != '\n')
                        {
              /* jump space */
                            for (;
                                 *pos1 == '+' || *pos1 == ' ' || *pos1 == '\t';
                                 pos1++)
                                ;

              /* find corresponding + or \n */
                            pos2 = strchr(pos1, '+');
                            if (!pos2)
                            {
                                for (pos2 = pos1; *pos2 != '\n'; pos2++)
                                    ;
                            }

              /* copy string in line2 */
                            for (p = pos1, i = 0;
                                 p < pos2 && i < sizeof(line2) && *p != '+' &&
                                 *p != ' ' && *p != '\t';
                                 p++, i++)
                            {
                                line2[i] = *p;
                            }
                            line2[i] = '\0';

              /* is a numeric keycode (c:nnn) ? */
                            if (line2[0] == 'c' && line2[1] == ':')
                            {
                                if (isdigit(line2[2]))
                                {
                                    type = CODE;
                                    keycode =
                                        strtol(line2 + 2, (char **)NULL, 0);
                                }
                                else
                                {
                                    keysym  = 0;
                                    keycode = 0;
                                    button  = 0;
                                    break;
                                }
                            }
                            else       /* is a numeric modifier (m:nnn) ? */
                                if (line2[0] == 'm' && line2[1] == ':')
                                {
                                    if (isdigit(line2[2]))
                                    {
                                        modifier |=
                                            strtol(line2 + 2, (char **)NULL, 0);
                                    }
                                    else
                                    {
                                        keysym  = 0;
                                        keycode = 0;
                                        button  = 0;
                                        break;
                                    }
                                }
                                else       /* is a mouse button (b:nnn) ? */
                                    if (line2[0] == 'b' && line2[1] == ':')
                                    {
                                        if (isdigit(line2[2]))
                                        {
                                            type   = BUTTON;
                                            button = strtol(line2 + 2,
                                                            (char **)NULL,
                                                            0);
                                        }
                                        else
                                        {
                                            keysym  = 0;
                                            keycode = 0;
                                            button  = 0;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        /* apply to modifier, release/press or key */
                                        if (strcasecmp(line2, "control") == 0)
                                            modifier |= ControlMask;
                                        else if (strcasecmp(line2, "shift") ==
                                                 0)
                                            modifier |= ShiftMask;
                                        else if (strcasecmp(line2, "mod1") ==
                                                     0 ||
                                                 strcasecmp(line2, "alt") == 0)
                                            modifier |= Mod1Mask;
                                        else if (strcasecmp(line2, "mod2") == 0)
                                            modifier |= Mod2Mask;
                                        else if (strcasecmp(line2, "mod3") == 0)
                                            modifier |= Mod3Mask;
                                        else if (strcasecmp(line2, "mod4") == 0)
                                            modifier |= Mod4Mask;
                                        else if (strcasecmp(line2, "mod5") == 0)
                                            modifier |= Mod5Mask;
                                        else if (strcasecmp(line2, "release") ==
                                                 0)
                                            event_type = RELEASE;
                                        else
                                        {
                                            type   = SYM;
                                            keysym = XStringToKeysym(line2);
                                            if (keysym == 0) break;
                                        }
                                    }

                            pos1 = pos2;
                        }
                    }

                    if (add_key(type,
                                event_type,
                                keysym,
                                keycode,
                                button,
                                modifier,
                                command) != 0)
                        break;
                }
            }
        }
    }

    /* Close RC File */
    if (stream != NULL) fclose(stream);

    if (keys == NULL)
    {
        fprintf(stderr, "Error in alocation of keys\n");
        return (-1);
    }

    /* Verify if all is good (like my english) */
    for (i = 0; i < nb_keys; i++)
    {
        if (keys[i].key.sym == 0 || keys[i].command == NULL)
        {
            fprintf(stderr, "Error in RC file : %s\n", rc_file);
            return (-1);
        }
    }

    if (verbose) printf("%d keys in %s\n", nb_keys, rc_file);

    return (0);
}
