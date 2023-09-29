#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void create_script_file(char *os_type, char *script_file_name, char *script_file_contents)
{
    FILE *fp = fopen(script_file_name, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    fprintf(fp, "%s\n", script_file_contents);
    fprintf(fp, "git push\n");

    fclose(fp);
}

int main()
{
    // Detect type of OS
    char *os_type = getenv("OSTYPE");
    char *script_file_name = NULL;
    char *script_file_contents = NULL;

    if (strcmp(os_type, "Windows_NT") == 0)
    {
        script_file_name = "script.bat";
        script_file_contents = "git commit -m \"Update README.md\"";
    }
    else if (strcmp(os_type, "Linux") == 0 || strcmp(os_type, "Darwin") == 0)
    {
        script_file_name = "script.sh";
        script_file_contents = "#!/bin/bash\ngit commit -m \"Update README.md\"\ngit push";
    }
    else
    {
        fprintf(stderr, "Unsupported OS type: %s\n", os_type);
        exit(1);
    }

    // Get the current date and time.
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // Open the README.md file for writing, replace it if it exists
    FILE *fp = fopen("README.md", "w+");
    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    // Write the current date and time to the README.md file
    fprintf(fp, "Contribution: %d-%02d-%02d %02d:%02d\n",
            tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min);

    // Close the README.md file
    fclose(fp);

    // Create a bat or sh script
    create_script_file(os_type, script_file_name, script_file_contents);

    return 0;
}
