#define _CRT_SECURE_NO_WARNINGS // MSVCのセキュリティ警告を無効化

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Windows API のために必要

// 最大行長、最大キー長、パス用のバッファサイズを定義
#define MAX_LINE_LENGTH 256
#define MAX_KEY_LENGTH 32
#define MAX_PATH_LENGTH 1024 

/**
 * @brief パラメータと応答の対応をファイルから読み込み、応答を出力する関数。
 * @param target ユーザーが入力したパラメータ (argv[1])
 * @param filename 応答データファイルのフルパス
 * @return 応答が見つかったら 1, 見つからなかったら 0
 */
int find_response(const char* target, const char* filename) {
    FILE* file = fopen(filename, "r");
    // ファイルが開けない場合（見つからない、アクセス不可など）
    if (file == NULL) {
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    char key[MAX_KEY_LENGTH];
    char response[MAX_LINE_LENGTH];

    // ファイルを1行ずつ読み込む
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // 行末の改行文字があれば削除
        line[strcspn(line, "\n")] = 0;

        // コロン (:) の位置を探す
        char* colon_pos = strchr(line, ':');
        if (colon_pos != NULL) {
            // キーの長さ
            size_t key_len = colon_pos - line;
            if (key_len < MAX_KEY_LENGTH) {
                // キーをコピーし、ヌル終端
                strncpy(key, line, key_len);
                key[key_len] = '\0';
            }
            else {
                continue; // キーが長すぎる場合はスキップ
            }

            // 応答をコピー
            // NOTE: strcpyは警告が出やすいが、ここではバッファサイズ(MAX_LINE_LENGTH)を信じて使用
            // より安全にするにはsnprintf/sprintfを使用する
            strcpy(response, colon_pos + 1);

            // ターゲットキーとファイル内のキーを比較
            if (strcmp(target, key) == 0) {
                printf("%s\n", response);
                fclose(file);
                return 1; // 応答が見つかった
            }
        }
    }

    fclose(file);
    return 0; // 応答が見つからなかった
}

//---

int main(int argc, char* argv[]) {
    // パラメーターがない場合
    if (argc < 2) {
        printf("fuck *what*?\n");
        return 0;
    }

    const char* target = argv[1];
    // 実行ファイルがあるディレクトリのパスを格納するバッファ
    char module_path[MAX_PATH_LENGTH];
    // データファイル (fucks.txt) のフルパスを格納するバッファ
    char data_filepath[MAX_PATH_LENGTH];

    // 1. 実行ファイル (fuck.exe) のフルパスを取得
    DWORD path_len = GetModuleFileNameA(NULL, module_path, MAX_PATH_LENGTH);

    if (path_len == 0 || path_len >= MAX_PATH_LENGTH) {
        // パス取得に失敗した場合
        fprintf(stderr, "Error: Could not get module path.\n");
        // 続行不可能なのでエラー終了
        return 1;
    }

    // 2. 実行ファイル名 (fuck.exe) の部分を切り捨て、ディレクトリパスのみにする
    // 最後のバックスラッシュ(\)を探す
    char* last_slash = strrchr(module_path, '\\');
    if (last_slash != NULL) {
        // スラッシュの直後をヌル終端にしてファイル名を切り捨てる
        *(last_slash + 1) = '\0';
    }
    else {
        // スラッシュが見つからなかった場合（予期せぬ状況だが、念のため）
        module_path[0] = '\0';
    }

    // 3. ディレクトリパスとファイル名を結合してフルパスを作成
    // snprintfは安全に文字列を結合できる（バッファサイズを超えない）
    snprintf(data_filepath, MAX_PATH_LENGTH, "%s%s", module_path, "fucks.txt");

    // フルパスを使ってファイルから応答を探す
    if (find_response(target, data_filepath)) {
        return 0; // 応答が見つかったので終了
    }

    // ファイルに見つからなかった場合のデフォルト応答
    if (strcmp(target, "-h") == 0 || strcmp(target, "help") == 0) {
        printf("Usage: fuck <target>\n(Check %s for custom targets)\n", "fucks.txt");
    }
    else if (strcmp(target, "-v") == 0) {
        printf("version FUCK.1.0 (The RUDE edition)\n");
    }
    else {
        printf("I don't know how to fuck that.\n");
    }

    return 0;
}