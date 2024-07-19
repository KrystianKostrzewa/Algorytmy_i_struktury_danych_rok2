#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define NO_OF_CHARS 256

using namespace std;

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// naive 
void naive_search(const string& text, const string& pattern) {
    int counter = 0;
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; ++i) {
        int j;
        for (j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) {
            counter++;
        }
    }
    cout << "Word '" << pattern << "' found " << counter << " times in the text" << endl;
}
// Rabin-Karp's
void RKsearch(const string& text, const string& pattern) {
    int counter = 0;
    int patternLength = pattern.length();
    int textLength = text.length();

    const int d = 256;
    const int q = 101;

    int patternHash = 0;
    int textHash = 0;

    int h = 1;
    for (int i = 0; i < patternLength - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < patternLength; i++) {
        patternHash = (d * patternHash + pattern[i]) % q;
        textHash = (d * textHash + text[i]) % q;
    }

    for (int i = 0; i <= textLength - patternLength; i++) {
        if (patternHash == textHash) {
            int j;
            for (j = 0; j < patternLength; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == patternLength)
                counter++;
        }

        if (i < textLength - patternLength) {
            textHash = (d * (textHash - text[i] * h) + text[i + patternLength]) % q;
            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
    cout << "Word '" << pattern << "' found " << counter << " times in the text" << endl;
}

// Knuth-Moriss-Pratt's
int* pre_kmp(const string& pattern) {
    int size = pattern.size();
    int* pie = new int[size];
    pie[0] = 0;
    int k = 0;
    for (int i = 1; i < size; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = pie[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            k++;
        }
        pie[i] = k;
    }
    return pie;
}

void KMPsearch(const string& text, const string& pattern) {
    int counter = 0;
    int* pie = pre_kmp(pattern);
    int matched_pos = 0;
    for (int current = 0; current < text.length(); current++) {
        while (matched_pos > 0 && pattern[matched_pos] != text[current])
            matched_pos = pie[matched_pos - 1];

        if (pattern[matched_pos] == text[current])
            matched_pos++;

        if (matched_pos == pattern.length()) {
            counter++;
            matched_pos = pie[matched_pos - 1];
        }
    }
    delete[] pie;
    cout << "Word '" << pattern << "' found " << counter << " times in the text" << endl;
}

// Boyer-Moore's
int max(int a, int b)
{
    return (a > b) ? a : b;
}

void badCharHeuristic(const string& str, int size, int badchar[NO_OF_CHARS])
{
    fill(badchar, badchar + NO_OF_CHARS, -1);

    for (int i = 0; i < size; i++)
        badchar[(unsigned char)str[i]] = i;
}

void BMsearch(const string& txt, const string& pat)
{
    int m = pat.length();
    int n = txt.length();
    int counter = 0;

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            counter++;
            s += (s + m < n) ? m - badchar[(unsigned char)txt[s + m]] : 1;
        }
        else
            s += max(1, j - badchar[(unsigned char)txt[s + j]]);
    }
    cout << "Word '" << pat << "' found " << counter << " times in the text" << endl;
}

//longest Prefix/Suffix
string longestPrefixSuffix(const string& s) {
    int* pi = pre_kmp(s);
    int length = pi[s.size() - 1];
    delete[] pi;
    return s.substr(0, length);
}

//match checking
bool isMatch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;

    for (int j = 1; j <= m; j++) {
        if (pattern[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (pattern[j - 1] == '?' || pattern[j - 1] == text[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if (pattern[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        }
    }

    return dp[n][m];
}

//searching words in 2D table
bool search2D(const vector<vector<char>>& grid, int row, int col, const string& word, int xDir, int yDir) {
    int n = grid.size();
    int m = grid[0].size();
    int len = word.size();

    for (int k = 0; k < len; k++) {
        int newRow = row + k * xDir;
        int newCol = col + k * yDir;

        if (newRow >= n || newRow < 0 || newCol >= m || newCol < 0)
            return false;

        if (grid[newRow][newCol] != word[k])
            return false;
    }
    return true;
}

void patternSearch(const vector<vector<char>>& grid, const string& word) {
    int n = grid.size();
    int m = grid[0].size();
    int len = word.size();

    vector<pair<int, int>> directions = {
        {0, 1}, // right
        {1, 0}, // down
        {1, 1}, // right-down
        {1, -1}, // right-up
        {-1, 0}, // up
        {0, -1}, // left
        {-1, -1}, // left-up
        {-1, 1} // left-down
    };

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            for (auto& dir : directions) {
                if (search2D(grid, row, col, word, dir.first, dir.second)) {
                    cout << "Pattern found at (" << row + 1 << ", " << col + 1 << ")" << endl;
                }
            }
        }
    }
}

int main() {
    ifstream file("Hobbit.txt");
    if (!file.is_open()) {
        cerr << "Nie mo¿na otworzyæ pliku!" << endl;
        return 1;
    }

    string text;
    string line;
    while (getline(file, line)) {
        text += line + " ";
    }
    file.close();

    text = toLowerCase(text);
    string pattern = "hobbit";
    pattern = toLowerCase(pattern);

    cout << "TASK 1\n";
    clock_t start, stop;

    start = clock();
    naive_search(text, pattern);
    stop = clock();
    cout << "Naive search algorithm took " << (stop - start) << " ms." << endl;

    cout << "\n\nTASK 2\n";
    start = clock();
    RKsearch(text, pattern);
    stop = clock();
    cout << "Rabin-Karp's algorithm took " << (stop - start) << " ms." << endl;

    start = clock();
    KMPsearch(text, pattern);
    stop = clock();
    cout << "Knuth-Morris-Pratt's algorithm took " << (stop - start) << " ms." << endl;

    start = clock();
    BMsearch(text, pattern);
    stop = clock();
    cout << "Boyer-Moore's algorithm took " << (stop - start) << " ms." << endl;


    cout << "\n\nTASK 3\n";
    string input = "kotlowniaxyzkotlownia";
    string result = longestPrefixSuffix(input);
    cout << "Longest prefix that is suffix also: " << result << endl;
    
    cout << "\n\nTASK 4\n";
    string text1 = "alamakota";
    string pattern1 = "ala?akota";
    string pattern2 = "a*ta";

    cout << "Input1: " << pattern1 << " -> " << (isMatch(text1, pattern1) ? "True" : "False") << endl;
    cout << "Input2: " << pattern2 << " -> " << (isMatch(text1, pattern2) ? "True" : "False") << endl;

    cout << "\n\nTASK 5\n";
    vector<vector<char>> grid = {
        {'i', 'g', 'e', 'f'},
        {'h', 'd', 'k', 'l'},
        {'q', 'z', 'u', 'x'},
        {'m', 'j', 'o', 'a'}
    };

    string word = "audi";
    patternSearch(grid, word);

    return 0;
}
