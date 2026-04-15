
#include <ctype.h>
int count(char s[]) {
    int i = 0;
    int constants = 0;
    while (s[i] != '\0') {
        char ch = tolower(s[i]);
        if(isalpha(ch))
        {
            if(ch != 'a' && ch!= 'e' && ch != 'i' && ch != 'o' && ch != 'u')
            {
                constants++;
            }
        }
        i++;
    }
    return constants;
}
