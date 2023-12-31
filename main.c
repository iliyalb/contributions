#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void create_bat_file(char *script_file_name, char *script_file_contents)
{
    FILE *fp = fopen(script_file_name, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    fprintf(fp, "%s\n", script_file_contents);

    fclose(fp);
}

void create_sh_file(char *script_file_name, char *script_file_contents)
{
    FILE *fp = fopen(script_file_name, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    fprintf(fp, "#!/bin/bash\n");
    fprintf(fp, "%s\n", script_file_contents);

    fclose(fp);
}

int main()
{
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
    char *script_file_contents = "git commit -am \"Update README.md\" && git push";
    create_bat_file("script.bat", script_file_contents);
    create_sh_file("script.sh", script_file_contents);

    return 0;
}
