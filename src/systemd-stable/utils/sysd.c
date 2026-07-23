/*
 * sysd - Service Manager Interface
 *
 *
 * Copyright (C) 2026  Chris McGimpsey-Jones <chrisjones.unixmen@gmail.com>
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAME "sysd"
#define TAG "Service Manager Interface"
#define VERSION "0.1.0"


static void usage(void)
{
    printf("%s - %s\n", NAME, TAG);
    printf("Version %s\n\n", VERSION);

    printf("Usage:\n");
    printf("  sysd <prompt> [service]\n\n");

    printf("Prompts:\n");
    printf("  status     Check service status\n");
    printf("  check      Check service status\n");
    printf("  start      Start service\n");
    printf("  stop       Stop service\n");
    printf("  restart    Restart service\n");
    printf("  enable     Enable service\n");
    printf("  disable    Disable service\n");
    printf("  logs       Show service logs\n");
    printf("  failed     Show failed services\n");
    printf("  version    Show version information\n\n");

    printf("Example:\n");
    printf("  sysd restart squid\n\n");

    exit(EXIT_FAILURE);
}


static void require_service(const char *service)
{
    if (service == NULL || strlen(service) == 0)
        usage();
}


static int needs_root(const char *prompt)
{
    return strcmp(prompt, "start") == 0 ||
           strcmp(prompt, "stop") == 0 ||
           strcmp(prompt, "restart") == 0 ||
           strcmp(prompt, "enable") == 0 ||
           strcmp(prompt, "disable") == 0;
}


static void elevate_self(int argc, char **argv)
{
    char **args = calloc(argc + 2, sizeof(char *));

    if (!args)
        exit(EXIT_FAILURE);

    args[0] = "elevate";

    for (int i = 0; i < argc; i++)
        args[i + 1] = argv[i];

    execvp("elevate", args);

    perror("elevate");
    exit(EXIT_FAILURE);
}


static void run_service_command(const char *command,
                                const char *service)
{
    char unit[256];

    snprintf(unit, sizeof(unit), "%s.service", service);

    execlp("systemctl",
           "systemctl",
           command,
           unit,
           NULL);

    perror("systemctl");
    exit(EXIT_FAILURE);
}


static void run_systemctl(const char *argument)
{
    execlp("systemctl",
           "systemctl",
           argument,
           NULL);

    perror("systemctl");
    exit(EXIT_FAILURE);
}


static void run_logs(const char *service)
{
    char unit[256];

    snprintf(unit, sizeof(unit), "%s.service", service);

    execlp("journalctl",
           "journalctl",
           "-u",
           unit,
           NULL);

    perror("journalctl");
    exit(EXIT_FAILURE);
}


static void show_version(void)
{
    printf("%s %s\n\n", NAME, VERSION);
    fflush(stdout);

    run_systemctl("--version");
}


int main(int argc, char **argv)
{
    if (argc < 2)
        usage();


    const char *prompt = argv[1];
    const char *service = NULL;

    if (argc >= 3)
        service = argv[2];


    /*
     * Only elevate commands that modify system state.
     */
    if (geteuid() != 0 && needs_root(prompt))
        elevate_self(argc, argv);


    if (strcmp(prompt, "status") == 0 ||
        strcmp(prompt, "check") == 0)
    {
        require_service(service);
        run_service_command("status", service);
    }


    else if (strcmp(prompt, "start") == 0)
    {
        require_service(service);
        run_service_command("start", service);
    }


    else if (strcmp(prompt, "stop") == 0)
    {
        require_service(service);
        run_service_command("stop", service);
    }


    else if (strcmp(prompt, "restart") == 0)
    {
        require_service(service);
        run_service_command("restart", service);
    }


    else if (strcmp(prompt, "enable") == 0)
    {
        require_service(service);
        run_service_command("enable", service);
    }


    else if (strcmp(prompt, "disable") == 0)
    {
        require_service(service);
        run_service_command("disable", service);
    }


    else if (strcmp(prompt, "logs") == 0)
    {
        require_service(service);
        run_logs(service);
    }


    else if (strcmp(prompt, "failed") == 0)
    {
        run_systemctl("--failed");
    }


    else if (strcmp(prompt, "version") == 0 ||
             strcmp(prompt, "--version") == 0)
    {
        show_version();
    }


    else
    {
        printf("Sorry, unknown prompt: %s\n\n", prompt);
        usage();
    }


    return 0;
}
