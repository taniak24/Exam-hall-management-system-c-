#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct group_data
{
    int id;
    string specialty;
    int students;
    string exam;
};

struct hall_data
{
    int id;
    int capacity;
    string building;
};

vector<group_data> groups;
vector<hall_data>  halls;

int read_int(const string& prompt, int min_value, int max_value)
{
    while(true)
    {
        cout << prompt;
        string line;
        if (!getline(cin, line))
        {
            exit(0);
        }
        stringstream ss(line);
        int value;
        char extra;

        if (ss >> value && !(ss >> extra))
        {
            if (value >= min_value && value <= max_value) return value;
            cout << "ERROR. Please enter number between " << min_value << " and " << max_value << endl;
        }
        else
        {
            cout << "  ERROR: enter full number" << endl;
        }
    }
}

string read_word(const string& prompt)
{
    while (true)
    {
        cout << prompt;
        string line;
        if (!getline(cin, line)) exit(0);

        stringstream ss(line);
        string word, extra;

        if (ss >> word && !(ss >> extra)) return word;
        cout << "  Error: enter one word without spaces" << endl;
    }
}

int find_group_index(int id)
{
    for (size_t i = 0; i < groups.size(); i++)
        if (groups[i].id == id) return (int)i;
    return -1;
}

int find_hall_index(int id)
{
    for (size_t i = 0; i < halls.size(); i++)
        if (halls[i].id == id) return (int)i;
    return -1;
}

void load_groups(const string& file_name)
{
    ifstream in(file_name);
    if (!in)
    {
        cout << "File " << file_name << " was not found" << endl;
        return;
    }
    string line;
    int line_number = 0, loaded = 0;

    while (getline(in, line))
    {
        line_number++;
        if (line.empty()) continue;

        stringstream ss(line);
        group_data g;

        if (!(ss >> g.id >> g.specialty >> g.students >> g.exam) || g.students <= 0 || g.id <= 0)
        {
            cout << "  Skipped line " << line_number << " (invalid data): " << line << endl;
            continue;
        }
        if (find_group_index(g.id) != -1)
        {
            cout << "  Skipped line " << line_number << " (duplicate ID " << g.id << ")" << endl;
            continue;
        }
        groups.push_back(g);
        loaded++;
    }
    cout << "Groups loaded: " << loaded << endl;
}

void load_halls(const string& file_name)
{
    ifstream in(file_name);

    if (!in)
    {
        cout << "File " << file_name << " was not found" << endl;
        return;
    }
    string line;
    int line_number = 0, loaded = 0;

    while(getline(in, line))
    {
        line_number++;
        if (line.empty()) continue;

        stringstream ss(line);
        hall_data h;

        if (!(ss >> h.id >> h.capacity >> h.building) || h.capacity <= 0 || h.id <= 0)
        {
            cout << "  Skipped line " << line_number << " (invalid data): " << line << endl;
            continue;
        }
        if (find_hall_index(h.id) != -1)
        {
            cout << "  Skipped line " << line_number << " (duplicate ID " << h.id << ")" << endl;
            continue;
        }
        halls.push_back(h);
        loaded++;
    }
    cout << "Halls loaded: " << loaded << endl;
}

void print_groups()
{
    if(groups.empty()) 
    { 
        cout << "No groups have been entered.\n"; 
        return; 
    }

    cout << left << setw(8) << "ID" << setw(20) << "Specialty" << setw(12) << "Students" << "Exam" << endl;
    for(const group_data& g : groups)
    {
        cout << left << setw(8) << g.id << setw(20) << g.specialty << setw(12) << g.students << g.exam << endl;
    }
}

void print_halls()
{
    if(halls.empty()) 
    { 
        cout << "No halls have been entered\n"; 
        return; 
    }

    cout << left << setw(8) << "ID" << setw(12) << "Capacity" << "Building" << endl;

    for(const hall_data& h : halls)
    {
        cout << left << setw(8) << h.id << setw(12) << h.capacity << h.building << endl;
    }
}

void add_group()
{
    group_data g;
    g.id = read_int("Group ID: ", 1, 1000000);

    if (find_group_index(g.id) != -1)
    {
        cout << "A group with this ID already exists" << endl;
        return;
    }
    g.specialty = read_word("Specialty: ");
    g.students = read_int("Number of students: ", 1, 1000);
    g.exam = read_word("Exam: ");
    groups.push_back(g);

    cout << "Group added successfully" << endl;
}

void add_hall()
{
    hall_data h;
    h.id = read_int("Hall ID: ", 1, 1000000);

    if (find_hall_index(h.id) != -1)
    {
        cout << "A hall with this ID already exists" << endl;
        return;
    }
    h.capacity = read_int("Capacity: ", 1, 1000);
    h.building = read_word("Building: ");
    halls.push_back(h);

    cout << "Hall added successfully" << endl;
}

void delete_group()
{
    int id = read_int("Enter the group ID to delete: ", 1, 1000000);
    int i = find_group_index(id);

    if(i == -1)
    {
        cout << "No group with this ID was found" << endl;
        return;
    }
    groups.erase(groups.begin() + i);
    cout << "Group deleted successfully" << endl;
}

void delete_hall()
{
    int id = read_int("Enter the hall ID to delete: ", 1, 1000000);
    int i = find_hall_index(id);
    if(i == -1)
    {
        cout << "No hall with this ID was found" << endl;
        return;
    }
    halls.erase(halls.begin() + i);
    cout << "Hall deleted successfully" << endl;
}

void edit_group()
{
    int id = read_int("Enter the group ID to edit: ", 1, 1000000);
    int i = find_group_index(id);

    if(i == -1)
    {
        cout << "No group with this ID was found" << endl;
        return;
    }
    group_data& g = groups[i];

    cout << "Current details: " << g.specialty << ", " << g.students << " students, exam " << g.exam << endl;
    g.specialty = read_word("New specialty: ");
    g.students  = read_int("New number of students: ", 1, 1000);
    g.exam      = read_word("New exam: ");

    cout << "Group updated successfully" << endl;
}

void edit_hall()
{
    int id = read_int("Enter the hall ID to edit: ", 1, 1000000);
    int i = find_hall_index(id);

    if (i == -1)
    {
        cout << "No hall with this ID was found" << endl;
        return;
    }
    hall_data& h = halls[i];

    cout << "Current details: capacity " << h.capacity << ", building " << h.building << endl;
    h.capacity = read_int("New capacity: ", 1, 1000);
    h.building = read_word("New building: ");
    cout << "Hall updated successfully" << endl;
}

void search_menu()
{
    cout << "1. Find a group by ID\n2. Find groups by specialty\n3. Find a hall by ID\n"
            "4. Find halls with capacity >= X\n";

    int c = read_int("Choice: ", 1, 4);
    bool found = false;

    if(c == 1)
    {
        int i = find_group_index(read_int("ID: ", 1, 1000000));
        if(i != -1)
        {
            const group_data& g = groups[i];
            cout << "Group " << g.id << ": " << g.specialty << ", " << g.students << " students, exam " << g.exam << endl;
            found = true;
        }
    }
    else if(c == 2)
    {
        string s = read_word("Specialty: ");
        for(const group_data& g : groups)
        {
            if(g.specialty == s)
            {
                cout << "Group " << g.id << ": " << g.students << " students, exam " << g.exam << endl;
                found = true;
            }
        }
    }
    else if(c == 3)
    {
        int i = find_hall_index(read_int("ID: ", 1, 1000000));
        if (i != -1)
        {
            cout << "Hall " << halls[i].id << ": " << halls[i].capacity << " seats, building " << halls[i].building << endl;
            found = true;
        }
    }
    else
    {
        int x = read_int("Minimum capacity: ", 1, 1000);
        for(const hall_data& h : halls)
        {
            if(h.capacity >= x)
            {
                cout << "Hall " << h.id << ": " << h.capacity << " seats, building " << h.building << "\n";
                found = true;
            }
        }
    }

    if(!found)
    {
        cout << "No results found";
    }
}

bool group_before(group_data a, group_data b, int sort_choice)
{
    if(sort_choice == 1)
    {
        return a.students > b.students;
    }
    else if(sort_choice == 2)
    {
        return a.specialty < b.specialty;
    }
    else
    {
        return a.id < b.id;
    }
}

void merge_groups(vector<group_data>& list, int left, int middle, int right, int sort_choice)
{
    vector<group_data> temporary;
    int i = left;
    int j = middle + 1;

    while(i <= middle && j <= right)
    {
        if(group_before(list[i], list[j], sort_choice))
        {
            temporary.push_back(list[i]);
            i++;
        }
        else
        {
            temporary.push_back(list[j]);
            j++;
        }
    }

    while(i <= middle)
    {
        temporary.push_back(list[i]);
        i++;
    }

    while(j <= right)
    {
        temporary.push_back(list[j]);
        j++;
    }

    for(int k = 0; k < (int)temporary.size(); k++)
    {
        list[left + k] = temporary[k];
    }
}

void merge_sort_groups(vector<group_data>& list, int left, int right, int sort_choice)
{
    if (left >= right)
    {
         return;
    }

    int middle = (left + right) / 2;

    merge_sort_groups(list, left, middle, sort_choice);
    merge_sort_groups(list, middle + 1, right, sort_choice);
    merge_groups(list, left, middle, right, sort_choice);
}

bool hall_before(hall_data a, hall_data b, int sort_choice)
{
    if(sort_choice == 1)
    {
        return a.capacity > b.capacity;
    }
    else if(sort_choice == 2)
    {
        return a.id < b.id;
    }
    else
    {
        return a.building < b.building;
    }
}

void merge_halls(vector<hall_data>& list, int left, int middle, int right, int sort_choice)
{
    vector<hall_data> temporary;
    int i = left;
    int j = middle + 1;

    while(i <= middle && j <= right)
    {
        if(hall_before(list[i], list[j], sort_choice))
        {
            temporary.push_back(list[i]);
            i++;
        }
        else
        {
            temporary.push_back(list[j]);
            j++;
        }
    }

    while(i <= middle)
    {
        temporary.push_back(list[i]);
        i++;
    }

    while(j <= right)
    {
        temporary.push_back(list[j]);
        j++;
    }

    for(int k = 0; k < (int)temporary.size(); k++)
    {
        list[left + k] = temporary[k];
    }
}

void merge_sort_halls(vector<hall_data>& list, int left, int right, int sort_choice)
{
    if(left >= right)
    {
        return;
    }


    int middle = (left + right)/2;

    merge_sort_halls(list, left, middle, sort_choice);
    merge_sort_halls(list, middle + 1, right, sort_choice);
    merge_halls(list, left, middle, right, sort_choice);
}

void sort_groups_menu()
{
    if(groups.empty())
    {
        cout << "No groups to sort";
        return;
    }

    cout << "1. By number of students (descending)" << endl;
    cout << "2. By specialty (alphabetical)" << endl;
    cout << "3. By ID" << endl;

    int choice = read_int("Choice: ", 1, 3);
    merge_sort_groups(groups, 0, (int)groups.size() - 1, choice);
    print_groups();
}

void sort_halls_menu()
{
    if (halls.empty())
    {
        cout << "No halls to sort";
        return;
    }

    cout << "1. By capacity (descending)" << endl;
    cout << "2. By ID" << endl;
    cout << "3. By building (alphabetical)" << endl;

    int choice = read_int("Choice: ", 1, 3);
    merge_sort_halls(halls, 0, (int)halls.size() - 1, choice);
    print_halls();
}

struct distribution_result
{
    vector<vector<int>> hall_groups;
    vector<int> free_seats;
    vector<int> unplaced_groups;
};

int used_halls(const distribution_result& r)
{
    int counter = 0;
    for(int i = 0; i < (int)r.hall_groups.size(); i++)
    {
        if(!r.hall_groups[i].empty())
        {
            counter++;
        }
    }
    return counter;
}

void print_result(const distribution_result& r, const vector<group_data>& gs)
{
    for (size_t h = 0; h < halls.size(); h++)
    {
        if(r.hall_groups[h].empty())
        {
            continue;
        }

        int used = halls[h].capacity - r.free_seats[h];
        cout << "Hall " << halls[h].id << " (" << halls[h].building << ", " << used << "/" << halls[h].capacity << " seats): ";

        for (size_t k = 0; k < r.hall_groups[h].size(); k++)
        {
            const group_data& g = gs[r.hall_groups[h][k]];
            cout << (k ? ", " : "") << "Group " << g.id << " (" << g.students << ")";
        }
        cout << endl;
    }

    cout << "Halls used: " << used_halls(r) << " out of " << halls.size() << endl;

    if (!r.unplaced_groups.empty())
    {
        cout << "UNASSIGNED groups, not enough capacity: ";
        for(size_t k = 0; k < r.unplaced_groups.size(); k++)
        {
            const group_data& g = gs[r.unplaced_groups[k]];
            cout << (k ? ", " : "") << "Group " << g.id << " (" << g.students << ")";
        }
        cout << endl;
    }
    else
    {
        cout << "All groups have been assigned" << endl;
    }
}

distribution_result greedy_distribute(const vector<group_data>& gs)
{
    distribution_result r;

    r.hall_groups.assign(halls.size(), {});
    r.free_seats.resize(halls.size());

    for(size_t h = 0; h < halls.size(); h++)
    {
        r.free_seats[h] = halls[h].capacity;
    }

    for(size_t i = 0; i < gs.size(); i++)
    {
        int best = -1;
        for(size_t h = 0; h < halls.size(); h++)
        {
            if(r.free_seats[h] >= gs[i].students && (best == -1 || r.free_seats[h] < r.free_seats[best]))
            {
                best = (int)h;
            }
        }
        if(best == -1)
        {
            r.unplaced_groups.push_back((int)i);
        }
        else
        {
            r.hall_groups[best].push_back((int)i);
            r.free_seats[best] -= gs[i].students;
        }
    }
    return r;
}

void run_greedy()
{
    if(groups.empty() || halls.empty())
    {
        cout << "At least one group and one hall are required" << endl;
        return;
    }

    vector<group_data> sorted = groups;
    merge_sort_groups(sorted, 0, (int)sorted.size() - 1, 1);
    distribution_result r = greedy_distribute(sorted);

    cout << endl << "--Reslut(Greedy, Best Fit)--" << endl;
    print_result(r, sorted);
}

void print_menu()
{
    cout << "\n========== MAIN MENU ==========\n"
            " 1.Show groups\n"
            " 2.Show halls\n"
            " 3.Add a group\n"
            " 4.Add a hall\n"
            " 5.Delete a group\n"
            " 6.Delete a hall\n"
            " 7.Edit a group\n"
            " 8.Edit a hall\n"
            " 9.Search\n"
            "10.Sort groups\n"
            "11.Sort halls\n"
            "12.Assign groups (Greedy)\n"
            " 0.Exit\n";
}

int main()
{
    load_groups("groups.txt");
    load_halls("halls.txt");

    while (true)
    {
        print_menu();
        int c = read_int("Choice: ", 0, 12);
        cout << endl;
        switch (c) {
            case 1:  print_groups();     break;
            case 2:  print_halls();      break;
            case 3:  add_group();        break;
            case 4:  add_hall();         break;
            case 5:  delete_group();     break;
            case 6:  delete_hall();      break;
            case 7:  edit_group();       break;
            case 8:  edit_hall();        break;
            case 9:  search_menu();      break;
            case 10: sort_groups_menu();  break;
            case 11: sort_halls_menu();   break;
            case 12: run_greedy();       break;
            case 0:  cout << "Exit" << endl; return 0;
        }
    }
}
