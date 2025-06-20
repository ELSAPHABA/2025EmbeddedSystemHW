#include "textlcd.h"
#include "textlcddrv.h"

unsigned int linenum = 0;
stTextLCD st; // stTextLCD 구조체를 가지고 드라이버와 인터페이스
int fd;
char str[LINE_NUM][COLUMN_NUM];
char str_mid1[LINE_NUM][COLUMN_NUM+4];
char str_mid2[LINE_NUM][COLUMN_NUM+4];
char str1[COLUMN_NUM];
char str2[COLUMN_NUM];

int main()
{
    int i = 0, c = 0;         // 반복문 인덱스 초기화
    int lineFlag;             // 선언 추가

    txtlcd_Init();
    printf("textlcdtest ");
    scanf("%d", &lineFlag);
    getchar(); // scanf 후 버퍼 클리어

    if (lineFlag == 1) {
        fgets(str_mid1, sizeof(str_mid1), stdin);
        i = 0; c = 0;
        for (; i < strlen(str_mid1); i++) {
            if (str_mid1[i] != '\'') {
                str1[c] = str_mid1[i];
                c++;
            }
        }
        str1[c] = '\0';
        str2[0] = '\0';
    } else if (lineFlag == 2) {
        fgets(str_mid2, sizeof(str_mid2), stdin);
        i = 0; c = 0;
        for (; i < strlen(str_mid2); i++) {
            if (str_mid2[i] != '\'') {
                str2[c] = str_mid2[i];
                c++;
            }
        }
        str2[c] = '\0';
        str1[0] = '\0';
    }

    //lcdtextwrite(str1, str2, lineFlag);
    lcdtextwrite("PRESS START", "", 1);        // 두 번째 인자 빈 문자열로 전달
    lcdtextwrite("PRESS START", "0xff", 2);

    txtlcd_Exit();
    return 0;
}
