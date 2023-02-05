// Joshua Baron
// CovidDB.h

#include <vector>
#include <string>

using namespace std;

class DataEntry {
    private:
        string date;
        string country;
        int c_cases;
        int c_deaths;
    public:
        void setDate(string setDate) {date = setDate;};
        void setCountry(string setCountry) {country = setCountry;};
        void setCases(int cases) {c_cases = cases;};
        void setDeaths(int deaths) {c_deaths = deaths;};
        string getDate() const{return date;};
        string getCountry() const{return country;};
        int getCases() const{return c_cases;};
        int getDeaths() const{return c_deaths;};
};

class CovidDB {
    private:
        int size = 17;
        vector<vector<DataEntry>> table;
        int hashData(string country);
    public:
        CovidDB(int m) {
            // use this?
            size = m;
            table = vector<vector<DataEntry>>(m);
        }
        bool add(DataEntry entry);
        DataEntry* get(string country);
        void remove(string country);
        void print();
};
