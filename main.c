#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

// 가사 (중복 제거 됨)
const wchar_t* LYRICS[] = {
        L"언제든 Day and night",
        L"Hit me hit me up",
        L"Hit me hit me up now oh",
        L"네 맘속 Delight",
        L"Show me right now yeah",
        L"Show me right now woo",
        L"Super Super",
        L"Supersonic Supersonic uh",
        L"By my side",
        L"Show me oh Supersonic",
        L"Heat and sweat 단숨에 후 세게 Blow",
        L"We got that 이대로 Go with the flow",
        L"달라진 온도 차오른 설렘 Overload",
        L"자 지금부터 뛰어들어 Ready set you go"
};

typedef struct splitWord {
    int len;
    wchar_t** split;
} SplitWord;

typedef struct similarity {
    int same, off;
    int simIndex[2];
    int simLen;
} Similarity;

typedef struct result {
    int* changed;
    int len;
    int lineIndex;
} Result;

SplitWord* splitWords(const wchar_t* ipt) {
    wchar_t* split[7];

    int i = 0, si = 0;
    wchar_t c = *ipt;
    wchar_t tmp[14];
    while (1) {
        if(c == L' ' || c == L'\0') {
            tmp[i++] = L'\0';
            wchar_t* word = malloc(sizeof(wchar_t)*(i+1)); // 메모리 빌림 1
            wcsncpy(word, tmp, i+1);

            split[si++] = word;

            i = 0;
            if(c=='\0') break;
        }else tmp[i++] = c;
        c = *++ipt;
    }

    wchar_t** finalSplit = malloc(sizeof(wchar_t*)*si); // 메모리 빌림 2
    for (int j = 0; j < si; j++) {
        finalSplit[j] = split[j];
    }

    SplitWord* sw = malloc(sizeof(SplitWord)); // 메모리 빌림 3
    sw -> len = si;
    sw -> split = finalSplit;
    return sw;
}

void freeSplitWord(SplitWord* word) {
    for(int i = 0; i<word->len; i++) {
        free(word->split[i]); // 메모리 돌려줌 1
    }
    free(word->split); // 메모리 돌려줌 2
    free(word); // 메모리 돌려줌 3
}

// 유사도 검사
Similarity* calculateSimilarity(const SplitWord* lyrics, const SplitWord* ipt) {
    Similarity* sim = malloc(sizeof(Similarity)); // 메모리 빌림 4
    sim->same = 0;
    sim->off = 0;
    sim->simLen = 0;

    for (int i = 0; i < lyrics->len; i++) {
//        wprintf(L"%ls\n", ipt->split[i]);
        int compared = wcscmp(lyrics->split[i], ipt->split[i]);
        if(compared==0) {
            sim->same++;
        }else {
            sim->simIndex[sim->simLen++] = i;
            sim->off += compared;
        }

        if(sim->simLen>=2) break;
    }
    return sim;
}

Result* process(SplitWord* ipts) {
    // 제일 가까운 가사의 index, 제일 가까운 가사의 유사도
    Similarity* s = NULL;
    int lineIndex;

    for(int i = 0; i < 14; i++) {
        SplitWord* currentLine = splitWords(LYRICS[i]);

        // 가사 단어 개수가 같은지 체크
        if(currentLine->len == ipts->len) {
            Similarity* cs = calculateSimilarity(currentLine, ipts);
            if(cs->same >= (ipts->len > 3 ? 2 : 1) && (s==NULL || s->off > cs->off)) {
                if(s != NULL) free(s);
                s = cs;
                lineIndex = i;
            }else {
                free(cs); // 메모리 돌려줌 4
            }
        }

        freeSplitWord(currentLine);
    }

    //고오오급스러운 코딩 기법
    if(s == NULL) return NULL;

    Result* result = malloc(sizeof(Result)); // 메모리 빌림 5
    int* changed = malloc(sizeof(int) * (s->simLen)); // 메모리 빌림 6
    for(int i =0; i<s->simLen; i++) {
        changed[i] = s->simIndex[i];
    }
    result->changed = changed;
    result->len = s->simLen;
    result->lineIndex = lineIndex;


    free(s); // 메모리 돌려줌 4
    return result;
}

void freeResult(Result* result) {
    free(result->changed); // 메모리 돌려줌 6
    free(result); // 메모리 돌려줌 5
}

wchar_t* getLine() {
    wchar_t tmp[32];
    int len = 0;
    wchar_t c;
    while ((c = getwchar()) != L'\n') {
        tmp[len++] = c;
    }
    tmp[len++] = '\0';
    wchar_t* line = malloc(sizeof(wchar_t)*len); // 메모리 빌림 8
    wcsncpy(line, tmp, len);
    return line;
}

int main(void) {
    if(setlocale(LC_ALL, "korean") == NULL){
        perror("setlocale failed");
        exit(1);
    }
    _wsetlocale(LC_ALL, L"korean");

    wchar_t* ip = getLine();
    SplitWord* word = splitWords(ip);
    Result* result = process(word);
    SplitWord* line = splitWords(LYRICS[result->lineIndex]);
    for(int i =0; i<result->len; i++) {
        wprintf(L"%ls -> %ls\n", word->split[result->changed[i]], line->split[result->changed[i]]);
    }
    wprintf(L"%ls", LYRICS[result->lineIndex]);
    freeSplitWord(line);
    freeSplitWord(word);
    freeResult(result);
    free(ip); // 메모리 돌려줌 8
    return 0;
}