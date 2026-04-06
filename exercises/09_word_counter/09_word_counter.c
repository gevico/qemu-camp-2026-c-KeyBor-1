#include <stdio.h>

int main() {
    char str[]="Don't  ask what your country can do for you, but ask what you can do for your country . ";
    int wordCount = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] != ' ') {
            continue;
        } else {
            while(str[i] == ' ' || str[i] == ',') {
                i++;
            }
            if(str[i] == '.') break;
            wordCount++;
        }
    }
    wordCount++;
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}