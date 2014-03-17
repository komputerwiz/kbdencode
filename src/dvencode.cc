#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#include <boost/program_options.hpp>

using namespace std;

map<string, string> keymaps = {
    { "qwerty", "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?" },
    { "dvorak", "`1234567890[]',.pyfgcrl/=\\aoeuidhtns-;qjkxbmwvz~!@#$%^&*(){}\"<>PYFGCRL?+|AOEUIDHTNS_:QJKXBMWVZ" }
};


map<char,char> zip(const string& keys, const string& vals)
{
    std::map<char, char> m;

    for (size_t i = 0; i < min(keys.size(), vals.size()); ++i)
        m[keys[i]] = vals[i];

    return m;
}

void dvencode(istream& in, ostream& out, const map<char,char>& m)
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
        cout << "Usage: " << argv[0] << " [options] [files...]\n" << desc << endl;
        return 1;
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

    if (vm.count("files")) {
        vector<string> files = vm["files"].as< vector<string> >();
        for (const string &file : files) {
            fstream in(file);
            dvencode(in, out, charMap);
            in.close();
        }
    } else {
        dvencode(cin, out, charMap);
    }

    return 0;
}
