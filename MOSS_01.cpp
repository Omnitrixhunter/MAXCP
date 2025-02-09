#include <bits/stdc++.h>
using namespace std;

// List of C++ keywords
unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
    "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",
    "class", "public", "private", "protected", "virtual", "include", "namespace", "using", "std"
};

// List of C++ operators
unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^",
    "<<", ">>", "++", "--", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="
};

// Function to tokenize the given code
vector<string> tokenize(const string &code) {
    vector<string> tokens;
    stringstream ss(code);
    string word;

    while (ss >> word) {
        // Remove unwanted characters like ';' and ','
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return ispunct(c) && c != '_'; }), word.end());

        // If the word is a keyword or operator, keep it as it is
        if (keywords.count(word) || operators.count(word)) {
            tokens.push_back(word);
        } 
        // If it's a number, store as "<num>"
        else if (isdigit(word[0])) {
            tokens.push_back("<num>");
        } 
        // Otherwise, treat it as a variable (store as "<var>")
        else {
            tokens.push_back("<var>");
        }
    }

    return tokens;
}

// Function to compute LCS (Longest Common Subsequence) length
int LCS(vector<string> &tokens1, vector<string> &tokens2) {
    int n = tokens1.size(), m = tokens2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (tokens1[i - 1] == tokens2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

// Function to calculate similarity percentage
double calculateSimilarity(vector<string> &tokens1, vector<string> &tokens2) {
    int lcsLength = LCS(tokens1, tokens2);
    int maxLength = max(tokens1.size(), tokens2.size());
    return (double)lcsLength / maxLength * 100;
}

int main() {
    string code1, code2;

    cout << "Enter first code snippet: ";
    getline(cin, code1);

    cout << "Enter second code snippet: ";
    getline(cin, code2);

    // Tokenizing the input code
    vector<string> tokens1 = tokenize(code1);
    vector<string> tokens2 = tokenize(code2);

    // Calculate similarity percentage
    double similarity = calculateSimilarity(tokens1, tokens2);

    // Output results
    cout << "Similarity: " << fixed << setprecision(2) << similarity << "%" << endl;
    if (similarity > 95) {
        cout << "Plagiarism detected! (Cheated)" << endl;
    } else {
        cout << "No plagiarism detected." << endl;
    }

    return 0;
}

  
