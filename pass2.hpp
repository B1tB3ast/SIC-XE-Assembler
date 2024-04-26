#include <bits/stdc++.h>
#include "pass1.hpp"
using namespace std;

void pass2()
{
    for (auto line : inst)
    {
        bool twoop = 0;
        for (auto it : line.second.second)
        {
            if (it == ',')
                twoop = 1;
        }
        string op1 = line.second.second;
        string op2 = "";
        //cerr << op1 << endl;
        if (twoop)
        {
            op1 = "";
            int i;
            for (i = 0;; i++)
            {
                if (line.second.second[i] == ',')
                    break;
                op1.push_back(line.second.second[i]);
            }
            for (int j = i + 1; j < line.second.second.length(); j++)
            {
                op2.push_back(line.second.second[j]);
            }
        }
        if (line.second.first == "RESB" || line.second.first == "RESW" || line.second.first == "USE")
        {
            int f;
            if (line.second.first == "RESB")
            {
                f = stoi(op1);
            }
            else if (line.second.first == "RESW")
            {
                f = stoi(op1) * 3;
            }
            textrec.push_back({"-1", line.first.first + blockstart[line.first.second] - f});
            continue;
        }
        int f;
        if (line.second.first == "WORD")
        {
            f = 3;
        }
        else if (line.second.first == "BYTE")
        {
            f = line.second.second.length() / 2;
        }
        else if (line.second.first == "BASE")
        {
            base_rel = 1;
            continue;
        }
        else if (line.second.first == "NOBASE")
        {
            base_rel = 0;
            continue;
        }
        else
            f = format(line.second.first);
        string p = singleIns(line.first.first + blockstart[line.first.second], line.second.first, op1, op2);
        if (p == "error")
            err << "Invalid since opcode not found : "<<line.second.first << endl;
        textrec.push_back({p, line.first.first + blockstart[line.first.second] - f});
    }

    // HEADER RECORD
    if (program_name.length() <= 6)
    {
        int d = 6 - program_name.length();
        for (int i = 0; i < d; i++)
        {
            program_name += "_";
        }
    }
    cout << "H" << program_name << " " << intToStringHex(intermed[0].first.first, 6) << " " << intToStringHex((blockstart[no_of_blocks - 1] + block_length[no_of_blocks - 1] - intermed[0].first.first), 6) << endl;

    int prev = textrec[0].second;
    string t = "";

    // cout<<"T";
    vector<vector<pair<string, int>>> tprint;
    int curr_len = 0;
    vector<pair<string, int>> v;
    vector<int> len;
    for (auto it : textrec)
    {

        if (it.first == "-1")
        {

            if (!v.empty())
            {
                tprint.push_back(v);
                len.push_back(curr_len);
            }
            v.clear();
            t = "";
            curr_len = 0;
        }
        else if (curr_len + it.first.length() <= 60)
        {
            t = it.first;
            curr_len += it.first.length();
            v.push_back({t, it.second});
        }
        else
        {
            if (!v.empty())
            {
                tprint.push_back(v);
                len.push_back(curr_len);
            }
            v.clear();
            t = it.first;
            curr_len = 0;
            v.push_back({t, it.second});
            curr_len += it.first.length();
        }
    }
    if (!v.empty())
    {
        tprint.push_back(v);
        len.push_back(curr_len);
    }
    int i = 0;
    for (auto it : tprint)
    {
        cout << "T" << intToStringHex(it[0].second, 6) << " " << intToStringHex(len[i] / 2, 2) << " ";
        {
            for (auto p : it)
            {
                cout << p.first << " ";
            }
        }
        i++;
        cout << endl;
    }
    // END RECORD
    for (auto it : form4)
    {
        cout << "M" << intToStringHex(it, 6) << "05" << endl;
    }
    cout << "E" << intToStringHex(LABELS[start_address].first + blockstart[LABELS[start_address].second], 6) << endl;
    if(endsf==0)
    {
        err<<"END statement not found"<<endl;
    }
    err.close();

    ofstream list("listing.txt");

    // Check if the file is successfully opened
    if (!list.is_open())
    {
        std::cerr << "Error opening file listing.txt" << std::endl;
    }

    // Iterate through the map and write each entry to the file
    list << "This is the listing file" << endl;
    list << "------------------------------------------------------------" << endl;
    int x = 0;
    int m = 0;
    //cerr << intermed.size() << endl;
    //cerr << printer.size() << endl;
    for (const auto &it : intermed)
    {
        string s;
        if (printer[x] == 1)
        {
            while (textrec[m].first == "-1")
            {
                m++;
                if (m > textrec.size())
                {
                    break;
                }
            }
            list << it.first.second << " " << intToStringHex(it.first.first, 4) << " " << it.second << textrec[m].first << endl;
            m++;
        }
        else
            list << it.first.second << " " << intToStringHex(it.first.first, 4) << " " << it.second << std::endl;
        x++;
        if (m > textrec.size() || x > printer.size())
        {
            break;
        }
    }

    list.close();
}
