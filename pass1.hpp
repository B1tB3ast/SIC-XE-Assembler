#include <bits/stdc++.h>
using namespace std;
map<string, string> f1 = {{"FIX", "C4"}, {"FLOAT", "C0"}, {"HIO", "F4"}, {"NORM", "C8"}, {"SIO", "F0"}, {"TIO", "F8"}};
map<string, string> f2 = {{"ADDR", "90"}, {"CLEAR", "B4"}, {"COMPR", "A0"}, {"DIVR", "9C"}, {"MULR", "98"}, {"RMO", "AC"}, {"SHIFTL", "A4"}, {"SHIFTR", "A8"}, {"SUBR", "94"}, {"SVC", "B0"}, {"TIXR", "B8"}};
map<string, string> f34 = {{"ADD", "18"}, {"ADDF", "58"}, {"AND", "40"}, {"COMP", "28"}, {"COMPF", "88"}, {"DIV", "24"}, {"DIVF", "64"}, {"J", "3C"}, {"JEQ", "30"}, {"JGT", "34"}, {"JLT", "38"}, {"JSUB", "48"}, {"LDA", "00"}, {"LDB", "68"}, {"LDCH", "50"}, {"LDF", "70"}, {"LDL", "08"}, {"LDS", "6C"}, {"LDT", "74"}, {"LDX", "04"}, {"LPS", "D0"}, {"MUL", "20"}, {"MULF", "60"}, {"OR", "44"}, {"RD", "D8"}, {"RSUB", "4F"}, {"SSK", "EC"}, {"STA", "0C"}, {"STB", "78"}, {"STCH", "54"}, {"STF", "80"}, {"STI", "D4"}, {"STL", "14"}, {"STS", "7C"}, {"STSW", "E8"}, {"STT", "84"}, {"STX", "10"}, {"SUB", "1C"}, {"SUBF", "5C"}, {"TD", "E0"}, {"TIX", "2C"}, {"WD", "DC"}};
vector<pair<string, int>> textrec;
string start_address;
vector<pair<pair<int, int>, pair<string, string>>> inst;
map<pair<int, int>, int> pl;
string program_name;
string str;
int currentblk = 0; // stores length of the current block
int no_of_blocks = 1;
unordered_map<string, int> block;
map<string, pair<int, int>> LABELS;
map<string, pair<int, int>> LITTAB;
map<int, int> block_length;
map<int, int> blockstart;
set<int> form4;
map<string, int> absolute;
vector<pair<pair<int, int>, string>> intermed;
vector<int> printer;
int endsf=0;
ofstream err("error.txt");
std::string charTOAsc(const std::string &str)
{
    std::stringstream ss;

    // Iterate through each character in the string
    for (char c : str)
    {
        // Convert the character to its ASCII code and then to hexadecimal format
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }

    // Return the concatenated hexadecimal string
    return ss.str();
}
string intToStringHex(int x, int fill = 5)
{
    if (x < 0)
    {
        return intToStringHex(1 << 4 * fill - x + 1);
    }
    stringstream s;
    s << setfill('0') << setw(fill) << hex << x;
    string temp = s.str();
    temp = temp.substr(temp.length() - fill, fill);
    transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    return temp;
}
std::string ltrim(const std::string &s)
{
    size_t start = 0;
    while (start < s.length() && std::isspace(s[start]))
    {
        start++;
    }
    return s.substr(start);
}

// Trim trailing whitespace from a string
std::string rtrim(const std::string &s)
{
    size_t end = s.length();
    while (end > 0 && std::isspace(s[end - 1]))
    {
        end--;
    }
    return s.substr(0, end);
}
int hexStringToInt(const std::string &hexString)
{
    // Create a stringstream to parse the hexadecimal string
    std::stringstream ss;
    ss << std::hex << hexString;
    int intValue;
    ss >> intValue;
    return intValue;
}
// Trim leading and trailing whitespace from a string
std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}
std::string intToBinaryString(int num, int length)
{
    std::string binary = ""; // Initialize an empty string to store the binary representation
    for (int i = length - 1; i >= 0; --i)
    {
        // Check if the bit at position i is set
        int bit = (num >> i) & 1;
        // Append the bit to the binary string
        binary += std::to_string(bit);
    }
    return binary;
}
string hexToBinaryString(string sHex)
{
    string sReturn = "";
    for (int i = 0; i < sHex.length(); ++i)
    {
        switch (sHex[i])
        {
        case '0':
            sReturn.append("0000");
            break;
        case '1':
            sReturn.append("0001");
            break;
        case '2':
            sReturn.append("0010");
            break;
        case '3':
            sReturn.append("0011");
            break;
        case '4':
            sReturn.append("0100");
            break;
        case '5':
            sReturn.append("0101");
            break;
        case '6':
            sReturn.append("0110");
            break;
        case '7':
            sReturn.append("0111");
            break;
        case '8':
            sReturn.append("1000");
            break;
        case '9':
            sReturn.append("1001");
            break;
        case 'a':
            sReturn.append("1010");
            break;
        case 'b':
            sReturn.append("1011");
            break;
        case 'c':
            sReturn.append("1100");
            break;
        case 'd':
            sReturn.append("1101");
            break;
        case 'e':
            sReturn.append("1110");
            break;
        case 'f':
            sReturn.append("1111");
            break;
        case 'A':
            sReturn.append("1010");
            break;
        case 'B':
            sReturn.append("1011");
            break;
        case 'C':
            sReturn.append("1100");
            break;
        case 'D':
            sReturn.append("1101");
            break;
        case 'E':
            sReturn.append("1110");
            break;
        case 'F':
            sReturn.append("1111");
            break;
        default:
            sReturn.append("error");
            break;
        }
    }
    return sReturn;
}
std::string toUpper(const std::string &str)
{
    std::string result;
    for (char c : str)
    {
        result += std::toupper(c);
    }
    return result;
}
string binaryToHex(string sBinary)
{
    string rest(""), tmp;
    for (int i = 0; i < sBinary.length(); i += 4)
    {
        tmp = sBinary.substr(i, 4);
        if (!tmp.compare("0000"))
        {
            rest = rest + "0";
        }
        else if (!tmp.compare("0001"))
        {
            rest = rest + "1";
        }
        else if (!tmp.compare("0010"))
        {
            rest = rest + "2";
        }
        else if (!tmp.compare("0011"))
        {
            rest = rest + "3";
        }
        else if (!tmp.compare("0100"))
        {
            rest = rest + "4";
        }
        else if (!tmp.compare("0101"))
        {
            rest = rest + "5";
        }
        else if (!tmp.compare("0110"))
        {
            rest = rest + "6";
        }
        else if (!tmp.compare("0111"))
        {
            rest = rest + "7";
        }
        else if (!tmp.compare("1000"))
        {
            rest = rest + "8";
        }
        else if (!tmp.compare("1001"))
        {
            rest = rest + "9";
        }
        else if (!tmp.compare("1010"))
        {
            rest = rest + "A";
        }
        else if (!tmp.compare("1011"))
        {
            rest = rest + "B";
        }
        else if (!tmp.compare("1100"))
        {
            rest = rest + "C";
        }
        else if (!tmp.compare("1101"))
        {
            rest = rest + "D";
        }
        else if (!tmp.compare("1110"))
        {
            rest = rest + "E";
        }
        else if (!tmp.compare("1111"))
        {
            rest = rest + "F";
        }
        else
        {
            continue;
        }
    }
    return rest;
}

int format(string &opcode)
{
    if (f1.find(opcode) != f1.end())
        return 1;
    else if (f2.find(opcode) != f2.end())
        return 2;
    else if (f34.find(opcode) != f34.end())
        return 3;
    else if (opcode[0] == '+' && f34.find(opcode.substr(1)) != f34.end())
        return 4;
    return 0;
}

string reg(string &s)
{
    map<string, string> conv = {{"A", "0"}, {"B", "3"}, {"F", "6"}, {"L", "2"}, {"PC", "8"}, {"S", "4"}, {"SW", "9"}, {"T", "5"}, {"X", "1"}};
    if (conv.find(s) != conv.end())
        return conv[s];
    return "0" + s;
}

bool base_rel = 0;
int pc = 0;
int base;

bool islabel(string s)
{
    if (LABELS.find(s) != LABELS.end() && LABELS.empty() == false)
        return true;
    return false;
}
bool islit(string s)
{
    if (LITTAB.find(s) != LITTAB.end() && LITTAB.empty() == false)
        return true;
    return false;
}
bool isabs(string s)
{
    if (absolute.find(s) != absolute.end() && absolute.empty() == false)
        return true;
    return false;
}
string singleIns(int lc, string opcode, string operand1, string operand2 = "")
{
    if (opcode == "WORD")
    {
        return (binaryToHex(intToBinaryString(stoi(operand1), 24)));
    }
    else if (opcode == "BYTE")
    {
        return (operand1);
    }
    else
    {
        int f = format(opcode);
        if (f == 1)
            return f1[opcode];
        else if (f == 2)
        {
            string r1 = reg(operand1);
            if (opcode == "SVC" || opcode == "TIXR" || opcode == "CLEAR")
            {
                return f2[opcode] + r1 + "0";
            }
            else
            {
                string r2;
                if (opcode == "SHIFTL" || opcode == "SHIFTR")
                {
                    r2 = to_string(stoi(operand2) + 1);
                }
                else
                    r2 = reg(operand2);
                return f2[opcode] + r1 + r2;
            }
        }
        else if (f == 3)
        {
            string ans = hexToBinaryString(f34[opcode]);
            if (operand1[0] == '#')
                ans[7] = '1';
            else if (operand1[0] == '@')
                ans[6] = '1';
            else
            {
                ans[6] = '1';
                ans[7] = '1';
            }

            if (operand1[0] == '#' || operand1[0] == '@')
                operand1 = operand1.substr(1);
            if (operand2 == "X")
                ans.push_back('1');
            else
                ans.push_back('0');
            // cout<<operand1<<""<<endl;
            if (isabs(operand1))
            {
                ans += "000";
                ans += intToBinaryString(absolute[operand1], 12);
            }
            else if (islabel(operand1))
            {
                // cout<<operand1<<endl;
                int diff = LABELS[operand1].first + blockstart[LABELS[operand1].second] - lc;
                if (diff < 2048 && diff >= -2048)
                {
                    ans += "010";
                    ans += intToBinaryString(diff, 12);
                }
                else if (base_rel)
                {
                    int disp = LABELS[operand1].first + blockstart[LABELS[operand1].second] - base;
                    if (disp >= 0 && disp <= 4095)
                    {
                        ans += "100";
                        ans += intToBinaryString(disp, 12);
                    }
                }
                else
                {
                    if (base_rel == 0)
                        err << "Displacement too large but directive BASE not FOUND so base relative not possible";
                    else
                        err << "Displacement too large to be handled";
                }
            }
            else if (islit(operand1))
            {
                int diff = LITTAB[operand1].first + blockstart[LITTAB[operand1].second] - lc;
                // cout<<operand1<<"in lit"<<endl;
                if (diff < 2048 && diff >= -2048)
                {
                    ans += "010";
                    ans += intToBinaryString(diff, 12);
                }
                else if (base_rel)
                {
                    int disp = LITTAB[operand1].first + blockstart[LITTAB[operand1].second] - base;
                    if (disp >= 0 && disp <= 4095)
                    {
                        ans += "100";
                        ans += intToBinaryString(disp, 12);
                    }
                }
                else
                {
                    if (base_rel == 0)
                        err << "Displacement too large but directive BASE not FOUND so base relative not possible";
                    else
                        err << "Displacement too large to be handled";
                }
            }
            else
            {
                ans += "000";
                ans += intToBinaryString(stoi(operand1), 12);
            }

            return binaryToHex(ans);
        }
        else if (f == 4)
        {

            string ans = hexToBinaryString(f34[opcode.substr(1)]);
            if (operand1[0] == '#')
                ans[7] = '1';
            else if (operand1[0] == '@')
                ans[6] = '1';
            else
            {
                ans[6] = '1';
                ans[7] = '1';
            }
            if (operand1[0] == '#' || operand1[0] == '@')
                operand1 = operand1.substr(1);
            if (operand2 == "X")
                ans.push_back('1');
            else
                ans.push_back('0');
            ans += "001";
            if ((operand2 == "X" && (ans[6] == '0' && ans[7] == '1')) || (operand2 == "X" && (ans[6] == '1' && ans[7] == '0')))
            {
                err << "YOU cannot use immediate/indirect addressing modes with indexing";
            }
            if (isabs(operand1))
            {
                ans += intToBinaryString(absolute[operand1], 20);
            }
            else if (islabel(operand1))
            {
                form4.insert(lc - 3);
                ans += intToBinaryString(LABELS[operand1].first + blockstart[LABELS[operand1].second], 20);
            }
            else if (islit(operand1))
            {
                form4.insert(lc - 3);
                ans += intToBinaryString(LITTAB[operand1].first + blockstart[LITTAB[operand1].second], 20);
            }
            else
            {
                ans += intToBinaryString(stoi(operand1), 20);
            }
            return binaryToHex(ans);
        }
        return "error";
    }
}

void pass1()
{
// ios_base::sync_with_stdio(false);cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    block["default"] = 0;
    string base_label;
    block_length[-1] = 0;
    while (getline(cin, str))
    {
        stringstream ss(str);
        str = toUpper(str);
        vector<string> tokens;
        int pre = -1;
        trim(str);
        str += " ";
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == ' ')
            {
                tokens.push_back(trim(str.substr(pre + 1, i - pre)));
                pre = i;
            }
        }
        string opcode;
        string operand;
        string label;

        string progs;
        // debug(inst)
        // cerr<<inst.first.first<<" "<<inst.first.second<<" "<<inst.second.first<<" "<<inst.second.second<<endl;
        if (tokens.size() == 3)
        {
            label = tokens[0];
            opcode = tokens[1];
            operand = tokens[2];
            if (opcode == "START")
            {
                program_name = label;
                pc = hexStringToInt(operand);
                printer.push_back(0);
                intermed.push_back({{pc, currentblk}, str});
                continue;
            }
            else
            {
                if (LABELS.find(label) != LABELS.end())
                {
                    err << "SYMBOL ALREADY DEFINED, YOU CANNOT DUPLICATE SYMBOL: " << label << endl;
                }

                LABELS[label] = {pc, currentblk};
            }
        }
        else if (tokens.size() == 2)
        {
            opcode = tokens[0];
            operand = tokens[1];
        }
        else if (tokens.size() == 1)
        {
            opcode = tokens[0];
        }
        intermed.push_back({{pc, currentblk}, str});
        if (opcode == "RSUB")
            operand = "0000";
        if (operand[0] == '=')
        {
            if (LITTAB.find(operand) == LITTAB.end())
            {
                string opr = operand.substr(3, operand.length() - 4);
                LITTAB[operand] = {-1, currentblk};
            }
        }
        if (opcode == "USE")
        {
            printer.push_back(0);
            if (tokens.size() == 1)
            {
                currentblk = 0;
                pc = block_length[currentblk];
            }
            else
            {
                if (block.find(operand) != block.end())
                {
                    currentblk = block[operand];
                    pc = block_length[currentblk];
                }
                else
                {
                    no_of_blocks++;
                    block[operand] = no_of_blocks - 1;
                    pc = 0;
                    currentblk = block[operand];
                }
            }
            inst.push_back({{-3, currentblk}, {"USE", ""}});
        }
        else if (opcode == "NOBASE")
        {
            printer.push_back(0);
            inst.push_back({{-2, currentblk}, {"NOBASE", ""}});
        }
        else if (opcode == "END")
        {
            printer.push_back(0);
            start_address = operand;
            endsf=1;
            continue;
        }
        else if (opcode == "BASE")
        {
            printer.push_back(0);
            inst.push_back({{-1, currentblk}, {"BASE", ""}});
            base_label = operand;
        }
        else if (opcode == "LTORG")
        {
            printer.push_back(0);
            for (auto it : LITTAB)
            {
                if (it.second.first == -1)
                {
                    printer.push_back(1);
                    operand = it.first;
                    LITTAB[it.first] = {pc, currentblk}; // stores location of literal;
                    if (operand[1] == 'X')
                    {

                        string opr = operand.substr(3, operand.length() - 4);
                        intermed.push_back({{pc, currentblk}, "=X'" + opr + "'"});
                        int curr = pc;
                        pc += opr.length() / 2;
                        inst.push_back({{pc, currentblk}, {"BYTE", opr}});
                        block_length[currentblk] = pc;
                        pl[{pc, currentblk}] = curr;
                    }
                    else if (operand[1] == 'C')
                    {
                        string ops = operand.substr(3, operand.length() - 4);
                        string opr = charTOAsc(ops);
                        int curr = pc;
                        intermed.push_back({{pc, currentblk}, "=C'" + opr + "'"});
                        pc += opr.length() / 2;
                        inst.push_back({{pc, currentblk}, {"BYTE", opr}});
                        block_length[currentblk] = pc;
                        pl[{pc, currentblk}] = curr;
                    }
                }
            }
        }
        else if (opcode == "EQU")
        {
            printer.push_back(0);
            if (operand == "*")
            {
                LABELS[label] = {pc, currentblk};
            }
            else
            {
                string s1;
                string s2;
                int pos = -1;
                bool othersym = false;
                for (int i = 0; i < operand.length(); i++)
                {
                    if (operand[i] == '-')
                    {
                        pos = i;
                        break;
                    }
                    if (operand[i] == '*' || operand[i] == '+' || operand[i] == '/')
                    {
                        othersym = true;
                    }
                }
                if (othersym == false && pos == -1)
                {
                    if (LABELS.find(operand) == LABELS.end())
                    {
                        err << "OPERAND MUST BE DEFINED EARLIER FOR VALID ASSIGNMENT OF EXPRESSION";
                    }
                    LABELS[label] = LABELS[operand];
                }
                else
                {
                    s1 = operand.substr(0, pos);
                    s2 = operand.substr(pos + 1);
                    if (LABELS.find(s1) == LABELS.end() || LABELS.find(s2) == LABELS.end())
                    {
                        err << "OPERANDs MUST BE DEFINED EARLIER FOR VALID ASSIGNMENT OF EXPRESSION";
                    }
                    absolute[label] = LABELS[s1].first - LABELS[s2].first;
                }
            }
        }
        else if (opcode == "WORD")
        {
            printer.push_back(1);
            int curr = pc;
            pc += 3;
            inst.push_back({{pc, currentblk}, {opcode, operand}});
            block_length[currentblk] = pc;
            pl[{pc, currentblk}] = curr;
        }
        else if (opcode == "RESW")
        {
            printer.push_back(0);
            int curr = pc;
            pc += 3 * stoi(operand);

            inst.push_back({{pc, currentblk}, {opcode, operand}});
            block_length[currentblk] = pc;
            pl[{pc, currentblk}] = curr;
        }
        else if (opcode == "RESB")
        {
            printer.push_back(0);
            int curr = pc;
            pc += 1 * stoi(operand);

            inst.push_back({{pc, currentblk}, {opcode, operand}});
            block_length[currentblk] = pc;
            pl[{pc, currentblk}] = curr;
        }
        else if (opcode == "BYTE")
        {
            printer.push_back(1);
            if (operand[0] == 'X')
            {
                string opr = operand.substr(2, operand.length() - 3);
                int curr = pc;
                pc += opr.length() / 2;

                inst.push_back({{pc, currentblk}, {"BYTE", opr}});
                block_length[currentblk] = pc;
                pl[{pc, currentblk}] = curr;
            }
            else if (operand[0] == 'C')
            {
                string ops = operand.substr(2, operand.length() - 3);
                string opr = charTOAsc(ops);
                int curr = pc;
                pc += opr.length() / 2;
                inst.push_back({{pc, currentblk}, {"BYTE", opr}});
                block_length[currentblk] = pc;
                pl[{pc, currentblk}] = curr;
            }
        }
        else
        {
            printer.push_back(1);
            int f = format(opcode);
            int curr = pc;
            pc += f;
            if (opcode == "RSUB")
            {
                operand = "0000";
            }
            inst.push_back({{pc, currentblk}, {opcode, operand}});
            block_length[currentblk] = pc;
            pl[{pc, currentblk}] = curr;
        }
    }
    for (auto it : LITTAB)
    {
        if (it.second.first == -1)
        {
            printer.push_back(1);
            string operand = it.first;
            LITTAB[it.first] = {pc, currentblk}; // stores location of literal;
            if (operand[1] == 'X')
            {
                string opr = operand.substr(3, operand.length() - 4);
                intermed.push_back({{pc, currentblk}, "=X '" + opr + "'"});
                int curr = pc;
                pc += opr.length() / 2;
                inst.push_back({{pc, currentblk}, {"BYTE", opr}});
                block_length[currentblk] = pc;
                pl[{pc, currentblk}] = curr;
            }
            else if (operand[1] == 'C')
            {
                string ops = operand.substr(3, operand.length() - 4);
                string opr = charTOAsc(ops);
                int curr = pc;
                intermed.push_back({{pc, currentblk}, "=C'" + opr + "'"});
                pc += opr.length() / 2;
                inst.push_back({{pc, currentblk}, {"BYTE", opr}});
                block_length[currentblk] = pc;
                pl[{pc, currentblk}] = curr;
            }
        }
    }
    blockstart[0] = 0;
    for (int i = 1; i < no_of_blocks; i++)
    {
        blockstart[i] = blockstart[i - 1] + block_length[i - 1];
    }

    ofstream outputFile("intermediate.txt");

    // Check if the file is successfully opened
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file intermediate.txt" << std::endl;
    }

    // Iterate through the map and write each entry to the file
    outputFile << "This is an intermediate file" << endl;
    outputFile << "------------------------------------------------------------" << endl;
    for (const auto &it : intermed)
    {
        // Write to file instead of cout
        outputFile << it.first.second << " " << intToStringHex(it.first.first, 4) << " " << it.second << std::endl;
    }
    outputFile << "------------------------------------------------------------" << endl;
    outputFile << "SYMBOL TABLE" << endl;
    outputFile << endl;
    for (auto it : LABELS)
    {
        outputFile << it.first << " " << intToStringHex(it.second.first + blockstart[it.second.second], 4) << endl;
    }
    for (auto it : absolute)
    {
        outputFile << it.first << " " << intToStringHex(it.second, 4) << endl;
    }
    outputFile.close();
    base = LABELS[base_label].first + blockstart[LABELS[base_label].second];
}