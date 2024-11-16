//
//  main.c
//  cose354-project1
//
//  Created by 유지연 on 10/27/24.
//

//cipertext [0] XOR subkey3 XOR = plaintext[0] mul subkey1 modulo 2^16


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 16        // 행 개수
#define COLS 16        // 열 개수
#define MAX_LINE 1024  // 한 줄의 최대 문자 수

uint16_t mul_mod_16(uint16_t a, uint16_t b) {
    uint32_t result = (uint32_t)a * (uint32_t)b;  // 32비트 정수로 곱셈
    return (uint16_t)(result & 0xFFFF);           // 하위 16비트만 반환
}

uint16_t xor_16bit(uint16_t a, uint16_t b) {
    return a ^ b;  // XOR 연산
}

// 열 이름을 열 인덱스로 변환하는 함수
int get_column_index(const char *col_name) {
    if (col_name[0] == 'C') {
        int col = atoi(col_name + 1);  // "C" 다음 숫자를 추출
        if (col >= 0 && col < COLS) {
            return col;
        }
    }
    return -1;  // 유효하지 않은 열 이름일 경우 -1 반환
}

// 지정된 행과 열에서 값을 찾는 함수
int get_value_from_csv(const char *filename, int row, const char *col_name) {
    FILE *file = NULL;
    file = fopen("s_box_1.csv", "r" );
    //FILE *file = fopen("s_box_1.csv", "r");
    if (!file) {
        printf("파일을 열 수 없습니당.\n");
        return -1;
    }

    char line[MAX_LINE];
    int current_row = 0;
    int col_index = get_column_index(col_name);
    if (col_index == -1) {
        printf("잘못된 열 이름입니다.\n");
        fclose(file);
        return -1;
    }

    // CSV 파일의 각 줄을 읽어 원하는 행을 찾음
    while (fgets(line, MAX_LINE, file)) {
        if (current_row == row) {
            char *token;
            int current_col = 0;
            token = strtok(line, ",");
            // 각 셀을 읽어 원하는 열 값을 찾음
            while (token && current_col <= col_index) {
                if (current_col == col_index) {
                    int value = atoi(token);  // 정수로 변환
                    fclose(file);
                    return value;
                }
                token = strtok(NULL, ",");
                current_col++;
            }
        }
        current_row++;
    }

    printf("지정된 행 또는 열을 찾을 수 없습니다.\n");
    fclose(file);
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Result: 0x%X\n", mul_mod_16(0x1245, 0x2673));
    
    const char *filename = "s_box_1.csv";
        int row = 2;              // 찾고자 하는 행
        const char *col_name = "C4";  // 찾고자 하는 열 이름

        int value = get_value_from_csv(filename, row, col_name);
        if (value != -1) {
            printf("Row %d, Column %s의 값: %d\n", row, col_name, value);
        }
    return 0;
}
