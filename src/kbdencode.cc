/**
 * kbdencode, a keyboard layout encoder filter
 * Copyright (C) 2014 Matthew J. Barry (http://komputerwiz.net/kbdencode)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <stdexcept>

#include <boost/program_options.hpp>

using namespace std;

map<string, string> keymaps = {
    { "qwerty", "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?" },
    { "dvorak", "`1234567890[]',.pyfgcrl/=\\aoeuidhtns-;qjkxbmwvz~!@#$%^&*(){}\"<>PYFGCRL?+|AOEUIDHTNS_:QJKXBMWVZ" }
};


class IOException : public runtime_error
{
public:
    IOException(const string &what) : runtime_error("IO Exception: " + what) {}
};



void loadConfig(const string &filePath)
{
    ifstream file(filePath);

    if (!file.is_open())
        throw IOException("Could not open configuration file: " + filePath);

    while (file.good()) {
        string layoutName;
        string layoutStr;

        getline(file, layoutName);
        getline(file, layoutStr);

        if (layoutName.size() > 0 && layoutStr.size() > 0)
            keymaps[layoutName] = layoutStr;
    }

    file.close();
}

map<char,char> zip(const string& keys, const string& vals)
{
    map<char, char> m;

    for (size_t i = 0; i < min(keys.size(), vals.size()); ++i)
        m[keys[i]] = vals[i];

    return m;
}

void kbdencode(istream& in, ostream& out, const map<char,char>& m)
{
    for (char c = in.get(); in.good(); c = in.get()) {
        map<char, char>::const_iterator it = m.find(c);
        if (it == m.end()) {
            out << c;
        } else {
            out << it->second;
        }
    }
}

int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "print this help message")
        ("config,c", po::value<string>(), "configuration file containing layout definitions (default: ~/.kbdencoderc)")
        ("from,f", po::value<string>(), "keyboard layout in which the message is actually typed (default: qwerty)")
        ("to,t", po::value<string>(), "keyboard layout to convert to (default: dvorak)")
        ("files", po::value< vector<string> >(), "input files (optional)")
        ;

    po::positional_options_description p;
    p.add("files", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << "Usage: " << argv[0] << " [options] [files...]\n"
             << desc << '\n'
             << "kbdencode version 0.1.2, Copyright (C) 2014 Matthew J. Barry\n"
             << "kbdencode comes with ABSOLUTELY NO WARRANTY.\n"
             << "This is free software, and you are welcome to redistribute it\n"
             << "under certain conditions"
             << endl;
        return 1;
    }

    string configFilePath = string(getenv("HOME")) + "/.kbdencoderc";
    bool customConfigPath = false;
    if (vm.count("config")) {
        configFilePath = vm["config"].as<string>();
        customConfigPath = true;
    }

    try {
        loadConfig(configFilePath);
    } catch (IOException &e) {
        if (customConfigPath) {
            cerr << e.what() << endl;
            return 1;
        }
    }

    string from = keymaps["qwerty"];
    if (vm.count("from")) {
        from = vm["from"].as<string>();

        map<string,string>::iterator it = keymaps.find(from);
        if (it != keymaps.end())
            from = it->second;
    }

    string to = keymaps["dvorak"];
    if (vm.count("to")) {
        to = vm["to"].as<string>();

        map<string,string>::iterator it = keymaps.find(to);
        if (it != keymaps.end())
            to = it->second;
    }

    map<char, char> charMap = zip(from, to);

    ostream &out = cout;

    try {
        if (vm.count("files")) {
            vector<string> files = vm["files"].as< vector<string> >();
            for (const string &file : files) {
                try {
                    ifstream in(file);
                    kbdencode(in, out, charMap);
                    in.close();
                } catch (ios_base::failure &e) {
                    cerr << e.what() << endl;
                }
            }
        } else {
            kbdencode(cin, out, charMap);
        }
    } catch (...) {
        cerr << "An unknown error occurred." << endl;
        return -1;
    }

    return 0;
}
