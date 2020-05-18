#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

int valid_key(string key);
void encipher(string key, string plain);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    else if (valid_key(argv[1]) == -1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (valid_key(argv[1]) == 0)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string plain = get_string("plaintext: ");

    encipher(argv[1], plain);

    printf("ciphertext: %s\n", plain);
    return 0;
}

int valid_key(string key)
{
    if (key[0] == '\0')
    {
        return -1;
    }
    else if (strlen(key) != 26)
    {
        return 0;
    }
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122)
        {
            return -1;
        }
        for (int j = i - 1; j > 0; j--)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                return -1;
            }
        }
    }
    return 1;
}

void encipher(string key, string plain)
{
    for (int i = 0; plain[i] != '\0'; i++)
    {
        for (int j = 'A', k = 0; j <= 'Z'; j++, k++)
        {
            if (plain[i] == j)
            {
                plain[i] = toupper(key[k]);
                break;
            }
            else if (plain[i] == j + 32)
            {
                plain[i] = tolower(key[k]);
                break;
            }
        }
    }
    return ;
}