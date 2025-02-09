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
vector<string> tokenize(const string &code, unordered_set<string> &varNames) {
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
            varNames.insert(word);  // Insert the variable name into the set
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

// Function to calculate the set-based similarity of variable names
double calculateVarSimilarity(unordered_set<string> &vars1, unordered_set<string> &vars2) {
    unordered_set<string> intersection;
    unordered_set<string> unionSet = vars1; // Start with all elements of vars1
    
    // Find intersection
    for (const string &var : vars2) {
        if (vars1.count(var)) {
            intersection.insert(var);
        }
        unionSet.insert(var);
    }

    // Return the percentage similarity of the variable names
    return (double)intersection.size() / unionSet.size() * 100;
}

int main() {
    string code1, code2;

    cout << "Enter first code snippet: ";
    getline(cin, code1);

    cout << "Enter second code snippet: ";
    getline(cin, code2);

    // Sets to store variable names from code1 and code2
    unordered_set<string> vars1, vars2;

    // Tokenizing the input code and extracting variable names
    vector<string> tokens1 = tokenize(code1, vars1);
    vector<string> tokens2 = tokenize(code2, vars2);

    // Calculate the similarity percentage based on tokens (LCS)
    double tokenSimilarity = calculateSimilarity(tokens1, tokens2);

    // Calculate similarity based on variable names (weight 0.12)
    double varSimilarity = calculateVarSimilarity(vars1, vars2) * 0.12;

    // Final plagiarism score (token similarity + weighted variable similarity)
    double finalSimilarity = tokenSimilarity + varSimilarity;

    // Output results
    cout << "Final Similarity: " << fixed << setprecision(2) << finalSimilarity << "%" << endl;

    if (finalSimilarity >= 90) {
        cout << "Plagiarism detected! (Cheated)" << endl;
    }
    else if (finalSimilarity >= 80) {
        cout << "Suspicious Code" << endl;
    }
    else {
        cout << "No plagiarism detected." << endl;
    }

    return 0;
}
