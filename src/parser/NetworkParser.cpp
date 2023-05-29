#include "NetworkParser.h"

vector<Connection> NetworkParser::parseConnections(const string &file) {
    string line;
    vector<Connection> data;

    ifstream fileStream(file, ios_base::binary);

    if (fileStream.is_open()) {
        getline(fileStream, line); // skip the first line
        while (getline(fileStream, line)) {
            string newLine = lineTransformer(line);
            vector<string> values;
            string::size_type pos = 0;
            while ((pos = newLine.find(splitter)) != string::npos) {
                string value = newLine.substr(0, pos);
                values.push_back(value);
                newLine.erase(0, pos + splitter.length());
            }
            values.push_back(newLine); // add the last value

            int sourceNode = 0;
            int destNode = 0;
            double distanceValue = 0;
            try {
                sourceNode = stoi(values[0]);
                destNode = stoi(values[1]);
                distanceValue = stoi(values[2]);
            }
            catch (invalid_argument const &ex) {
                cerr << "Invalid argument: " << ex.what() << endl;
            }
            Connection networkData(sourceNode, destNode, distanceValue);
            data.push_back(networkData);
        }
        fileStream.close();
    }
    else {
        cerr << "Unable to open file" << endl;
    }

    return data;
}

set<Node> NetworkParser::parseNodes(const string& file) {
    string line;
    set<Node> data;

    ifstream fileStream(file, ios_base::binary);

    if (fileStream.is_open()) {
        getline(fileStream, line); // skip the first line
        while (getline(fileStream, line)) {
            string newLine = lineTransformer(line);
            vector<string> values;
            string::size_type pos = 0;
            while ((pos = newLine.find(splitter)) != string::npos) {
                string value = newLine.substr(0, pos);
                values.push_back(value);
                newLine.erase(0, pos + splitter.length());
            }
            values.push_back(newLine); // add the last value

            if (values.size() != 3) {
                cout << "WARNING operation='parseStations', msg='Invalid station found', station=" << values[0] << endl;
                continue;
            }

            int idValue = 0;
            double longitudeValue = 0;
            double latitudeValue = 0;
            try {
                idValue = stoi(values[0]);
                longitudeValue = stoi(values[1]);
                latitudeValue = stoi(values[2]);
            }
            catch (invalid_argument const &ex) {
                cerr << "Invalid argument: " << ex.what() << endl;
            }
            Node nodeData(idValue, longitudeValue, latitudeValue);
            auto result = data.insert(nodeData);
            if (!result.second) {
                cout << "WARNING operation='parseStations', msg='Duplicate station found', station="
                << nodeData.getId() << endl;
            }
        }
        fileStream.close();
    }
    else {
        int numberOfNodes = 10000;
        cout << "Unable to open file, Creating default nodes" << endl;
        for (int i=0; i<numberOfNodes; i++) {
            data.insert(Node(i, 0, 0));
        }
    }
    return data;
}

string NetworkParser::lineTransformer(string line) {
    bool inQuotes = false;

    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] == '\"') {
            inQuotes = !inQuotes;
        }
        if (line[i] == ',' && !inQuotes) {
            line[i] = ';';
        }
    }
    line.erase(remove(line.begin(), line.end(), '\"'), line.end());
    return line;
}