
#include "budget.h"

void save_user(User *user)
{
    User users[MAX_USERS];
    int count = 0;
    int found = 0;

    FILE *file = fopen(USER_FILE, "rb");

    /* Read existing users. */
    if (file != NULL)
    {
        while (count < MAX_USERS &&
               fread(&users[count], sizeof(User), 1, file) == 1)
        {
            if (strcmp(users[count].username, user->username) == 0)
            {
                users[count] = *user;
                found = 1;
            }

            count++;
        }

        fclose(file);
    }

    /* Add the user if not already present. */
    if (!found)
    {
        if (count >= MAX_USERS)
        {
            printf("Error: Maximum number of users reached.\n");
            return;
        }

        users[count] = *user;
        count++;
    }

    /* Save all user records. */
    file = fopen(USER_FILE, "wb");

    if (file == NULL)
    {
        printf("Error opening user file for writing.\n");
        return;
    }

    if (fwrite(users, sizeof(User), count, file) != (size_t)count)
    {
        printf("Error saving user data.\n");
    }
    else
    {
        printf("User data saved successfully.\n");
    }

    fclose(file);
}

int load_user(const char username[], User *user)
{
    FILE *file = fopen(USER_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(user, sizeof(User), 1, file) == 1)
    {
        if (strcmp(user->username, username) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
